"""tu_skeleton's provider guard (ProviderGuard): a merge, split or shatter keeps every definition its
replaced objects made, with equal bytes and relocations, and the copy the real link keeps of each COMDAT
under exit_link's retail order and its path order. P142 (2026-11-12): merge e3e2807bd83 moved
FamilyDeletingDtors_Rva006F8460's ??_GRva006F8460 (the pool release) into AptDisplayList.cpp with the same
bytes; in path order that object comes after Rva006F84C0DeletingDtor.cpp, whose copy calls the global
delete, and the image kept that copy."""
import struct
import sys
import tempfile
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402
import tu_skeleton as T  # noqa: E402

COMDAT_ANY = b"\0" * 14 + bytes([2]) + b"\0" * 3
COMDAT_NODUP = b"\0" * 14 + bytes([1]) + b"\0" * 3
CODE = 0x60000020
DATA = 0xC0000040
BSS = 0xC0000080

DONOR = "Code/GameEngine/Source/Common/FamilyDeletingDtors_Rva006F8460.cpp"
OTHER = "Code/GameEngine/Source/Common/Rva006F84C0DeletingDtor.cpp"
TU = "Code/Libraries/Source/Apt/AptDisplayList.cpp"
DTOR = "??_GRva006F8460@@UAEPAXI@Z"
POOL = b"\x56\x8b\xf1\xe8\0\0\0\0\x6a\x18\x56\xe8\0\0\0\0\x5e\xc2\x04\x00"     # dtor; freeBlock(this, 0x18)
GLOBAL = b"\x56\x8b\xf1\xe8\0\0\0\0\x56\xe8\0\0\0\0\x59\x5e\xc2\x04\x00\x90"  # dtor; operator delete(this)
CHANGED = b"\x90" + b"\xc3" * 7                                                # a carved body, edited


def coff(sections, symbols):
    """A COFF object: `sections` [(name, flags, raw or None (uninitialized, its size), [(offset, symbol, type)])],
    `symbols` [(name, value, section, storage, aux bytes or None[, COFF type])]."""
    at = 20 + 40 * len(sections)
    table = sum(18 * (2 if s[4] else 1) for s in symbols)
    strs, records = b"", b""
    for name, value, section, storage, aux, *kind in symbols:
        spelled = name.encode()
        if len(spelled) > 8:
            spelled = struct.pack("<II", 0, 4 + len(strs))
            strs += name.encode() + b"\0"
        records += struct.pack("<8sIhHBB", spelled, value, section, kind[0] if kind else 0, storage,
                               1 if aux else 0) + (aux or b"")
    tail = struct.pack("<I", 4 + len(strs)) + strs
    offset = at + table + len(tail)
    headers, raws = b"", b""
    for name, flags, raw, relocs in sections:
        packed = b"".join(struct.pack("<IIH", *r) for r in relocs)
        size = raw if isinstance(raw, int) else len(raw)
        body = b"" if isinstance(raw, int) else raw
        headers += struct.pack("<8sIIIIIIHHI", name.encode(), 0, 0, size, offset if body else 0,
                               offset + len(body) if relocs else 0, 0, len(relocs), 0, flags)
        raws += body + packed
        offset += len(body) + len(packed)
    return (struct.pack("<HHIIIHH", 0x14C, len(sections), 0, at, sum(2 if s[4] else 1 for s in symbols), 0, 0)
            + headers + records + tail + raws)


def comdat_object(path, functions, extra_sections=(), extra_symbols=()):
    """An object with one COMDAT code section per (name, bytes, selection aux) in `functions`, each calling
    `_callee` at offset 4."""
    sections, symbols = [], []
    for number, (name, raw, aux) in enumerate(functions, 1):
        sections.append((".text", CODE | 0x1000, raw, [(4, 3 * len(functions), 20)]))
        symbols += [(".text", 0, number, 3, aux), (name, 0, number, 2, None)]
    symbols.append(("_callee", 0, 0, 2, None))      # index 3n: a section symbol and its aux, then its function
    sections += list(extra_sections)
    symbols += list(extra_symbols)
    Path(path).write_bytes(coff(sections, symbols))
    return Path(path)


