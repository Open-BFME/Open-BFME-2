"""Qualified private views keep their identity through contract/header adoption."""
import json
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_contract as contract
import class_layouts
import class_views
import header_adopt_lane as lane

NAME = "StrategicHUD::BattlePromptArmyPanelMovieClip::Impl"
VIEW = f"""class StrategicHUD::BattlePromptArmyPanelMovieClip::Impl : public Base {{
public:
    void SetSelected(bool);
private:
    bool selected;
}};
class Independent {{ int x; }};
"""


def test_full_scope_survives_both_view_readers():
    assert set(class_views.class_bodies(VIEW)) == {NAME, "Independent"}
    assert set(class_layouts.class_bodies(VIEW)) == {NAME, "Independent"}
    assert "StrategicHUD" not in class_views.class_bodies(VIEW)
    assert lane.body_span(VIEW, "StrategicHUD") is None
    assert lane.body_span(VIEW, NAME) is not None
    replaced = lane.swap(VIEW, [NAME], "ArmyPanelClip.h")
    assert "bool selected" not in replaced
    assert "class Independent" in replaced
    assert '#include "ArmyPanelClip.h"' in replaced


def test_census_does_not_treat_scope_prefix_as_a_class(tmp_path, monkeypatch):
    (tmp_path / "clip.cpp").write_text(VIEW, encoding="utf-8")
    monkeypatch.setattr(contract, "ROOT", tmp_path)
    rows = [{"source": "clip.cpp"}]
    assert contract.census(NAME, rows) == ["clip.cpp"]
    assert contract.census("StrategicHUD", rows) == []


def test_qualified_ledger_evidence_uses_msvc_scope_order():
    member = {"name": "?SetSelected@Impl@BattlePromptArmyPanelMovieClip@StrategicHUD@@QAEX_N@Z"}
    ctor = {"name": "??0Impl@BattlePromptArmyPanelMovieClip@StrategicHUD@@QAE@XZ"}
    unrelated = {"name": "?SetSelected@Impl@Other@@QAEX_N@Z"}
    assert contract.thiscall_rows(NAME, [member, ctor, unrelated]) == ([member], [ctor])
    pointer = {"name": "?use@@YAXPAVImpl@BattlePromptArmyPanelMovieClip@StrategicHUD@@@Z"}
    assert contract.ledger_key(NAME, [pointer]) == {"class": 1}
    assert contract.thiscall_rows("Independent", [{"name": "?f@Independent@@QAEXXZ"}])[0]


@pytest.mark.parametrize("name", [NAME, "A::B", "A__B", "A%3A%3AB", "../A", "A/B", "A\\B", "CON", "NUL", "LPT1", "é"])
def test_contract_component_is_portable_and_stays_in_one_directory(name, tmp_path, monkeypatch):
    monkeypatch.setattr(contract, "CONTRACTS", tmp_path)
    path = contract.contract_path(name)
    assert path.parent == tmp_path
    assert not set('<>:"/\\|?*.') & set(path.stem)
    path.write_text("{}", encoding="utf-8")
    assert path.read_text(encoding="utf-8") == "{}"


def test_components_do_not_collide_and_simple_paths_stay_compatible():
    names = ["A::B", "A__B", "A%3A%3AB", "CON", "%43ON"]
    assert len({contract.portable_component(n) for n in names}) == len(names)
    assert contract.portable_component("Coord3D") == "Coord3D"
    with pytest.raises(ValueError):
        contract.portable_component("")


def test_adoption_reads_frozen_contract_and_writes_portable_report(tmp_path, monkeypatch):
    monkeypatch.setattr(contract, "CONTRACTS", tmp_path / "contracts")
    monkeypatch.setattr(lane, "SCRATCH", tmp_path / "reports")
    monkeypatch.setattr(contract, "census", lambda name: ["clip.cpp"])
    frozen = {"class": NAME, "queue": []}
    path = contract.contract_path(NAME)
    path.parent.mkdir()
    path.write_text(json.dumps(frozen), encoding="utf-8")
    def tournament(name, frozen_input, sources, header, variants, jobs, fixed_header):
        assert frozen_input == frozen
        assert fixed_header
        return {"registered": {"verdicts": {"clip.cpp": None}, "seconds": 0}}
    monkeypatch.setattr(lane, "tournament", tournament)
    args = SimpleNamespace(name=NAME, header="clip.h", generate=False, sample=None,
                           variants="data", jobs=1, apply=False)
    assert lane.run(args) == 0
    report = lane.SCRATCH / path.name
    assert json.loads(report.read_text(encoding="utf-8"))["passed"] == ["clip.cpp"]


def test_contract_command_freezes_qualified_identity_at_portable_path(tmp_path, monkeypatch):
    monkeypatch.setattr(contract, "ROOT", tmp_path)
    monkeypatch.setattr(contract, "CONTRACTS", tmp_path / "contracts")
    evidence = {"views": 1, "view_errors": 0, "zh": {}}
    decided = {"class": NAME, "key": "class", "key_by": "bytes", "size": 64,
               "size_by": "bytes", "bases": [], "bases_by": "bytes", "evidence": evidence,
               "fields": [], "vslots": {}, "queue": [], "sources": ["clip.cpp"]}
    monkeypatch.setattr(contract, "decide", lambda *args, **kwargs: decided)
    assert contract.main(["--class", NAME, "--write"]) == 0
    frozen = json.loads(contract.contract_path(NAME).read_text(encoding="utf-8"))
    assert frozen["class"] == NAME
    assert "sources" not in frozen


def test_qualified_class_key_rewrite_preserves_scope(tmp_path, monkeypatch):
    ledger = tmp_path / "functions.csv"
    before = "?use@@YAXPAUImpl@BattlePromptArmyPanelMovieClip@StrategicHUD@@@Z"
    ledger.write_text("name,source\n" + before + ",clip.cpp\n", encoding="utf-8")
    monkeypatch.setattr(lane, "LEDGER", ledger)
    assert lane.ledger_renames("clip.cpp", NAME, "class") == [
        (before, before.replace("PAUImpl", "PAVImpl"))]
