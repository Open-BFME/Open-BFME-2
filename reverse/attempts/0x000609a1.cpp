// ?rva000609A1@MilesAudioManager@@QAEXABVAsciiString@@H@Z
// partial score=0.81 date=2026-10-09
// Bank: MilesAudioManager 0x609A1 (876B), Zero Hour removePlayingAudio(eventName) + view type.
// Insert into MilesAudioManager.cpp with: decl void rva000609A1(const AsciiString&, int) in the class.
// Remaining (similarity 0.81): register allocation in the three list sweeps -- retail keeps
// the first list in edi and reloads the ref into ecx; in sweeps 2/3 it addresses the list
// via ebx+off and caches the ref pointer in edi. Name compare must be operator== (getter first).
// diff --git a/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp b/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
// index 8efffe88cc..877f1de820 100644
// --- a/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
// +++ b/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
// @@ -862,6 +862,7 @@ public:
//      void rva0005452B(void);
//      void rva000606CE(bool accelerated);
//      void rva00060123(unsigned int viewMask);
// +    void rva000609A1(const AsciiString &eventName, int viewType);
//      void rva00060309(void);
//      void rva0006047C(void);
//      void rva000544EB(void);
// @@ -2921,6 +2922,114 @@ void MilesAudioManager::rva0005824D(PolygonTrigger *trigger, float level)
//      m_at6AA = true;
//  }
//  
// +// The event info's name getter is its vtable slot 1.
// +class Rva000609A1InfoName
// +{
// +public:
// +    virtual void slot0();
// +    virtual const AsciiString &name() const;
// +};
// +
// +static inline const AsciiString &audioEventName(const AudioEventRTS *event)
// +{
// +    return reinterpret_cast<const Rva000609A1InfoName *>(event->m_info)->name();
// +}
// +
// +// Rowed single-element erase of the +0xE0 queued-event vectors (0x000554A9).
// +class Rva000554A9 { public: void *rva000554A9(void *where); };
// +
// +// Native 000609A1..00060D0D. Zero Hour's removePlayingAudio(eventName) for
// +// one view type: under the mutex, playing sounds, 3D sounds and streams of
// +// that event give their Miles handles back and leave their lists, its
// +// entries leave both music stacks, its queued copies unmap their handles
// +// and go, and pending requests for it are dropped (set entries deleted,
// +// queued ones only unlinked).
// +void MilesAudioManager::rva000609A1(const AsciiString &eventName, int viewType)
// +{
// +    MilesMutexGuard guard(&m_mutex, 0);
// +    PlayingAudioRef playing;
// +    OpaqueRefList::iterator it;
// +
// +    it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).begin();
// +    while (it != reinterpret_cast<OpaqueRefList &>(m_playingSounds).end()) {
// +        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
// +        if (playing.get() && audioEventName(playing->m_event.get()) == eventName
// +            && playing->m_event->m_viewType == viewType) {
// +            releaseMilesHandles(*playing.get());
// +            it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).erase(it);
// +        } else {
// +            ++it;
// +        }
// +    }
// +    it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).begin();
// +    while (it != reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).end()) {
// +        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
// +        if (playing.get() && audioEventName(playing->m_event.get()) == eventName
// +            && playing->m_event->m_viewType == viewType) {
// +            releaseMilesHandles(*playing.get());
// +            it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(it);
// +        } else {
// +            ++it;
// +        }
// +    }
// +    it = reinterpret_cast<OpaqueRefList &>(m_playingStreams).begin();
// +    while (it != reinterpret_cast<OpaqueRefList &>(m_playingStreams).end()) {
// +        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
// +        if (playing.get() && audioEventName(playing->m_event.get()) == eventName
// +            && playing->m_event->m_viewType == viewType) {
// +            releaseMilesHandles(*playing.get());
// +            it = reinterpret_cast<OpaqueRefList &>(m_playingStreams).erase(it);
// +        } else {
// +            ++it;
// +        }
// +    }
// +
// +    for (int musicSystem = 0; musicSystem < 2; ++musicSystem) {
// +        MusicStack &stack = m_musicStack[viewType][musicSystem];
// +        MusicStack::iterator entry = stack.begin();
// +        while (entry != stack.end()) {
// +            playing = *reinterpret_cast<const PlayingAudioRef *>(&*entry);
// +            if (playing.get() && audioEventName(playing->m_event.get()) == eventName
// +                && playing->m_event->m_viewType == viewType)
// +                entry = stack.erase(entry);
// +            else
// +                ++entry;
// +        }
// +    }
// +
// +    QueuedAudioEvents &queued = m_queuedEvents[viewType];
// +    QueuedAudioEvents::iterator event = queued.begin();
// +    while (event != queued.end()) {
// +        if (audioEventName(reinterpret_cast<const AudioEventRTS *>(&*event)) == eventName) {
// +            unmapPhysicalHandle(event->m_playingHandle);
// +            event = (QueuedAudioEvents::iterator)reinterpret_cast<Rva000554A9 *>(&queued)->rva000554A9(event);
// +        } else {
// +            ++event;
// +        }
// +    }
// +
// +    Rva00051107AudioRequestSet::iterator pending;
// +    for (pending = m_requestSet.begin(); pending != m_requestSet.end(); ) {
// +        Rva00051107AudioRequest *req = *pending;
// +        if (req->m_pendingEvent.get() && audioEventName(req->m_pendingEvent.get()) == eventName) {
// +            Rva00051107AudioRequestSet::iterator victim = pending++;
// +            m_requestSet.erase(victim);
// +            deleteAudioRequest(req);
// +        } else {
// +            ++pending;
// +        }
// +    }
// +    Rva00051107AudioRequestList::iterator queuedReq = m_audioRequests.begin();
// +    while (queuedReq != m_audioRequests.end()) {
// +        Rva00051107AudioRequest *req = *queuedReq;
// +        if (req->m_request == 0 && req->m_pendingEvent.get()
// +            && audioEventName(req->m_pendingEvent.get()) == eventName)
// +            queuedReq = m_audioRequests.erase(queuedReq);
// +        else
// +            ++queuedReq;
// +    }
// +}
// +
//  // Retail 0x000606CE, called from onAudioLODChanged (0x607BB) and 0x61A2E.
//  // With a provider selected it releases every playing 3D sound under the
//  // mutex and unselects it, then reselects through 0x604A3 and, if that found
