// ?rva00055FCA@MilesAudioManager@@QAE_NIPAPAVAudioEventRTS@@PAVPlayingAudioRef@@@Z
// partial score=0.85 date=2026-10-09
// Banked body for MilesAudioManager.cpp (retail 0x00055FCA, 628B): BFME 2's
// isCurrentlyPlaying(handle) with outputs. Change the declaration to
// rva00055FCA(unsigned int, AudioEventRTS **, PlayingAudioRef *), make the two
// callers (0x562A2/0x562CF) use AudioEventRTS *result, drop the old symbols.csv
// pin. Structure and calls match; retail keeps the handle memory-homed (the
// early `handle < 5` exit precedes push edi) and holds the PlayingAudio
// pointer in edi, while this source enregisters the handle in edi.
// 0x00055951 needs a pin (rowless set lookup by handle).
// The pending set's lookup by playing handle (0x00055951): it builds a key
// request carrying the handle and finds it. Rowless; called on the set.
class Rva00055951 {
public:
    Rva00051107AudioRequestSet::iterator rva00055951(unsigned int handle);
};

// Retail 0x00055FCA: Zero Hour's isCurrentlyPlaying(handle) with outputs.
// Handles below 5 are never live. Looks through the playing lists, then per
// view type the queued events and both music stacks, then the request list's
// pending events and the pending request set; reports the event (and, for a
// playing sound, a reference to it).
bool MilesAudioManager::rva00055FCA(unsigned int handle, AudioEventRTS **eventOut, PlayingAudioRef *playingOut)
{
    if (eventOut)
        *eventOut = 0;
    if (playingOut)
        reinterpret_cast<Rva000A8C9B *>(playingOut)->clear();
    if (handle < 5)
        return false;

    PlayingAudioRef playing;
    OpaqueRefList::iterator it;
    for (it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).begin();
         it != reinterpret_cast<OpaqueRefList &>(m_playingSounds).end(); ++it) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        if (playing.get() && playing->m_event->m_playingHandle == handle) {
            if (eventOut)
                *eventOut = playing->m_event.get();
            if (playingOut)
                *playingOut = playing;
            return true;
        }
    }
    for (it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).begin();
         it != reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).end(); ++it) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        if (playing.get() && playing->m_event->m_playingHandle == handle) {
            if (eventOut)
                *eventOut = playing->m_event.get();
            if (playingOut)
                *playingOut = playing;
            return true;
        }
    }
    for (it = reinterpret_cast<OpaqueRefList &>(m_playingStreams).begin();
         it != reinterpret_cast<OpaqueRefList &>(m_playingStreams).end(); ++it) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        if (playing.get() && playing->m_event->m_playingHandle == handle) {
            if (eventOut)
                *eventOut = playing->m_event.get();
            if (playingOut)
                *playingOut = playing;
            return true;
        }
    }

    for (int viewType = 0; viewType < 3; ++viewType) {
        QueuedAudioEvents::iterator event;
        for (event = m_queuedEvents[viewType].begin(); event != m_queuedEvents[viewType].end(); ++event) {
            if (event->m_playingHandle == handle) {
                if (eventOut)
                    *eventOut = reinterpret_cast<AudioEventRTS *>(&*event);
                return true;
            }
        }
        for (int musicSystem = 0; musicSystem < 2; ++musicSystem) {
            MusicStack::iterator music;
            for (music = m_musicStack[viewType][musicSystem].begin();
                 music != m_musicStack[viewType][musicSystem].end(); ++music) {
                playing = *reinterpret_cast<const PlayingAudioRef *>(&*music);
                if (playing.get() && playing->m_event->m_playingHandle == handle) {
                    if (eventOut)
                        *eventOut = playing->m_event.get();
                    if (playingOut)
                        *playingOut = playing;
                    return true;
                }
            }
        }
    }

    Rva00051107AudioRequestList::iterator request;
    for (request = m_audioRequests.begin(); request != m_audioRequests.end(); ++request) {
        if (*request && (*request)->m_pendingEvent.get()
            && (*request)->m_pendingEvent->m_playingHandle == handle) {
            if (eventOut)
                *eventOut = (*request)->m_pendingEvent.get();
            return true;
        }
    }

    Rva00051107AudioRequestSet::iterator pending =
        reinterpret_cast<Rva00055951 &>(m_requestSet).rva00055951(handle);
    if (pending != m_requestSet.end()) {
        if (eventOut)
            *eventOut = (*pending)->m_pendingEvent.get();
        return true;
    }
    return false;
}

