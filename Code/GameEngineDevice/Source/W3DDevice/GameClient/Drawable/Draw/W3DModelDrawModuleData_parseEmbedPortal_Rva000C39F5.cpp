// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw
//
// ?parseEmbedPortal@W3DModelDrawModuleData@@SAXPAVINI@@PAX1PBX@Z
// retail 0x000C39F5, 190 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawModuleData_parseEmbedPortal.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /Os it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here.
// stlport
// Retail field-table owner: W3DModelDrawModuleData::EmbedPortal at +0xF0.

typedef int Int;

namespace _STL
{
struct Rva007719C0Element;
}

// Retail's element construct callee 0x000BBA47 is the shared copy rowed as
// Rva000BBA47Construct (stlport_construct_game_structs.cpp); same cdecl ABI.
struct TreeKey00242F5E;
void Rva000BBA47Construct(TreeKey00242F5E *destination, const TreeKey00242F5E &source);


#include "../../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

namespace _STL
{
struct __false_type
{
};

struct Rva007719C0Element
{
    Int m_mode;
    AsciiString m_name;
    Rva007719C0Element() : m_name() {}
    ~Rva007719C0Element()
    {
    }
};

template <class T>
class allocator
{
};

template <class T>
void _Construct(T *destination, const T &source);

template <class T>
__forceinline void BfmeElementConstruct(T *destination, const T &source)
{
    Rva000BBA47Construct((TreeKey00242F5E *)destination,
        *(const TreeKey00242F5E *)&source);
}

template <class T, class Allocator>
class vector
{
public:
    void push_back(const T &value)
    {
        T *end = m_endOfStorage;
        T *finish = m_finish;
        if (finish != end)
        {
            BfmeElementConstruct(finish, value);
            finish = m_finish;
            ++finish;
            m_finish = finish;
        }
        else
        {
            __false_type tag;
            _M_insert_overflow(finish, value, tag, 1, true);
        }
    }

    T *back()
    {
        return m_finish - 1;
    }

protected:
    void _M_insert_overflow(T *position, const T &value,
        const __false_type &tag, unsigned int fillLength, bool atEnd);

public:
    T *m_start;
    T *m_finish;
    T *m_endOfStorage;
};
}

using _STL::Rva007719C0Element;

#include "../../../../../../GameEngine/Include/Common/INI/INI.h"

class W3DModelDrawModuleData
{
public:
    static void parseEmbedPortal(INI *ini, void *instance, void *store,
        const void *userData);
};

// ?parseEmbedPortal@W3DModelDrawModuleData@@SAXPAVINI@@PAX1PBX@Z
void W3DModelDrawModuleData::parseEmbedPortal(INI *ini, void *, void *store,
    const void *userData)
{
    {
        Rva007719C0Element empty;
        ((_STL::vector<Rva007719C0Element,
            _STL::allocator<Rva007719C0Element> > *)store)->push_back(empty);
    }
    Rva007719C0Element *finish =
        ((_STL::vector<Rva007719C0Element,
            _STL::allocator<Rva007719C0Element> > *)store)->m_finish;
    {
        AsciiString mode = ini->getNextAsciiString();
        ((StringBase<char> &)(mode)).toLower();
        finish[-1].m_name =
            ini->getNextAsciiString();

        // Retail's compares land on the rowed StringBase<char>::compare (0x000069B1).
        if (((const StringBase<char> &)(mode)).compare("ramp") == 0)
            finish[-1].m_mode = 2;
        else if (((const StringBase<char> &)(mode)).compare("ladder") == 0)
            finish[-1].m_mode = 3;
    }
}