def objname(source):
    return build.obj_path(build.ROOT / source).name


def fake_orders(rows):
    """Path order: object names sorted (exit_link's paths share one directory). Retail order: by each
    object's lowest row address."""
    low = {}
    for row in rows:
        name = objname(row["source"])
        low[name] = min(low.get(name, 1 << 32), int(row["target_rva"], 16))
    return {"path order": sorted(low), "retail order": sorted(low, key=lambda n: (low[n], n))}


ROWS = [{"source": OTHER, "target_rva": "0x006F84C0"}, {"source": DONOR, "target_rva": "0x006F8490"},
        {"source": TU, "target_rva": "0x006F6000"}]


def guard(index_copies, rows=ROWS):
    index = {"objects": [objname(s) for s in (TU, DONOR, OTHER)], "strong": {}, "comdat": index_copies}
    g = T.ProviderGuard(rows=rows, orders=fake_orders)
    assert g.load(index) is None
    return g


def digest(path, name):
    return T.provider_definitions(path)[name][2]


def merge_judge(g, donor_obj, merged_obj, tu_obj=None):
    before = {DONOR: donor_obj, TU: tu_obj}
    moved = {(r["source"], r["target_rva"]): TU for r in g.rows if r["source"] == DONOR}
    return g.judge(before, {TU: merged_obj}, {TU: [DONOR, TU]}, moved)


@pytest.fixture
def objs(tmp_path):
    donor = comdat_object(tmp_path / "donor.obj", [(DTOR, POOL, COMDAT_ANY)])
    merged = comdat_object(tmp_path / "merged.obj", [(DTOR, POOL, COMDAT_ANY), ("?seed@@YAXXZ", b"\xc3" * 8,
                                                                             COMDAT_NODUP)])
    tu = comdat_object(tmp_path / "tu.obj", [("?seed@@YAXXZ", b"\xc3" * 8, COMDAT_NODUP)])
    other = comdat_object(tmp_path / "other.obj", [(DTOR, GLOBAL, COMDAT_ANY)])
    return donor, merged, tu, other


def test_p142_a_moved_copy_that_now_follows_another_units_copy_in_path_order_is_refused(objs):
    donor, merged, tu, other = objs
    g = guard({DTOR: [(1, digest(donor, DTOR), "retail"), (2, digest(other, DTOR), "wrong")]})
    found = merge_judge(g, donor, merged, tu)
    assert [(c, n) for c, n, _ in found] == [("path order", DTOR)]           # bytes kept; retail order unchanged
    assert "the link keeps" in found[0][2] and digest(other, DTOR) in found[0][2]
    assert T.provider_report(found) == {"path order": [DTOR]}


def test_p142_the_path_clause_is_its_own_check(objs, monkeypatch):
    donor, merged, tu, other = objs
    g = guard({DTOR: [(1, digest(donor, DTOR), "retail"), (2, digest(other, DTOR), "wrong")]})
    monkeypatch.setattr(T, "ORDER_CLAUSES", ("retail order",))        # the real link on --order retail
    assert merge_judge(g, donor, merged, tu) == []


def test_an_equal_outside_copy_or_an_earlier_merged_object_changes_nothing(objs, tmp_path):
    donor, merged, tu, other = objs
    same = comdat_object(tmp_path / "same.obj", [(DTOR, POOL, COMDAT_ANY)])
    g = guard({DTOR: [(1, digest(donor, DTOR), "retail"), (2, digest(same, DTOR), "retail")]})
    assert merge_judge(g, donor, merged, tu) == []
    rows = [dict(r, source="Code/Libraries/Source/Apt/ZzLater.cpp") if r["source"] == OTHER else r for r in ROWS]
    g = guard({DTOR: [(1, digest(donor, DTOR), "retail"), (2, digest(other, DTOR), "wrong")]}, rows)
    g.index["objects"][2] = objname("Code/Libraries/Source/Apt/ZzLater.cpp")
    assert merge_judge(g, donor, merged, tu) == []                  # the merged object still comes first


