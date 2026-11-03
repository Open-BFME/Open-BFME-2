### W3DTerrainBackground seed reconciliation (2026-11-01, halilkkaya-codex)

Native ctor 112DBE has no vptr; the seed now uses its D4-byte three-camera
layout instead of Zero Hour's class. Nine unused legacy bodies are removed;
doPartialUpdate stays to emit three homeless helper rows. All six sole
external providers remain. The only two dropped helpers with outside touches
are already defined by every respective referring object. A 37-unit preview
retains 85,090 predicted linking bytes (30 LINKS, seven existing blockers);
seed 820 -> 820 and all 18 rows exact. Donor private views and the two mixed
files still need reconciliation before the TU merge. No census gain claimed.
Evidence: reverse/attempt_support/w3dterrainbackground-consolidation-20261101/.
