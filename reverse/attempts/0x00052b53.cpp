// ?recalculateMicrophone@MilesAudioManager@@QAEXXZ
// partial score=0.95 date=2026-10-08
// Stash for recalculateMicrophone 0x52B53: unified diff against MilesAudioManager.cpp at 32e787e48d (declarations + body).
#if 0
--- build/scratch/mam_head.cpp	2026-10-08 15:24:35.881384627 +0000
+++ build/scratch/recalc_mic_stash.cpp	2026-10-08 15:24:23.738379526 +0000
@@ -480,6 +480,28 @@
     Coord3D m_pos;
     bool m_valid;                        // +0x0C
 };
+// The same five corners as recalculateMicrophone's local (rowed: element
+// ctor 0x00051CA2 with the folded empty dtor; array ctor 0x00052751) and the
+// rowed five-corner comparison 0x00051CF1.
+class Rva00051CA2 {
+public:
+    Rva00051CA2();
+    ~Rva00051CA2();
+private:
+    float x, y, z;
+    bool active;
+};
+class Rva0005276C {
+public:
+    Rva0005276C();
+    ~Rva0005276C() {}
+private:
+    Rva00051CA2 slots[5];
+};
+class Rva00051CF1 { public: bool rva00051CF1(Rva00051CF1 &other); };
+// Coord3D::Normalize (rowed 0x00005A70, returns the length) under an
+// address-derived view; the canonical Coord3D declares a void normalize.
+class Rva00005A70 { public: float rva00005A70(void); };
 
 struct AudioTriggerArea {
     PolygonTrigger *m_trigger;
@@ -500,13 +522,25 @@
 
 // AudioSettings view (Zero Hour's MilesAudioManager reads it through
 // m_audioSettings at +0x10): +0x74 is an int distance, +0xB8 a float limit.
-// Per-view record of AudioSettings, indexed by the manager's +0x678 view
-// type; setOcclusionLevels divides the listener distance by +0x00 when it is
-// within +0x04 (squared).
-struct AudioViewSettings {
-    float m_at00;
-    float m_at04;
-    char at08[0x48 - 0x08];
+// Per-view microphone record of AudioSettings (WorldBuilder's assert names
+// m_microphoneSettings), indexed by the manager's +0x678 view type.
+// recalculateMicrophone reads +0x00..+0x18 and +0x38..+0x44; setOcclusionLevels
+// divides the listener distance by +0x30 when it is within +0x34 (squared).
+struct MicrophoneSettings {
+    float m_at00;                        // +0x00, fraction past the far limit
+    float m_at04;                        // +0x04, squared-distance scale
+    float m_at08;                        // +0x08, numerator between the limits
+    float m_at0C;                        // +0x0C, near squared limit
+    float m_at10;                        // +0x10, numerator past the far limit
+    float m_at14;                        // +0x14, far squared limit
+    float m_at18;                        // +0x18, pull toward corner 0
+    char at1C[0x30 - 0x1C];
+    float m_at30;                        // +0x30
+    float m_at34;                        // +0x34
+    float m_at38;                        // +0x38, outer corner distance
+    float m_at3C;                        // +0x3C, outer squared limit
+    float m_at40;                        // +0x40, inner corner distance
+    float m_at44;                        // +0x44, inner squared limit
 };
 
 struct AudioSettings {
@@ -530,12 +564,13 @@
     bool m_atBC;                         // +0xBC, disables occlusion
     char atBD[0xC0 - 0xBD];
     float m_atC0;                        // +0xC0, occlusion floor
-    char atC4[0x15C - 0xC4];
-    AudioViewSettings m_viewSettings[3]; // +0x15C
+    char atC4[0x12C - 0xC4];
+    MicrophoneSettings m_microphoneSettings[3]; // +0x12C
 };
 
 extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_distances(void *sample, float maxDistance, float minDistance);
 extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_position(void *sample, float x, float y, float z);
+extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_orientation(void *obj, float xFace, float yFace, float zFace, float xUp, float yUp, float zUp);
 extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_volume(void *sample, float volume);
 extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_reverb_levels(void *sample, float dry, float wet);
 extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_effects_level(void *sample3D, float level);
@@ -664,7 +699,7 @@
     void rva00057B74(void);
     ~Rva00056CF8();
 private:
-    char opaque[0x10];
+    char opaque[0xC];
 };
 
 // {priority, volume} ranking key and its free less (rowed at 0x000515E4).
@@ -763,8 +798,9 @@
     virtual void slot86(); virtual void slot87(); virtual void slot88(); virtual void slot89(); virtual void slot90();
     virtual void slot91(); virtual void slot92(); virtual void slot93(); virtual void slot94(); virtual void slot95();
     virtual void slot96(); virtual void slot97(); virtual void slot98(); virtual void slot99(); virtual void slot100();
-    virtual void slot101(); virtual void slot102(); virtual void slot103(); virtual void slot104(); virtual void slot105();
-    virtual void slot106();
+    virtual void slot101(); virtual void slot102(); virtual void slot103(); virtual void slot104(); 
+    virtual void slot105(Coord3D *cameraPos);
+    virtual void slot106(Rva0005276C *corners);
     virtual bool rva000516EF(const Coord3D *pos);
     virtual void slot108(); virtual void slot109();
     // Slot 110 (+0x1B8), the first call init() makes.
@@ -816,7 +852,12 @@
         bool m_atC4;                               // +0xC4
         char atC5[0x1B8 - 0xC5];
         Rva00056CF8 m_at1B8;                       // +0x1B8
+        // Per-view microphone update (WB 0x77A260, unnamed) on the settings
+        // record and the camera-to-microphone offset.
+        void rva0005213E(const MicrophoneSettings *settings, const Coord3D *delta);
     };
