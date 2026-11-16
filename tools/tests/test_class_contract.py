"""Array type counts have explicit units; old contracts need extent proof."""
import copy
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_contract as C
import header_adopt_lane as H


def contract(type_name, size, unit=None):
    result = {"class": "Probe", "key": "struct", "key_by": "bytes", "size": size, "size_by": "bytes",
              "bases": [], "fields": [{"name": "x", "offset": 0, "size": size, "kind": "A",
                                      "type": type_name}], "vslots": {}, "queue": []}
    if unit is not None:
        result["array_count_unit"] = unit
    return result


@pytest.mark.parametrize("old,size,expected,declaration", [
    ("uint[16]", 16, "uint[4]", "unsigned int x[4]"),
    ("int[32]", 32, "int[8]", "int x[8]"),
    ("float[80]", 80, "float[20]", "float x[20]"),
    ("char[13]", 13, "char[13]", "char x[13]"),
    ("uchar[9]", 9, "uchar[9]", "unsigned char x[9]"),
    ("int[8]", 8, "int[2]", "int x[2]"),
    ("GameSlot*[32]", 32, "GameSlot*[8]", "GameSlot* x[8]"),
    ("uint*[16]", 16, "uint*[4]", "unsigned int* x[4]"),
    ("GameSlot*[2048][36864]", 36864, "GameSlot*[18][512]", "GameSlot* x[18][512]"),
])
def test_legacy_byte_dimensions_are_normalized_with_recorded_extent(old, size, expected, declaration):
    before = contract(old, size)
    original = copy.deepcopy(before)
    normalized = C.normalize_array_counts(before)
    assert normalized["fields"][0]["type"] == expected
    assert normalized["array_count_unit"] == "elements"
    assert C.normalize_array_counts(normalized) == normalized
    assert before == original
    assert H.spelled(expected, "x") == declaration


@pytest.mark.parametrize("spelling,size", [
    ("uint[4]", 16), ("int[8]", 32), ("float[20]", 80), ("char[13]", 13),
    ("float[768]", 3072), ("float[3]", 12), ("Coord2D[2]", 16),
    ("int[2][3]", 24),
])
def test_already_correct_counts_and_char_arrays_stay_unchanged(spelling, size):
    assert C.normalize_array_counts(contract(spelling, size))["fields"][0]["type"] == spelling


def test_unknown_legacy_width_requires_remeasurement_instead_of_another_views_size(monkeypatch):
    # A canonical class's sizeof is not necessarily the sizeof of an old private view.
    monkeypatch.setattr(C, "contract_path", lambda name: pytest.fail("must not infer another view's width"))
    with pytest.raises(ValueError, match="remeasure"):
        C.normalize_array_counts(contract("PrivateThing[64]", 64))


def test_explicit_element_unit_has_no_legacy_fallback():
    with pytest.raises(ValueError, match="inconsistent"):
        C.normalize_array_counts(contract("uint[16]", 16, "elements"))


def test_unsupported_count_units_are_refused():
    with pytest.raises(ValueError, match="unsupported"):
        C.normalize_array_counts(contract("uint[16]", 16, "bytes"))


def test_ambiguous_byte_array_shape_needs_an_explicit_unit():
    with pytest.raises(ValueError, match="ambiguous"):
        C.normalize_array_counts(contract("char[1][16]", 16))
    assert C.normalize_array_counts(contract("char[1][16]", 16, "elements"))["fields"][0]["type"] == "char[1][16]"


def test_header_generator_normalizes_before_declaring_a_wide_array():
    text = H.generate(contract("uint[16]", 16), "data", {}, special=[])
    assert "unsigned int x[4];" in text
    assert "x[16]" not in text


def test_header_generator_holds_unknown_legacy_array_counts():
    with pytest.raises(H.LayoutError, match="remeasure"):
        H.generate(contract("PrivateThing[64]", 64), "data", {}, special=[])


