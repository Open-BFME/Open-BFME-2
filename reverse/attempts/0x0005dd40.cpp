// ?checkForNaturalSoundCompletion@MilesAudioManager@@QAEXAAVPlayingAudioRef@@@Z
// partial score=0.8 date=2026-10-08
// Bank for 0x0005DD40 MilesAudioManager::checkForNaturalSoundCompletion (605 B, 627 compiled).
// Apply as a patch to Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
// at the base below; it adds the AudioEventRTS/PlayingAudio members the body needs.
// base: b09365e8f857e5c34c7b7eab68bc27f6c2b627a7
#if 0
diff --git a/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp b/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
index c351bf76e3..a771a7ad89 100644
--- a/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
+++ b/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
@@ -147,6 +147,26 @@ struct AudioEventInfo {
     _STL::vector<AudioEventChannelVolume> m_channelVolumes;  // +0xB8
 };
 
+// Owning AudioEventRTS reference (its refcount base sits at event +0x88);
+// the ledger's established name, assignment rowed at 0x00051971 and copy
+// constructor at 0x00051950.
+struct BfmePoolHolder88;
+class AudioEventRTS;
+
+class BfmePoolRef10 {
+public:
+    BfmePoolRef10() : m_ptr(0) {}
+    BfmePoolRef10(const BfmePoolRef10 &other);
+    inline ~BfmePoolRef10();
+    AudioEventRTS *operator->(void) const { return m_ptr; }
+    AudioEventRTS *get(void) const { return m_ptr; }
+    BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
+    void rva00053D26(BfmePoolHolder88 *p);  // assign from a raw event (0x00053D26)
+    void rva000519BD(void);                 // release then null (0x000519BD)
+private:
+    AudioEventRTS *m_ptr;
+};
+
 class AudioEventRTS {
 public:
     bool isPositionalAudio(void) const;
@@ -154,6 +174,9 @@ public:
     unsigned int getSoundClass(void) const;
     bool hasMoreLoops(void) const;
     void rva002D9ADC(void);
+    // WorldBuilder names; both are inline in retail.
+    void decrementNumberOfEventsNeedingToBeDoneBeforeReplaying(void) { --m_at14; }
+    void setNumberOfTimesToPlayMusicOrMultisound(int times) { m_at7C = times; }
     void advanceNextPlayPortion(void);
     // Inline in WorldBuilder too (its twin copies the read into a temp);
     // putFileIntoLoopBuffer's first reads go through it into a register.
@@ -164,7 +187,9 @@ public:
     char at00[0x08];
     AudioEventInfo *m_info;  // +0x08 (owning ref in WB)
     int m_playingHandle;     // +0x0C, copied into a requeued loop's request
-    char at10[0x30 - 0x10];
+    BfmePoolRef10 m_at10;    // +0x10, the event waiting on this one (0x002D9AD4 sets it)
+    int m_at14;              // +0x14, events still to finish before it replays
+    char at18[0x30 - 0x18];
     int m_viewType;          // +0x30
     char at34[0x38 - 0x34];
     int m_ownerType;         // +0x38, 2 when object-owned (getObjectID's test)
@@ -178,21 +203,13 @@ public:
     char at68[0x74 - 0x68];
     int m_portionToPlayNext; // +0x74, the portion advanceNextPlayPortion steps
     MusicSystem m_musicSystem; // +0x78
+    int m_at7C;              // +0x7C, plays left; -12345 repeats for ever
+    char at80[0x84 - 0x80];
+    AsciiString m_at84;      // +0x84
+    OpaqueRefCounted m_ref;  // +0x88
 };
 
-// Owning AudioEventRTS reference (its refcount base sits at event +0x88);
-// the ledger's established name, assignment rowed at 0x00051971.
-struct BfmePoolHolder88;
-
-class BfmePoolRef10 {
-public:
-    AudioEventRTS *operator->(void) const { return m_ptr; }
-    BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
-    void rva00053D26(BfmePoolHolder88 *p);  // assign from a raw event (0x00053D26)
-    void rva000519BD(void);                 // release then null (0x000519BD)
-private:
-    AudioEventRTS *m_ptr;
-};
+inline BfmePoolRef10::~BfmePoolRef10() { if (m_ptr) m_ptr->m_ref.Release_Ref(); }
 
 // Open audio file the holder below points at. WorldBuilder names its getters
 // (OpenAudioFile::getMilesSoundInfo, getFileImage): the file name sits at +0,
@@ -251,11 +268,16 @@ struct PlayingAudio {
     int m_at38;                          // +0x38, area index 0x55C5D starts from
     float m_at3C;                        // +0x3C, extra volume handed to a requeued loop
     float m_at40;                        // +0x40, cleared once that volume is handed on
-    char at44[0x49 - 0x44];
+    bool m_at44;                         // +0x44
+    char at45;
+    bool m_at46;                         // +0x46
+    char at47;
+    bool m_at48;                         // +0x48
     bool m_at49;                         // +0x49
     bool m_at4A;                         // +0x4A
     bool m_at4B;                         // +0x4B, set by 0x000535A6
-    char at4C[0x4E - 0x4C];
+    char at4C;
+    bool m_at4D;                         // +0x4D, completion check: event +0x84 name is set
     bool m_at4E;                         // +0x4E, m_at24 holds a position
 };
 
@@ -284,6 +306,19 @@ private:
     PlayingAudio *m_ptr;
 };
 
