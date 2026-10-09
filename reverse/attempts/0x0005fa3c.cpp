// ?rva0005FA3C@MilesAudioManager@@QAEXI@Z
// partial score=0.91 date=2026-10-09
// ?rva0005FA3C@MilesAudioManager@@QAEXI@Z
// NEAR bank score=0.91 date=2026-10-09 (helper mam5, claude-opus-5-5)
// Insert into build/scratch_agents/mam5/MilesAudioManager.cpp (which already
// defines checkForNaturalSoundCompletion 0x5DD40 above processAudioCompletion
// and the in-class noinline BfmePoolRef10 copy ctor) before
// "// Retail 0x0005FDCA"; it also needs BfmeStringTailRecord144 m_at80 (+0x80)
// and m_at8C (+0x8C) and 0x00055951 defined in-unit (mk.py rec144=1 move55951=1).
// Findings this round:
//  - With the real 0x5DD40 body in the unit the stream loop already releases
//    its copy straight from esi; moving startNextLoop/rva00059CE6 above
//    processAudioCompletion is NOT needed (identical output either way).
//    deleteAudioRequest (0x527C7) in-unit changes nothing.
//  - This body (early-return form) differs only in where loop 1's found block
//    sits: cl places it right after loop 1 with jle; retail places it after
//    loop 2's body with jg to the release+return block (shared with loop 2).
//  - WorldBuilder's shape (if (count <= 0) { ...; break; } else return;) in
//    loop 1 gives retail's block layout (jg) but then cl enregisters handle
//    in edi from the entry (mov edi,[ebp+8]; cmp edi,5) swaps loop 1's
//    iterator/ref registers and CSEs &playing->m_event (score 0.90).
//    Tried: break inside/after the if; no else; per-loop iterators;
//    iterator declared before the handle test; post-increment; direct-init
//    copy; == operand order; WB-shaped music slot / request list / loops 2-3;
//    all leave handle in edi.
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
