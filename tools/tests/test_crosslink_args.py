#!/usr/bin/env python3
"""crosslink.py writes by default, so its argument handling is a safety feature.

Nothing in main() had ever looked at argv beyond `--check`, so every other
argument fell straight through to the write path: `tools/crosslink.py --help`
rewrote comment links into 2,804 files, and so would a typo like `--chek` or a
habitual `--dry-run`. The links themselves are comment-only and harmless, but a
2,804-file working tree is not something a `--help` should produce, and in a
shared clone it collides with every other agent's rebase.

These tests pin that an unrecognised argument never reaches the tree walk.
ledger_index() is the first thing the write path calls, so monkeypatching it to
raise proves the refusal happens before any file is read or written.
"""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import crosslink  # noqa: E402


@pytest.fixture
def no_work(monkeypatch):
    """Make any attempt to start the real run fail loudly."""
    def boom(*a, **k):
        raise AssertionError("crosslink started its tree walk")
    monkeypatch.setattr(crosslink, "ledger_index", boom)


@pytest.mark.parametrize("flag", ["--help", "-h"])
def test_help_prints_usage_and_writes_nothing(flag, monkeypatch, capsys, no_work):
    monkeypatch.setattr(sys, "argv", ["crosslink.py", flag])
    assert crosslink.main() == 0
    out = capsys.readouterr().out
    assert "--check" in out and "Link the two halves" in out


@pytest.mark.parametrize("flag", ["--chek", "--dry-run", "--write", "extra"])
def test_an_unknown_argument_is_refused_and_writes_nothing(flag, monkeypatch,
                                                           capsys, no_work):
    monkeypatch.setattr(sys, "argv", ["crosslink.py", flag])
    assert crosslink.main() == 2
    err = capsys.readouterr().err
    assert flag in err
    assert "nothing was written" in err


def test_check_is_still_recognised(monkeypatch, no_work):
    """--check must keep reaching the real run; the guard is not a blanket no."""
    monkeypatch.setattr(sys, "argv", ["crosslink.py", "--check"])
    with pytest.raises(AssertionError, match="tree walk"):
        crosslink.main()


def test_no_argument_still_means_write(monkeypatch, no_work):
    """Writing stays the documented default -- the guard must not change that."""
    monkeypatch.setattr(sys, "argv", ["crosslink.py"])
    with pytest.raises(AssertionError, match="tree walk"):
        crosslink.main()
