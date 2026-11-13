### LINK-604: MilesAudioManager header adoption in three audio consumers
Status: Cleared for the three consumers below by byte and link-preview checks, 2026-11-05; inspected revision `d7dd0eadbe`.
Scope / completed: `MilesAudioManagerScaledValue.cpp`, `MilesAudioManager_getGlobalReverbMultiplier.cpp` and `MilesAudioManager_isPlayingLowerPriority.cpp` now use the canonical manager header; its opaque fields retain local typed access views. The owning acceptance tool retired all three queue rows together.
Evidence: [source changes, object-provider audit and verification](../../reverse/attempt_support/link_604_miles_audio_manager_header_adoptions.md).
Remaining / next check: other MilesAudioManager queue rows retain their existing prerequisites; no shared header or member provider was changed. Census confirmation and real-image validation are not claimed.


2026-11-13 (merge-climb, source consolidation at `1b7a6e99402b`):
The official TU merge absorbs 3 approved satellites into
`Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp`. `./build.sh` verifies
415/415 matched rows with zero row identities lost; CSV and frozen-source
checks pass. Fresh index SHA-256 `0d99f769fe7bb4a4c08d24769264a6f025abce03d648a0496abfe3915e757e70`
(meta `ec61e5dbe7`, underlying census `cbed44f606`)
admits the applied composition through LinkGuard and ProviderGuard. The
header queue's current source/acceptance commands follow the absorbed donor.
This is a partial source merge; it does not retire further header-adoption debt
or establish census, real-link, or runtime closure for the manager. The
three-consumer clearance and other remaining prerequisites above are retained.
