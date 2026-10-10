// ?removePlayingAudio@MilesAudioManager@@UAEXABVAsciiString@@H@Z
// partial score=0.98 date=2026-10-10
// ?removePlayingAudio@MilesAudioManager@@UAEXABVAsciiString@@H@Z
// banked 2026-10-10: 889B vs 876B; loops 1-3 (audio-local), queued,
// request-set/list and epilogue all exact (tail reconverges at +13,
// all non-reloc bytes match). Sole residue: music-stack loop emits
// in ecx (mov ecx,eax) + a peeled first-compare in the outer body
// vs retail eax (imul eax) + plain jmp to inner-top. Tried ptr+do-while
// +countdown (correct control: add-stack/dec/jne-near match), ref+for,
// per-iter end, named end, barrier, const/const_iterator, volatile.
// Needs: slot26 rename + BfmeStringTailRecord144::m_info from
// MilesAudioManager.cpp. Requires MilesAudioManager receiver.
// AudioEventInfo's slot-1 event-name getter (0x000609A1's compares go
// through it); the view keeps the vtable use out of AudioEventInfo itself.
class BfmeAudioEventInfoNameView {
public:
    virtual void slot0();
    virtual const AsciiString &getEventName(void) const;
};
static __forceinline const AsciiString &bfmeEventName(const AudioEventInfo *info)
{
    return reinterpret_cast<const BfmeAudioEventInfoNameView *>(info)->getEventName();
}

// The queued-event vector's single erase, rowed under an address name.
class Rva000554A9 { public: void *rva000554A9(void *position); };

// Retail 0x000609A1 (876 bytes, vftable slot 26): Zero Hour's
// removePlayingAudio by event name, limited to one view type. BFME 2 also
// drops the name from that view's two music stacks and queued events
// (unmapping their handles), from the pending request set (deleting those
// requests) and from the request list's pending plays.
void MilesAudioManager::removePlayingAudio(const AsciiString &eventName, int viewType)
{
    MilesMutexGuard guard(&m_mutex, 0);
    PlayingAudioRef playing;
    PlayingAudio *audio;
    OpaqueRefList::iterator it;

    it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playingSounds).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        audio = playing.get();
        if (audio && bfmeEventName(audio->m_event->m_info) == eventName
            && audio->m_event->m_viewType == viewType) {
            releaseMilesHandles(*audio);
            it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).erase(it);
        } else {
            ++it;
        }
    }
    it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        audio = playing.get();
        if (audio && bfmeEventName(audio->m_event->m_info) == eventName
            && audio->m_event->m_viewType == viewType) {
            releaseMilesHandles(*audio);
            it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(it);
        } else {
            ++it;
        }
    }
    it = reinterpret_cast<OpaqueRefList &>(m_playingStreams).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playingStreams).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        audio = playing.get();
        if (audio && bfmeEventName(audio->m_event->m_info) == eventName
            && audio->m_event->m_viewType == viewType) {
            releaseMilesHandles(*audio);
            it = reinterpret_cast<OpaqueRefList &>(m_playingStreams).erase(it);
        } else {
            ++it;
        }
    }

    for (int musicSystem = 0; musicSystem < 2; ++musicSystem) {
        MusicStack &stack = m_musicStack[viewType][musicSystem];
        MusicStack::iterator music = stack.begin();
        while (music != stack.end()) {
            playing = *reinterpret_cast<const PlayingAudioRef *>(&*music);
            audio = playing.get();
            if (audio && bfmeEventName(audio->m_event->m_info) == eventName
                && audio->m_event->m_viewType == viewType) {
                music = stack.erase(music);
            } else {
                ++music;
            }
        }
    }

    QueuedAudioEvents &queued = m_queuedEvents[viewType];
    QueuedAudioEvents::iterator event = queued.begin();
    while (event != queued.end()) {
        if (bfmeEventName(event->m_info) == eventName) {
            unmapPhysicalHandle(event->m_playingHandle);
            event = (QueuedAudioEvents::iterator)reinterpret_cast<Rva000554A9 &>(queued).rva000554A9(event);
        } else {
            ++event;
        }
    }

    Rva00051107AudioRequestSet::iterator pending;
    pending = m_requestSet.begin();
    while (pending != m_requestSet.end()) {
        if ((*pending)->m_pendingEvent.get()
            && bfmeEventName((*pending)->m_pendingEvent->m_info) == eventName) {
            Rva00051107AudioRequestSet::iterator doomed = pending;
            ++pending;
            Rva00051107AudioRequest *request = *doomed;
            reinterpret_cast<Rva00051B89KeyedSet &>(m_requestSet).erase(
                reinterpret_cast<Rva00051B89KeyedSet::iterator &>(doomed));
            deleteAudioRequest(request);
        } else {
            ++pending;
        }
    }

    Rva00051107AudioRequestList::iterator request = m_audioRequests.begin();
    while (request != m_audioRequests.end()) {
        if ((*request)->m_request == 0 && (*request)->m_pendingEvent.get()
            && bfmeEventName((*request)->m_pendingEvent->m_info) == eventName) {
            request = m_audioRequests.erase(request);
        } else {
            ++request;
        }
    }
}
