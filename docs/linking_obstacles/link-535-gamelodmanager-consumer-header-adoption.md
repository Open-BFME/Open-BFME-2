### LINK-535: GameLODManager consumers need canonical layout and existing setter identity
Status: Partly cleared; two header consumers remain. Updated: 2026-11-05; inspected revision: `7ac44ac9c4`.
Completed: five private views replaced with GameLODManager.h; accept retired five header-queue rows. W3DDisplayInit retains the rowed Rva00202739 setter identity through an explicit view cast.
Remaining / next check: reconcile Rva00201DC4LODDefaults.cpp's RAM fields/alignment and MilesAudioManager.cpp's narrow audio accesses, then run header accept on those consumers.
Clearance: five changed units retain 165/165 code-row matches and preview LINKS, 18,032 -> 18,032 bytes; family closure remains incomplete. Census confirmation: awaiting; no gain claimed.
[Evidence, source scopes and verification](../../reverse/attempt_support/gamelod-header-adoption-20261105-codexb5.md).
