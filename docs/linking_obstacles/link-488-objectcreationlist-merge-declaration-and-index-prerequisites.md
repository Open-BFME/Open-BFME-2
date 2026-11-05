### LINK-488: ObjectCreationList merge declaration and index prerequisites

Status: Blocked. Updated: 2026-11-05; inspected revision: `868eff29fe`.
Scope / evidence: ObjectCreationList.cpp and its 14 clean donor candidates; [completed comparison, declaration repair and checks](../../reverse/attempt_support/ocl-list-view-20261105-codex.md).
Completed: shared ObjectCreationList declaration in CanCreate and nugget-parser donors; 8/8 rows exact, both previews LINKS (960 authored bytes preserved). Normal merge comparison remains 0 donors -> 0 donors; no paths move.
Header prerequisite repaired: AttackNuggetCreate now uses canonical AI interfaces; two header-queue rows retired, 4/4 exact and preview LINKS, 272 bytes preserved ([evidence](../../reverse/attempt_support/attack-nugget-ai-header-20261105-codex5.md)).
Remaining / next check: the 0x0076B063 index prerequisite is published. AttackNuggetCtor now composes but misses 0x001F05C1 because the seed's ZH RadiusDecalTemplate is 0x1C bytes, not BFME 2's 0x34; give the seed the BFME 2 type, keep it 58/58, then retry ([evidence](../../reverse/attempt_support/ocl-attacknugget-ctor-merge-20261105-claude2.md)). Other donors still need the documented class/include repairs. Keep the merge guard enabled.
Clearance / census: pending; no linking gain or census confirmation claimed.
