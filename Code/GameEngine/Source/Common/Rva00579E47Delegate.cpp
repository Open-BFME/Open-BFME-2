// cl: /MD
// ?rva00579E47@Rva00579E47@@QAEAAV1@PBUDelegateDesc@@@Z @0x00579E47 (59B):
// delegate-wrapper ctor (unlock lane, missing callee of 69 free functions).
// News 0x10-byte ref-counted impl (vtable RVA 0x0086ECB4), copies 8-byte
// [object, method] payload from the DelegateDesc arg, stores impl to wrapper
// at +0 and AddRefs (inc [eax+4] from 0 to 1), returns *this (mov eax,esi).
// Evidence: vtable 0x00C6ECB4 (9 slots: slot0 deleting dtor 0x005FAA31,
// slot1 thunk 0x005B4C73 mov ecx,[eax+8] jmp [eax+0xc], slot2 ICF getter
// 0x004C54EC); two call sites in StatsDisplay ctor 0x00579E82 (RollOver with
// method 0x00579B81 and RollOut with 0x00579C00, via ObjectCreationList add
// 0x0052458E); strings _level%u. _OnStatRollOver _OnStatRollOut StatsDisplay
// STRATEGICHUD:Stats* _OnClicked. Flags /O1 (inc, pop ecx cleanup of push
// 0x10); throw() new for null check; Base-with-virtual-dtor plus inline Impl
// ctor gives retail and-before-vtable order with mov ecx first (probe test3/4
// exact, 0 structural regions, vtable DIR32 filled by gate).
void *__cdecl operator new(unsigned int size) throw();

struct DelegateDesc {
    void *m_object;
    void *m_method;
};

struct ImplBase {
    virtual ~ImplBase() {}
    int m_ref;
    ImplBase() : m_ref(0) {}
};

struct Impl : ImplBase {
    void *m_object;
    void *m_method;
    Impl(const DelegateDesc &d) : m_object(d.m_object), m_method(d.m_method) {}
};

class Rva00579E47 {
public:
    Rva00579E47 &rva00579E47(const DelegateDesc *d);
private:
    Impl *m_ptr;
};

Rva00579E47 &Rva00579E47::rva00579E47(const DelegateDesc *d)
{
    Impl *p = new Impl(*d);
    m_ptr = p;
    if (p)
        p->m_ref++;
    return *this;
}

// Four more delegate-wrapper constructors of this 59-byte shape, each installing
// its own impl vtable (the only differing operand): VA 0xbe5898, 0xc67e80,
// 0xc684ac and 0xc684b4. One impl class per copy names that vtable; owners
// keep their addresses.

struct Impl002165B0 : ImplBase {
    void *m_object;
    void *m_method;
    Impl002165B0(const DelegateDesc &d) : m_object(d.m_object), m_method(d.m_method) {}
};
class Rva002165B0 {
public:
    Rva002165B0 &rva002165B0(const DelegateDesc *d);
private:
    Impl002165B0 *m_ptr;
};
Rva002165B0 &Rva002165B0::rva002165B0(const DelegateDesc *d)
{
    Impl002165B0 *p = new Impl002165B0(*d);
    m_ptr = p;
    if (p)
        p->m_ref++;
    return *this;
}

struct Impl00525916 : ImplBase {
    void *m_object;
    void *m_method;
    Impl00525916(const DelegateDesc &d) : m_object(d.m_object), m_method(d.m_method) {}
};
class Rva00525916 {
public:
    Rva00525916 &rva00525916(const DelegateDesc *d);
private:
    Impl00525916 *m_ptr;
};
Rva00525916 &Rva00525916::rva00525916(const DelegateDesc *d)
{
    Impl00525916 *p = new Impl00525916(*d);
    m_ptr = p;
    if (p)
        p->m_ref++;
    return *this;
}

struct Impl0052A786 : ImplBase {
    void *m_object;
    void *m_method;
    Impl0052A786(const DelegateDesc &d) : m_object(d.m_object), m_method(d.m_method) {}
};
class Rva0052A786 {
public:
    Rva0052A786 &rva0052A786(const DelegateDesc *d);
private:
    Impl0052A786 *m_ptr;
};
Rva0052A786 &Rva0052A786::rva0052A786(const DelegateDesc *d)
{
    Impl0052A786 *p = new Impl0052A786(*d);
    m_ptr = p;
    if (p)
        p->m_ref++;
    return *this;
}

struct Impl0052A7C1 : ImplBase {
    void *m_object;
    void *m_method;
    Impl0052A7C1(const DelegateDesc &d) : m_object(d.m_object), m_method(d.m_method) {}
};
class Rva0052A7C1 {
public:
    Rva0052A7C1 &rva0052A7C1(const DelegateDesc *d);
private:
    Impl0052A7C1 *m_ptr;
};
Rva0052A7C1 &Rva0052A7C1::rva0052A7C1(const DelegateDesc *d)
{
    Impl0052A7C1 *p = new Impl0052A7C1(*d);
    m_ptr = p;
    if (p)
        p->m_ref++;
    return *this;
}