+    // WorldBuilder name; places the Miles listener from the camera.
+    void recalculateMicrophone(void);
 
     void setMaxAmbientStreams(void);
     void rva0005452B(void);
@@ -907,7 +948,10 @@
     virtual void loadPostProcess(void);
 private:
     AudioSettings *m_audioSettings;      // +0x10 (Zero Hour name)
-    char at14[0x3C - 0x14];
+    char at14[0x18 - 0x14];
+    Coord3D m_micPos;                    // +0x18, Miles listener position
+    Coord3D m_micDir;                    // +0x24, Miles listener facing
+    Coord3D m_cameraPos;                 // +0x30, camera at the last recalculation
     AudioAreaCorner m_corners[5];        // +0x3C, entries 1..4 used by 0x53854
     float m_at8C;                        // +0x8C, distance occlusion scale
     char at90[0x98 - 0x90];
@@ -915,7 +959,8 @@
     Rva00051107AudioRequestSet m_requestSet;        // +0x9C
     char atB0[0xBC - 0xB0];
     Rva00059FBBMap m_allAudioEventInfo;  // +0xBC
-    char atD0[0x678 - 0xD0];
+    char atD0[0x12C - 0xD0];
+    GlobalVolumeData m_globalVolume[3];  // +0x12C, per view type
     int m_at678;                         // +0x678, compared with event view types
     char at67C[0x698 - 0x67C];
     unsigned int m_at698;                // +0x698, per-view-type bits processAudioCompletion clears
@@ -938,7 +983,9 @@
     unsigned int m_providerCount;        // +0x9CC
     unsigned int m_selectedProvider;     // +0x9D0, -1 when none
     void *m_mutex;                       // +0x9D4
-    char at9D8[0x9E8 - 0x9D8];
+    char at9D8[0x9E0 - 0x9D8];
+    void *m_listener;                    // +0x9E0 (Zero Hour name), unselectProvider closes it
+    char at9E4[0x9E8 - 0x9E4];
     MilesFileTextMap m_fileText;         // +0x9E8
     _STL::vector<UnicodeString> m_pendingFileText;  // +0x9FC
     _STL::vector<AsciiString> m_unknownFileNames;   // +0xA08
@@ -2216,10 +2263,10 @@
     if (m_at8C > 0.0f && playing->m_event->m_info->m_atA4 > 0.0f) {
         float distSqr = rva00053854(pos);
         float scale;
-        if (distSqr > m_audioSettings->m_viewSettings[m_at678].m_at04)
+        if (distSqr > m_audioSettings->m_microphoneSettings[m_at678].m_at34)
             scale = 1.0f;
         else
-            scale = sqrt(distSqr) / m_audioSettings->m_viewSettings[m_at678].m_at00;
+            scale = sqrt(distSqr) / m_audioSettings->m_microphoneSettings[m_at678].m_at30;
         occlusion *= 1.0 - scale * m_at8C * playing->m_event->m_info->m_atA4;
     }
     float finalOcclusion = 1.0f - occlusion;
@@ -2986,3 +3033,104 @@
     loop->m_isValid = true;
     return true;
 }
