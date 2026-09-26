#!/usr/bin/env python3
"""Tests for build.bfme1_subtree(): the open-bfme-1 submodule's two layouts.

Upstream moved its tree (Code/ -> game/, reference/ -> inputs/reference/,
build/toolchains/ -> inputs/toolchains/, baselines/ -> inputs/baselines/,
vendor/ -> inputs/vendor/). Every path this repo reaches into the submodule with
goes through bfme1_subtree(), so a clone pinned to either submodule commit
resolves the same logical subtree. These tests pin that behaviour: the failure
they guard against is silent, because a missing /I directory is not an error to
cl -- a regression here does not fail the build, it changes which headers 626
already-matched sources compile against.
"""
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import build  # noqa: E402

LOGICAL = {
    "reference": ("inputs/reference", "reference"),
    "toolchains": ("inputs/toolchains", "build/toolchains"),
    "baselines": ("inputs/baselines", "baselines"),
    "vendor": ("inputs/vendor", "vendor"),
    "game": ("game", "Code"),
}


@pytest.fixture
def fake_root(tmp_path, monkeypatch):
    """Point build at an empty stand-in for the submodule checkout."""
    monkeypatch.setattr(build, "BFME1_ROOT", tmp_path)
    return tmp_path


@pytest.mark.parametrize("kind,spellings", sorted(LOGICAL.items()))
def test_each_layout_spelling_is_found_when_it_is_the_one_present(
        kind, spellings, fake_root):
    for spelling in spellings:
        (fake_root / spelling).mkdir(parents=True)
        assert build.bfme1_subtree(kind) == spelling
        # Remove it again so the next spelling is tested on its own, not
        # shadowed by the one just created.
        for part in reversed(list(Path(spelling).parents)[:-1] + [Path(spelling)]):
            target = fake_root / part
            if target.is_dir() and not any(target.iterdir()):
                target.rmdir()


@pytest.mark.parametrize("kind,spellings", sorted(LOGICAL.items()))
def test_current_upstream_spelling_wins_when_both_are_present(
        kind, spellings, fake_root):
    current, legacy = spellings
    (fake_root / current).mkdir(parents=True)
    (fake_root / legacy).mkdir(parents=True)
    assert build.bfme1_subtree(kind) == current


@pytest.mark.parametrize("kind,spellings", sorted(LOGICAL.items()))
def test_absent_tree_reports_where_it_belongs_today(kind, spellings, fake_root):
    # Not an exception: the caller turns this into a "run git submodule update"
    # message, which has to name the current location rather than the one
    # upstream retired.
    assert build.bfme1_subtree(kind) == spellings[0]


def test_bfme1_path_joins_onto_the_resolved_subtree(fake_root):
    (fake_root / "Code").mkdir()
    assert build.bfme1_path("game", "Libraries", "x.h") == (
        fake_root / "Code" / "Libraries" / "x.h")


def test_an_unknown_logical_name_is_a_typo_not_a_silent_miss():
    with pytest.raises(KeyError):
        build.bfme1_subtree("no-such-subtree")


def test_the_real_checkout_resolves_every_logical_subtree():
    """Whichever commit this clone pins, all five subtrees must be present."""
    if not build.BFME1_ROOT.is_dir():
        pytest.skip("reference/open-bfme-1 is not checked out")
    missing = [kind for kind in LOGICAL
               if not (build.BFME1_ROOT / build.bfme1_subtree(kind)).is_dir()]
    assert not missing, f"submodule layout resolves nothing for: {missing}"
