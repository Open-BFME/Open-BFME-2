// cl: /MD
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

// 0x00577E43: the target body spans 45 bytes immediately after the rowed
// 0x00577E3E thunk and ends at its own ret. It calls 0x005C6CC7, then walks
// the range at this+0x44..this+0x48 backward by four bytes, calling rowed
// 0x00577914 on each value and rowed 0x005F8FCC(0) on the resulting slot.
// The address-derived owner and element roles are structural views; the
// original class and routine purpose are unknown.
class Rva005C6CC7Call
{
public:
    void rva005C6CC7();
};
class Rva00577914
{
public:
    void rva00577914();
};
class Rva005F8FCC
{
public:
    void *rva005F8FCC(unsigned int flags);
};
class Rva00577E43
{
public:
    void rva00577E43();

private:
    char m_pad00[0x44];
    void **m_begin;
    void **m_end;
};
void Rva00577E43::rva00577E43()
{
    ((Rva005C6CC7Call *)this)->rva005C6CC7();
    while (m_begin != m_end) {
        ((Rva00577914 *)m_end[-1])->rva00577914();
        --m_end;
        ((Rva005F8FCC *)m_end)->rva005F8FCC(0);
    }
}

// ?rva00577EAA@Rva00577EAA@@QAEXXZ retail 0x00577EAA 8 bytes. Forwards to
// rowed 0x00577E43 via the pointer at +4. Evidence: single caller 0x005F882E
// passes its own this in ecx with no pushes; target is the rowed
// Rva00577E43::rva00577E43 in this file; no vtable or strings.
class Rva00577EAA
{
public:
    void rva00577EAA();

private:
    char m_pad00[4];
    Rva00577E43 *m_target;
};
void Rva00577EAA::rva00577EAA()
{
    m_target->rva00577E43();
}
