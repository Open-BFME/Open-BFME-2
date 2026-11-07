"""A template argument's commas do not separate parameters.

`rename.parameters` split a parameter list on every comma, so a declaration
like

    void AISpellBookBase::findUnitInCombat(
        _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *combatUnits,
        Player *player)

parsed as three parameters, and the first "parameter" was the fragment
`_STL::vector<const ModuleData *`, whose last word is the type `ModuleData`.
The scoped naming lane inventoried that as a renameable parameter and served it
to a voter, who would have been proposing a new spelling for a type. The real
parameters were still found, so this was a phantom rather than lost coverage -
but `parameters` is also used as a membership test in several places, where a
phantom name can wrongly allow or refuse a rename.

`prototype_param_spans` already refuses to read a list with template commas
positionally, so the hazard was known; the splitter just did not share that care.
"""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import rename  # noqa: E402


VECTOR = ("_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *combatUnits, "
          "Player *player")


def test_a_template_argument_list_is_one_parameter():
    assert list(rename.parameters(VECTOR)) == ["combatUnits", "player"]


def test_the_type_inside_the_template_is_not_offered_as_a_name():
    assert "ModuleData" not in set(rename.parameters(VECTOR))


@pytest.mark.parametrize("params, expected", [
    ("", []),
    ("void", []),
    ("int count", ["count"]),
    ("int a, int b", ["a", "b"]),
    ("const Coord3D *pos, float angle", ["pos", "angle"]),
    # nested templates, and the two-angle-bracket close
    ("_STL::map<int, _STL::vector<int> > *byIndex", ["byIndex"]),
    # A function-pointer parameter's name is not the list's last word, so this
    # heuristic has never yielded it - with the naive split the fragments ended
    # in the keyword `void` and were dropped, and grouping them changes nothing.
    # Recorded as the behaviour it is, not as a wish.
    ("int (*compare)(const void *, const void *), int count", ["count"]),
    # an array extent carries no comma but must not unbalance the scan
    ("char buffer[32], int length", ["buffer", "length"]),
])
def test_ordinary_lists_are_unchanged(params, expected):
    assert list(rename.parameters(params)) == expected


def test_an_arrow_in_a_default_argument_is_not_a_closing_bracket():
    params = "int count = owner->m_limit, bool force"
    assert list(rename.parameters(params)) == ["count", "force"]


def test_an_unbalanced_list_falls_back_to_the_plain_split():
    """Malformed input must not parse worse than it did before."""
    params = "_STL::vector<int *two, Player *player"
    assert list(rename.parameters(params)) == list(
        name for part in params.split(",")
        for name in ([rename.name_metric.WORD.findall(part.split("=")[0])[-1]]
                     if len(rename.name_metric.WORD.findall(part.split("=")[0])) >= 2 else []))


def test_parameter_parts_keeps_every_parameter():
    assert len(rename.parameter_parts(VECTOR)) == 2
