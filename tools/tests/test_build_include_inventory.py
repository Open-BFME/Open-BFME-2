"""A new earlier include must invalidate an object with unchanged old dependencies.

Ported from Open-BFME-1's tools/tests/test_build_include_inventory.py. Here the
inventory is the census's receipt (compile_is_current(strict=True)); the
ordinary gate keeps its dependency-hash receipt, so an unprovable search
writes that ordinary sidecar instead of none, and strict currency refuses it."""
import json
import os
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


def _fixture(tmp_path, monkeypatch):
    root = tmp_path / "project"
    code = root / "game"
    early = root / "inputs" / "reference" / "shims" / "sweep"
    late = root / "inputs" / "reference" / "original"
    (early / "Common").mkdir(parents=True)
    (late / "Common").mkdir(parents=True)
    code.mkdir()
    source = code / "NetPacket.cpp"
    source.write_text('#include "Common/MessageStream.h"\n')
    original = late / "Common" / "MessageStream.h"
    original.write_text("#define PACKET_RANGE 6\n")
    output = root / "NetPacket.obj"
    output.write_bytes(b"old object")
    command = ["cl", "-I" + str(early), "-I" + str(late)]
    env = {}
    monkeypatch.setattr(build, "ROOT", root)
    monkeypatch.setattr(build, "compiler_command", lambda *_: (command, env))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda *_: "command")
    inventory = build.search_inventory(source, command, env)
    build._write_deps_sidecar(source, output, "command",
                              "Note: including file: " + str(original), True,
                              command, env, inventory, [])
    return source, output, early, original, command, env


def _census_grade(output):
    sidecar = build._deps_sidecar(output)
    return sidecar.exists() and json.loads(sidecar.read_text()).get("version") == 2


def test_new_higher_priority_header_invalidates_old_object(tmp_path, monkeypatch):
    source, output, early, original, _, _ = _fixture(tmp_path, monkeypatch)
    assert build.compile_is_current(source, output, strict=True)
    shadow = early / "Common" / "MessageStream.h"
    shadow.write_text("#define PACKET_RANGE 7\n")
    # Make the directory timestamp change explicit on coarse filesystems.
    previous = (early / "Common").stat().st_mtime_ns
    os.utime(early / "Common", ns=(previous + 1_000_000_000, previous + 1_000_000_000))
    assert original.read_text() == "#define PACKET_RANGE 6\n"
    assert not build.compile_is_current(source, output, strict=True)


def test_split_include_flags_are_in_the_same_search_inventory(tmp_path, monkeypatch):
    source, _, early, original, command, env = _fixture(tmp_path, monkeypatch)
    late = original.parents[1]
    split = ["cl", "-I", str(early), "/I", str(late)]
    assert build.search_inventory(source, split, env) == build.search_inventory(source, command, env)


def test_parent_include_uses_wine_casing_and_keeps_shadow_invalidation(tmp_path, monkeypatch):
    source, output, _, original, command, env = _fixture(tmp_path, monkeypatch)
    # Like wwdebug.h's ../../../../gameengine/include/common/debug.h: the
    # actual GameEngine/Include/Common directories have different casing.
    source.write_text('#include "../inputs/reference/original/common/MessageStream.h"\n')
    inventory = build.search_inventory(source, command, env)
    build._write_deps_sidecar(source, output, "command",
                              "Note: including file: " + str(original), True,
                              command, env, inventory, [])
    assert _census_grade(output)
    assert build.compile_is_current(source, output, strict=True)

    # A newly created exact-spelling directory can change Wine's choice even
    # though the previously opened header's contents have not changed.
    shadow = original.parent.parent / "common" / original.name
    if os.name == "nt":
        # Native Windows cannot create case-distinct sibling directories.
        # It reaches the same anchored header, whose content still invalidates
        # the receipt when changed. Wine's separate-spelling case is below.
        assert shadow.samefile(original)
        shadow.write_text("#define PACKET_RANGE 7\n")
        assert not build.compile_is_current(source, output, strict=True)
        return
    shadow.parent.mkdir()
    shadow.write_text("#define PACKET_RANGE 7\n")
    assert original.read_text() == "#define PACKET_RANGE 6\n"
    assert not build.compile_is_current(source, output, strict=True)


