// cl: /O1 /MD
// Each class is declared locally only so its deleting destructor is emitted;
// the complete destructor call resolves through that destructor's own row.
// Same-shape family as FamilyDeletingDtors2.cpp (??_GVersion 0x21C7 shape):
// members selected by a rowed QAE dtor callee.

// ??_GLockClass@MutexClass@@QAEPAXI@Z @0x99203
struct MutexClass { struct LockClass { ~LockClass(); }; };
void famgenDelete(MutexClass::LockClass *p) { delete p; }

// ??_GWriteLockClass@VertexBufferClass@@QAEPAXI@Z @0x107346
struct VertexBufferClass { struct WriteLockClass { ~WriteLockClass(); }; };
void famgenDelete(VertexBufferClass::WriteLockClass *p) { delete p; }

// ??_GWriteLockClass@IndexBufferClass@@QAEPAXI@Z @0x107362
// Shares its dtor address with AppendLockClass (folded twins); rowed as WriteLock.
struct IndexBufferClass { struct WriteLockClass { ~WriteLockClass(); }; };
void famgenDelete(IndexBufferClass::WriteLockClass *p) { delete p; }

// ??_GLockClass@CriticalSectionClass@@QAEPAXI@Z @0x55077c
struct CriticalSectionClass { struct LockClass { ~LockClass(); }; };
void famgenDelete(CriticalSectionClass::LockClass *p) { delete p; }

// ??_GPrereqUnitRec@ProductionPrerequisite@@QAEPAXI@Z @0x3b3fb1
struct ProductionPrerequisite { struct PrereqUnitRec { ~PrereqUnitRec(); }; };
void famgenDelete(ProductionPrerequisite::PrereqUnitRec *p) { delete p; }