def test_a_retail_order_change_is_its_own_clause(objs):
    donor, merged, tu, other = objs
    # retail order: the TU's own code comes first, then the other unit's copy, then the donor's
    rows = [{"source": OTHER, "target_rva": "0x006F7000"}, {"source": DONOR, "target_rva": "0x006F8000"},
            {"source": TU, "target_rva": "0x006F6000"}]
    g = guard({DTOR: [(1, digest(donor, DTOR), "retail"), (2, digest(other, DTOR), "wrong")]}, rows)
    found = merge_judge(g, donor, merged, tu)
    assert {c for c, _, _ in found} == {"retail order", "path order"}


def test_a_definition_the_merged_object_drops_or_changes_is_refused(objs, tmp_path):
    donor, merged, tu, other = objs
    g = guard({})
    dropped = comdat_object(tmp_path / "dropped.obj", [("?seed@@YAXXZ", b"\xc3" * 8, COMDAT_NODUP)])
    assert [(c, n) for c, n, _ in merge_judge(g, donor, dropped, tu)] == [("bytes", DTOR)]
    changed = comdat_object(tmp_path / "changed.obj", [(DTOR, GLOBAL, COMDAT_ANY),
                                                      ("?seed@@YAXXZ", b"\xc3" * 8, COMDAT_NODUP)])
    found = merge_judge(g, donor, changed, tu)
    assert ("bytes", DTOR) in [(c, n) for c, n, _ in found]
    nodup = comdat_object(tmp_path / "nodup.obj", [(DTOR, POOL, COMDAT_NODUP),
                                                  ("?seed@@YAXXZ", b"\xc3" * 8, COMDAT_NODUP)])
    assert ("bytes", DTOR) in [(c, n) for c, n, _ in merge_judge(g, donor, nodup, tu)]   # selection counts


def test_members_that_define_a_name_differently_are_refused(objs, tmp_path):
    donor, merged, tu, other = objs
    tu_global = comdat_object(tmp_path / "tu_global.obj", [(DTOR, GLOBAL, COMDAT_ANY),
                                                           ("?seed@@YAXXZ", b"\xc3" * 8, COMDAT_NODUP)])
    found = merge_judge(guard({}), donor, merged, tu_global)
    assert ("members disagree", DTOR) in [(c, n) for c, n, _ in found]


# LINK-661 (2026-11-13): the pointgr.cpp merge. The donor PointGroupClassRva0017A890.cpp and the seed define the
# inline ?Get_Transform@DX8Wrapper@@SAXW4_D3DTRANSFORMSTATETYPE@@AAVMatrix4@@@Z differently, the donor's copy
# is the one path order keeps today and another unit's after the merge, and no relocation of any object names
# it: whichever copy the link keeps, no code runs it.
INLINE = "?Get_Transform@DX8Wrapper@@SAXW4_D3DTRANSFORMSTATETYPE@@AAVMatrix4@@@Z"
SEED, BODY = ("?seed@@YAXXZ", b"\xc3" * 8, COMDAT_NODUP), ("?body@@YAXXZ", b"\xcc" * 8, COMDAT_NODUP)


def pointgr(tmp_path, caller=False, debug=False, merged_copy=GLOBAL):
    """(donor, merged, tu, other) objects of the pointgr shape. `caller`: the seed and the merged object hold a
    non-COMDAT section calling INLINE; `debug`: only a .debug$S record names it (as /Zi's do)."""
    extra = []
    if caller:
        extra.append(((".text", CODE, b"\xe8\0\0\0\0\xc3", [(1, 2, 20)]), []))          # REL32 to symbol 2
    if debug:
        extra.append(((".debug$S", 0x42100040, b"\0" * 8, [(0, 2, 0xB)]), []))         # SECREL to symbol 2
    sections = [s for s, _ in extra]
    donor = comdat_object(tmp_path / "donor.obj", [(INLINE, POOL, COMDAT_ANY), BODY])
    tu = comdat_object(tmp_path / "tu.obj", [(INLINE, GLOBAL, COMDAT_ANY), SEED], sections)
    merged = comdat_object(tmp_path / "merged.obj", [(INLINE, merged_copy, COMDAT_ANY), SEED, BODY], sections)
    other = comdat_object(tmp_path / "other.obj", [(INLINE, CHANGED, COMDAT_ANY)])
    return donor, merged, tu, other