def test_case_insensitive_parent_include_outside_inventory_still_refuses(tmp_path, monkeypatch):
    source, output, _, original, command, env = _fixture(tmp_path, monkeypatch)
    outside = build.ROOT / "Outside" / "Header.h"
    outside.parent.mkdir()
    outside.write_text("#define OUTSIDE 1\n")
    source.write_text('#include "../outside/Header.h"\n')
    inventory = build.search_inventory(source, command, env)
    build._write_deps_sidecar(source, output, "command",
                              "Note: including file: " + str(original) + "\n"
                              "Note: including file: " + str(outside), True,
                              command, env, inventory, [])
    if os.name == "nt":
        # Windows resolves the literal quoted path directly, so this header is
        # anchored rather than reached through an unknown case spelling. Its
        # content hash must still prevent reuse after an actual change.
        assert _census_grade(output)
        assert build.compile_is_current(source, output, strict=True)
        outside.write_text("#define OUTSIDE 2\n")
        assert not build.compile_is_current(source, output, strict=True)
        return
    assert not _census_grade(output)
    assert not build.compile_is_current(source, output, strict=True)


def test_source_adjacent_header_invalidates_old_object(tmp_path, monkeypatch):
    source, output, _, _, _, _ = _fixture(tmp_path, monkeypatch)
    assert build.compile_is_current(source, output, strict=True)
    (source.parent / "Common").mkdir()
    (source.parent / "Common" / "MessageStream.h").write_text("#define PACKET_RANGE 7\n")
    assert not build.compile_is_current(source, output, strict=True)


def test_new_sibling_cpp_does_not_invalidate_header_free_namespace(tmp_path, monkeypatch):
    source, output, _, _, _, _ = _fixture(tmp_path, monkeypatch)
    assert build.compile_is_current(source, output, strict=True)
    (source.parent / "AnotherBody.cpp").write_text("int other() { return 1; }\n")
    assert build.compile_is_current(source, output, strict=True)


def test_legacy_cpp_receipt_cannot_prove_search_precedence(tmp_path, monkeypatch):
    source, output, _, _, _, _ = _fixture(tmp_path, monkeypatch)
    sidecar = build._deps_sidecar(output)
    metadata = json.loads(sidecar.read_text())
    metadata.pop("version")
    metadata.pop("inventory")
    sidecar.write_text(json.dumps(metadata))
    assert not build.compile_is_current(source, output, strict=True)


def test_legacy_header_free_receipt_remains_reusable(tmp_path, monkeypatch):
    source = tmp_path / "bare.cpp"
    source.write_text("int f() { return 1; }\n")
    output = tmp_path / "bare.obj"
    output.write_bytes(b"old object")
    command, env = ["cl"], {}
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "compiler_command", lambda *_: (command, env))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda *_: "command")
    build._deps_sidecar(output).write_text(json.dumps({
        "cmd": "command", "source": build._hash_file(str(source)), "deps": {},
    }))
    assert build.compile_is_current(source, output, strict=True)
    command.append("-FIhidden.h")
    assert not build.compile_is_current(source, output, strict=True)


def test_legacy_empty_deps_with_include_directive_misses(tmp_path, monkeypatch):
    source = tmp_path / "broken.cpp"
    source.write_text('#inc\\\nlude "Later.h"\n')
    output = tmp_path / "broken.obj"
    output.write_bytes(b"old object")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "compiler_command", lambda *_: (["cl"], {}))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda *_: "command")
    build._deps_sidecar(output).write_text(json.dumps({
        "cmd": "command", "source": build._hash_file(str(source)), "deps": {},
    }))
    assert not build.compile_is_current(source, output, strict=True)


