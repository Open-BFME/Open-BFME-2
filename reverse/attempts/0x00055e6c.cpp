// ?rva00055E6C@MilesAudioManager@@QAE_NABVAsciiString@@HHH@Z
// partial score=0.99 date=2026-10-10
// ?rva00055E6C@MilesAudioManager@@QAE_NABVAsciiString@@HHH@Z
// banked 2026-10-10: 352B vs 350B, loop1+loop2-body exact, sole residue
// is the loop2 prologue address form (add eax,0x10 + mov esi,eax vs
// retail lea esi,[eax+0x10]); needs decl + Rva000A8B59/Rva002D9AC3 views
// from MilesAudioManager.cpp. Requires MilesAudioManager receiver.
// Retail 0x00055E6C (350 bytes): whether a music stream or stacked music of
// the view type already plays the named event and passes the stream
// predicate 0xA8B59. Playing streams must also match the music system.
static __forceinline bool rva00055E6CNameMatches(AudioEventRTS *event, const AsciiString &name)
{
    const AsciiString *eventName = reinterpret_cast<const AsciiString *>(reinterpret_cast<Rva002D9AC3 *>(event)->rva002D9AC3());
    return eventName->compare(name) == 0;
}

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
    const MusicStack &stack = m_musicStack[viewType][musicSystem];
    MusicStack::const_iterator music;
    for (music = stack.begin(); music != stack.end(); ++music) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*music);
        if (playing.get() && playing->m_event->m_info->m_atB0 == 0 && playing->m_event->m_viewType == viewType
            && rva00055E6CNameMatches(playing->m_event.get(), name)
            && reinterpret_cast<Rva000A8B59 *>(&playing->m_at0C)->rva000A8B59(streamArg))
            return true;
    }
    return false;
}
