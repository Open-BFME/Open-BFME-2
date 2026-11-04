### LINK-232: VertexMaterialClass header adoption duplicates StringClass assignment in Load_W3D

Status: Blocked. Updated: 2026-11-04; inspected revision: `9acaa20c92`.
Scope: `Code/Libraries/Source/WWVegas/WW3D2/VertexMaterialLoadW3D.cpp`, RVA `0x0013E8B0`; adopting VertexMaterialClass.h introduces duplicate `??4StringClass@@QAEABV0@PBD@Z` through wwstring.h, dropping 308 census-linked bytes in the preview despite exact row bytes.
Completed / next check: reverted this trial and retained its header-queue row; three peer adoptions pass. Reconcile the shared material header's StringClass dependency with declaration-only StringClassData.h while preserving other consumers' required inline bodies, then repeat byte and consumer link checks.
Evidence: [trial and accepted scope](../../reverse/attempt_support/vertexmaterial-header-codex4-20261104/readme.md).
Clearance: pending; no census change claimed.