def test_spliced_or_comment_prefixed_parent_include_refuses_cache(tmp_path, monkeypatch, capsys):
    source, output, _, original, command, env = _fixture(tmp_path, monkeypatch)
    for directive in ('#inc\\\nlude "../outside/Header.h"\n',
                      '/*why*/ #include "../outside/Header.h"\n'):
        source.write_text('const char *a = "/*"; const char *b = "*/";\n' + directive)
        inventory = build.search_inventory(source, command, env)
        build._write_deps_sidecar(source, output, "command",
                                  "Note: including file: " + str(original), True,
                                  command, env, inventory, [])
        assert not _census_grade(output)
        assert "unknown search roots" in capsys.readouterr().err


def test_stlport_native_macro_accepts_one_parent_only(tmp_path, monkeypatch):
    vendor = tmp_path / "vendor" / "stlport"
    vendor.mkdir(parents=True)
    header = vendor / "math.h"
    monkeypatch.setattr(build, "ROOT", tmp_path)
    header.write_text("#include _STLP_NATIVE_C_HEADER(math.h)\n")
    assert not build._include_escapes_search_roots(header, True)
    header.write_text("#include _STLP_NATIVE_C_HEADER(../../../outside.h)\n")
    assert build._include_escapes_search_roots(header, True)
    header.write_text("#include _STLP_NATIVE_C_HEADER(body.cpp)\n")
    assert build._include_escapes_search_roots(header, True)


def test_stlport_root_watches_its_native_include_not_its_whole_parent(tmp_path, monkeypatch):
    source, output, _, original, command, env = _fixture(tmp_path, monkeypatch)
    root = build.ROOT
    command.append("-I" + str(root))  # /I. makes the checkout itself a root
    monkeypatch.setattr(build, "source_needs_stlport", lambda _: True)
    build._write_deps_sidecar(source, output, "command",
                              "Note: including file: " + str(original), True,
                              command, env, build.search_inventory(source, command, env), [])
    assert build.compile_is_current(source, output, strict=True)
    # A sibling of the checkout is outside every searched directory.
    (root.parent / "sibling-checkout").mkdir()
    (root.parent / "sibling-checkout" / "algorithm").write_text("// unrelated\n")
    assert build.compile_is_current(source, output, strict=True)
    # <../include/HEADER> from the /I. root lands here.
    (root.parent / "include").mkdir()
    (root.parent / "include" / "algorithm").write_text("// native shadow\n")
    assert not build.compile_is_current(source, output, strict=True)


def test_batch_inventory_detects_edit_after_memoized_check(tmp_path, monkeypatch):
    source, _, early, _, command, env = _fixture(tmp_path, monkeypatch)
    cache = {}
    assert build.search_inventory(source, command, env, inventory_cache=cache)
    assert build._inventory_cache_still_current(cache)
    (early / "Common" / "New.h").write_text("#define NEW 1\n")
    assert not build._inventory_cache_still_current(cache)


def test_root_inventory_ignores_unrelated_nested_worktrees(tmp_path, monkeypatch):
    source, output, _, original, command, env = _fixture(tmp_path, monkeypatch)
    root = build.ROOT
    command.insert(1, "-I" + str(root))
    build._write_deps_sidecar(source, output, "command",
                              "Note: including file: " + str(original), True,
                              command, env, build.search_inventory(source, command, env), [])
    assert build.compile_is_current(source, output, strict=True)
    cache = {}
    build.search_inventory(source, command, env, inventory_cache=cache)
    other = root / ".claude" / "worktrees" / "independent" / "Code"
    other.mkdir(parents=True)
    (other / "Header.h").write_text("// not a compiler input\n")
    assert build.compile_is_current(source, output, strict=True)
    assert build._inventory_cache_still_current(cache)
    (source.parent / "RealNewHeader.h").write_text("// still watched\n")
    assert not build.compile_is_current(source, output, strict=True)