def pointgr_guard(donor, tu, other, edges=None, orders=fake_orders):
    import link_check as LC
    index = {"objects": [objname(s) for s in (TU, DONOR, OTHER)], "strong": {}, "alternates": {},
             "comdat": {INLINE: [(0, digest(tu, INLINE), None), (1, digest(donor, INLINE), None),
                                 (2, digest(other, INLINE), None)]},
             "references": {"schema": LC.REFERENCES_SCHEMA, "edges": dict(edges or {}),
                            "referenced": {"_callee"}}}
    g = T.ProviderGuard(rows=ROWS, orders=orders)
    assert g.load(index) is None
    return g


def test_link661_an_unreferenced_inline_copy_is_not_judged_for_members_or_order(tmp_path):
    donor, merged, tu, other = pointgr(tmp_path)
    assert merge_judge(pointgr_guard(donor, tu, other), donor, merged, tu) == []
    g = pointgr_guard(donor, tu, other)
    del g.index["references"]                                             # an index with no reference graph
    found = merge_judge(g, donor, merged, tu)
    assert [(c, n) for c, n, _ in found] == [("members disagree", INLINE), ("path order", INLINE)]
    donor, merged, tu, other = pointgr(tmp_path, debug=True)              # only a .debug$S record names it
    assert merge_judge(pointgr_guard(donor, tu, other), donor, merged, tu) == []


def test_link661_one_relocation_naming_the_copy_keeps_it_judged(tmp_path):
    expected = [("members disagree", INLINE), ("path order", INLINE)]
    donor, merged, tu, other = pointgr(tmp_path, caller=True)             # the seed calls it
    assert [(c, n) for c, n, _ in merge_judge(pointgr_guard(donor, tu, other), donor, merged, tu)] == expected
    donor, merged, tu, other = pointgr(tmp_path)                          # an outside COMDAT's section calls it
    g = pointgr_guard(donor, tu, other, edges={"?outside@@YAXXZ": frozenset({INLINE})})
    assert [(c, n) for c, n, _ in merge_judge(g, donor, merged, tu)] == expected
    # an object of the link the index does not hold, with no path to read: nothing is proven unreferenced
    unindexed = lambda rows: {k: v + ["^zz_unindexed.obj"] for k, v in fake_orders(rows).items()}
    g = pointgr_guard(donor, tu, other, orders=unindexed)
    assert [(c, n) for c, n, _ in merge_judge(g, donor, merged, tu)] == expected


def test_link661_the_merged_object_must_keep_one_members_copy(tmp_path):
    donor, merged, tu, other = pointgr(tmp_path, merged_copy=CHANGED[::-1])   # neither the donor's nor the seed's
    found = merge_judge(pointgr_guard(donor, tu, other), donor, merged, tu)
    assert ("members disagree", INLINE) in [(c, n) for c, n, _ in found]


def test_a_split_judges_both_objects_that_continue_the_file(tmp_path):
    # the residual keeps the inline copy, the destination takes the carved function and its own copy
    original = comdat_object(tmp_path / "orig.obj", [(DTOR, POOL, COMDAT_ANY), ("?carved@@YAXXZ", b"\xc3" * 8,
                                                                               COMDAT_NODUP)])
    residual = comdat_object(tmp_path / "res.obj", [(DTOR, POOL, COMDAT_ANY)])
    dest = comdat_object(tmp_path / "dest.obj", [(DTOR, POOL, COMDAT_ANY), ("?carved@@YAXXZ", b"\xc3" * 8,
                                                                            COMDAT_NODUP)])
    rows = [{"source": DONOR, "target_rva": "0x006F8490"}, {"source": DONOR, "target_rva": "0x006F8500"}]
    g = T.ProviderGuard(rows=rows, orders=fake_orders)
    g.load({"objects": [objname(DONOR)], "strong": {}, "comdat": {}})
    moved = {(DONOR, "0x006F8500"): TU}
    assert g.judge({DONOR: original, TU: None}, {DONOR: residual, TU: dest},
                   {DONOR: [DONOR], TU: [DONOR, TU]}, moved) == []
    lost = comdat_object(tmp_path / "lost.obj", [(DTOR, POOL, COMDAT_ANY)])
    found = g.judge({DONOR: original, TU: None}, {DONOR: residual, TU: lost}, {DONOR: [DONOR], TU: [DONOR, TU]}, moved)
    assert [(c, n) for c, n, _ in found] == [("bytes", "?carved@@YAXXZ")]
    # a carved row whose bytes change in its new unit (SplitLinkGuard lets that pass when no other unit can
    # select the body: the provider guard does not)
    changed = comdat_object(tmp_path / "changed.obj", [(DTOR, POOL, COMDAT_ANY), ("?carved@@YAXXZ", CHANGED,
                                                                                COMDAT_NODUP)])
    found = g.judge({DONOR: original, TU: None}, {DONOR: residual, TU: changed}, {DONOR: [DONOR], TU: [DONOR, TU]},
                    moved)
    assert [(c, n) for c, n, _ in found] == [("bytes", "?carved@@YAXXZ")]


