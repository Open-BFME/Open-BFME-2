### LINK-191: Apt view class conflicts block further consolidation
Status: Blocked for further consolidation; current accepted pair links. Updated: 2026-11-04; inspected revision: defdb8c250.
Completed: merged Rva00789900Init.cpp into the approved Common/W3DAptComponentView3D.cpp, removing one source file while preserving 18 matched rows and the existing linked code/data definitions.
Evidence: [byte, object, EH, link-preview and path-consumer audit; six rejected donors](../../reverse/attempt_support/apt-view3d-consolidation-20261104-codexb4/README.md).
Remaining / next step: reconcile Rva007401F6/base constructor and virtual-slot views, canonical CameraClass/LightClass adoption, SimpleSceneClass/RenderInfoClass declaration order and StringBase/shim duplication before retrying the remaining donors. No new census-linked coverage claimed.
Recovery verification (2026-11-04): [rebase, byte checks and nine-source audit handoff](../../reverse/attempt_support/checkout-recovery-20261104-codexb4.md); batch linking remains unverified because the index predates the base and current object receipts are missing; carry the listed scope into the next scheduled census.