def test_excluded_root_candidate_cannot_shadow_a_later_header(tmp_path, monkeypatch):
    source, output, _, original, command, env = _fixture(tmp_path, monkeypatch)
    command.insert(1, "-I" + str(build.ROOT))
    for excluded in ("build", ".git", ".claude"):
        later = original.parents[1] / excluded / "Header.h"
        later.parent.mkdir(exist_ok=True)
        later.write_text("#define VALUE 1\n")
        source.write_text('#include <' + excluded + '/Header.h>\n')
        build._write_deps_sidecar(source, output, "command",
                                  "Note: including file: " + str(later), True,
                                  command, env, build.search_inventory(source, command, env), [])
        # An earlier candidate lies in a skipped directory. Even before it
        # exists, a reusable receipt cannot prove search precedence here.
        assert not _census_grade(output)
        assert not build.compile_is_current(source, output, strict=True)


def test_bytecode_cache_written_mid_run_keeps_receipts_current(tmp_path, monkeypatch):
    # link_census imports tools lazily, so Python writes tools/__pycache__
    # under a "." search root after the receipts were taken: six StlSweep TUs
    # were "not current for their source" on every fresh checkout.
    source, output, early, original, command, env = _fixture(tmp_path, monkeypatch)
    root = build.ROOT
    (root / "tools").mkdir()
    command.insert(1, "-I" + str(root))
    build._write_deps_sidecar(source, output, "command",
                              "Note: including file: " + str(original), True,
                              command, env, build.search_inventory(source, command, env), [])
    assert build.compile_is_current(source, output, strict=True)
    cache = {}
    build.search_inventory(source, command, env, inventory_cache=cache)
    nested = build._directory_inventory(early)
    for directory in (root / "tools", early / "Common"):
        (directory / "__pycache__").mkdir()
        (directory / "__pycache__" / "progress.cpython-312.pyc").write_bytes(b"bytecode")
    assert build._directory_inventory(early) == nested
    assert build.compile_is_current(source, output, strict=True)
    assert build._inventory_cache_still_current(cache)
    (early / "Common" / "Shadow.h").write_text("// still watched\n")
    assert build._directory_inventory(early) != nested
    assert not build.compile_is_current(source, output, strict=True)
    assert not build._inventory_cache_still_current(cache)


def test_header_in_a_bytecode_cache_refuses_a_census_receipt(tmp_path, monkeypatch, capsys):
    source, output, early, _, command, env = _fixture(tmp_path, monkeypatch)
    header = early / "Common" / "__pycache__" / "MessageStream.h"
    header.parent.mkdir()
    header.write_text("#define PACKET_RANGE 7\n")
    # Named by an include: an unwatched cache in an earlier root could shadow it.
    source.write_text('#include "Common/__pycache__/MessageStream.h"\n')
    build._write_deps_sidecar(source, output, "command", "Note: including file: " + str(header), True,
                              command, env, build.search_inventory(source, command, env), [])
    assert not _census_grade(output)
    assert "unknown search roots" in capsys.readouterr().err
    # Reached some other way, it still lies outside every walked directory.
    monkeypatch.setattr(build, "_include_escapes_search_roots", lambda *a, **k: False)
    build._write_deps_sidecar(source, output, "command", "Note: including file: " + str(header), True,
                              command, env, build.search_inventory(source, command, env), [])
    assert not _census_grade(output)
    assert "outside the inventoried search roots" in capsys.readouterr().err


def test_explicit_nested_worktree_search_root_is_still_watched(tmp_path, monkeypatch):
    monkeypatch.setattr(build, "ROOT", tmp_path)
    nested = tmp_path / ".claude" / "worktrees" / "independent"
    nested.mkdir(parents=True)
    (nested / "Existing.h").write_text("// explicit compiler input\n")
    before = build._directory_inventory(nested)
    (nested / "New.h").write_text("// can shadow a later include\n")
    assert build._directory_inventory(nested) != before


def test_search_change_during_compile_refuses_sidecar(tmp_path, monkeypatch, capsys):
    source, output, early, original, command, env = _fixture(tmp_path, monkeypatch)
    inventory = build.search_inventory(source, command, env)
    (early / "Common" / "MessageStream.h").write_text("#define PACKET_RANGE 7\n")
    previous = (early / "Common").stat().st_mtime_ns
    os.utime(early / "Common", ns=(previous + 1_000_000_000, previous + 1_000_000_000))
    build._write_deps_sidecar(source, output, "command",
                              "Note: including file: " + str(original), True,
                              command, env, inventory, [])
    assert not _census_grade(output)
    assert not build.compile_is_current(source, output, strict=True)
    assert "no include inventory" in capsys.readouterr().err


