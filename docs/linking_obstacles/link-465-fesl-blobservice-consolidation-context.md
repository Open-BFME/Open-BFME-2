### LINK-465: FESL blobservice record views and writer compiler context prevent consolidation
Status: Blocked. Updated: 2026-11-05; inspected revision: aa9fa2e00ff.
Evidence / affected units: `blobservice.cpp`, `Rva007F05A0BlobCursor.cpp`, `V2FeslBlobRecordPopulate.cpp`, `Rva007F1220BlobWriter.cpp`; [verification and restored trials](../../reverse/attempt_support/blobservice-context-header-20261105-codex.md).
Completed: canonical diagnostic header accepted in blobservice; 21/21 rows match and preview preserves 1,029 linked bytes; one header-queue row retired. Merge accepts 0/3 donors; no paths moved.
Remaining / next check: reconcile the BlobRecord volatile-word/64-bit views; separately preserve writer scheduling and security-cookie/static-CRT context together with the seed's deleting destructor. All failed trials restored.
Clearance: header-adoption scope passes; consolidation remains blocked. Census confirmation: awaiting; no headline change claimed.