def data_obj(path, raw, value_b=4, bss=16):
    """`_a` at 0 (a DIR32 to `_target`), `_b` at `value_b` in .data holding `raw`; `_z` alone in a .bss of `bss`
    bytes; `_c` COMMON 12."""
    Path(path).write_bytes(coff([(".data", DATA, raw, [(0, 4, 6)]), (".bss", BSS, bss, [])],
                                [(".data", 0, 1, 3, None), ("_a", 0, 1, 2, None),
                                 ("_b", value_b, 1, 2, None), ("_z", 0, 2, 2, None),
                                 ("_target", 0, 0, 2, None), ("_c", 12, 0, 2, None)]))
    return Path(path)


def test_provider_definitions_reads_what_the_link_compares(tmp_path):
    one = T.provider_definitions(data_obj(tmp_path / "1.obj", b"\0\0\0\0\x01\x02\0\0"))
    assert one["_a"][:3] == ("section", False, 4) and one["_a"][4] == ((0, 6, "_target", bytes(4)),)
    assert one["_z"] == ("bss", False, 16) and one["_c"] == ("common", 12)
    # alignment padding before another next definition: the longer extent continues the shorter
    two = T.provider_definitions(data_obj(tmp_path / "2.obj", b"\0\0\0\0\x01\x02\0\0\0\0\0\0"))
    assert T.same_definition(one["_b"], two["_b"]) and not T.same_definition(two["_b"], one["_b"])
    three = T.provider_definitions(data_obj(tmp_path / "3.obj", b"\0\0\0\0\x01\x03\0\0"))
    assert not T.same_definition(one["_b"], three["_b"]) and T.same_definition(one["_a"], three["_a"])
    four = T.provider_definitions(data_obj(tmp_path / "4.obj", b"\0\0\0\0\x01\x02\0\0\x07\0\0\0"))
    assert not T.same_definition(one["_b"], four["_b"])            # a surplus byte is no padding
    with pytest.raises(T.ProviderUnknown):
        T.provider_definitions(tmp_path / "missing.obj")


def test_review_r1_a_smaller_uninitialized_allocation_is_refused(tmp_path):
    # a sole 16-byte .bss global replaced by one of 4 bytes: callers would run past it
    g = guard({})
    big = data_obj(tmp_path / "big.obj", b"\0" * 8, bss=16)
    small = data_obj(tmp_path / "small.obj", b"\0" * 8, bss=4)
    found = g.judge({DONOR: big}, {TU: small}, {TU: [DONOR]}, {})
    assert ("bytes", "_z") in [(c, n) for c, n, _ in found]
    assert g.judge({DONOR: small}, {TU: big}, {TU: [DONOR]}, {}) == []          # larger: padding at most