def test_unknown_or_parent_traversing_include_refuses_sidecar(tmp_path, monkeypatch, capsys):
    source, output, _, original, command, env = _fixture(tmp_path, monkeypatch)
    for directive in ("#include HEADER_NAME\n", '#include"../Common/MessageStream.h"\n',
                      '#include "AnotherBody.cpp"\n'):
        source.write_text(directive)
        inventory = build.search_inventory(source, command, env)
        build._write_deps_sidecar(source, output, "command",
                                  "Note: including file: " + str(original), True,
                                  command, env, inventory, [])
        assert not _census_grade(output)
        assert "unknown search roots" in capsys.readouterr().err


def test_legacy_asm_without_include_can_still_reuse(tmp_path, monkeypatch):
    source = tmp_path / "body.asm"
    source.write_text("body PROC\nret\nbody ENDP\n")
    output = tmp_path / "body.obj"
    output.write_bytes(b"old object")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "compiler_command", lambda *_: (["ml"], {}))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda *_: "command")
    build._deps_sidecar(output).write_text(json.dumps({
        "cmd": "command", "source": build._hash_file(str(source)), "deps": {},
    }))
    assert build.compile_is_current(source, output, strict=True)


def test_unknown_asm_receipt_version_and_legacy_includes_are_misses(tmp_path, monkeypatch):
    source, output = tmp_path / 'body.asm', tmp_path / 'body.obj'
    output.write_bytes(b'object')
    monkeypatch.setattr(build, 'ROOT', tmp_path)
    monkeypatch.setattr(build, 'compiler_command', lambda *_: (['ml'], {}))
    monkeypatch.setattr(build, '_cmd_fingerprint', lambda *_: 'command')
    for version, body in ((99, 'ret\n'), (None, 'include hidden.inc\nret\n')):
        source.write_text(body)
        build._deps_sidecar(output).write_text(json.dumps({
            'version': version, 'cmd': 'command', 'source': build._hash_file(str(source)), 'deps': {},
        }))
        assert not build.compile_is_current(source, output, strict=True)


def test_unterminated_quote_cannot_hide_an_escaping_include(tmp_path, monkeypatch):
    # A literal ends at its line: an apostrophe in #error/#pragma text used to open a
    # multi-line "char literal" that shifted comment parsing and blanked the include below.
    monkeypatch.setattr(build, "ROOT", tmp_path)
    header = tmp_path / "game" / "a.h"
    header.parent.mkdir(parents=True)
    # The apostrophe in "don't" paired with the one inside the later string "'/*", so
    # the string's /* opened a fake comment that blanked the real include up to "*/".
    for text in ("#if 0\n#error don't\n#endif\nconst char *p = \"'/*\";\n"
                 "#include \"../../outside.h\"\nconst char *q = \"*/\";\n",
                 "#if 0\n#error don't\n#endif\nconst char *p = \"'/*\";\n"
                 "#include BODY\nconst char *q = \"*/\";\n"):
        header.write_text(text)
        assert build._include_escapes_search_roots(header, False), text


def test_an_untracked_included_header_change_forces_that_tu_to_recompile(tmp_path, monkeypatch):
    # The landing service's in-window gate recompiles only TUs whose recorded
    # dependency fingerprints changed (compile_is_current). An included header
    # counts by CONTENT whatever git thinks of it: ignored/untracked included.
    source, output, early, original, _, _ = _fixture(tmp_path, monkeypatch)
    root = original.parents[4]
    (root / ".gitignore").write_text(original.relative_to(root).as_posix() + "\n")
    assert build.compile_is_current(source, output, strict=True)
    original.write_text("#define PACKET_RANGE 7\n")
    assert not build.compile_is_current(source, output, strict=True)


