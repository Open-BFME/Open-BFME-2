// ?rva00055E6C@MilesAudioManager@@QAE_NABVAsciiString@@HHH@Z
// partial score=0.95 date=2026-10-09
// ?rva00055E6C@MilesAudioManager@@QAE_NABVAsciiString@@HHH@Z 0x55E6C 350B. Body for MilesAudioManager.cpp (decl: bool rva00055E6C(const AsciiString &name, int streamArg, int viewType, int musicSystem);)
#if 0
class Rva000A8B59 { public: bool rva000A8B59(int arg); };
static __forceinline bool rva00055E6CNameMatches(AudioEventRTS *event, const AsciiString &name)
{
    const AsciiString *eventName = reinterpret_cast<const AsciiString *>(reinterpret_cast<Rva002D9AC3 *>(event)->rva002D9AC3());
    return eventName->compare(name) == 0;
}

// Retail 0x00055E6C (address-derived): whether a music stream or stacked music
// of the view type already plays the named event and passes the stream
// predicate 0x A8B59. Playing streams must also match the music system.
bool MilesAudioManager::rva00055E6C(const AsciiString &name, int streamArg, int viewType, int musicSystem)
{
    MilesMutexGuard guard(&m_mutex, 0);
    PlayingAudioRef playing;
    for (PlayingAudioList::iterator it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
        playing = *it;
        if (playing.get() && playing->m_event->m_info->m_atB0 == 0 && playing->m_event->m_viewType == viewType
            && playing->m_event->m_musicSystem == musicSystem
            && rva00055E6CNameMatches(playing->m_event.get(), name)
            && reinterpret_cast<Rva000A8B59 *>(&playing->m_at0C)->rva000A8B59(streamArg))
            return true;
    }
    MusicStack &stack = m_musicStack[viewType][musicSystem];
    for (MusicStack::iterator it = stack.begin(); it != stack.end(); ++it) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        if (playing.get() && playing->m_event->m_info->m_atB0 == 0 && playing->m_event->m_viewType == viewType
            && rva00055E6CNameMatches(playing->m_event.get(), name)
            && reinterpret_cast<Rva000A8B59 *>(&playing->m_at0C)->rva000A8B59(streamArg))
            return true;
    }
    return false;
}

#endif
