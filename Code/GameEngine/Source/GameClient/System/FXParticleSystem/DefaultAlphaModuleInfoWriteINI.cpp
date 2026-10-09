// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva0055B735@DefaultAlphaModuleInfo@FXParticleSystem@@QAEXPAVFile@@I@Z @0x0055B735 302B writeINI via WriteHeader.
// Evidence: vslot 7 of DefaultAlphaModuleInfo 0x0081BA60 (slot 0 its rowed
// ??_E 0x003A61B3; slot 2 the rowed GetSnapshotName 0x003A611B) and of
// ConcreteModuleTemplate DefaultModuleTag $01 0x0081BF10; calls rowed
// WriteHeader 0x0055B65D (category 1) then ostringstream then for each of
// 8 keyframes (random variable plus frame; 16 bytes from +0x0C) gated by
// rowed IsZero 0x001F3744 or a non-zero frame: Pad 0x001F6951 "Alpha"
// index+1 " = " then the rowed variable Put 0x001F87D5 ' ' frame '\n'
// (_M_put_nowiden _M_put_num<unsigned long> _M_put_char) then rowed str plus
// FileWrite 0x001F458B plus free plus footer 0x003AFC6B.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <sstream>

class File {
public:
    virtual ~File();
    virtual bool open(const char *n, int a = 0);
    virtual void close();
    virtual int read(void *b, int bsz);
    virtual int write(const void *b, int bsz);
};
struct Rva001F458BText {
    const char *m_start;
    const char *m_finish;
};
File &Rva001F458BWrite(File &file, const Rva001F458BText &text);
extern "C" void __cdecl free(void *p);

void Rva0055B65DWriteHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F6951Pad(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int n);

struct S001F87D5 {
    char _0[4];
    float x;
    float y;
};
struct S001F3744 {
    char m_00[4];
    float m_04;
    float m_08;
};
bool __cdecl Rva001F3744IsZero(const S001F3744 *p);
_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F87D5Put(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    const S001F87D5 &s);

namespace FXParticleSystem {

struct AlphaKeyframe {
    S001F87D5 m_alpha;
    unsigned int m_frame;
};

class DefaultAlphaModuleInfo {
public:
    void rva0055B735(File *file, unsigned int flags);
private:
    char m_pad[12];
    AlphaKeyframe m_alphaKey[8]; // +0x0C
};

void DefaultAlphaModuleInfo::rva0055B735(File *file, unsigned int flags)
{
    Rva0055B65DWriteHeader(this, file, &flags);
    _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
    for (unsigned int i = 0; i < 8; ++i)
    {
        if (!Rva001F3744IsZero((const S001F3744 *)&m_alphaKey[i].m_alpha) || m_alphaKey[i].m_frame != 0)
        {
            Rva001F6951Pad(oss, flags) << "Alpha" << i + 1 << " = ";
            Rva001F87D5Put(oss, m_alphaKey[i].m_alpha) << ' ' << m_alphaKey[i].m_frame << '\n';
        }
    }
    Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
    Rva003AFC6BWrite(file, &flags);
}

} // namespace FXParticleSystem
