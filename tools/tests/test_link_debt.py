"""link_debt: new hard-coded image addresses fail; moves and removals pass."""
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_debt as L  # noqa: E402


def git(root, *args):
    subprocess.run(["git", *args], cwd=root, check=True, capture_output=True)


@pytest.fixture
def repo(tmp_path, monkeypatch):
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "user.name", "Fixture")
    git(tmp_path, "config", "user.email", "fixture@example.invalid")
    monkeypatch.setattr(L, "ROOT", tmp_path)
    return tmp_path


def put(root, path, text):
    target = root / path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(text)
    git(root, "add", "--", path)


LITERAL = "int f() { return *(int *)0x00C2D5C8; }\n"
NAMED = "extern int g_012ED5C8;\nint f() { return g_012ED5C8; }\n"


def test_new_literal_fails(repo):
    put(repo, "Code/A.cpp", NAMED)
    git(repo, "commit", "-qm", "base")
    put(repo, "Code/A.cpp", LITERAL)
    assert L.staged() == 1


def test_replacing_a_literal_passes(repo):
    put(repo, "Code/A.cpp", LITERAL)
    git(repo, "commit", "-qm", "base")
    put(repo, "Code/A.cpp", NAMED)
    assert L.staged() == 0


def test_moving_a_file_keeps_its_count(repo):
    put(repo, "Code/A.cpp", LITERAL)
    git(repo, "commit", "-qm", "base")
    git(repo, "mv", "Code/A.cpp", "Code/B.cpp")
    assert L.staged() == 0


def test_generated_roots_are_not_watched(repo):
    put(repo, "Code/A.cpp", NAMED)
    git(repo, "commit", "-qm", "base")
    put(repo, "Code/gen_small/x.cpp", LITERAL)
    assert L.staged() == 0


def test_failed_staged_listing_refuses_instead_of_treating_it_as_empty(repo, monkeypatch, capsys):
    put(repo, "Code/A.cpp", NAMED)
    git(repo, "commit", "-qm", "base")
    put(repo, "Code/A.cpp", LITERAL)
    broken_index = repo / "broken-index"
    broken_index.write_bytes(b"not a git index\n")
    monkeypatch.setenv("GIT_INDEX_FILE", str(broken_index))
    assert L.main(["--staged"]) == 1
    error = capsys.readouterr().err
    assert "git diff" in error and "index" in error


def test_failed_report_listing_refuses_instead_of_reporting_no_debt(repo, monkeypatch, capsys):
    broken_index = repo / "broken-index"
    broken_index.write_bytes(b"not a git index\n")
    monkeypatch.setenv("GIT_INDEX_FILE", str(broken_index))
    assert L.main(["--report"]) == 1
    output = capsys.readouterr()
    assert "git ls-files" in output.err and "index" in output.err
    assert "0 hard-coded image addresses" not in output.out


def test_git_cannot_start_refuses_with_a_diagnostic(repo, monkeypatch, capsys):
    def unavailable(*args, **kwargs):
        raise FileNotFoundError("fixture: git is unavailable")

    monkeypatch.setattr(L.subprocess, "run", unavailable)
    assert L.main(["--staged"]) == 1
    error = capsys.readouterr().err
    assert "cannot run git" in error and "git is unavailable" in error


@pytest.mark.parametrize("ref", ["HEAD", ""])
def test_failed_source_read_refuses_instead_of_treating_it_as_empty(repo, monkeypatch, capsys, ref):
    source = "Code/source with spaces.cpp"
    put(repo, source, NAMED)
    git(repo, "commit", "-qm", "base")
    put(repo, source, NAMED + "// changed\n")
    run = subprocess.run

    def fail_one_read(command, *args, **kwargs):
        if command == ["git", "show", f"{ref}:{source}"]:
            return subprocess.CompletedProcess(command, 128, "", "fixture: cannot read object")
        return run(command, *args, **kwargs)

    monkeypatch.setattr(L.subprocess, "run", fail_one_read)
    assert L.main(["--staged"]) == 1
    error = capsys.readouterr().err
    assert "git show" in error and source in error and "cannot read object" in error


def test_first_commit_needs_no_head_blob(repo):
    put(repo, "Code/A.cpp", NAMED)
    assert L.main(["--staged"]) == 0
    put(repo, "Code/A.cpp", LITERAL)
    assert L.main(["--staged"]) == 1


def test_deleting_source_needs_no_index_blob(repo):
    put(repo, "Code/A.cpp", LITERAL)
    git(repo, "commit", "-qm", "base")
    git(repo, "rm", "Code/A.cpp")
    assert L.main(["--staged"]) == 0


def test_moving_source_with_spaces_and_unicode_keeps_its_count(repo):
    put(repo, "Code/old name.cpp", LITERAL)
    git(repo, "commit", "-qm", "base")
    git(repo, "mv", "Code/old name.cpp", "Code/Größe name.cpp")
    assert L.main(["--staged"]) == 0


