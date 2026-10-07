// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep
// stlport
// Donor: Open-BFME-1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/Libraries/Source/assetmanager/Rva009EF6D0.cpp. The two 113-byte
// getters at 0x00622190/0x00622210 hold the receiver lock at +0x34 while
// copying its trees at +0x1D4/+0x198. These offsets are eight bytes beyond
// the donor and agree with assetmanager_impl.cpp's established BFME2 view.
// Both call the rowed 207-byte integer-tree copy constructor at 0x00620CA0.
// This replaces the old speculative four-byte Gen_t tree dependency of the
// 30-byte result constructor at 0x006216F0. Its owning type, the getter names,
// application meaning of the tree elements and trailing fields remain unknown.
// The address-qualified names retain that uncertainty. The tree declaration
// below is the existing STLport provider's 12-byte ABI, with external lifetime
// operations; it does not generate competing template definitions.

#include <windows.h>
extern "C" void __cdecl _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
namespace _STL {
template<class T> struct _Identity {};
template<class T> struct less {};
template<class T> class allocator {};
template<class K, class V, class I, class C, class A> class _Rb_tree {
public:
    _Rb_tree(const _Rb_tree &);
    ~_Rb_tree();
private:
    unsigned int m_storage[3];
};
}
typedef _STL::_Rb_tree<int, int, _STL::_Identity<int>, _STL::less<int>, _STL::allocator<int> > IntSetTree;
struct Rva009EF6B0 {
    IntSetTree m_tree;
    unsigned m_field0c;
    bool m_field10;
    explicit Rva009EF6B0(const IntSetTree &tree);
};
Rva009EF6B0::Rva009EF6B0(const IntSetTree &tree)
    : m_tree(tree), m_field0c(0), m_field10(true) {}
class CriticalSectionLock {
public:
    explicit CriticalSectionLock(CRITICAL_SECTION *lock) : m_lock(lock) { EnterCriticalSection(m_lock); }
    ~CriticalSectionLock() { LeaveCriticalSection(m_lock); }
    CRITICAL_SECTION *m_lock;
};
struct Rva00622190Output {
    Rva00622190Output(const IntSetTree &source) : m_tree(source) {
        m_value = 0;
        _ReadWriteBarrier();
        m_active = true;
    }
    IntSetTree m_tree;
    unsigned m_value;
    bool m_active;
};
class Rva00622190Owner {
public:
    Rva00622190Output Rva00622190();
    Rva00622190Output Rva00622210();
private:
    unsigned char m_unknown000[0x34];
    CRITICAL_SECTION m_lock;
    unsigned char m_unknown04c[0x14c];
    IntSetTree m_tree198;
    unsigned char m_unknown1a4[0x30];
    IntSetTree m_tree1d4;
};
Rva00622190Output Rva00622190Owner::Rva00622190() {
    CriticalSectionLock lock(&m_lock);
    return Rva00622190Output(m_tree1d4);
}
Rva00622190Output Rva00622190Owner::Rva00622210() {
    CriticalSectionLock lock(&m_lock);
    return Rva00622190Output(m_tree198);
}
typedef char TreeSize[sizeof(IntSetTree) == 12 ? 1 : -1];
typedef char OutputSize[sizeof(Rva00622190Output) == 20 ? 1 : -1];
typedef char LockSize[sizeof(CRITICAL_SECTION) == 24 ? 1 : -1];
