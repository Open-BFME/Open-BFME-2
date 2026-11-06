# DefaultPhysicsModuleInfo deleting-destructor identity review

Read-only source snapshot: 63c2149983. Native baseline: baselines/bfme2/workshop-vanilla-1.06/files/game.dat. Existing local link index: d707d2f53b, clean tree, 2026-11-06 11:04. No builds, network calls, claims, or tracked edits performed.

## Target facts

- Export rows identify DefaultPhysicsModuleInfo's default constructor RVA 0x55EE5E, copy constructor 0x3A7736, complete destructor 0x49B47C, and vtable RVA 0x81BCB0 / VA 0xC1BCB0. Both native constructor bodies explicitly store VA 0xC1BCB0 into this+0.
- The native four-slot table at VA 0xC1BCB0 contains RVAs 0x3A77A7, 0x0B3FD0, 0x3A612D, 0x55EECB. The last three exported identities are LoadPostProcess, non-const GetSnapshotName, and DoXfer(Xfer &). Native GetSnapshotName returns VA 0xC1B950; its snapshot name is DefaultPhysicsModuleInfo.
- Native vector-deleting body 0x3A77A7/75 supplies complete destructor VA 0x89B47C at RVA 0x3A77B5, array stride 0x24 at 0x3A77BF, and calls the EH vector iterator at 0x3A77C2. Its scalar branch calls the same complete destructor at 0x3A77DA. Array free is 0x2FD80, scalar free 0x2FD60. The complete destructor writes Snapshot table VA 0xBBB554 and returns.
- Native vector-deleting body 0x3A69B4/75 instead passes stride 0x20 at 0x3A69CC. Its complete-destructor callback and scalar call also reach 0x49B47C. C1BB00's four slot RVAs are 0x3A69B4, 0x0B3FD0, 0x1F354A, 0x47A69C. That table's constructor and header evidence identify an emission-volume class family, not DefaultPhysicsModuleInfo.
- Default construction writes offsets +0x20/+0x21 and the copy constructor copies them. The native 0x24 stride agrees with these accesses and canonical header size. Native bytes and consumer facts are saved separately in evidence.json.

## Existing source and identity debt

- DefaultPhysicsModuleInfoVectorDeletingDestructor_Rva003A69B4.cpp creates an unrelated private class view with vptr plus 0x1C data = 0x20 bytes. Its named deleting wrapper row is assigned to 0x3A69B4. The source's comment itself cites RVA 0x5D7F70 and ILT 0x42F28 rather than the target lifetime facts above.
- The ledger notes call this a BFME1 donor and a unique masked placement. These are donor/placement claims, not native BFME2 identity evidence. No donor source was consulted for this review.
- VectorDeletingDtorsV03_Unresolved.cpp already owns the native 0x3A77A7/75 body as opaque Rva003A77A7Vec, with correct size 0x24. The same collector also has an existing opaque 0x3A69B4 copy. Existing attempt-support/vector-delete-collector-link-20261024.md preserves the old named+opaque 69B4 group but supplies no proof that DefaultPhysics has size 0x20.
- The canonical DefaultPhysicsModuleInfo.h already documents the correct native identity/size/slots. Its class contract JSON is stale/empty (size 0, no slots), and header_queue has an explicit FAIL for the incorrect named 69B4 unit.

## Current known consumer risk

- The local index's sole provider of ??_EDefaultPhysicsModuleInfo@FXParticleSystem@@UAEPAXI@Z is the incorrect 69B4 named wrapper unit; selection names that provider. Both EmissionInfoDefaultCtors.cpp and Rva003A7736CopyCtor.cpp define the same four-slot DefaultPhysics vtable, and their slot-zero edge names this symbol. Those constructors are actual existing consumers of the wrong identity through their emitted vtable.
- The index records weak _E -> _G fallbacks in those two units, so merely removing the incorrect provider can silently leave a scalar deleting destructor in the slot. A native four-slot/array-stride repair needs the correct 77A7 provider under the DefaultPhysics name, rather than relying on fallback resolution.
- Opaque 77A7 currently has only the collector's synthetic opaque table as its indexed consumer. No direct named 77A7 caller is visible in source or the index.
- The synthetic MakeDefaultPhysicsModuleInfoArray helper in the wrong source allocates/iterates 0x20-byte elements while calling the real 0x24-byte constructor, which writes +0x20/+0x21. This is an additional structural overflow if that helper executes. No runtime execution or reachability is claimed here.
- Single-object deleting behavior can coincide because both wrappers call the same folded complete destructor and scalar free; array behavior differs materially. No current crash is established.

## Conclusion

This is latent identity/stride cleanup. The complete destructors legitimately fold at 49B47C; the two vector-deleting wrappers cannot legitimately fold because their element-stride immediate differs. Correct canonical DefaultPhysics ownership is 3A77A7/75, already covered by an opaque row. A coordinated provider/ledger move should preserve the emission-volume 69B4 body under its target-supported identity, establish DefaultPhysics at 77A7, retire the wrong private view and its debt by the supported register paths, and check the two emitted vtable consumers together. This review does not request or perform that repair.