def test_aggregate_debt_can_move_between_staged_sources(repo):
    put(repo, "Code/A.cpp", LITERAL)
    put(repo, "Code/B.cpp", NAMED)
    git(repo, "commit", "-qm", "base")
    put(repo, "Code/A.cpp", NAMED)
    put(repo, "Code/B.cpp", LITERAL)
    assert L.main(["--staged"]) == 0


def test_explicit_base_counts_the_requested_version(repo):
    put(repo, "Code/A.cpp", NAMED)
    git(repo, "commit", "-qm", "baseline")
    git(repo, "branch", "baseline")
    put(repo, "Code/A.cpp", LITERAL)
    git(repo, "commit", "-qm", "existing debt")
    put(repo, "Code/A.cpp", LITERAL + "// changed\n")
    assert L.main(["--staged"]) == 0
    assert L.main(["--staged", "--base", "baseline"]) == 1


def test_explicit_base_may_lack_a_source_that_exists_in_head(repo):
    git(repo, "commit", "--allow-empty", "-qm", "baseline")
    git(repo, "branch", "baseline")
    put(repo, "Code/A.cpp", LITERAL)
    git(repo, "commit", "-qm", "existing debt")
    put(repo, "Code/A.cpp", LITERAL + "// changed\n")
    assert L.main(["--staged"]) == 0
    assert L.main(["--staged", "--base", "baseline"]) == 1


def test_merge_base_may_own_a_staged_addition_absent_from_head(repo):
    git(repo, "commit", "--allow-empty", "-qm", "baseline")
    git(repo, "branch", "baseline")
    put(repo, "Code/source with spaces.cpp", LITERAL)
    git(repo, "commit", "-qm", "other parent")
    git(repo, "branch", "other-parent")
    git(repo, "checkout", "--detach", "baseline")
    git(repo, "merge", "--no-ff", "--no-commit", "other-parent")
    assert L.main(["--staged"]) == 1
    assert L.main(["--staged", "--base", "MERGE_HEAD"]) == 0


def test_invalid_explicit_base_refuses_even_when_no_literal_is_added(repo, capsys):
    put(repo, "Code/A.cpp", NAMED)
    git(repo, "commit", "-qm", "base")
    put(repo, "Code/A.cpp", NAMED + "// changed\n")
    assert L.main(["--staged", "--base", "missing-base"]) == 1
    assert "missing-base" in capsys.readouterr().err


def test_masks_and_comments_are_not_addresses():
    assert L.literals("if (x & 0x80000000) {}  // *(int *)0x00C2D5C8\n") == []


def test_addresses_catch_every_form_of_an_image_address():
    text = """
    *(unsigned *)this = 0x00E1C340;          // vftable stored as an integer
    m_vptr = 0x00D1ff78u;
    float f = BFME_AT(float, 0x00A76C24);
    return reinterpret_cast<void (*)()>(0x0043c9cf);
    """
    assert L.addresses(text) == ["0x00E1C340", "0x00D1ff78u", "0x00A76C24", "0x0043c9cf"]


def test_addresses_skip_flags_masks_sizes_comments_and_strings():
    text = """
    m_flags |= 0x1000100;      // two bits: a flag word
    unsigned m = v & 0xffffff; // one repeated digit: a mask
    size_t n = 0x00401000;     // low 12 bits clear
    const char *s = "0x00E1C340";
    /* 0x00E1C340 */
    int small = 0x3FC;
    """
    assert L.addresses(text) == []


def test_asm_semicolon_comments_are_not_addresses():
    text = """
EXTERN ?g_vp6IdctConstantBlock@@3PAGA:WORD     ; retail 0x00E22980
    mov eax, 0x00E1C340                        ; still counted: an address in code
"""
    assert L.addresses(text, "Code/Libraries/Source/VP6/MmxIDct.asm") == ["0x00E1C340"]
    # C++ keeps ';' as a statement end: an address after it is still counted.
    assert L.addresses("int x; int *p = (int *)0x00E1C340;", "Code/A.cpp") == ["0x00E1C340"]


def test_a_quote_character_literal_opens_no_string():
    # GameWindowManagerScript.cpp, 2026-11-18: `'"'` in code opened a string that swallowed the start
    # of a later comment and exposed the address inside it; LinkGuard refused a merge for an address no
    # source held.
    text = r"""
    while (*p != '"') p++;
    // - seps "\n\"" lives at 0xC0C2B8.
"""
    assert L.addresses(text) == []
    assert L.literals(text) == []


def test_a_quote_character_literal_hides_no_address():
    # the same misreading hid real code: everything from `'"'` to the next `"` was a "string"
    text = r"""char c = '"'; int *p = (int *)0x00E1C340; // " """
    assert L.addresses(text) == ["0x00E1C340"]
    assert len(L.literals(text)) == 1
    # an escaped quote literal and a literal after the address change nothing
    assert L.addresses(r"""char q = '\''; int *p = (int *)0x00E1C340; char r = '"';""") == ["0x00E1C340"]
    # more than four characters is no character literal: nothing inside quotes that long is skipped
    assert L.addresses("int *p = (int *)'0x00E1C340';") == ["0x00E1C340"]
