"""next_work.py: wpo_detect warnings annotate candidates and sort them last."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import next_work  # noqa: E402
import wpo_detect  # noqa: E402

WARN = {0x0F000200: "likely unreproducible: 0x0F000900 reads eax",
        0x0F000300: "possibly unreproducible: 0x0F000901 reads esi"}


def patch(monkeypatch):
    monkeypatch.setattr(wpo_detect, "warning", lambda rva, size=None: WARN.get(rva))
    monkeypatch.setattr(wpo_detect, "is_cached", lambda rva: True)


def queue():
    return [{"target_rva": f"0x{rva:08X}", "size": 40, "function": f"f{rva:x}", "source": "Code/A.cpp"}
            for rva in (0x0F000100, 0x0F000200, 0x0F000300, 0x0F000400)]


def test_annotate_sorts_likely_last_and_keeps_everything(monkeypatch):
    patch(monkeypatch)
    out = next_work.annotate_wpo(queue())
    assert [c["target_rva"] for c in out] == ["0x0F000100", "0x0F000300", "0x0F000400", "0x0F000200"]
    assert out[-1]["wpo"].startswith("likely")
    assert out[1]["wpo"].startswith("possibly")
    assert "wpo" not in out[0]


def test_weighted_choice_serves_likely_unreproducible_only_when_alone(monkeypatch):
    patch(monkeypatch)
    out = next_work.annotate_wpo(queue())
    for _ in range(40):
        assert not next_work.unreproducible(next_work.weighted_choice(out))
    alone = [c for c in out if next_work.unreproducible(c)]
    assert next_work.weighted_choice(alone) is alone[0]


def test_wpo_line_printed(monkeypatch, capsys):
    patch(monkeypatch)
    out = next_work.annotate_wpo(queue())
    next_work._print_wpo(out[-1])
    assert "wpo: likely unreproducible" in capsys.readouterr().out
