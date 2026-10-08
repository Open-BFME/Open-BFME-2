"""flag_hint.py byte tells and retail_body plumbing, on assembled bytes."""
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import flag_hint  # noqa: E402
import retail_body as rb  # noqa: E402

BASE = 0x1000


def rel32(at, target):
    return struct.pack("<i", target - (at + 5))


def tells_of(code, cxx=True):
    insns = rb.disasm(BASE, len(code), data=code)
    return {t: (at, text) for t, at, text in
            flag_hint.find_tells(insns, BASE, handler_is_cxx=lambda h: cxx)}


def test_add_one_and_sse_and_cmov():
    code = (b"\x83\xC0\x01"            # add eax, 1
            b"\xF3\x0F\x10\x00"        # movss xmm0, [eax]
            b"\x0F\x4D\xC1"            # cmovge eax, ecx
            b"\x83\x40\x04\xFF"        # add dword ptr [eax+4], -1
            b"\xC3")
    found = tells_of(code)
    assert found["add_one"][0] == BASE
    assert found["sse"][0] == BASE + 3
    assert found["cmov"][0] == BASE + 7
    assert "add_one_mem" in found


def test_eh_prolog_needs_cxx_handler():
    at = BASE + 5
    code = b"\xB8\x00\x00\x40\x00" + b"\xE8" + rel32(at, flag_hint.EH_PROLOG) + b"\xC3"
    assert {"eh_frame", "eh_prolog"} <= set(tells_of(code))
    assert "eh_frame" not in tells_of(code, cxx=False)


def test_inline_eh_frame():
    code = (b"\x6A\xFF"                       # push -1
            b"\x68\x00\x10\x40\x00"           # push handler
            b"\x64\xA1\x00\x00\x00\x00"       # mov eax, fs:[0]
            b"\xC3")
    found = tells_of(code)
    assert found["eh_frame"][0] == BASE + 2
    assert "eh_inline" in found
    assert "eh_prolog" not in found


def test_gs_cookie_call():
    code = b"\xE8" + rel32(BASE, flag_hint.SECURITY_CHECK_COOKIE) + b"\xC3"
    assert "gs_cookie" in tells_of(code)


def test_effective_flags_and_holds():
    eff = rb.effective_flags(["/O1", "/G7", "/EHsc", "/arch:SSE"])
    assert eff["opt"] == "/O1" and eff["G7"] and eff["EH"] == "/EHsc"
    assert flag_hint.flag_holds("/arch:SSE", eff)
    assert flag_hint.flag_holds("/O1", eff)
    base = rb.effective_flags([])
    assert base["opt"] == "/O2" and not base["G7"] and base["EH"] is None
    assert flag_hint.flag_holds("/G7", rb.effective_flags(["/arch:SSE2"]))


def test_build_flags_are_what_build_passes(tmp_path, monkeypatch):
    # A Code/ unit's region decides /O, /arch and /G whatever its `// cl:` says,
    # so the diff must read the build's answer, not the bare line.
    import build
    source = tmp_path / "unit.cpp"
    source.write_text("// cl: /MD /EHsc\nint f() { return 0; }\n")
    monkeypatch.setattr(build, "source_extra_flags",
                        lambda path: ["-O1", "-arch:SSE", "-G7", "-MD", "-EHsc"])
    tokens = rb.build_flags(source)
    assert tokens == ["-O1", "-arch:SSE", "-G7", "-MD", "-EHsc"]
    assert rb.source_flags(source) == ["/MD", "/EHsc"]
    eff = rb.effective_flags(tokens)
    assert eff["opt"] == "/O1" and eff["G7"] and eff["arch"] == "SSE"
    assert rb.build_flags(tmp_path / "missing.cpp") is None


def test_build_flags_fall_back_to_the_cl_line(tmp_path, monkeypatch):
    import build
    source = tmp_path / "unit.cpp"
    source.write_text("// cl: /O1 /G7\n")

    def broken(path):
        raise SystemExit("no toolchain")
    monkeypatch.setattr(build, "source_extra_flags", broken)
    assert rb.build_flags(source) == ["/O1", "/G7"]


def test_build_flags_match_the_build_for_a_ledger_source():
    import build
    row = next(r for r in rb.stream_matched()
               if r["source"].startswith("Code/GameEngine/") and r["source"].endswith(".cpp"))
    path = rb.ROOT / row["source"]
    assert rb.build_flags(path) == list(build.source_extra_flags(path.resolve()))


def test_diff_suggests_missing_flag_only():
    tells = [("add_one", BASE, "add eax, 1"), ("sse", BASE + 3, "movss")]
    lines = flag_hint.diff_lines(tells, ["/O1", "/arch:SSE"])
    assert any(line.lstrip().startswith("+ /G7") for line in lines)
    assert any(line.lstrip().startswith("= /arch:SSE") for line in lines)


def test_disabled_tells_hidden_by_default():
    assert "inc_dec" in flag_hint.DISABLED
    lines = flag_hint.diff_lines([("inc_dec", BASE, "inc eax")], ["/G7"])
    assert lines == []
    assert flag_hint.diff_lines([("inc_dec", BASE, "inc eax")], ["/G7"], all_tells=True)


def test_every_enabled_tell_is_calibrated_above_threshold():
    for tell in flag_hint.TELLS:
        if tell not in flag_hint.DISABLED:
            prec = flag_hint.CALIBRATION[tell][0]
            assert prec is not None and prec >= flag_hint.MIN_PRECISION


def test_live_in_ignores_saves_and_zero_idioms():
    code = (b"\x56"              # push esi           (save, not a read)
            b"\x33\xC0"          # xor eax, eax       (zero idiom)
            b"\x8B\x31"          # mov esi, [ecx]     (reads ecx)
            b"\x03\xC2"          # add eax, edx       (reads edx)
            b"\x5E\xC3")         # pop esi; ret
    found = rb.live_in(rb.disasm(BASE, len(code), data=code))
    assert set(found) == {"ecx", "edx"}


def test_live_in_follows_both_branches():
    code = (b"\x85\xC9"          # test ecx, ecx
            b"\x74\x03"          # je +3
            b"\x8B\x06"          # mov eax, [esi]     only on the fallthrough
            b"\xC3"              # ret
            b"\x8B\xC7"          # mov eax, edi       on the taken path
            b"\xC3")
    found = rb.live_in(rb.disasm(BASE, len(code), data=code))
    assert set(found) == {"ecx", "esi", "edi"}


def test_partial_write_then_full_read_is_not_an_input():
    # mov al, [ecx]; and eax, 1: the stale upper bytes are ignored, not passed in
    code = b"\x8A\x01" + b"\x83\xE0\x01" + b"\xC3"
    found = rb.live_in(rb.disasm(BASE, len(code), data=code))
    assert set(found) == {"ecx"}
