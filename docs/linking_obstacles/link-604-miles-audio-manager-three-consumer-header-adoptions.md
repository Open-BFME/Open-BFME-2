### LINK-604: MilesAudioManager header adoption in three audio consumers
Status: Cleared for the three consumers below by byte and link-preview checks, 2026-11-05; inspected revision `d7dd0eadbe`.
Scope / completed: `MilesAudioManagerScaledValue.cpp`, `MilesAudioManager_getGlobalReverbMultiplier.cpp` and `MilesAudioManager_isPlayingLowerPriority.cpp` now use the canonical manager header; its opaque fields retain local typed access views. The owning acceptance tool retired all three queue rows together.
Evidence: [source changes, object-provider audit and verification](../../reverse/attempt_support/link_604_miles_audio_manager_header_adoptions.md).
Remaining / next check: other MilesAudioManager queue rows retain their existing prerequisites; no shared header or member provider was changed. Census confirmation and real-image validation are not claimed.
