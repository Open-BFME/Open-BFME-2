// ?addResumeOrPushMultisound@MilesAudioManager@@QAEHPAVAudioEventRTS@@HHHHH@Z
// partial score=0.99 date=2026-10-08
// Banked attempt for 0x5A451 addResumeOrPushMultisound (877B). Apply as a patch against master at the commit recorded; body is byte-exact except 4 unnamed callee relocs.
/*
diff --git a/Code/GameEngine/Source/Common/Audio/AudioEventRTS.cpp b/Code/GameEngine/Source/Common/Audio/AudioEventRTS.cpp
index ff10d577e2..dd1d0d72e1 100644
--- a/Code/GameEngine/Source/Common/Audio/AudioEventRTS.cpp
+++ b/Code/GameEngine/Source/Common/Audio/AudioEventRTS.cpp
@@ -191,3 +191,22 @@ int Rva002D9C7A::rva002D9C7A() {
  }
  return -1;
 }
+
+// AudioEventRTS::setPlayingHandle (Zero Hour name): the 10-byte store of the
+// handle at +0x0C, which ICF folds onto 0x005F69C4 with every other +0x0C
+// setter. addResumeOrPushMultisound (0x0005A451) calls it on the multisound
+// parent with the handle the first subsound got.
+class AudioEventRTS
+{
+public:
+	void setPlayingHandle(unsigned int handle);
+private:
+	char m_pad[0x0C];
+	unsigned int m_playingHandle;
+};
+
+// ?AudioEventRTS::setPlayingHandle present-unmatched
+void AudioEventRTS::setPlayingHandle(unsigned int handle)
+{
+	m_playingHandle = handle;
+}
diff --git a/Code/GameEngine/Source/Common/Thing/AudioEventInfoRefConstructor.cpp b/Code/GameEngine/Source/Common/Thing/AudioEventInfoRefConstructor.cpp
index 771e743236..6be631f27b 100644
--- a/Code/GameEngine/Source/Common/Thing/AudioEventInfoRefConstructor.cpp
+++ b/Code/GameEngine/Source/Common/Thing/AudioEventInfoRefConstructor.cpp
@@ -16,6 +16,7 @@ class AudioEventInfoRef
 {
 public:
 	AudioEventInfoRef(const AudioEventInfo *info);
+	AudioEventInfoRef(const AudioEventInfoRef &other);
 
 	const AudioEventInfo *m_info;
 };
@@ -26,3 +27,15 @@ AudioEventInfoRef::AudioEventInfoRef(const AudioEventInfo *info)
 	if (m_info)
 		InterlockedIncrement(&const_cast<AudioEventInfo *>(m_info)->m_refCount);
 }
+
+// The counted copy is the out-of-line 31-byte body at 0x000A8C7C, which ICF
+// shares with every other four-byte counted reference copy (rowed there as
+// Rva0036CA00Str's). MilesAudioManager::addResumeOrPushMultisound (0x0005A451)
+// copies a subsound's AudioEventInfo reference through it.
+// ?AudioEventInfoRef::AudioEventInfoRef present-unmatched
+AudioEventInfoRef::AudioEventInfoRef(const AudioEventInfoRef &other)
+	: m_info(other.m_info)
+{
+	if (m_info)
+		InterlockedIncrement(&const_cast<AudioEventInfo *>(m_info)->m_refCount);
+}
diff --git a/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp b/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
index 51621ab374..d2084e4dd7 100644
--- a/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
+++ b/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
@@ -131,11 +131,13 @@ struct AudioEventChannelVolume {
 struct AudioEventInfo {
     char at00[0x08];
     AsciiString m_audioName;                 // +0x08
-    char at0C[0x44 - 0x0C];
+    char at0C[0x40 - 0x0C];
+    int m_lastSubsoundIndex;                 // +0x40, addResumeOrPushMultisound avoids repeating it
     int m_priority;                          // +0x44
     unsigned int m_type;                     // +0x48, bit 3 global
     unsigned int m_control;                  // +0x4C, Zero Hour's AudioControl bits (AC_LOOP = 1)
-    char at50[0x90 - 0x50];
+    char at50[0x8C - 0x50];
+    unsigned int m_totalSubsoundWeight;      // +0x8C, the random subsound pick's range
     float m_at90;                            // +0x90, occlusion factor when positive
     float m_maxDistance;                     // +0x94
     float m_minDistance;                     // +0x98
@@ -146,6 +148,9 @@ struct AudioEventInfo {
     int m_atB0;                              // +0xB0, processRequest preloads a file when 2
     char atB4[0xB8 - 0xB4];
     _STL::vector<AudioEventChannelVolume> m_channelVolumes;  // +0xB8
+
+    // Rowed at 0x001D96F8 (+0x80); declared below once its element exists.
+    const _STL::vector<class BfmeStringTailRecord156> &getSubsoundVector(void) const;
 };
 
 class AudioEventRTS {
@@ -163,10 +168,14 @@ public:
     // loop-buffer refill's decay test reads through it.
     const AudioEventInfo *getAudioEventInfo(void) const { return m_info; }
     AsciiString getFilename(void);
+    // Rowed at 0x005F69C4 (the ICF-shared +0x0C store).
+    void setPlayingHandle(unsigned int handle);
     char at00[0x08];
     AudioEventInfo *m_info;  // +0x08 (owning ref in WB)
     int m_playingHandle;     // +0x0C, copied into a requeued loop's request
-    char at10[0x30 - 0x10];
+    AudioEventRTS *m_multiSoundParent; // +0x10, owning ref of the multisound this subsound plays for
+    int m_eventsBeforeReplay; // +0x14, subsounds still playing for a multisound parent
+    char at18[0x30 - 0x18];
     int m_viewType;          // +0x30
     char at34[0x38 - 0x34];
     int m_ownerType;         // +0x38, 2 when object-owned (getObjectID's test)
@@ -189,6 +198,7 @@ struct BfmePoolHolder88;
 
 class BfmePoolRef10 {
 public:
+    BfmePoolRef10() : m_ptr(0) {}
     ~BfmePoolRef10() { if (m_ptr) reinterpret_cast<OpaqueRefCounted *>(reinterpret_cast<char *>(m_ptr) + 0x88)->Release_Ref(); }
     AudioEventRTS *operator->(void) const { return m_ptr; }
     AudioEventRTS *get(void) const { return m_ptr; }
@@ -692,6 +702,7 @@ typedef _STL::list<OpaqueRefElement4> OpaqueRefList;
 // Owning AudioEventInfo reference returned by the slot-75 lookup.
 class AudioEventInfoRef {
 public:
+    AudioEventInfoRef(const AudioEventInfoRef &other);  // out of line at 0x000A8C7C
     ~AudioEventInfoRef() { if (m_ptr) m_ptr->Release_Ref(); }
     AudioEventInfo *get(void) const { return (AudioEventInfo *)m_ptr; }
 private:
@@ -841,7 +852,10 @@ public:
     void rva0005876E(int viewType, int musicSystem, int arg, int resume);
     bool addAudioEventMusic(BfmePoolRef10 &event, int requestType, int append);
     int pushMusicEventInternal(AudioEventRTS *event, int arg1, int arg2, int append);
-    int addResumeOrPushMultisound(AudioEventRTS *event, int requestType, int arg2, int arg3, int arg4, int arg5);
+    int addResumeOrPushMultisound(AudioEventRTS *event, int requestType, int arg2, int arg3, int allocateHandle, int arg5);
+    unsigned int addOrResumeAudioEvent(AudioEventRTS *event, int requestType, int arg2, int allocateHandle, int arg5);
+    void mapLogicalHandleToPhysicalHandle(unsigned int logical, unsigned int physical);
+    unsigned int allocateNewHandle(void) { return m_nextHandle++; }
     BfmePoolRef10 rva0005286A(AudioEventRTS *event, int arg);
     void rva000592B8(AudioEventRTS *event);
     bool shouldPlayLocally(const AudioEventRTS *event);
@@ -926,7 +940,8 @@ private:
     Rva00051107AudioRequestSet m_requestSet;        // +0x9C
     char atB0[0xBC - 0xB0];
     Rva00059FBBMap m_allAudioEventInfo;  // +0xBC
-    char atD0[0x678 - 0xD0];
+    unsigned int m_nextHandle;               // +0xD0, allocateNewHandle's counter
+    char atD4[0x678 - 0xD4];
     int m_at678;                         // +0x678, compared with event view types
     char at67C[0x698 - 0x67C];
     unsigned int m_at698;                // +0x698, per-view-type bits processAudioCompletion clears
@@ -3019,3 +3034,125 @@ void MilesAudioManager::GlobalVolumeData::rva0005213E(const MicrophoneSettings *
     }
     rva00052015(1);
 }
+
+// Subsound entry of AudioEventInfo +0x80: the event info reference and the
+// weight the random pick walks (8 bytes, 0x0005A451 strides by 8).
+class BfmeStringTailRecord156 {
+public:
+    AudioEventInfoRef m_eventInfo;
+    unsigned int m_weight;
+};
+
+// The 0x88-byte event copy (copy constructor 0x002D99E3, virtual destructor
+// 0x002D9A43) addResumeOrPushMultisound plays each subsound through.
+// class-gate: allow BfmeAudioEventPrefix136 caller-view: the canonical header redefines this TU's OpaqueRefCounted and BfmePoolRef10 views
+struct BfmeAudioEventPrefix136 {
+    BfmeAudioEventPrefix136(const BfmeAudioEventPrefix136 &other);
+    virtual ~BfmeAudioEventPrefix136();
+    char at04[0x10 - 0x04];
+    AudioEventRTS *m_multiSoundParent;   // +0x10
+    char at14[0x7C - 0x14];
+    int m_loopCount;                     // +0x7C
+    char at80[0x88 - 0x80];
+};
+class Rva002D9C2F { public: OpaqueRefElement4 &rva002D9C2F(const OpaqueRefElement4 &other); };
+class Rva002D9AD4 { public: BfmePoolRef10 &rva002D9AD4(const BfmePoolRef10 &other); };
+int GetGameAudioRandomValue(int lo, int hi, char *file, int line);
+
+// WorldBuilder 0x786370 (asserts 3761..3830). A multisound (control bit 0x80)
+// either plays one weighted random subsound, never the last one picked, or
+// every subsound under one logical handle mapped to each physical handle;
+// a looping info (bit 1) first takes a multisound parent reference.
+int MilesAudioManager::addResumeOrPushMultisound(AudioEventRTS *event, int requestType, int arg2, int arg3, int allocateHandle, int arg5)
+{
+    Rva0036CA00Str infoRef(*reinterpret_cast<const Rva0036CA00Str *>(&event->m_info));
+    AudioEventInfo *info = reinterpret_cast<AudioEventInfo *>(infoRef.get());
+    BfmePoolRef10 multiSound;
+    if (info->m_control & 1)
+        multiSound = rva0005286A(event, allocateHandle);
+    if (reinterpret_cast<AudioEventInfo *>(infoRef.get())->m_control & 0x80) {
+        const _STL::vector<BfmeStringTailRecord156> &subs = reinterpret_cast<AudioEventInfo *>(infoRef.get())->getSubsoundVector();
+        int index;
+        if (subs.size() <= 1) {
+            index = 0;
+        } else {
+            do {
+                unsigned int pick = GetGameAudioRandomValue(0, reinterpret_cast<AudioEventInfo *>(infoRef.get())->m_totalSubsoundWeight - 1, MILES_AUDIO_MANAGER_FILE, 3761);
+                _STL::vector<BfmeStringTailRecord156>::const_iterator it = subs.begin();
+                _STL::vector<BfmeStringTailRecord156>::const_iterator end = subs.end();
+                while (it != end && pick >= it->m_weight) {
+                    pick -= it->m_weight;
+                    ++it;
+                }
+                if (it == end)
+                    return 0;
+                index = it - subs.begin();
+            } while (index == event->getAudioEventInfo()->m_lastSubsoundIndex);
+        }
+        reinterpret_cast<AudioEventInfo *>(infoRef.get())->m_lastSubsoundIndex = index;
+        if (index < 0 || (unsigned int)index >= subs.size())
+            return 1;
+        AudioEventInfoRef sub(subs[index].m_eventInfo);
+        if (sub.get() == 0)
+            return 1;
+        BfmeAudioEventPrefix136 copy(*reinterpret_cast<const BfmeAudioEventPrefix136 *>(event));
+        ((Rva002D9C2F *)&copy)->rva002D9C2F(*reinterpret_cast<const OpaqueRefElement4 *>(&sub));
+        if (multiSound.get()) {
+            ((Rva002D9AD4 *)&copy)->rva002D9AD4(multiSound);
+            multiSound->m_eventsBeforeReplay++;
+            copy.m_loopCount = 1;
+        }
+        unsigned int result;
+        if (requestType == 2)
+            result = pushMusicEventInternal(reinterpret_cast<AudioEventRTS *>(&copy), arg3, allocateHandle, arg5);
+        else
+            result = addOrResumeAudioEvent(reinterpret_cast<AudioEventRTS *>(&copy), requestType, arg2, allocateHandle, arg5);
+        if (multiSound.get() && result >= 5)
+            multiSound->setPlayingHandle(result);
+        return result;
+    } else {
+        unsigned int handle;
+        if (multiSound.get())
+            handle = multiSound->m_playingHandle;
+        else if (allocateHandle == 1)
+            handle = event->m_playingHandle;
+        else
+            handle = allocateNewHandle();
+        if (!multiSound.get()) {
+            AudioEventRTS *parent = event->m_multiSoundParent;
+            if (parent)
+                parent->m_eventsBeforeReplay--;
+        }
+        const _STL::vector<BfmeStringTailRecord156> &subs = event->getAudioEventInfo()->getSubsoundVector();
+        _STL::vector<BfmeStringTailRecord156>::const_iterator it = subs.begin();
+        _STL::vector<BfmeStringTailRecord156>::const_iterator end = subs.end();
+        bool played = false;
+        unsigned int result = 1;
+        for (; it != end; ++it) {
+            if (it->m_eventInfo.get() == 0)
+                continue;
+            BfmeAudioEventPrefix136 copy(*reinterpret_cast<const BfmeAudioEventPrefix136 *>(event));
+            ((Rva002D9C2F *)&copy)->rva002D9C2F(*reinterpret_cast<const OpaqueRefElement4 *>(&it->m_eventInfo));
+            if (multiSound.get())
+                ((Rva002D9AD4 *)&copy)->rva002D9AD4(multiSound);
+            if (copy.m_multiSoundParent)
+                copy.m_loopCount = 1;
+            unsigned int r;
+            if (requestType == 2)
+                r = pushMusicEventInternal(reinterpret_cast<AudioEventRTS *>(&copy), arg3, 0, arg5);
+            else
+                r = addOrResumeAudioEvent(reinterpret_cast<AudioEventRTS *>(&copy), requestType, 1, 0, arg5);
+            if (r >= 5) {
+                if (copy.m_multiSoundParent)
+                    copy.m_multiSoundParent->m_eventsBeforeReplay++;
+                played = true;
+                mapLogicalHandleToPhysicalHandle(handle, r);
+            } else {
+                result = r;
+            }
+        }
+        if (played)
+            return handle;
+        return result;
+    }
+}
diff --git a/reverse/hatch_baseline.tsv b/reverse/hatch_baseline.tsv
index 39df4c9d12..b7ef2528a9 100644
--- a/reverse/hatch_baseline.tsv
+++ b/reverse/hatch_baseline.tsv
@@ -24079,9 +24079,9 @@ pin	reverse/symbols.csv	0x000A8AC0	1
 pin	reverse/symbols.csv	0x000A8ACC	1
 pin	reverse/symbols.csv	0x000A8B04	1
 pin	reverse/symbols.csv	0x000A8B4B	1
-pin	reverse/symbols.csv	0x000A8C7C	2
+pin	reverse/symbols.csv	0x000A8C7C	3	allow=eaeede01c87646e37973692a253ed2ec2e93e315
 pin	reverse/symbols.csv	0x000A8C9B	2
-pin	reverse/symbols.csv	0x000A8D0B	1	allow=657327a6118434623b79f16ef83ae78b0e20283a
+pin	reverse/symbols.csv	0x000A8D0B	1
 pin	reverse/symbols.csv	0x000A8D5F	1
 pin	reverse/symbols.csv	0x000A8E0A	1
 pin	reverse/symbols.csv	0x000A8E95	1
diff --git a/reverse/symbols.csv b/reverse/symbols.csv
index 657327a611..eaeede01c8 100644
--- a/reverse/symbols.csv
+++ b/reverse/symbols.csv
@@ -16257,3 +16257,4 @@ ___CxxFrameHandler,0x00629182,callee of __ehhandler$??1Rva005813E@@UAE@XZ
 ?rva000592B8@MilesAudioManager@@QAEXPAVAudioEventRTS@@@Z,0x000592B8,direct REL32 callee of MilesAudioManager::pushMusicEventInternal 0x0005952D; WorldBuilder 0x788390 calls the same sequence (addResumeOrPushMultisound and shouldPlayLocally named there; 0x5286A/0x592B8 unnamed WB 0x786D30/0x785A70)
 ?shouldPlayLocally@MilesAudioManager@@QAE_NPBVAudioEventRTS@@@Z,0x00053BA1,direct REL32 callee of MilesAudioManager::pushMusicEventInternal 0x0005952D; WorldBuilder 0x788390 calls the same sequence (addResumeOrPushMultisound and shouldPlayLocally named there; 0x5286A/0x592B8 unnamed WB 0x786D30/0x785A70)
 ?rva000A8D0B@Rva000A8D0B@@QAEXPAXABVAsciiString@@H@Z,0x000A8D0B,Called by processPushMusicRequest at 0x5DC82 on playing+0x0C with (manager+0xB90; const AsciiString& filename; 0); body operator new(0x28) then ret 0xC (three stack args); WB 0x8E8400 unnamed; owner identity unresolved
+??0AudioEventInfoRef@@QAE@ABV0@@Z,0x000A8C7C,ICF twin of the rowed 31-byte counted copy; REL32 at 0x0005A501 in MilesAudioManager::addResumeOrPushMultisound copies the chosen subsound's AudioEventInfo reference (WB 0x786370 inlines the same null-checked InterlockedIncrement copy); fold-proof=Code/GameEngine/Source/Common/Thing/AudioEventInfoRefConstructor.cpp
*/
