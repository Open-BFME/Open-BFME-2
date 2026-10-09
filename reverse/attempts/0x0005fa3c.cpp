// ?rva0005FA3C@MilesAudioManager@@QAEXI@Z
// partial score=0.86 date=2026-10-09
// NEAR bank for retail 0x0005FA3C (910 bytes) ?rva0005FA3C@MilesAudioManager@@QAEXI@Z
// Body for MilesAudioManager.cpp (defined after processRequest; e.g. before
// releaseMilesHandles). Needs in the unit:
//  - AudioEventRTS: int m_at80 at +0x80 (hold count; 0x000562CF adds one)
//  - BfmeStringTailRecord144: int m_at80 at +0x80 and bool m_at8C at +0x8C
//  - the 0x00055951 lookup defined in-unit before this body (so cl knows the
//    find's hidden return slot does not escape; then the request-set part
//    keeps the node in ecx as retail does) -- verified exact in-unit with
//    the unit's /EHsc flags
//  - the visible inline PlayingAudioRef::operator= (same as for 0x00055FCA)
// Blocker: loop 1 (streams) releases its PlayingAudioRef copy after
// processAudioCompletion(playing) from esi without reload; cl does that only
// when processAudioCompletion and every callee it hands the reference to are
// already compiled in the unit: startNextLoop and rva00059CE6 moved above it
// and checkForNaturalSoundCompletion (0x0005DD40, unrowed, banked partial)
// defined above it. With a dummy 0x5DD40 body above processAudioCompletion
// the only remaining diff is loop 1's found-block placement (retail sinks it
// after loop 2; an if(count<=0){...}else return; form gets that layout but
// then cl enregisters the handle in edi). blocked-on=0x0005DD40
// Retail 0x0005FA3C (910 bytes; WorldBuilder twin 0x00792D90 logs it as
// "Processing stop handle request"): the stop request for one playing
// handle (processRequest case 1). Handles below 5 are never live. Each
// match drops one hold (+0x80) and stops only once none is left: a stream
// is flagged (+0x4C) and completed unless its info defers that (bit 0x10)
// a 2D or 3D sound is flagged; then per view type a queued event is flagged
// (+0x8C) the active music stream reference is cleared and a stacked
// track is erased from its music stack; a pending request found in the
// request set through 0x00055951 is erased and deleted and so is every
// queued play request (type 0) for the handle.
void MilesAudioManager::rva0005FA3C(unsigned int handle)
{
    if (handle < 5)
        return;

    PlayingAudioList::iterator it;
    for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
        PlayingAudioRef playing = *it;
        if (!playing.get())
            continue;
        if (playing->m_event->m_playingHandle == handle) {
            --playing->m_event->m_at80;
            if (playing->m_event->m_at80 > 0)
                return;
            playing->m_event->m_at4C = true;
            if (!(playing->m_event->getAudioEventInfo()->m_control & 0x10))
                processAudioCompletion(playing);
            break;
        }
    }
    for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it) {
        PlayingAudioRef playing = *it;
        if (!playing.get())
            continue;
        if (playing->m_event->m_playingHandle == handle) {
            --playing->m_event->m_at80;
            if (playing->m_event->m_at80 > 0)
                return;
            playing->m_event->m_at4C = true;
            break;
        }
    }
    for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); ++it) {
        PlayingAudioRef playing = *it;
        if (!playing.get())
            continue;
        if (playing->m_event->m_playingHandle == handle) {
            --playing->m_event->m_at80;
            if (playing->m_event->m_at80 > 0)
                return;
            playing->m_event->m_at4C = true;
            break;
        }
    }

    for (int viewType = 0; viewType < 3; ++viewType) {
        QueuedAudioEvents::iterator event;
        for (event = m_queuedEvents[viewType].begin(); event != m_queuedEvents[viewType].end(); ++event) {
            if (event->m_playingHandle == handle) {
                --event->m_at80;
                if (event->m_at80 > 0)
                    return;
                event->m_at8C = true;
                break;
            }
        }
        PlayingAudioRef &music = m_playingMusic[viewType];
        if (music.get() && music->m_event->m_playingHandle == handle) {
            --music->m_event->m_at80;
            if (music->m_event->m_at80 > 0)
                return;
            reinterpret_cast<Rva000A8C9B *>(&music)->clear();
        }
        for (int musicSystem = 0; musicSystem < 2; ++musicSystem) {
            MusicStack &stack = m_musicStack[viewType][musicSystem];
            for (MusicStack::iterator music = stack.begin(); music != stack.end(); ++music) {
                PlayingAudioRef &track = reinterpret_cast<PlayingAudioRef &>(*music);
                if (track.get() && track->m_event->m_playingHandle == handle) {
                    --track->m_event->m_at80;
                    if (track->m_event->m_at80 > 0)
                        return;
                    stack.erase(music);
                    break;
                }
            }
        }
    }

    {
        Rva00054EBETable::iterator found =
            reinterpret_cast<Rva00055951 &>(m_requestSet).rva00055951(handle);
        if (found._M_cur) {
            Rva00051107AudioRequest *req = *reinterpret_cast<Rva00051107AudioRequestSet::iterator &>(found);
            --req->m_pendingEvent->m_at80;
            if (req->m_pendingEvent->m_at80 > 0)
                return;
            reinterpret_cast<Rva00051B89KeyedSet &>(m_requestSet).erase(
                reinterpret_cast<Rva00051B89KeyedSet::iterator &>(found));
            deleteAudioRequest(req);
        }
    }

    Rva00051107AudioRequestList::iterator request = m_audioRequests.begin();
    while (request != m_audioRequests.end()) {
        Rva00051107AudioRequest *req = *request;
        if (req && req->m_request == 0) {
            bool match = req->m_pendingEvent.get()
                ? req->m_pendingEvent->m_playingHandle == handle
                : req->m_at08 == handle;
            if (match) {
                if (req->m_pendingEvent.get())
                    --req->m_pendingEvent->m_at80;
                if (req->m_pendingEvent.get() && req->m_pendingEvent->m_at80 > 0)
                    return;
                deleteAudioRequest(req);
                request = m_audioRequests.erase(request);
                continue;
            }
        }
        ++request;
    }
}
