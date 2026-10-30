"""tu_holdout (tu_map.py --holdout): anchors are stripped before the build, truth never feeds a fold,
only held-out rows are scored, purity and name precision are counted, and runs are reproducible."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import tu_holdout as H  # noqa: E402
import tu_map  # noqa: E402


def ev(rva, F=None, Z=None, S=None, L=None, W=None, N=None, tool=False):
    hard = F or Z or S or L
    return {"rva": rva, "F": F, "Z": Z, "S": S, "L": L, "W": W, "N": N, "hard": hard, "hint": hard or N,
            "tool": tool}


def row(rva, tu, conf="approved", by="N", evidence=""):
    return {"rva": f"0x{rva:08X}", "size": "8", "kind": "code", "tu": tu, "confidence": conf, "by": by,
            "evidence": evidence, "source": ""}


def test_strip_removes_every_anchor_naming_a_held_out_tu_and_nothing_else():
    rows = [ev(1, F="Code/A.cpp", N="Code/A.cpp"), ev(2, Z="Code/A.cpp", S="Code/B.cpp"),
            ev(3, L="Code/a.cpp", W="Code/A.cpp"), ev(4, Z="Code/B.cpp", W="Code/B.cpp")]
    out = H.strip(rows, frozenset({"code/a.cpp"}))
    assert [(r["F"], r["Z"], r["S"], r["L"], r["W"]) for r in out] == [
        (None, None, None, None, None), (None, None, "Code/B.cpp", None, None),
        (None, None, None, None, None), (None, "Code/B.cpp", None, None, "Code/B.cpp")]
    assert out[0]["hard"] is None and out[0]["hint"] == "Code/A.cpp"     # the naming hint (N) stays
    assert out[1]["hard"] == "Code/B.cpp" and rows[0]["F"] == "Code/A.cpp"  # the input is not mutated


def test_no_held_out_anchor_reaches_the_folds_build(monkeypatch):
    """Leakage: everything tu_map.build sees for a fold comes through the stripped evidence rows."""
    import tu_evidence
    rows = [ev(1, F="Code/A.cpp"), ev(2, Z="Code/A.cpp"), ev(3, Z="Code/B.cpp")]
    seen = []

    def build(layout):
        got = tu_map.evidence_rows(layout)
        seen.append((got, tu_map.PROV_MIN, tu_evidence.P_GROUPS))
        return []
    monkeypatch.setattr(tu_map, "build", build)
    b = H.Builder(layout=None)
    b.rows = rows
    b.build(frozenset({"code/a.cpp"}), p_groups=True, prov_min=1)
    got, prov_min, groups = seen[0]
    assert not [r for r in got for s in H.STRIP if r.get(s) and r[s].lower() == "code/a.cpp"]
    assert (prov_min, groups) == (1, True)
    assert tu_map.PROV_MIN == 2 and tu_map.evidence_rows is not None    # restored after the build
    b.build()
    assert seen[1][0][0]["F"] == "Code/A.cpp" and seen[1][2] is False    # the live build: nothing stripped


def test_truth_excludes_provisional_and_rule_tokens():
    rows = [row(1, "Code/A.cpp", by="Z"), row(2, "Code/A.cpp", by="C"),
            row(3, "Code/P.cpp", evidence="N=Code/P.cpp provisional"),
            row(4, "Code/A.cpp", by="P", evidence="P=0x1@FuncInfo0x2 p-group"),
            row(5, "Code/A.cpp", conf="proposed")]
    assert H.truth_of(rows) == {"0x00000001": "code/a.cpp", "0x00000002": "code/a.cpp"}


def test_folds_are_deterministic():
    keys = [f"code/f{i}.cpp" for i in range(50)]
    assert [H.fold_of(k) for k in keys] == [H.fold_of(k) for k in keys]
    assert set(H.fold_of(k) for k in keys) == set(range(H.FOLDS))


def test_score_fold_counts_purity_names_and_never_scores_rows_whose_anchors_stayed():
    truth = {f"0x{i:08X}": t for i, t in ((1, "code/a.cpp"), (2, "code/a.cpp"), (3, "code/a.cpp"),
                                          (4, "code/b.cpp"), (5, "code/c.cpp"), (6, "code/d.cpp"))}
    held = frozenset({"code/a.cpp", "code/b.cpp", "code/d.cpp"})
    off = [row(1, "Code/A.cpp"), row(2, "Code/Agroup.cpp", conf="proposed"), row(3, "", conf=""),
           row(4, "", conf=""), row(5, "Code/C.cpp", conf="proposed"), row(6, "", conf="")]
    on = [row(1, "Code/A.cpp"), row(2, "Code/Agroup.cpp", by="P"), row(3, "Code/A.cpp", by="P"),
          row(4, "Code/A.cpp", by="P"), row(5, "Code/C.cpp", by="P"), row(6, "Code/Solo.cpp", by="P")]
    stats, worst = H.collections.Counter(), []
    H.score_fold("p-groups", off, on, truth, held, stats, worst)
    assert stats["scored"] == 4                                          # rows 2, 3, 4, 6; row 5 kept its anchor
    assert stats["not held out"] == 1
    # rows 2 and 6: one-row groups (pure by construction, other names); row 4 (truth B) joins A's group,
    # so that group mixes two TUs and both rows joining it (3 and 4) count as mixed
    assert stats["pure"] == 2 and stats["singleton"] == 2 and stats["name"] == 1
    assert [w["rva"] for w in worst] == ["0x00000003", "0x00000004"]
    assert worst[1]["group"] == {"code/a.cpp": 2, "code/b.cpp": 1}
    assert stats["recoverable"] == 4 and stats["recovered"] == 1


def test_post_pass_rules_are_measured_on_the_off_map():
    rows = [row(0x10, "Code/A.cpp", by="Z"), row(0x20, "Code/A.cpp", conf="proposed", by="C"),
            row(0x30, "Code/A.cpp", by="Z"), row(0x40, "Code/B.cpp", conf="proposed", by="K")]
    got = H.newly_approved("brackets", rows)
    assert list(got) == ["0x00000020"]
    assert H.newly_approved("k-only", rows) == {}                        # B has no approved row
    with pytest.raises(SystemExit, match="unknown rule"):
        H.holdout("bogus", builder=object())


class FakeBuilder:
    """Two anchored TUs; a held-out TU's rows lose approval; the ON map gives them back."""
    layout = None

    def build(self, held=frozenset(), p_groups=False, prov_min=2):
        out = []
        for i, key in enumerate(("Code/A.cpp", "Code/B.cpp")):
            for j in range(3):
                gone = key.lower() in held
                out.append(row(0x100 * i + j, key, conf="proposed" if gone and not p_groups else "approved",
                               by="P" if gone else "Z"))
        return out


