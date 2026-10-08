// ?putPlayingMusicOnStack@MilesAudioManager@@QAEXHH@Z
// partial score=0.93 date=2026-10-09
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Apply this body to the Miles unit; the include supplies its landed views.
#include "../../Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp"

// WorldBuilder's putPlayingMusicOnStack (MilesAudioManager.cpp:7431 assert),
// retail 0x0005A812 (246 bytes). A playing track of the view type goes onto
// its own music system's stack and its slot is cleared; otherwise the stream
// found for the active system (0x0005442A) is stacked and, unless arg is
// zero, stopped and taken off the playing streams. The stacked copy is the
// counted Rva0036CA00Str form: out-of-line copy 0x000A8C7C and an
// unconditional release (no null test) at scope end.
void MilesAudioManager::putPlayingMusicOnStack(int viewType, int arg)
{
    MusicSystem activeMusicSystem = m_activeMusicSystem[viewType];
    PlayingAudioRef &music = m_playingMusic[viewType];
    if (music.get()) {
        MusicSystem musicSystem = music->m_event->m_musicSystem;
        ((Rva00058B90 *)&m_musicStack[viewType][musicSystem])->rva00058B90(*(const Rva0036CA00Str *)&music);
        ((Rva000A8C9B *)&music)->clear();
        return;
    }
    PlayingAudioList::iterator it;
    it = rva0005442A(viewType, activeMusicSystem, 1);
    if (it != m_playingStreams.end()) {
        const Rva0036CA00Str ref(*reinterpret_cast<const Rva0036CA00Str *>(&*it));
        ((Rva00058B90 *)&m_musicStack[viewType][activeMusicSystem])->rva00058B90(ref);
        PlayingAudio *playing = ref.get();
        playing->m_at45 = false;
        if (!arg) {
            playing->at44[0] = 1;
        } else {
            playing->at44[0] = 0;
            ((MilesStreamRef *)&playing->m_at0C)->rva000A8AC0();
            playing->m_at30 = (float)m_audioSettings->m_at78;
            reinterpret_cast<OpaqueRefList &>(m_playingStreams).erase(
                OpaqueRefList::iterator((OpaqueRefList::_Node *)it._M_node));
        }
    }
}
