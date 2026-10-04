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

// Native577DE1/26 is a no-argument thiscall that clears its one pointer word
// before destroying and freeing the old value. The original owner and payload
// names remain unknown. The existing PrereqUnitRec destructor spelling is used
// only as the already-linked call contract for the native577998 shared cleanup;
// its +8 AsciiString teardown does not identify this payload as PrereqUnitRec.
class Rva00577DE1OwningCell
{
    void *m_value;
public:
    __declspec(noinline) void clear();
    void rva00577E3EForwardClear();
};
void Rva00577DE1OwningCell::clear()
{
    void *old = m_value;
    m_value = 0;
    if (old)
    {
        static_cast<ProductionPrerequisite::PrereqUnitRec *>(old)->~PrereqUnitRec();
        ::operator delete(old);
    }
}

// Native Ghidra577E3E/5 retains the no-argument receiver contract above.
// Its whole body tail-jumps to the independently verified577DE1 clear.
void Rva00577DE1OwningCell::rva00577E3EForwardClear()
{
    clear();
}
