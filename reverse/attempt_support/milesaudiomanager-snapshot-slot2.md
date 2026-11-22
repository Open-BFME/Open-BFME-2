# MilesAudioManager Snapshot table 0x007C559C bridge (slot 2)

Retail table VA 0x00BC559C (Snapshot at +0xC): [0x5D41D thunk, 0x587C6 loadPostProcess, 0x518B2 name getter, 0x5E3E5 xfer].
Our unit compiles slot 2 as __purecall: the moduledata Snapshot shim falls back to crc() and nothing overrides it.
The 0x518B2 row is ?name@MilesAudioManager@@QBEPBDXZ (non-virtual stub in Common/SubsystemNameGetters.cpp); tu_map approves it in MilesAudioManager.cpp.

Fix (ready): rename.py function --rva 0x000518B2 --to-class MilesAudioManager --new '?GetSnapshotName@MilesAudioManager@@MBEPBDXZ' --approval-base <rev> with the prepared sources below.
Blocked only on name_lane approval for slot key Code/GameEngineDevice/Include/MilesAudioDevice/MilesAudioManager.h|slot|MilesAudioManager@0x00BC559C|2 (one vote GetSnapshotName recorded; needs a second independent voter).

```diff
--- Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp	2026-11-17 20:35:08
+++ Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp	2026-11-22 02:26:04
@@ -60,6 +60,8 @@
 #include "../../../Libraries/Include/Lib/Coord3D.h"
 #define COORD2D_VIEW_DTOR
 #include "../../../Libraries/Include/Lib/Coord2DCtorView.h"
+// Retail's Snapshot slot 2 is the class-name getter (0x000518B2).
+#define BFME_SNAPSHOT_NAME_SLOT
 #include "Common/Snapshot.h"
 // Version pair xfer (slot 10) reads and rewrites; xfer (0x0005E3E5) seeds
 // 1 and 4 and gates its later fields on the second byte.
@@ -1259,6 +1261,7 @@
     void createListener();
 protected:
     virtual void loadPostProcess(void);
+    virtual const char *GetSnapshotName(void) const;
 public:
     virtual void xfer(Xfer *transfer);
 private:
@@ -1916,6 +1919,10 @@
     else
         ((Rva000A8ACC *)stream)->rva000A8ACC();
 }
+const char *MilesAudioManager::GetSnapshotName(void) const
+{
+    return "MilesAudioManager";
+}
 class File;
 #include "../../../GameEngine/Include/Common/FileSystem.h"
 extern FileSystem *TheFileSystem;
--- Code/GameEngine/Source/Common/SubsystemNameGetters.cpp	2026-11-16 23:15:00
+++ Code/GameEngine/Source/Common/SubsystemNameGetters.cpp	2026-11-22 02:26:04
@@ -103,7 +103,6 @@
 {
 	return "GeometryInfo";
 }
-BFME_LITERAL_NAME_GETTER(MilesAudioManager, "MilesAudioManager")
 BFME_LITERAL_NAME_GETTER(Rva0008BC8BNamed, "View")
 BFME_LITERAL_NAME_GETTER(Rva00226309Named, "SaveMapPreview")
 BFME_LITERAL_NAME_GETTER(Rva002296E6Named, "GameSlot")
```