def test_review_r1_a_label_inside_a_function_bounds_nothing(tmp_path):
    # external _f at 0 and a label $L1 at 1 (storage 6), then a static function _g at 3: _f's extent is 0..3
    def code_obj(path, raw):
        Path(path).write_bytes(coff([(".text", CODE, raw, [])],
                                    [(".text", 0, 1, 3, None), ("_f", 0, 1, 2, None, 0x20), ("$L1", 1, 1, 6, None),
                                     ("_g", 3, 1, 3, None, 0x20)]))
        return Path(path)
    one = T.provider_definitions(code_obj(tmp_path / "1.obj", b"\x90\xc3\xcc\xc3"))
    assert one["_f"][2] == 3
    two = T.provider_definitions(code_obj(tmp_path / "2.obj", b"\x90\xcc\xcc\xc3"))   # changed after the label
    assert not T.same_definition(one["_f"], two["_f"])
    found = guard({}).judge({DONOR: tmp_path / "1.obj"}, {TU: tmp_path / "2.obj"}, {TU: [DONOR]}, {})
    assert [(c, n) for c, n, _ in found] == [("bytes", "_f")]


def test_review_r2_a_relocation_operand_past_the_extent_counts(tmp_path):
    # _a at 0 with a DIR32 to _target at 0, _b at 2: the operand 00 00 01 00 runs into _b. Moving _b to 4
    # (two zeros inserted) keeps both extents' own bytes but changes the addend to 0
    def obj(path, raw, value_b):
        Path(path).write_bytes(coff([(".data", DATA, raw, [(0, 3, 6)])],
                                    [(".data", 0, 1, 3, None), ("_a", 0, 1, 2, None), ("_b", value_b, 1, 2, None),
                                     ("_target", 0, 0, 2, None)]))
        return Path(path)
    old = obj(tmp_path / "old.obj", b"\0\0\x01\0", 2)
    new = obj(tmp_path / "new.obj", b"\0\0\0\0\x01\0", 4)
    found = guard({}).judge({DONOR: old}, {TU: new}, {TU: [DONOR]}, {})
    assert {n for c, n, _ in found if c == "bytes"} == {"_a", "_b"}
    assert guard({}).judge({DONOR: old}, {TU: obj(tmp_path / "same.obj", b"\0\0\x01\0", 2)}, {TU: [DONOR]}, {}) == []


def test_review_r3_an_absolute_relocation_is_ignored(tmp_path):
    # IMAGE_REL_I386_ABSOLUTE has no operand and the linker ignores it: one inside _a's extent, or in padding a
    # longer extent takes in, changes nothing
    def obj(path, raw, relocs):
        Path(path).write_bytes(coff([(".data", DATA, raw, relocs)],
                                    [(".data", 0, 1, 3, None), ("_a", 0, 1, 2, None), ("_target", 0, 0, 2, None)]))
        return Path(path)
    plain = obj(tmp_path / "plain.obj", b"\x01\x02\x03\x04", [])
    inside = obj(tmp_path / "inside.obj", b"\x01\x02\x03\x04", [(1, 2, 0x0)])
    padded = obj(tmp_path / "padded.obj", b"\x01\x02\x03\x04\0\0\0\0", [(5, 2, 0x0)])
    for old, new in ((plain, inside), (inside, plain), (plain, padded)):
        assert guard({}).judge({DONOR: old}, {TU: new}, {TU: [DONOR]}, {}) == []


def test_review_r2_an_unknown_relocation_type_is_not_judged(tmp_path):
    Path(tmp_path / "odd.obj").write_bytes(coff([(".data", DATA, b"\0" * 8, [(0, 2, 0x9)])],     # SEG12
                                                [(".data", 0, 1, 3, None), ("_a", 0, 1, 2, None),
                                                 ("_target", 0, 0, 2, None)]))
    with pytest.raises(T.ProviderUnknown):
        T.provider_definitions(tmp_path / "odd.obj")


