"""wpo_detect.py: private register conventions, on assembled bytes."""
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import wpo_detect  # noqa: E402

BASE = 0x1000
CALLEE = 0x5000


def call(at, target):
    return b"\xE8" + struct.pack("<i", target - (at + 5))


def test_nonstandard_allows_thiscall_and_fastcall():
    assert wpo_detect.nonstandard({"ecx": 1}) == {}
    assert wpo_detect.nonstandard({"ecx": 1, "edx": 2}) == {}
    assert set(wpo_detect.nonstandard({"edx": 2})) == {"edx"}
    assert set(wpo_detect.nonstandard({"eax": 1, "ebp": 2})) == {"eax"}


def test_body_reading_eax_on_entry_is_flagged():
    code = b"\x8B\xF0" + b"\x8B\x06" + b"\xC3"     # mov esi, eax; mov eax, [esi]; ret
    result = wpo_detect.analyse(BASE, len(code), data=code)
    assert set(result["self"]) == {"eax"}
    assert wpo_detect.verdict(result) == "likely"
    assert "body reads eax" in wpo_detect.summary(result)


def test_unrestored_push_is_a_use_but_a_save_is_not():
    saved = b"\x56" + b"\x33\xF6" + b"\x5E\xC3"    # push esi; xor esi, esi; pop esi; ret
    assert wpo_detect.analyse(BASE, len(saved), data=saved)["self"] == {}
    passed = b"\x56" + b"\xE8\x00\x00\x00\x00" + b"\x59\xC3"   # push esi; call; pop ecx; ret
    assert "esi" in wpo_detect.analyse(BASE, len(passed), data=passed)["self"]


def test_callee_with_register_args_and_loading_caller(monkeypatch):
    monkeypatch.setattr(wpo_detect, "entry_regs",
                        lambda rva: {"eax": rva} if rva == CALLEE else {})
    monkeypatch.setattr(wpo_detect, "is_helper", lambda rva: False)
    code = b"\x8B\x41\x04" + call(BASE + 3, CALLEE) + b"\xC3"   # mov eax, [ecx+4]; call
    result = wpo_detect.analyse(BASE, len(code), data=code)
    assert result["self"] == {}
    assert result["callees"][0]["callee"] == f"0x{CALLEE:08X}"
    assert result["callees"][0]["set_by_caller"] == ["eax"]
    assert wpo_detect.summary(result).startswith("likely unreproducible: 0x00005000 reads eax")


def test_callee_reading_registers_the_caller_did_not_load_is_only_possible(monkeypatch):
    monkeypatch.setattr(wpo_detect, "entry_regs", lambda rva: {"esi": rva})
    monkeypatch.setattr(wpo_detect, "is_helper", lambda rva: False)
    code = b"\x6A\x01" + call(BASE + 2, CALLEE) + b"\x59\xC3"   # push 1; call; pop ecx
    result = wpo_detect.analyse(BASE, len(code), data=code)
    assert wpo_detect.verdict(result) == "possible"


def test_helpers_are_skipped(monkeypatch):
    monkeypatch.setattr(wpo_detect, "entry_regs", lambda rva: {"eax": rva})
    code = b"\xB8\x00\x00\x40\x00" + call(BASE + 5, 0x00629188) + b"\xC3"   # mov eax; call __EH_prolog
    assert wpo_detect.analyse(BASE, len(code), data=code)["callees"] == []


def test_cache_round_trip(tmp_path, monkeypatch):
    calls = []
    monkeypatch.setattr(wpo_detect, "analyse",
                        lambda rva, size: calls.append(rva) or {"self": {"eax": "0x1"}, "callees": []})
    cache = wpo_detect.Cache(path=tmp_path / "c.json")
    assert cache.get(0x1234, 10)["self"] == {"eax": "0x1"}
    cache.save()
    again = wpo_detect.Cache(path=tmp_path / "c.json")
    assert again.get(0x1234, 10)["self"] == {"eax": "0x1"}
    assert calls == [0x1234]


def test_no_inputs_means_no_advice_and_no_error(monkeypatch):
    # next_work.py annotates every queue through warning(); a checkout that
    # cannot read game.dat or the function index must still serve work.
    def missing():
        raise FileNotFoundError("game.dat")
    monkeypatch.setattr(wpo_detect, "_stamp", missing)
    monkeypatch.setattr(wpo_detect, "_CACHE", None)
    assert wpo_detect.warning(0x1234, 16) is None
    assert wpo_detect.is_cached(0x1234)
    wpo_detect.save_cache()
