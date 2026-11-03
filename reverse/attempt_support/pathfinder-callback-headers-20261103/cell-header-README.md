# F600C standalone canonical PathfindCell header trial

Verdict: PASS for this one standalone source prerequisite only. The frozen-file check ran first and printed 'All defined functions are already matched'. The entire canonical PathfindCell.h was read in the existing supported private tree.

The candidate changes only the WHOLE private PathfindCell declaration to `#include "../../../Include/GameLogic/PathfindCell.h"` and the callback's single `to->flags` access to `to->m_0C`. Its native16-byte/no-base/no-virtual shape retains the packed unsigned field at0x0C. No other source declaration/body, flags, pin, alias, marker, header or ledger was changed. Private Pathfinder/member-pointer and Rva002F600CInfo views remain untouched.

Control and candidate each match the single105-byte code row at0x002F600C. Both emit exactly one ordinary external definition; its complete E.Obj bytes and ordered symbolic relocation list are identical. BSS-aware E.Obj section.data is used. No EH graph exists in either object (both EH maps are empty); there is no additional helper/vtable/data provider. proof.json contains full code row, provider records and verifier verdicts. The call's existing CheckForAdjust binding is therefore unchanged by this Cell-only trial.

Control source SHA256: `2b57a7be8c7476b8afb1b116314bc5b06507e3faacb94e40091c17d20bc36dd0`.

Files: control.cpp/candidate.cpp are full scratch source snapshots, control.obj/candidate.obj are copied sanctioned private Verifier outputs, proof.json is the proof. Harness: ../core-header-proof/f600c-cell-probe.py. Apply only the two local intended edits to the claimed public source; do not overwrite it from this possibly older full snapshot.

This does not prove composition with canonical Pathfinder or the competing Rva002F600CInfo seed view. Main owns those additional ABI/provider obligations, ordinary build, header acceptance, commit and publication. No tracked source/ledger edit, claim, network, normal build or shared cache write occurred. Tracked reads stopped.