+
+// WorldBuilder twin MilesAudioManager::recalculateMicrophone (0x78A8C0):
+// pulls the listener from the camera toward the ground, faces it along the
+// camera's ground heading and scales +0x8C by the shortest corner edge.
+void MilesAudioManager::recalculateMicrophone(void)
+{
+    const MicrophoneSettings *settings = &m_audioSettings->m_microphoneSettings[m_at678];
+    m_at6AB = false;
+    Coord3D cameraPos;
+    cameraPos.x = 0.0f;
+    cameraPos.y = 0.0f;
+    cameraPos.z = 0.0f;
+    slot105(&cameraPos);
+    Rva0005276C corners;
+    slot106(&corners);
+    if (m_cameraPos == cameraPos && ((Rva00051CF1 *)m_corners)->rva00051CF1((Rva00051CF1 &)corners))
+        return;
+    *(Rva0005276C *)m_corners = corners;
+    m_cameraPos = cameraPos;
+
+    Coord3D lookDir;
+    {
+        const Coord3D *corner = &m_corners[0].m_pos;
+        lookDir.x = cameraPos.x - corner->x;
+        lookDir.y = cameraPos.y - corner->y;
+        lookDir.z = cameraPos.z - corner->z;
+    }
+    float lengthSqr = lookDir.x * lookDir.x + lookDir.y * lookDir.y + lookDir.z * lookDir.z;
+    float fraction;
+    if (lengthSqr * settings->m_at04 >= settings->m_at14) {
+        float dist = sqrtf(lengthSqr);
+        fraction = settings->m_at10 / dist;
+    } else if (lengthSqr <= settings->m_at0C)
+        fraction = 1.0f;
+    else if (lengthSqr * settings->m_at04 <= settings->m_at0C) {
+        float dist = sqrtf(lengthSqr);
+        fraction = settings->m_at08 / dist;
+    } else
+        fraction = settings->m_at00;
+
+    {
+        Coord3D scaled;
+        scaled.x = lookDir.x * fraction;
+        scaled.y = lookDir.y * fraction;
+        scaled.z = lookDir.z * fraction;
+        Coord3D mic;
+        mic.x = cameraPos.x - scaled.x;
+        mic.y = cameraPos.y - scaled.y;
+        mic.z = cameraPos.z - scaled.z;
+        if (m_corners[0].m_valid) {
+            m_micPos.x = (m_corners[0].m_pos.x - mic.x) * settings->m_at18 + mic.x;
+            m_micPos.y = (m_corners[0].m_pos.y - mic.y) * settings->m_at18 + mic.y;
+            m_micPos.z = mic.z;
+        } else {
+            m_micPos = mic;
+        }
+    }
+    if (lookDir.x != 0.0f || lookDir.y != 0.0f) {
+        m_micDir.x = -lookDir.x;
+        m_micDir.y = -lookDir.y;
+        m_micDir.z = 0.0f;
+        ((Rva00005A70 *)&m_micDir)->rva00005A70();
+    }
+    if (m_listener) {
+        AIL_set_3D_orientation(m_listener, m_micDir.x, m_micDir.y, -m_micDir.z, 0.0f, 0.0f, -1.0f);
+        AIL_set_3D_position(m_listener, m_micPos.x, m_micPos.y, -m_micPos.z);
+    }
+
+    {
+        Coord3D delta;
+        delta.x = cameraPos.x - m_micPos.x;
+        delta.y = cameraPos.y - m_micPos.y;
+        delta.z = cameraPos.z - m_micPos.z;
+        m_globalVolume[m_at678].rva0005213E(settings, &delta);
+    }
+
+    float shortest = g_Va00BBDA30;
+    for (int i = 1; i < 5; ++i) {
+        int next = i + 1;
+        if (next == 5)
+            next = 1;
+        if (m_corners[i].m_valid && m_corners[next].m_valid) {
+            const AudioAreaCorner &a = m_corners[i];
+            const AudioAreaCorner &b = m_corners[next];
+            float ex = a.m_pos.x - b.m_pos.x;
+            float ey = a.m_pos.y - b.m_pos.y;
+            float edgeSqr = ex * ex + ey * ey;
+            if (shortest > edgeSqr)
+                shortest = edgeSqr;
+        }
+    }
+    if (shortest >= settings->m_at3C)
+        m_at8C = 0.0f;
+    else if (shortest <= settings->m_at44)
+        m_at8C = 1.0f;
+    else
+    {
+        float dist = sqrtf(shortest);
+        m_at8C = (settings->m_at38 - dist) / (settings->m_at38 - settings->m_at40);
+    }
+}
#endif