def test_review_r1_outside_copies_a_change_reorders_are_judged(objs, tmp_path):
    # the merge defines nothing named ?shared, but retail order's initializer slots move outside object A
    # ahead of B; their copies of ?shared differ, so the copy the link keeps changes
    donor, merged, tu, other = objs
    a = comdat_object(tmp_path / "a.obj", [("?shared@@YAXXZ", b"\xc3" * 4, COMDAT_ANY)])
    b = comdat_object(tmp_path / "b.obj", [("?shared@@YAXXZ", b"\x90\xc3" * 2, COMDAT_ANY)])
    A, B = objname("Code/A.cpp"), objname("Code/B.cpp")
    def orders(rows):
        moved = not any(r["source"] == DONOR for r in rows)
        names = [objname(TU), objname(DONOR), objname(OTHER)]
        retail = [objname(DONOR), objname(TU), B, A] if not moved else [objname(TU), A, B]
        return {"path order": names + [A, B] if not moved else [objname(TU), objname(OTHER), A, B],
                "retail order": retail}
    index = {"objects": [objname(s) for s in (TU, DONOR, OTHER)] + [A, B], "strong": {},
             "comdat": {DTOR: [(1, digest(donor, DTOR), "retail")],
                        "?shared@@YAXXZ": [(3, digest(a, "?shared@@YAXXZ"), None),
                                           (4, digest(b, "?shared@@YAXXZ"), None)]}}
    g = T.ProviderGuard(rows=ROWS, orders=orders)
    g.load(index)
    found = merge_judge(g, donor, merged, tu)
    assert [(c, n) for c, n, _ in found] == [("retail order", "?shared@@YAXXZ")]


def test_the_real_link_orders_are_exit_links(monkeypatch):
    # link_orders hands exit_link its own inputs: path order is expected_objects, retail order is
    # retail_object_order over link_census.code_places
    import exit_link
    calls = {}

    def expected(rows):
        calls["order"] = exit_link.ORDER
        return [build.ROOT / "build/match/b.obj", build.ROOT / "build/match/a.obj"]
    monkeypatch.setattr(exit_link, "expected_objects", expected)
    monkeypatch.setattr(exit_link, "retail_object_order", lambda rows, paths, ini, places: list(reversed(paths)))
    monkeypatch.setattr(exit_link, "ORDER", "retail")
    g = T.ProviderGuard(rows=[])
    g._initializers, g._places = [], {}
    with patch.object(T.ProviderGuard, "object_of", lambda self, row: build.ROOT / "build/match/a.obj"):
        got = g.link_orders([{"source": "Code/a.cpp", "target_rva": "0x1000"}])
    assert calls["order"] == "path" and exit_link.ORDER == "retail"
    assert got == {"path order": ["b.obj", "a.obj"], "retail order": ["a.obj", "b.obj"]}


class FindsB:
    """A provider guard that refuses any change replacing Code/B.cpp's object."""
    calls = []

    def __init__(self, *args, **kwargs):
        pass

    def load(self, index):
        return None

    def original(self, source):
        return Path(source + ".obj")

    def judge(self, before, after, continues, moved):
        FindsB.calls.append((dict(before), dict(after), dict(continues), dict(moved)))
        return [("path order", DTOR, "the link keeps b's copy today and c's after")] if "Code/B.cpp" in before else []


def merge_fakes():
    import re
    from types import SimpleNamespace

    class Verifier:
        fd = SimpleNamespace(MANAGED=re.compile(r"(?!)"), overrides=lambda: {})
        errors, all_errors, flags, obj = [], [], None, "merged.obj"

        def matched(self, text, rows):
            return {r["target_rva"] for r in rows}

    class Guard:
        index = {"objects": [], "strong": {}, "comdat": {}}

        def __init__(self, *args, **kwargs):
            pass

        def load(self):
            return self.index

        def linked(self, files):
            return []

        def prepare(self, files):
            return None

        def judge(self, obj, files, text):
            return []
    return Verifier, Guard