def test_holdout_is_reproducible(monkeypatch):
    monkeypatch.setattr(H, "files_freed", lambda layout, live, gained: 0)
    first = H.holdout("p-groups", builder=FakeBuilder(), log=lambda *a: None)
    second = H.holdout("p-groups", builder=FakeBuilder(), log=lambda *a: None)
    assert first == second and first["scored"] == 6 and first["purity"] == 1.0
    assert "purity 6/6 = 100.00%" in H.render(first)


def test_strip_by_row_removes_only_the_held_out_rows_own_anchors():
    rows = [ev(1, Z="Code/A.cpp", N="Code/A.cpp"), ev(2, Z="Code/A.cpp", S="Code/A.cpp")]
    out = H.strip(rows, frozenset(), frozenset({1}))
    assert (out[0]["Z"], out[0]["hard"], out[0]["hint"]) == (None, None, "Code/A.cpp")
    assert (out[1]["Z"], out[1]["S"]) == ("Code/A.cpp", "Code/A.cpp")      # the TU keeps its other anchors


def test_a_signal_rule_promotes_it_for_on_and_drops_it_for_off(monkeypatch):
    import tu_evidence
    seen = []
    monkeypatch.setattr(tu_map, "build", lambda layout: seen.append(tu_evidence.PROMOTED) or [])
    monkeypatch.setattr(tu_evidence, "PROMOTED", frozenset("EP"))
    b = H.Builder(layout=None)
    b.rows = [ev(1, Z="Code/A.cpp")]
    off, on = H.toggles("signal-T")
    b.build(**off)
    b.build(**on)
    assert seen == [frozenset("EP"), frozenset("EPT")]
    assert H.toggles("signal-E")[0] == {"without": "E"} and H.toggles("brackets") is None
    assert tu_evidence.PROMOTED == frozenset("EP")                        # restored after the build


class RowBuilder:
    """Rows of two TUs; a held-out row loses approval unless the signal (T) is on."""
    layout = None

    def build(self, held=frozenset(), p_groups=False, prov_min=2, signal=None, without=None,
              held_rows=frozenset()):
        out = []
        for i, key in enumerate(("Code/A.cpp", "Code/B.cpp")):
            for j in range(10):
                rva = 0x100 * i + j
                gone = rva in held_rows
                out.append(row(rva, key if not gone or signal else "", conf="approved" if not gone or signal else "",
                               by="T" if gone else "Z"))
        return out


def test_row_folds_hold_out_rows_and_score_the_rule_on_them(monkeypatch):
    monkeypatch.setattr(H, "files_freed", lambda layout, live, gained: 0)
    rep = H.holdout("signal-T", builder=RowBuilder(), log=lambda *a: None, unit="row")
    assert rep["unit"] == "row" and rep["truth_rows"] == 20
    assert rep["scored"] == 20 and rep["name_correct"] == 20 and rep["purity"] == 1.0
    assert "hold-out of truth rows" in H.render(rep)
