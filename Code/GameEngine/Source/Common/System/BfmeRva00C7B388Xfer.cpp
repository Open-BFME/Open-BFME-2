// cl: /Ireference/shims/bfme2_ascii

// A text-dumping Xfer, vtable 0x00C7B388 (constructor 0x0060DEB1, destructor
// 0x0060DED5).  Every typed transfer prints its value with a labelled format --
// "%i=0x%x [byte]", "version: %i", "'%s' [ascii]" -- through the variadic
// helper at 0x0060D5F2, which either writes one indent unit per open block or
// formats into a 1 KB buffer and hands the text to the stream at +8.  A flag at
// +4 suppresses the indent once, after a label has been printed.  Retail keeps
// no string naming the class; the name XferSaveAsText (renamed from the
// address-derived BfmeRva00C7B388) is target evidence from WorldBuilder's
// debug xfer_debug.cpp, whose ~XferSaveAsText (asserting !m_file, the stream
// at +8, then destroying the vector at +0x0C) aligns with the destructor at
// 0x0060DED5 and whose XferSaveAsText::XferRawBytes aligns with 0x0060D66E.
// The method names are the base Xfer's, mapped slot by slot (the operator==
// run is laid out in reverse declaration order, as Xfer.cpp explains).
//
// The base class and the value types below are Xfer.cpp's model verbatim, so
// the vtable lines up with the shipped one.

#include <stdarg.h>

// Declared by hand: retail calls _vsnprintf through the msvcr71 import table
// but strlen directly (its thunk at 0x00629170), which no one pair of CRT
// headers gives under a single /MD setting.
extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char *buffer, unsigned int count, const char *format, va_list args);
extern "C" unsigned int __cdecl strlen(const char *text);

struct Coord3DBase
{
    float x;
    float y;
    float z;
};

struct ICoord3D
{
    int x;
    int y;
    int z;
};

#include "../../../../Libraries/Include/Lib/Coord2D.h"

struct ICoord2D
{
    int x;
    int y;
};

struct Region3D
{
    Coord3DBase lo;
    Coord3DBase hi;
};

struct IRegion3D
{
    ICoord3D lo;
    ICoord3D hi;
};

struct Region2D
{
    Coord2D lo;
    Coord2D hi;
};

struct IRegion2D
{
    ICoord2D lo;
    ICoord2D hi;
};

struct RealRange
{
    float lo;
    float hi;
};

struct RGBColor
{
    float red;
    float green;
    float blue;
};

struct RGBAColorReal
{
    float red;
    float green;
    float blue;
    float alpha;
};

struct RGBAColorInt
{
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int alpha;
};

class Xfer;

class Snapshot
{
public:
    virtual ~Snapshot();
    virtual void crc(Xfer *xfer) = 0;
    virtual void loadPostProcess() = 0;
    virtual void xfer(Xfer *xfer) = 0;
};

// The string types are reduced to what their transfers read: a pointer to a
// data block whose text starts eight bytes in.  ASCII and Unicode fall back to
// the shared empty literals when the pointer is null; the pooled string reads
// through it unchecked.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "ascii_string.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
#include "unicode_string.h"

class PooledString
{
    struct Data { int unexamined0; int unexamined4; };
    Data *m_data;

public:
    const char *peek() const { return reinterpret_cast<const char *>(m_data + 1); }
};
struct XferUnknown11;

// upstream layout: Code/GameEngine/Source/Common/System/Xfer.cpp (retail vtable 0x00BBB910)
class Xfer
{
public:
    class Version;

    Xfer();
    virtual ~Xfer() {}

    void Version1();

    virtual bool IsStoring() const;
    virtual bool IsLoading() const;
    virtual bool IsCRC() const;
    virtual bool IsLightCRC() const;

    virtual void v5() = 0;
    virtual void EndBlock() = 0;
    virtual void v7() = 0;

    virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
    virtual Xfer &XferRawBytes(void *data, unsigned int size);
    virtual Xfer &operator==(bool &value);
    virtual Xfer &operator==(char &value);
    virtual Xfer &operator==(unsigned char &value);
    virtual Xfer &operator==(short &value);
    virtual Xfer &operator==(unsigned short &value);
    virtual Xfer &operator==(int &value);
    virtual Xfer &operator==(unsigned int &value);
    virtual Xfer &operator==(__int64 &value);
    virtual Xfer &operator==(float &value);
    virtual Xfer &operator==(AsciiString &value);
    virtual Xfer &operator==(UnicodeString &value);
    virtual Xfer &operator==(PooledString &value);
    virtual Xfer &operator==(Coord3DBase &value);
    virtual Xfer &operator==(ICoord3D &value);
    virtual Xfer &operator==(Region3D &value);
    virtual Xfer &operator==(IRegion3D &value);
    virtual Xfer &operator==(Coord2D &value);
    virtual Xfer &operator==(ICoord2D &value);
    virtual Xfer &operator==(Region2D &value);
    virtual Xfer &operator==(IRegion2D &value);
    virtual Xfer &operator==(RealRange &value);
    virtual Xfer &operator==(RGBColor &value);
    virtual Xfer &operator==(RGBAColorReal &value);
    virtual Xfer &operator==(RGBAColorInt &value);
    virtual Xfer &operator==(Snapshot &value);
    virtual Xfer &operator==(XferUnknown11 &value) = 0;
    virtual Xfer &operator==(Version &value);

    virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
    virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
    Version(unsigned char current, unsigned char minimum)
        : m_current(current), m_minimum(minimum) {}

    unsigned char m_current;
    unsigned char m_minimum;
};

// The text sink: only its write slot (+0x10) is called.
struct BfmeRva00C7B388Stream
{
    virtual void _M_slot_00();
    virtual void _M_slot_04();
    virtual void _M_slot_08();
    virtual void _M_slot_0c();
    virtual void Write(const char *text, int length);
};

class XferSaveAsText : public Xfer
{
public:
    static void __cdecl Print(XferSaveAsText *self, const char *format, ...);

    virtual ~XferSaveAsText();

    virtual Xfer &operator==(bool &value);
    virtual Xfer &operator==(char &value);
    virtual Xfer &operator==(unsigned char &value);
    virtual Xfer &operator==(short &value);
    virtual Xfer &operator==(unsigned short &value);
    virtual Xfer &operator==(int &value);
    virtual Xfer &operator==(unsigned int &value);
    virtual Xfer &operator==(__int64 &value);
    virtual Xfer &operator==(float &value);
    virtual Xfer &operator==(AsciiString &value);
    virtual Xfer &operator==(UnicodeString &value);
    virtual Xfer &operator==(PooledString &value);
    virtual Xfer &operator==(Coord3DBase &value);
    virtual Xfer &operator==(ICoord3D &value);
    virtual Xfer &operator==(Region3D &value);
    virtual Xfer &operator==(IRegion3D &value);
    virtual Xfer &operator==(Coord2D &value);
    virtual Xfer &operator==(ICoord2D &value);
    virtual Xfer &operator==(Region2D &value);
    virtual Xfer &operator==(IRegion2D &value);
    virtual Xfer &operator==(RealRange &value);
    virtual Xfer &operator==(RGBColor &value);
    virtual Xfer &operator==(RGBAColorReal &value);
    virtual Xfer &operator==(RGBAColorInt &value);
    virtual Xfer &operator==(Xfer::Version &value);
    virtual Xfer &XferRawBytes(void *data, unsigned int size);
    virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);
    virtual void EndBlock();
    int rva0060DF27(const char *s);

private:
    bool m_bfme04;				// +0x04: skip the indent once, after a label
    BfmeRva00C7B388Stream *m_bfme08;	// +0x08
    char *m_bfme0C;				// +0x0C: open-block stack, 12-byte entries
    char *m_bfme10;
    char *m_bfme14;
};

// 0x0060D5F2: with no format, one indent unit per open block; otherwise the
// formatted text, measured and handed to the stream.
void __cdecl XferSaveAsText::Print(XferSaveAsText *self, const char *format, ...)
{
    if (format == 0) {
        for (int depth = (self->m_bfme10 - self->m_bfme0C) / 12; depth != 0; --depth)
            self->m_bfme08->Write("  ", 2);
        return;
    }
    char buffer[0x400];
    va_list args;
    va_start(args, format);
    _vsnprintf(buffer, sizeof(buffer), format, args);
    self->m_bfme08->Write(buffer, strlen(buffer));
}

