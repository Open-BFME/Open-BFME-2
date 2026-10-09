// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc
//
// ??1AptPlayer@@UAE@XZ retail 0x00224A90 (237B), the AptPlayer complete
// destructor (vtable 0x007E6E80; base SubsystemInterface dtor 0x001B4E74).
// Target evidence: after the vptr store and the shutdown body 0x0022274A the
// members unwind in reverse offset order: a free()d pointer at +0x2FC, the
// fourteen 0x28-byte level slots at +0xCC (ehvec dtor 0x00629110 with element
// dtor 0x00224252), then the STLport trees/hash tables at +0xB8 .. +0x0C.
// Member types are named by the destructors rowed/pinned at the called
// addresses (0x223FF1 ArchivedFileInfo map, 0x22366C and 0x224974 hash
// tables, 0x06BF2A pointer set); their real identities are unproven.
#include "ascii_string.h"

extern "C" void __cdecl free(void *block) throw(...);

namespace _STL {
template <class A, class B> struct pair;
template <class P> struct _Select1st;
template <class P> struct _Identity;
template <class T> struct less;
template <class T> class allocator;
}
class ArchivedFileInfo;
struct Rva001408C0Target;

namespace _STL {
template <class K, class V, class S, class C, class A>
class _Rb_tree
{
public:
    ~_Rb_tree();
    char m_pad[0x14];
};
template <>
class _Rb_tree<Rva001408C0Target *, Rva001408C0Target *,
               _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>,
               allocator<Rva001408C0Target *> >
{
public:
    ~_Rb_tree();
    char m_pad[0xC];
};
}

typedef _STL::_Rb_tree<AsciiString,
                       _STL::pair<const AsciiString, ArchivedFileInfo>,
                       _STL::_Select1st<_STL::pair<const AsciiString, ArchivedFileInfo> >,
                       _STL::less<AsciiString>,
                       _STL::allocator<_STL::pair<const AsciiString, ArchivedFileInfo> > > FileInfoTree;

typedef _STL::_Rb_tree<Rva001408C0Target *, Rva001408C0Target *,
                       _STL::_Identity<Rva001408C0Target *>,
                       _STL::less<Rva001408C0Target *>,
                       _STL::allocator<Rva001408C0Target *> > TargetSet;

class Rva0022366C
{
public:
    ~Rva0022366C();
    char m_pad[0x14];
};

class Rva00224163
{
public:
    ~Rva00224163();
    char m_pad[0x14];
};

class DetailedArchivedDirectoryInfo
{
public:
    ~DetailedArchivedDirectoryInfo();
    char m_pad[0x28];
};

struct FreeOnDestroy
{
    ~FreeOnDestroy()
    {
        if (m_block)
            free(m_block);
    }
    void *m_block;
};

class SubsystemInterface
{
public:
    virtual ~SubsystemInterface();
    char m_state[8];
};

class AptPlayer : public SubsystemInterface
{
public:
    virtual ~AptPlayer();
    void rva0022274A();
private:
    FileInfoTree m_0C;
    FileInfoTree m_20;
    FileInfoTree m_34;
    Rva00224163 m_48;
    Rva0022366C m_5C;
    Rva0022366C m_70;
    TargetSet m_84;
    Rva0022366C m_90;
    FileInfoTree m_A4;
    FileInfoTree m_B8;
    DetailedArchivedDirectoryInfo m_levels[14];
    FreeOnDestroy m_2FC;
};

// ??1AptPlayer@@UAE@XZ
AptPlayer::~AptPlayer()
{
    rva0022274A();
}