def test_an_unrelated_change_keeps_the_tu_current(tmp_path, monkeypatch):
    source, output, early, original, _, _ = _fixture(tmp_path, monkeypatch)
    root = original.parents[4]
    (root / "targets" / "game" / "reverse").mkdir(parents=True)
    (root / "targets" / "game" / "reverse" / "functions.csv").write_text("name\n")
    # outside every include search root of the TU (a NEW file inside one, even
    # an unrelated one, conservatively invalidates via the search inventory)
    (root / "tools").mkdir()
    (root / "tools" / "unrelated.py").write_text("x = 1\n")
    (root / "docs").mkdir()
    (root / "docs" / "notes.md").write_text("upstream prose\n")
    assert build.compile_is_current(source, output, strict=True)


def test_the_gate_keeps_its_dependency_hash_receipt(tmp_path, monkeypatch):
    # BFME2's per-file gate is unchanged: a legacy sidecar whose recorded
    # headers are unchanged stays reusable there, and only the census
    # (strict) refuses it for want of an include search inventory.
    source, output, early, _, _, _ = _fixture(tmp_path, monkeypatch)
    sidecar = build._deps_sidecar(output)
    metadata = json.loads(sidecar.read_text())
    for key in ("version", "inventory", "retry_dirs", "search_roots"):
        metadata.pop(key)
    sidecar.write_text(json.dumps(metadata))
    assert build.compile_is_current(source, output)
    assert not build.compile_is_current(source, output, strict=True)


def test_shadowing_header_is_seen_by_strict_currency_only(tmp_path, monkeypatch):
    source, output, early, _, _, _ = _fixture(tmp_path, monkeypatch)
    (early / "Common" / "MessageStream.h").write_text("#define PACKET_RANGE 7\n")
    assert build.compile_is_current(source, output)  # the gate: recorded bytes unchanged
    assert not build.compile_is_current(source, output, strict=True)


def test_header_reached_inside_a_skipped_build_dir_is_not_covered(tmp_path, monkeypatch, capsys):
    # A root that is the checkout itself skips build/ in its walk, so a header
    # found there through that root is outside the inventory.
    root = tmp_path / "project"
    (root / "build").mkdir(parents=True)
    header = root / "build" / "generated.h"
    header.write_text("#define VALUE 1\n")
    source = root / "unit.cpp"
    source.write_text('#include "build/generated.h"\n')
    output = root / "unit.obj"
    output.write_bytes(b"object")
    command, env = ["cl", "-I" + str(root)], {}
    monkeypatch.setattr(build, "ROOT", root)
    monkeypatch.setattr(build, "_unwatched_tops", lambda: {root.resolve()})
    monkeypatch.setattr(build, "compiler_command", lambda *_: (command, env))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda *_: "command")
    monkeypatch.setattr(build, "_include_escapes_search_roots", lambda *a, **k: False)
    inventory = build.search_inventory(source, command, env)
    build._write_deps_sidecar(source, output, "command", "Note: including file: " + str(header), True,
                              command, env, inventory, [])
    assert not _census_grade(output)
    assert "outside the inventoried search roots" in capsys.readouterr().err


def test_missing_search_directory_is_watched_through_its_parent(tmp_path, monkeypatch):
    # A nonexistent /I directory: creating it (in any casing Wine accepts)
    # must invalidate the receipt.
    source, output, early, original, command, env = _fixture(tmp_path, monkeypatch)
    missing = build.ROOT / "inputs" / "Lib"
    command.insert(1, "-I" + str(missing))
    build._write_deps_sidecar(source, output, "command", "Note: including file: " + str(original), True,
                              command, env, build.search_inventory(source, command, env), [])
    assert build.compile_is_current(source, output, strict=True)
    (build.ROOT / "inputs" / "lib" / "Common").mkdir(parents=True)
    (build.ROOT / "inputs" / "lib" / "Common" / "MessageStream.h").write_text("#define PACKET_RANGE 7\n")
    assert not build.compile_is_current(source, output, strict=True)