Xfer &XferSaveAsText::operator==(bool &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%i [bool]\n", value);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(Xfer::Version &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "version: %i\n", value.m_minimum);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(char &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%i=0x%x [byte]\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(unsigned char &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%i=0x%x [ubyte]\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(short &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%i=0x%x [short]\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(unsigned short &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%i=0x%x [ushort]\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(int &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%i=0x%x [int]\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(unsigned int &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%u=0x%x [uint]\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(__int64 &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%I64i=0x%I64x [int64]\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(float &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%1.6f=%f\n", value, value);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(AsciiString &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "'%s' [ascii]\n", value.str());
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(UnicodeString &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%'%S' [unicode]\n", value.str());
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(PooledString &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "'%s' [pool]\n", value.peek());
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(Coord3DBase &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%1.6f,y:%1.6f,z:%1.6f [coord3d]\n", value.x, value.y, value.z);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(ICoord3D &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%i,y:%i,z:%i [icoord3d]\n", value.x, value.y, value.z);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(Region3D &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%1.6f,y:%1.6f,z:%1.6f to x:%1.6f,y:%1.6f,z:%1.6f [region3d]\n",
        value.lo.x, value.lo.y, value.lo.z, value.hi.x, value.hi.y, value.hi.z);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(IRegion3D &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%i,y:%i,z:%i to x:%i,y:%i,z:%i [iregion3d]\n",
        value.lo.x, value.lo.y, value.lo.z, value.hi.x, value.hi.y, value.hi.z);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(Coord2D &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%1.6f,y:%1.6f [coord2d]\n", value.x, value.y);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(ICoord2D &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%i,y:%i [icoord2d]\n", value.x, value.y);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(Region2D &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%1.6f,y:%1.6f to x:%1.6f,y:%1.6f [region2d]\n",
        value.lo.x, value.lo.y, value.hi.x, value.hi.y);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(IRegion2D &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "x:%i,y:%i to x:%i,y:%i [iregion2d]\n",
        value.lo.x, value.lo.y, value.hi.x, value.hi.y);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(RealRange &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "%1.6f to %1.6f [range]\n", value.lo, value.hi);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(RGBColor &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "r:%1.3f,g:%1.3f,b:%1.3f [rgb]\n", value.red, value.green, value.blue);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(RGBAColorReal &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "r:%1.3f,g:%1.3f,b:%1.3f,a:%1.3f [rgba]\n",
        value.red, value.green, value.blue, value.alpha);
    m_bfme04 = false;
    return *this;
}

Xfer &XferSaveAsText::operator==(RGBAColorInt &value)
{
    if (!m_bfme04)
        Print(this, 0);
    Print(this, "r:%i,g:%i,b:%i,a:%i [irgba]\n", value.red, value.green, value.blue, value.alpha);
    m_bfme04 = false;
    return *this;
}

// 0x0060DD1B 124B: vtable slot 37 (offset 0x94) of 0x00C7B388, the XferEnum
// override. Base Xfer::XferEnum at 0x0060BBD5 is slot 37 of 0x00BBB910.
// Prints the integer value selected by size, then " [name]", then newline.
Xfer &XferSaveAsText::XferRawBytes(void *data, unsigned int size)
{
    if (size != 0) {
        if (data == 0)
            return *this;
    }
    if (m_bfme04) {
        Print(this, "\n");
        m_bfme04 = false;
    }
    if (size == 0) {
        Print(this, (const char *)0);
        Print(this, "--- 0 raw bytes\n");
        return *this;
    }
    unsigned int off;
    for (off = 0; off < size; off += 0x10) {
        unsigned int col = 0;
        Print(this, (const char *)col);
        Print(this, "%04x", off);
        for (col = 0; col < 0x10; ++col) {
            if ((col & 7) == 0)
                Print(this, " ");
            if (col + off < size)
                Print(this, " %02x", ((unsigned char *)data)[col + off]);
            else
                Print(this, "   ");
        }
        Print(this, "  ");
        for (col = 0; col < 0x10; ++col) {
            if (col + off >= size)
                break;
            unsigned char c = ((unsigned char *)data)[col + off];
            int ch = (c > 0x20) ? (int)c : '.';
            Print(this, "%c", ch);
        }
        Print(this, "\n");
    }
    return *this;
}
Xfer &XferSaveAsText::XferEnum(const char *name, void *data, unsigned int size)
{
    if (!m_bfme04)
        Print(this, 0);
    switch (size) {
    case 1:
        Print(this, "%i", *(unsigned char *)data);
        break;
    case 2:
        Print(this, "%i", *(unsigned short *)data);
        break;
    case 3:
        Print(this, "%i", *(int *)data & 0xffffff);
        break;
    case 4:
        Print(this, "%i", *(int *)data);
        break;
    }
    Print(this, " [%s]", name);
    Print(this, "\n");
    m_bfme04 = false;
    return *this;
}

