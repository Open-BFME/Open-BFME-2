### LINK-537: AnimationSoundClientBehavior calls an undefined Drawable ID getter
Status: Repair verified locally / awaiting real link. Updated: 2026-11-05; inspected revision: `d992ebcd3c`.
Evidence / affected units: [target call, object-reference delta and verification](../../reverse/attempt_support/animation-sound-getid-link-20261105-codex3.md).
Completed: AnimationSoundClientBehavior.cpp calls the existing matched getter at RVA 0x0055A88B; its object no longer references the undefined Drawable::getID spelling. All 31 function rows and one data row verify; preview LINKS for 2,316 authored bytes.
Remaining / next check: next automated real link must stop listing this unit; independently claim other callers of the same missing name before repairing them. Provider identity recovery remains separate.
Clearance: local object-reference repair only; full real-link confirmation pending.
Census confirmation: not claimed; the 2026-11-05 05:17 preview already accepted the old spelling.

2026-11-05: the same object-reference repair is locally verified for InGameUICreateMouseoverHint.cpp and InGameUIXfer.cpp (32 rows; both previews LINKS); [retail call evidence and verification](../../reverse/attempt_support/ingameui-getid-link-20261105-codex3.md). Await the next real link for these two units; other callers remain.

2026-11-05: W3DTerrainVisualAddFactionBibDrawable.cpp and ModelConditionAudioLoopClientBehaviorUpdate.cpp now bind the same existing getter (9 rows exact; both previews LINKS); [retail calls and object-reference verification](../../reverse/attempt_support/bib-audioloop-getid-link-20261105-codex3.md). Await automated real-link confirmation for these two units; other callers remain.

2026-11-05: ObjectDoXfer.cpp, LuaScriptEngine.cpp and W3DGhostObjectScene.cpp bind the same existing getter, independently landed upstream in 2825058d58 / 3f56eb6465 during publication (266 function rows and two data rows exact; all three previews LINKS); [retail calls and object-reference verification](../../reverse/attempt_support/save-lua-drawable-getid-link-20261105-codex3.md). Await automated real-link confirmation for these three units; other callers remain.
