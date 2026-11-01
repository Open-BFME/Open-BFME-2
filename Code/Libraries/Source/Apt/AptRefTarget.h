// Target facts: ReleaseTreeHintRef00217D4C (RVA 0x0007DEEF) decrements signed dword +4, tests <=0, calls vtable slot 0 with deleting flag 0 and deletes its returned allocation through RVA 0x0002FD60. The referent has a virtual destructor and an eight-byte consumed prefix. Heap constructors at RVAs 0x00080221 and 0x00579E47 allocate 12 and 16 bytes, clear +4, install VAs 0x00BC6FF4 and 0x00C6ECB4, then store the allocation in the four-byte handle at +0 and increment allocation+4. These tables belong to the referents, not the handles; both slot 0 entries are deleting destructor RVA 0x005FAA31, which calls RVA 0x004E84A4. That destructor restores VA 0x00BC6F20, whose sole slot is deleting destructor RVA 0x0007E5EE.
// TreeHintRef00217D4C has no virtual functions: its +0 word is the owned pointer. TreeHintRef00217D4C's rowed nonvirtual destructor (RVA 0x005F8F96, also rowed for AptRef<AptCommandMap>, AptRef<AptOverButtonHandler> and AptRef<AptScreenInitGadgets>) reads +0 and tail-calls ReleaseTreeHintRef00217D4C when nonnull. The shared assignment at RVA 0x002174A4 is rowed for TreeHintRef00217D4C and AptRef<AptCommandMap>, AptRef<AptCustomRender>, AptRef<AptExternHandler>, AptRef<AptOverButtonHandler>, AptRef<AptTimer>; it retains the source, releases the destination and stores the source pointer unless self-assigning. Both operations are declared out of line.
// Copies retain referent+4 inline in RVAs 0x004F62DE and 0x004F6966; map subscript RVA 0x00218A23 constructs a null handle. No own constructor or destructor table is established for the placeholder TargetRef00217D4C. The unrelated non-template library class AptRef uses virtual slots 0 and 1 at RVA 0x006DE240 and slot 1 at RVA 0x0070DF60; those calls do not describe the callback handle template below. No original name or complete referent layout is inferred from the shared release ABI.

#ifndef BFME2_APT_APTREFTARGET_H
#define BFME2_APT_APTREFTARGET_H

struct TargetRef00217D4C
{
    virtual ~TargetRef00217D4C();
    int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

struct TreeHintRef00217D4C
{
    TargetRef00217D4C *m_ptr;

    TreeHintRef00217D4C() : m_ptr(0) {}
    TreeHintRef00217D4C(TargetRef00217D4C *ptr) : m_ptr(ptr)
    {
        if (m_ptr) ++m_ptr->references;
    }
    TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr)
    {
        if (m_ptr) ++m_ptr->references;
    }
    ~TreeHintRef00217D4C();
    TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &);
};

#endif
