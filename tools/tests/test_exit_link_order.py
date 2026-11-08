"""exit_link --order retail: objects in retail's order, not path order (P32).

link.exe lays out .CRT$XCU in input order, so the object order is the order static initializers
run. In path order LivingWorldRegionEffects' field table was filled (slot 252) before the strings
it copies were built (slots 658-666). These tests pin the rule retail_object_order documents.
"""
import importlib.util
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]


def _load(name):
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


sys.path.insert(0, str(TOOLS))
build = _load("build")
exit_link = _load("exit_link")


def obj(name):
    return build.ROOT / "build" / "match" / f"{name}.obj"


def row(name, rva):
    return {"name": f"?{name}@@YAXXZ", "target_rva": f"0x{rva:08X}", "source": f"Code/{name}.cpp"}


def order(rows, paths, initializers, places, monkeypatch):
    monkeypatch.setattr(build, "row_object", lambda r: obj(r["source"][5:-4]))
    found = exit_link.retail_object_order(rows, paths, initializers,
                                          {obj(k).resolve(): v for k, v in places.items()})
    return [p.stem for p in found]


def test_initializer_objects_follow_their_retail_slots_not_their_paths(monkeypatch):
    # P32: the table fill's object sorts first by path; retail registers the strings first.
    rows = [row("A_ColorProvider", 0x7AF9D6), row("B_Forward900", 0x7AF8E3), row("C_Forward980", 0x7AF98B)]
    paths = [obj("A_ColorProvider"), obj("B_Forward900"), obj("C_Forward980")]
    places = {"A_ColorProvider": (0, 0x3EE746), "B_Forward900": (0, 0x3EE900), "C_Forward980": (0, 0x3EE980)}
    got = order(rows, paths, [0x7AF8E3, 0x7AF98B, 0x7AF9D6], places, monkeypatch)
    assert got == ["B_Forward900", "C_Forward980", "A_ColorProvider"]


def test_only_initializer_objects_move_and_only_among_their_own_positions(monkeypatch):
    rows = [row("Init1", 0x9000), row("Init2", 0x9010)]
    paths = [obj(n) for n in ("Init1", "Init2", "Low", "Mid", "High")]
    places = {"Init1": (0, 0x200), "Init2": (0, 0x100), "Low": (0, 0x050), "Mid": (0, 0x150), "High": (0, 0x900)}
    # Address order: Low, Init2, Mid, Init1, High. Init1 registers first, so the two initializer
    # objects trade places; Low, Mid and High keep theirs (and so their COMDAT priority).
    got = order(rows, paths, [0x9000, 0x9010], places, monkeypatch)
    assert got == ["Low", "Init1", "Mid", "Init2", "High"]


def test_objects_without_initializers_keep_the_census_address_order(monkeypatch):
    paths = [obj(n) for n in ("Zfirst", "Asecond")]
    got = order([], paths, [], {"Zfirst": (0, 0x10), "Asecond": (0, 0x20)}, monkeypatch)
    assert got == ["Zfirst", "Asecond"]


def test_data_only_objects_follow_code_and_unplaced_objects_go_last_by_path(monkeypatch):
    paths = [obj(n) for n in ("Zdata", "Ycode", "Bnowhere", "Anowhere")]
    places = {"Zdata": (1, 0x100), "Ycode": (0, 0x900)}
    got = order([], paths, [], places, monkeypatch)
    assert got == ["Ycode", "Zdata", "Anowhere", "Bnowhere"]


def test_ties_fall_back_to_path(monkeypatch):
    rows = [row("Bsame", 0x9000), row("Asame", 0x9000)]
    paths = [obj("Bsame"), obj("Asame")]
    got = order(rows, paths, [0x9000], {"Bsame": (0, 0x10), "Asame": (0, 0x10)}, monkeypatch)
    assert got == ["Asame", "Bsame"]


def test_an_object_takes_its_lowest_slot(monkeypatch):
    rows = [row("Two", 0x9030), row("Two", 0x9000), row("One", 0x9010)]
    paths = [obj("One"), obj("Two")]
    got = order(rows, paths, [0x9000, 0x9010, 0x9030], {"One": (0, 0x1), "Two": (0, 0x2)}, monkeypatch)
    assert got == ["Two", "One"]


def test_path_order_stays_the_default(monkeypatch):
    assert exit_link.ORDER == "path"
    monkeypatch.setattr(exit_link, "retail_object_order",
                        lambda *a, **k: (_ for _ in ()).throw(AssertionError("retail order used")))
    monkeypatch.setattr(exit_link.census, "data_sources", lambda: [])
    monkeypatch.setattr(build, "row_object", lambda r: obj(r["source"][5:-4]))
    got = exit_link.expected_objects([row("B", 2), row("A", 1)])
    assert [p.stem for p in got] == ["A", "B"]