def test_new_contracts_explicitly_record_element_count_units(monkeypatch):
    layout = {"key": "struct", "size": 16, "bases": [], "fields": [[0, "x", "uint[4]", 16]],
              "statics": [], "methods": set(), "virtual": set(), "vslots": {}, "vfptr": False}
    monkeypatch.setattr(C.class_layouts, "build_module", lambda: object())
    monkeypatch.setattr(C, "ledger_rows", lambda: [])
    monkeypatch.setattr(C, "views", lambda *a: ({"u.cpp": layout}, {"u.cpp": {"Probe": layout}}))
    monkeypatch.setattr(C, "zh_layout", lambda *a: None)
    monkeypatch.setattr(C, "retail_access", lambda *a: {})
    monkeypatch.setattr(C, "witnesses", lambda *a: {})
    monkeypatch.setattr(C, "retail_vtable", lambda *a: {})
    monkeypatch.setattr(C, "retail_layout", lambda *a: {})
    monkeypatch.setattr(C, "export_key", lambda *a: set())
    decided = C.decide("Probe", sources=["u.cpp"])
    assert decided["array_count_unit"] == "elements"
    assert decided["fields"][0]["type"] == "uint[4]"
    assert "unsigned int x[4];" in H.generate(decided, "data", {}, special=[])


def test_committed_arrays_change_only_previously_wrong_declarations():
    import json
    import re

    def old_spelling(type_name, name):
        stem = type_name.rstrip("*")
        stars = type_name[len(stem):]
        array = re.match(r"(.+)\[(\d+)\]$", stem)
        if array:
            return f"{H.SPELL.get(array[1], array[1])} {name}[{array[2]}]"
        return f"{H.SPELL.get(stem, stem)} {stars}{name}"

    root = Path(__file__).resolve().parents[2]
    examined = changed = unchanged = held = 0
    for path in (root / "reverse/class_contracts").glob("*.json"):
        saved = json.loads(path.read_text())
        for field in saved["fields"]:
            array = C.ARRAY_TYPE.fullmatch(field.get("type", ""))
            if array is None:
                continue
            examined += 1
            mini = {"fields": [field]}
            if "array_count_unit" in saved:
                mini["array_count_unit"] = saved["array_count_unit"]
            try:
                normal = C.normalize_array_counts(mini)["fields"][0]
            except ValueError as why:
                assert "remeasure" in str(why) or "ambiguous" in str(why)
                held += 1
                continue
            before = old_spelling(field["type"], field["name"])
            after = H.spelled(normal["type"], field["name"])
            if before == after:
                unchanged += 1
            else:
                dimensions = [int(n) for n in re.findall(r"\d+", array[2])]
                width = C.array_element_size(array[1])
                old_size = width
                if width is not None:
                    for count in dimensions:
                        old_size *= count
                pointer_alias = array[1].endswith("*") and array[1].rstrip("*") in H.SPELL
                assert (len(dimensions) > 1       # old output put [] before the field identifier
                        or pointer_alias         # old output did not spell the primitive alias
                        or width is not None and old_size != field["size"]), (path, field, before, after)
                changed += 1
            if array[1] in ("char", "uchar", "int8", "uint8"):
                assert before == after, (path, field)
    assert examined == changed + unchanged + held
    assert examined > 0 and changed > 0 and unchanged > 0


@pytest.mark.parametrize("flag", ["error", "unparsed"])
def test_an_unmeasurable_nested_class_never_supplies_partial_array_facts(flag):
    bad = {"size": 16, "fwd": False, "fields": [[0, "prefix", "int", 4]],
           "bases": [], "vfptr": False, "virtual": [], flag: "array element width unknown"}
    assert C.aggregate({"Bad": bad}, "Bad", 16) is None
    outer = {"size": 16, "vfptr": False, "bases": [], "fields": [[0, "whole", "Bad", 16]]}
    assert C.flatten(outer, {"Bad": bad}, leaves=True) == [(0, 16, "S:Bad", "whole", "Bad")]