// 0x0060DED5 54B: dtor. Stores derived vtable 0x00C7B388, destroys the
// narrow-string vector at +0x0C (rowed 0x000C0399), then stores base vtable
// 0x00BBB910 with no base call (empty inline base). EH prolog arms state 0
// around the vector call. Caller 0x0060DF0E.
extern "C" void __cdecl free(void *block);
namespace _STL
{
void free(void *block);
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T> class char_traits
{
};
template <class C, class Tr, class A> class basic_string
{
public:
	basic_string(const C *s, const A &a = A());
	basic_string(const basic_string &other);
	__forceinline ~basic_string() { if (_M_start != 0) free(_M_start); }
	char *_M_start;
	char *_M_finish;
	char *_M_end;
};
template <class T, class A> class vector
{
public:
	~vector();
	void push_back(const T &x);
};
}

XferSaveAsText::~XferSaveAsText()
{
	typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > NarrowString;
	typedef _STL::vector<NarrowString, _STL::allocator<NarrowString> > NarrowStringVec;
	((NarrowStringVec *)&m_bfme0C)->~NarrowStringVec();
}

// 0x0060DF27 142B: vslot 5 of 0x00C7B388. Open-block with a label: if the
// pending-label flag is set print the newline, always print the indent,
// print the label format with the name (empty string when null), then push a
// copy of the name onto the narrow-string vector at +0x0C. Returns 0.
int XferSaveAsText::rva0060DF27(const char *s)
{
	if (m_bfme04) {
		Print(this, "\n");
		m_bfme04 = false;
	}
	Print(this, (const char *)0);
	const char *t = s != 0 ? s : "";
	Print(this, "<%s>\n", t);
	typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > NarrowString;
	typedef _STL::vector<NarrowString, _STL::allocator<NarrowString> > NarrowStringVec;
	NarrowString tmp(t);
	((NarrowStringVec *)&m_bfme0C)->push_back(tmp);
	return 0;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:_bfmeAppend=?Print@XferSaveAsText@@SAXPAV1@PBDZZ")

// A local view of the existing three-pointer label stack. Its element is the
// same STLport narrow string used by the already-matched begin-block body.
struct BfmeTextLabelStackView
{
    typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > Label;
    Label *begin;
    Label *finish;
    Label *capacity;
    Label *end() const { return finish; }
    Label &back() { return *(end() - 1); }
    __forceinline void pop()
    {
        --finish;
        finish->Label::~Label();
    }
};

// Retail 0x0060DE23..0x0060DEB1; WB 0x0165F260 names EndBlock in xfer_debug.cpp.
// Slot 6 of vtable RVA 0x0087B388 pops the 12-byte label and prints its closing tag.
void XferSaveAsText::EndBlock()
{
    typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > NarrowString;
    BfmeTextLabelStackView &labels = *reinterpret_cast<BfmeTextLabelStackView *>(&m_bfme0C);
    if (m_bfme0C == m_bfme10)
        return;
    NarrowString tmp(labels.back());
    labels.pop();
    if (m_bfme04) {
        Print(this, "\n");
        m_bfme04 = false;
    }
    Print(this, (const char *)0);
    Print(this, "</%s>\n", tmp._M_start);
}
