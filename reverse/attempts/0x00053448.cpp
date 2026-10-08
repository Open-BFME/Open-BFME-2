// ?processFade@MilesAudioManager@@QAE_NAAVPlayingAudioRef@@@Z
// partial score=0.8 date=2026-10-08
// Banked near miss for processFade (0x00053448). Insert into
// Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp after
// startPendingMusicTracks with these layout edits:
//   AudioEventRTS:  float m_extraVolume at +0x2C (char at10[0x2C - 0x10])
//   PlayingAudio:   bool m_isFadingDown +0x44, m_isFadingUp +0x45,
//                   m_isFadingDownFromShroud +0x46, m_isFadingUpFromShroud +0x47, m_at48 +0x48
//   MilesAudioManager: float m_at90 at +0x90
//   declare bool processFade(PlayingAudioRef &playing); in the class
// Remaining diff: xmm allocation only (retail spills elapsed to [ebp+8]).
class Rva00050D86 { public: bool rva00050D86(unsigned char mask); };

// WorldBuilder twin 0x7A0EB0 names it (asserts at lines 11651..11740):
// advances the volume fade toward m_at3C and the fade-down / fade-up time in
// m_at30 by this frame's milliseconds; true while a fade is in progress.
bool MilesAudioManager::processFade(PlayingAudioRef &playing)
{
    PlayingAudio *audio = playing.get();
    if (((Rva00050D86 *)audio)->rva00050D86(4))
        return false;
    const float &frame = m_at90;
    float elapsed = frame;
    if (m_at678 == 0 && frame < 1.0f && audio->m_event->m_viewType == 2)
        elapsed = g_00DBA4FC;
    bool fading = false;
    if (audio->m_at40 > 0.0f) {
        float remaining = audio->m_at40;
        audio->m_at40 -= elapsed;
        if (playing->m_at40 <= 0.0f) {
            playing->m_at40 = 0.0f;
            ((Rva00481FAFFloatSlot *)playing->m_event.operator->())->store(playing->m_at3C);
        } else {
            float volume = playing->m_event->m_extraVolume;
            float delta = volume - playing->m_at3C;
            if (remaining == 0.0f)
                remaining = 1.0f;
            ((Rva00481FAFFloatSlot *)playing->m_event.operator->())->store(volume - delta * (elapsed / remaining));
        }
        fading = true;
    }
    if (playing->m_isFadingDown || playing->m_isFadingDownFromShroud) {
        playing->m_at30 += elapsed;
        if (playing->m_at30 >= (float)m_audioSettings->m_at78) {
            playing->m_at30 = (float)m_audioSettings->m_at78;
            if (!playing->m_isFadingDown)
                playing->m_at48 = true;
            playing->m_isFadingDown = false;
            playing->m_isFadingDownFromShroud = false;
            playing->m_isFadingUp = false;
            playing->m_isFadingUpFromShroud = false;
        }
        return true;
    }
    if (playing->m_isFadingUp || playing->m_isFadingUpFromShroud) {
        playing->m_at30 -= elapsed;
        if (playing->m_at30 <= 0.0f) {
            playing->m_at30 = 0.0f;
            playing->m_isFadingUp = false;
            playing->m_isFadingUpFromShroud = false;
        }
        return true;
    }
    return fading;
}
