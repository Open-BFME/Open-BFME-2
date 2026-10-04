// cl: -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS /Os -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw
//
// ?parseEmbedPortal@W3DModelDrawModuleData@@SAXPAVINI@@PAX1PBX@Z
// retail 0x000C39F5, 190 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawModuleData_parseEmbedPortal.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /Os it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here.
// stlport
// Retail field-table owner: W3DModelDrawModuleData::EmbedPortal at +0xF0.
// class-gate: allow AsciiString the donor TU-local one-pointer AsciiString/StringBase view emits the retail 190B body at 0x000C39F5, including the bfmeCompare1294 ABI name that resolves to the rowed StringBase<char>::compare body at 0x000069B1

typedef int Int;

namespace _STL
{
struct Rva007719C0Element;
}

template <typename T>
class StringBase
{
    friend class AsciiString;
    friend struct _STL::Rva007719C0Element;

public:
    StringBase() : m_data(0) {}
    StringBase(const StringBase<T> &source);

    StringBase<T> &operator=(const StringBase<T> &source)
    {
        set(source);
        return *this;
    }

    void set(const StringBase<T> &source);
    void toLower();

private:
    void releaseBuffer();

public:
    void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const AsciiString &source) :
        StringBase<char>(*(const StringBase<char> *)&source) {}
    ~AsciiString();
    AsciiString &operator=(const AsciiString &source);

    void toLower() { StringBase<char>::toLower(); }
    void set(const AsciiString &source)
    {
        ((StringBase<char> *)this)->set(
            *(const StringBase<char> *)&source);
    }
    Int bfmeCompare1294(const char *text) const;
};

namespace _STL
{
struct __false_type
{
};

struct Rva007719C0Element
{
    Int m_mode;
    StringBase<char> m_name;
    Rva007719C0Element() : m_name() {}
    ~Rva007719C0Element()
    {
        ((AsciiString *)&m_name)->~AsciiString();
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
    _Construct(destination, source);
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

class INI
{
public:
    AsciiString getNextAsciiString();
};

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
        mode.toLower();
        finish[-1].m_name =
            *(const StringBase<char> *)&ini->getNextAsciiString();

        if (mode.bfmeCompare1294("ramp") == 0)
            finish[-1].m_mode = 2;
        else if (mode.bfmeCompare1294("ladder") == 0)
            finish[-1].m_mode = 3;
    }
}