def test_a_merge_leaves_out_the_donor_the_provider_guard_refuses_and_reports_its_names():
    Verifier, Guard = merge_fakes()
    tu = "Code/T.cpp"
    don = {tu: [{"source": tu, "target_rva": "0x1000"}], "Code/A.cpp": [{"source": "Code/A.cpp", "target_rva": "0x1010"}],
           "Code/B.cpp": [{"source": "Code/B.cpp", "target_rva": "0x1020"}]}
    FindsB.calls = []
    with patch.object(T, "Verifier", return_value=Verifier()), patch.object(T, "LinkGuard", Guard), \
            patch.object(T, "ProviderGuard", FindsB), patch.object(T, "map_regressions", return_value=None), \
            patch.object(T, "compose", side_effect=lambda tu_, sk, files, *a, **k: " ".join(files)), \
            patch.object(T, "Carry", return_value=SimpleNamespace(report=lambda: {}, problems=[])), \
            patch.object(T, "apply") as apply:
        out = T._merge(tu, [], don, {"accepted": [], "rejected": {}}, True, texts={f: f for f in don})
    assert sorted(out["accepted"]) == sorted([tu, "Code/A.cpp"]) and "blocked" not in out
    assert out["rejected"]["Code/B.cpp"].startswith("provider: provider path order: " + DTOR)
    assert out["provider"] == {"Code/B.cpp": {"path order": [DTOR]}}
    before, after, continues, moved = next(c for c in FindsB.calls if "Code/B.cpp" in c[0])
    assert after == {tu: "merged.obj"} and set(continues[tu]) == set(before)
    assert moved[("Code/B.cpp", "0x1020")] == tu and (tu, "0x1000") not in moved
    apply.assert_not_called()


def test_a_merge_with_no_census_index_is_blocked():
    Verifier, Guard = merge_fakes()
    Guard.index = None
    don = {"Code/T.cpp": [{"source": "Code/T.cpp", "target_rva": "0x1000"}],
           "Code/A.cpp": [{"source": "Code/A.cpp", "target_rva": "0x1010"}]}
    with patch.object(T, "Verifier", return_value=Verifier()), patch.object(T, "LinkGuard", Guard):
        out = T._merge("Code/T.cpp", [], don, {"accepted": [], "rejected": {}}, True, texts={f: f for f in don})
    assert out["blocked"].startswith("provider guard: no census index")


def test_a_saved_plan_the_provider_guard_refuses_is_searched_again(tmp_path):
    Verifier, Guard = merge_fakes()
    (tmp_path / "Code").mkdir()
    for name in ("T", "B"):
        (tmp_path / f"Code/{name}.cpp").write_text("int x;\n")
    don = {"Code/T.cpp": [{"source": "Code/T.cpp", "target_rva": "0x1000"}],
           "Code/B.cpp": [{"source": "Code/B.cpp", "target_rva": "0x1020"}]}
    plan = {"accepted": ["Code/T.cpp", "Code/B.cpp"], "text": "merged", "baseline": ["0x1000", "0x1020"],
            "rows": 2, "rejected": {}, "flags": [], "verifier_flags": None}
    with patch.object(T, "ROOT", tmp_path), patch.object(T, "Verifier", lambda *a, **k: Verifier()), \
            patch.object(T, "LinkGuard", Guard), patch.object(T, "ProviderGuard", FindsB), \
            patch.object(T, "apply") as apply:
        assert T.reuse_merge_plan("Code/T.cpp", don, {}, plan, False) is None
    apply.assert_not_called()


def test_a_split_judges_its_baseline_against_the_residual_and_the_destination():
    from types import SimpleNamespace
    g = T.SplitLinkGuard.__new__(T.SplitLinkGuard)
    g.root, g.rows, g.provider, g.files = build.ROOT, [], None, ("Code/B.cpp", "Code/T.cpp")
    g.provider_lines = {}
    g.guard = SimpleNamespace(index={"objects": []})
    g.records = {"Code/B.cpp": {"obj": "orig.obj"}}
    FindsB.calls = []
    with patch.object(T, "ProviderGuard", FindsB):
        why = g.provider_failures({"Code/B.cpp": "res.obj", "Code/T.cpp": "dest.obj"},
                                  {"Code/B.cpp": ["Code/B.cpp"], "Code/T.cpp": ["Code/B.cpp", "Code/T.cpp"]},
                                  {("Code/B.cpp", "0x1020"): "Code/T.cpp"})
    assert why == [f"provider path order: {DTOR} (the link keeps b's copy today and c's after)"]
    assert FindsB.calls[0][0] == {"Code/B.cpp": "orig.obj", "Code/T.cpp": None}
    assert T.provider_report(g.provider_findings(why)) == {"path order": [DTOR]}     # the split report's names
    assert g.provider_findings(["some other refusal"]) == []
