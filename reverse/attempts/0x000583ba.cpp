// ?rva000583BA@MilesAudioManager@@QAEXIIH@Z
// partial score=0.85 date=2026-10-09
// Bank 0x583BA (471B) MilesAudioManager view-masked pause. Diff vs HEAD of MilesAudioManager.cpp.
// Remaining: retail keeps the PlayingAudioRef pointer in edi (iterator ebx, viewMask from memory)
// and releases edi at exit without reloading; this build caches viewMask in ebx and the ref in
// eax, reloading at exit. Same family as 0x603ED; /Oa and a const& callee did not change it.
// diff --git a/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp b/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
// index 8efffe88cc..b414066111 100644
// --- a/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
// +++ b/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
// @@ -863,6 +863,7 @@ public:
//      void rva000606CE(bool accelerated);
//      void rva00060123(unsigned int viewMask);
//      void rva00060309(void);
// +    void rva000583BA(unsigned int affect, unsigned int viewMask, int arg);
//      void rva0006047C(void);
//      void rva000544EB(void);
//      void startPendingMusicTracks(void);
// @@ -965,7 +966,8 @@ private:
//      int m_at678;                         // +0x678, compared with event view types
//      char at67C[0x68C - 0x67C];
//      int m_at68C;                         // +0x68C, zeroed by 0x60309
// -    char at690[0x698 - 0x690];
// +    unsigned int m_at690;                // +0x690, view types whose music is paused (0x583BA)
// +    unsigned int m_at694;                // +0x694, the same for affect bit 0x20
//      unsigned int m_at698;                // +0x698, per-view-type bits processAudioCompletion clears
//      unsigned short m_maxAmbientStreams;  // +0x69C
//      char at69E[0x6A4 - 0x69E];
// @@ -2921,6 +2923,71 @@ void MilesAudioManager::rva0005824D(PolygonTrigger *trigger, float level)
//      m_at6AA = true;
//  }
//  
// +// Native 000583BA..00058591. Under the mutex, pauses every sound (affect bit
// +// 0x02), 3D sound (0x04) and stream whose class meets affect in the view
// +// types of viewMask: bit 0x20 marks the playing audio at +0x4A, otherwise
// +// +0x49, then pauseResumeSound applies it. Music (0x10) records the views
// +// at +0x694/+0x690, pending requests are flagged through 0x577E3, and
// +// unless arg is set the per-view masks at +0x6C0/+0x6B4 remember affect.
// +void MilesAudioManager::rva000583BA(unsigned int affect, unsigned int viewMask, int arg)
// +{
// +    MilesMutexGuard guard(&m_mutex, 0);
// +    PlayingAudioRef playing;
// +    PlayingAudioList::iterator it;
// +    if (affect & 0x02) {
// +        for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it) {
// +            playing = *it;
// +            if (playing.get() && (viewMask & (1 << playing->m_event->m_viewType))) {
// +                if (affect & 0x20)
// +                    playing->m_at4A = true;
// +                else
// +                    playing->m_at49 = true;
// +                pauseResumeSound(playing);
// +            }
// +        }
// +    }
// +    if (affect & 0x04) {
// +        for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); ++it) {
// +            playing = *it;
// +            if (playing.get() && (viewMask & (1 << playing->m_event->m_viewType))) {
// +                if (affect & 0x20)
// +                    playing->m_at4A = true;
// +                else
// +                    playing->m_at49 = true;
// +                pauseResumeSound(playing);
// +            }
// +        }
// +    }
// +    for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
// +        playing = *it;
// +        if (playing.get() && (viewMask & (1 << playing->m_event->m_viewType))
// +            && (playing->m_event->getSoundClass() & affect)) {
// +            if (affect & 0x20)
// +                playing->m_at4A = true;
// +            else
// +                playing->m_at49 = true;
// +            pauseResumeSound(playing);
// +        }
// +    }
// +    if (affect & 0x10) {
// +        if (affect & 0x20)
// +            m_at694 |= viewMask;
// +        else
// +            m_at690 |= viewMask;
// +    }
// +    rva000577E3(affect, viewMask, true);
// +    if (!arg) {
// +        for (int viewType = 0; viewType < 3; ++viewType) {
// +            if (viewMask & (1 << viewType)) {
// +                if (affect & 0x20)
// +                    m_at6C0[viewType] |= affect & ~0x20;
// +                else
// +                    m_at6B4[viewType] |= affect;
// +            }
// +        }
// +    }
// +}
// +
//  // Retail 0x000606CE, called from onAudioLODChanged (0x607BB) and 0x61A2E.
//  // With a provider selected it releases every playing 3D sound under the
//  // mutex and unselects it, then reselects through 0x604A3 and, if that found
