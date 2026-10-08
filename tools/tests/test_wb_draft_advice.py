"""wb_draft.py: the flag_hint / sig_check advice block beside each draft."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import sig_check  # noqa: E402
import wb_draft  # noqa: E402

DRAFT = ("// DRAFT -- UNVERIFIED.\n// game.dat rva 0x00001000 size 8\n\n"
         "int Widget::get(int a)\n\n{\n  return a == 3;\n}\n")


def test_advice_block_follows_the_header(monkeypatch):
    monkeypatch.setattr(wb_draft.flag_hint, "report", lambda target: f"flag_hint {target}\n  + /G7")
    monkeypatch.setattr(wb_draft.sig_check, "report_text",
                        lambda rva, text, name=None: f"sig_check 0x{rva:08X}\n  ! args x")
    out = wb_draft.with_advice(DRAFT, wb_draft.IMAGE_BASE + 0x1000).split("\n")
    assert out[0].startswith("// DRAFT")
    assert out[2].startswith("// ---- advice")
    assert "// flag_hint 0x00001000" in out
    assert "//   ! args x" in out
    assert out.index("int Widget::get(int a)") > out.index("//   ! args x")


def test_advice_failure_is_a_note_not_an_error(monkeypatch):
    def boom(target):
        raise SystemExit("0x00001000: no known boundary")
    monkeypatch.setattr(wb_draft.flag_hint, "report", boom)
    monkeypatch.setattr(wb_draft.sig_check, "report_text", lambda rva, text, name=None: "ok")
    lines = wb_draft.advice(wb_draft.IMAGE_BASE + 0x1000, DRAFT)
    assert any("flag_hint: unavailable" in line for line in lines)


def test_report_text_finds_the_draft_signature():
    decl, body = sig_check.decl_from_text(DRAFT, "Widget::get", None, "draft", assume_member=True)
    assert decl.member and decl.conv == "thiscall" and len(decl.params) == 1
    assert sig_check.SIGNATURE_RE.search(DRAFT).group(1) == "Widget::get"
