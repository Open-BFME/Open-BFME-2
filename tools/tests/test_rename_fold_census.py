"""The folds class --fold's initializer route admits over retail's whole table are exactly the ones a
reviewer has read by hand (reverse/initializer_fold_census.csv). Retail's bytes never change, so this is
what bounds a false accept: any change to the set fails here until a reviewer has looked at the new
member and added it. A listed fold that has landed no longer has a placeholder to fold, so it leaves
the census and stays on the list as history, which takes positive evidence (fold_census_problems).
Needs the retail image; skipped where there is none. The synthetic cases are in
test_rename_fold_initializer.py."""
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import build  # noqa: E402
import rename  # noqa: E402


@pytest.mark.skipif(not build.EXE.exists(), reason="the retail image is not here")
def test_the_census_over_retail_is_exactly_what_was_reviewed():
    assert rename.fold_census_problems(rename.Context(rename.ROOT, object_scan=False)) == []


def test_the_census_list_is_a_protected_path():
    import protected_paths
    assert protected_paths.protected([rename.FOLD_CENSUS]) == [rename.FOLD_CENSUS]