def test_missing_search_directory_under_build_survives_parallel_compiles(tmp_path, monkeypatch):
    # A nonexistent search directory whose deepest existing ancestor is
    # build/, which every parallel compile writes: watching that ancestor's
    # tree meant the inventory never held still across a compile. Only the
    # first missing name (in any casing) is watched now.
    source, output, early, original, command, env = _fixture(tmp_path, monkeypatch)
    (build.ROOT / "build" / "match").mkdir(parents=True)
    command.insert(1, "-I" + str(build.ROOT / "build" / "toolchains" / "dx81" / "include"))
    before = build.search_inventory(source, command, env)
    (build.ROOT / "build" / "match" / "another_tu.obj").write_bytes(b"written by a parallel compile")
    build._write_deps_sidecar(source, output, "command", "Note: including file: " + str(original), True,
                              command, env, before, [])
    assert _census_grade(output)
    (build.ROOT / "build" / "match" / "yet_another.obj").write_bytes(b"and another")
    assert build.compile_is_current(source, output, strict=True)
    (build.ROOT / "build" / "Toolchains").mkdir()  # Wine would now search build/Toolchains/dx81/include
    assert not build.compile_is_current(source, output, strict=True)


def test_header_free_tu_with_a_missing_build_search_dir_gets_a_census_receipt(tmp_path, monkeypatch):
    # The same shape end to end through try_compile_source with a census
    # receipt: no include, so no witnessed preprocess; the sidecar proves it.
    import census_receipts
    root = tmp_path / "repo"
    (root / "Code").mkdir(parents=True)
    (root / "build" / "match").mkdir(parents=True)
    source = root / "Code" / "Body.cpp"
    source.write_text("int body() { return 1; }\n")
    output = root / "build" / "match" / "Body.obj"
    command = ["cl", "-c", "-I" + str(root / "build" / "toolchains" / "dx81" / "include"), str(source)]
    env = {"INCLUDE": ""}
    monkeypatch.setattr(build, "ROOT", root)
    monkeypatch.setattr(build, "compiler_command", lambda *_: (list(command), dict(env)))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda *_: "command")

    def compile_(cmd, **kwargs):
        (root / "build" / "match" / "Sibling.obj").write_bytes(b"a parallel compile")
        output.write_bytes(b"object")
        return type("Done", (), {"returncode": 0, "stdout": ""})()
    monkeypatch.setattr(build.subprocess, "run", compile_)
    receipts = census_receipts.Receipts(tmp_path / "proof.json")
    assert build.try_compile_source(source, output, input_proof=receipts)[0]
    assert _census_grade(output) and build.compile_is_current(source, output, strict=True)


def test_header_free_tu_needs_no_inventory_for_its_census_receipt(tmp_path, monkeypatch):
    # Whatever stops the inventory (here: a search directory that changes
    # during the compile), a TU with no preprocessor line searches nothing:
    # its ordinary sidecar is what link_census's currency test accepts, so
    # the receipt must accept it too instead of refusing the whole census.
    import census_receipts
    root = tmp_path / "repo"
    (root / "Code").mkdir(parents=True)
    source = root / "Code" / "Body.cpp"
    source.write_text("int body() { return 1; }\n")
    output = root / "Body.obj"
    command, env = ["cl", "-c", str(source)], {"INCLUDE": ""}
    monkeypatch.setattr(build, "ROOT", root)
    monkeypatch.setattr(build, "compiler_command", lambda *_: (list(command), dict(env)))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda *_: "command")

    def compile_(cmd, **kwargs):
        (root / "Code" / f"New{len(list((root / 'Code').iterdir()))}.h").write_text("// appears mid-compile\n")
        output.write_bytes(b"object")
        return type("Done", (), {"returncode": 0, "stdout": ""})()
    monkeypatch.setattr(build.subprocess, "run", compile_)
    receipts = census_receipts.Receipts(tmp_path / "proof.json", collect=True)
    assert build.try_compile_source(source, output, input_proof=receipts)[0]
    assert not _census_grade(output)  # the inventory moved during the compile
    assert receipts.failures == []
    assert build.compile_is_current(source, output, strict=True)
    source.write_text('#include "New1.h"\nint body() { return 1; }\n')  # now it searches: no longer proven
    assert not build.compile_is_current(source, output, strict=True)
