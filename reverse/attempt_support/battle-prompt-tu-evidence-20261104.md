# Battle-prompt TU evidence, 2026-11-04

Inspected `b3f5048fc9`; claimed the three battle-prompt source files and
RVAs `0x005E9A5E`, `0x005E9B4A`, `0x005E9D78`, `0x005E9E41`.
No source, ledger owner or TU-map row changed.

Target facts: all three sources pass `find_declared_unmatched.py`. Current
`tu_map.evidence_rows()` gives no F, Z or S anchor to any of the four parents.
CreateLocalPlayerData and PopulateMovieClip have N hints for
`StrategicInGameUI.cpp`, not `StrategicInGameUIBattlePromptDialog.cpp`;
OnClipLoaded and Impl's constructor have no N hint. Wself is true for the
first three and false for the constructor. Global W validation is 170/170
and passes; the obstacle is independent ownership evidence, not its score.

Donor facts: `wb_show.py 0x005E9A5E` identifies WB `0x015E01F0`, assertions
49..62, score 4; `wb_show.py 0x005E9E41 --gd` identifies WB `0x015E0F80`,
assertion 290, score 1. Both push the candidate path. The latter shares the
six stored inputs, clip field at +0x18, callback to OnClipLoaded, and
StrategicBattlePrompt.swf with the target constructor. This supports the
pairing, but does not supply a target-side original path.

Conclusion: the WorldBuilder path is not refuted. It is blocked from TU
approval by the current non-circular W anchoring rule. Do not relabel the
namespace as a class, alter hints or weaken that rule to obtain approval.
Next useful evidence is an independent game-side path/definition anchor or
an independently validated retail structural routing rule. Existing body
matches and historical link blockers are separate from this ownership lead.
