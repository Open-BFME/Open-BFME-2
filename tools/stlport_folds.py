"""Prove emitted STLport storage members against existing retail owners.

This is deliberately narrower than a pin or an arbitrary ICF alias. Only the
listed STLport storage families are eligible: the empty-vector and
allocator-proxy constructors, and the list base destructor with the clear it
calls. The complete emitted callee must reproduce an existing, non-alias owner
of the same family, including every call's resolved target. A missing body,
interior address, changed extent or conflicting known binding refuses the
proof. Nothing is admitted from a name alone.
"""
import bisect
import struct


# (name prefix, required signature text, exact body size). The owner row must
# carry the same prefix and size; the signature text keeps each family to the
# one member it names.
FAMILIES = (
    ("??0?$_Vector_base@", "@_STL@@QAE@ABV?$allocator@", 29),
    ("??0?$_STLP_alloc_proxy@", "@_STL@@QAE@ABV?$allocator@", 11),
    # _List_base<T*>::~_List_base and clear fold onto list<int>'s (0x004EC395,
    # 0x0023DAA5): clear frees every node, the dtor clears and frees the head.
    ("??1?$_List_base@", "@_STL@@QAE@XZ", 23),
    ("?clear@?$_List_base@", "@_STL@@QAEXXZ", 39),
)


def family(name):
    for prefix, signature, size in FAMILIES:
        if name.startswith(prefix) and signature in name:
            return prefix, size
    return None


def prove(build, name, address, output, symbol_map, active=()):
    """Return the independently checked fold edges, or None on any refusal."""
    kind = family(name)
    if kind is None or name in symbol_map or (name, address) in active:
        return None
    prefix, size = kind
    owners = [row for row in build.load_all_function_rows()
              if row.get("status") == "matched"
              and row["name"].startswith(prefix)
              and int(row["target_rva"], 16) == address
              and int(row["target_size"]) == size
              and not build.is_alias_row(row)
              and "gen-alias" not in build.notes_tokens(row)]
    if not owners:
        return None
    try:
        body, relocs, info = build.read_object_symbol_bytes(
            output, name, code_only=True, detail=True)
        stat = output.stat()
        starts = build._function_starts(str(output), stat.st_mtime_ns, stat.st_size)
        starts = starts.get(info["section"], [])
        next_index = bisect.bisect_right(starts, info["value"])
        end = starts[next_index] if next_index < len(starts) else info["section_size"]
        body = body[:end - info["value"]].rstrip(b"\xcc")
        if len(body) != size:
            return None
        target = build.read_target_bytes(address, size)
    except (OSError, ValueError):
        return None

    resolved = bytearray(body)
    proofs = []
    covered = set()
    for offset, rtype, callee in relocs:
        if offset >= size:
            continue
        # These members contain only direct calls; no data relocation is
        # copied from retail and no nonzero COFF addend is silently discarded.
        if (rtype != 0x14 or offset < 1 or offset + 4 > size
                or body[offset - 1] not in (0xe8, 0xe9)
                or body[offset:offset + 4] != b"\0" * 4
                or covered.intersection(range(offset, offset + 4))):
            return None
        covered.update(range(offset, offset + 4))
        called = (address + offset + 4 + struct.unpack_from("<i", target, offset)[0]) & 0xffffffff
        if callee in symbol_map:
            if called not in symbol_map[callee]:
                return None
        else:
            nested = prove(build, callee, called, output, symbol_map,
                           active + ((name, address),))
            if nested is None:
                return None
            proofs.extend(nested)
        resolved[offset:offset + 4] = struct.pack("<i", called - address - offset - 4)
    if bytes(resolved) != target:
        return None
    proofs.append((name, address, size, owners[0]["name"]))
    return proofs