+// WorldBuilder's free comparison (inline in retail): same referent.
+inline bool operator==(const PlayingAudioRef &left, const PlayingAudioRef &right)
+{
+    return left.get() == right.get();
+}
+
+// Assignment of the event's +0x10 reference, rowed at 0x002D9AD4 under an
+// address-derived owner.
+class Rva002D9AD4 {
+public:
+    BfmePoolRef10 &rva002D9AD4(const BfmePoolRef10 &other);
+};
+
 // Retail 0x00051914, which ICF shares with AudioEventInfoRef's constructor;
 // the loop-buffer thread (0x0005EFE9) builds one from a buffer's playing audio.
 PlayingAudioRef::PlayingAudioRef(PlayingAudio *playing) : m_ptr(playing)
@@ -809,6 +844,9 @@ public:
     // WorldBuilder name (retail 0x0005DD40).
     void checkForNaturalSoundCompletion(PlayingAudioRef &playing);
     void rva0005EFE9(void);
+    // WorldBuilder's addOrResumeAudioEvent; MilesAudioManagerSmallSlots.cpp
+    // calls it under this address-derived spelling.
+    void rva0005D734(int event, int a, int b, int c, int d);
     void putPlayingMusicOnStack(int viewType, int arg);
     void rva00059CE6(PlayingAudioRef &looping);
     void rva0005AA72(PlayingAudioRef &playing);
@@ -851,7 +889,7 @@ private:
     PlayingAudioList m_playingStreams;   // +0xA48
     MusicStack m_musicStack[3][2];       // +0xA4C
     MusicSystem m_activeMusicSystem[3];  // +0xB3C
-    char atB48[0xB54 - 0xB48];
+    PlayingAudioRef m_pushPopPendingMusicTrack[3];  // +0xB48 (WB assert name)
     _STL::vector<AudioTriggerArea> m_triggerAreas;  // +0xB54, scanned by 0x55C5D
     char atB60[0xB8C - 0xB60];
     AudioFileCache *m_audioFileCache;    // +0xB8C (WorldBuilder requestFile receiver)
@@ -1044,6 +1082,94 @@ void MilesAudioManager::cleanUpLoopBuffer(LoopBuffer *buffer)
     buffer->m_at10 = false;
 }
 
+// Retail 0x0005DD40 (WorldBuilder twin 0x0079B840, asserts at its lines
+// 10100..10113): once a sound, stream or music track stops on its own, lets
+// the event waiting on it (+0x10) replay when it was the last one pending.
+// Multisounds and unknown types are only reported in WorldBuilder.
+void MilesAudioManager::checkForNaturalSoundCompletion(PlayingAudioRef &playing)
+{
+    if (playing->m_event->m_at84.isEmpty() && playing->m_event->m_at10.get() == 0)
+        return;
+    if (playing->m_event->m_at4C)
+        return;
+
+    bool foundPlaying = false;
+    bool foundOnStack = false;
+    bool foundPending = false;
+    PlayingAudioList::iterator it;
+    PlayingAudioList::iterator end;
+    int viewType;
+    int type = playing->m_event->getAudioEventInfo()->m_atB0;
+    switch (type) {
+    case 0:
+    case 1:
+    case 4:
+        it = m_playingStreams.begin();
+        end = m_playingStreams.end();
+        while (!foundPlaying && it != end) {
+            foundPlaying = (*it == playing);
+            ++it;
+        }
+        if (type == 0) {
+            viewType = playing->m_event->m_viewType;
+            MusicSystem musicSystem = playing->m_event->m_musicSystem;
+            MusicStack::iterator stackIt = m_musicStack[viewType][musicSystem].begin();
+            MusicStack::iterator stackEnd = m_musicStack[viewType][musicSystem].end();
+            while (!foundOnStack && stackIt != stackEnd) {
+                foundOnStack = (reinterpret_cast<PlayingAudioRef &>(*stackIt) == playing);
+                ++stackIt;
+            }
+            foundPending = (m_pushPopPendingMusicTrack[viewType] == playing);
+        }
+        if (!foundPlaying && !foundPending && !foundOnStack)
+            return;
+        break;
+    case 2:
+        it = m_playingSounds.begin();
+        end = m_playingSounds.end();
+        while (!foundPlaying && it != end) {
+            foundPlaying = (*it == playing);
+            ++it;
+        }
+        it = m_playing3DSounds.begin();
+        end = m_playing3DSounds.end();
+        while (!foundPlaying && it != end) {
+            foundPlaying = (*it == playing);
+            ++it;
+        }
+        if (!foundPlaying && !foundPending && !foundOnStack)
+            return;
+        break;
+    default:
+        return;
+    }
+
+    if ((playing->m_at44 || playing->m_at46) && !playing->m_at48 && !foundPending && !foundOnStack)
+        return;
+
+    if (playing->m_event->m_at10.get() != 0) {
+        BfmePoolRef10 waiting(playing->m_event->m_at10);
+        {
+            BfmePoolRef10 none;
+            ((Rva002D9AD4 *)playing->m_event.get())->rva002D9AD4(none);
+        }
+        waiting->decrementNumberOfEventsNeedingToBeDoneBeforeReplaying();
+        if (waiting->m_at14 <= 0) {
+            if (waiting->m_at7C != -12345 && waiting->m_at7C > 0)
+                waiting->setNumberOfTimesToPlayMusicOrMultisound(waiting->m_at7C - 1);
+            if (waiting->m_at7C == -12345 || waiting->m_at7C > 0) {
+                int how = 0;
+                if (foundOnStack)
+                    how = 2;
+                rva0005D734((int)waiting.get(), how, 1, 1, 0);
+                return;
+            }
+        }
+    }
+    if (!playing->m_event->m_at84.isEmpty())
+        playing->m_at4D = true;
+}
+
 // Retail 0x0005EC7A (WorldBuilder twin 0x0077D5F0, names from its asserts):
 // fills the play buffer from m_endOfLastCopy up to position, zero filling once
 // the event is done and switching to the decay or next primary file whenever
#endif
