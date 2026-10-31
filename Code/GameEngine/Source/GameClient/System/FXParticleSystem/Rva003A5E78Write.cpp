// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport46
//
// ?rva003A5E78@WindModuleTemplate@FXParticleSystem@@QAEXPAVFile@@I@Z
// retail 0x003A5E78..0x003A611B (675 bytes): the wind module's writeINI.
//
// Identity:
// - It is slot 3 of the ConcreteModuleTemplate<DefaultModuleTag<7>>
//   ModuleTemplate vtable 0x0081BFB8 and of the abstract vtable 0x0081BFA4.
// - Its WindModuleInfo (GetSnapshotName in vtable 0x0081BF94) sits at +0x08.
//   The layout comes from the rowed WindModuleInfo ctor 0x003A53C4
//   (Rva003A53C4Finish.cpp).
// - It calls the rowed wind header writer 0x003A5DA0 (category 7 WIND).
//
// What the body does:
// - The WindMotion enum is written through rowed 0x001F82AB with the name
//   table at VA 0x00C1B6C4 (NONE, Unused, PingPong, Circular). It is skipped
//   when it equals the default 1.
// - Eleven floats are written through rowed 0x003A5D34 when they differ from
//   the ctor defaults. Those defaults are the owned kG1..kG9 globals or 0.0f.
// - The rowed str, File write and footer 0x003AFC6B follow.
//
// The shape is the same as the rowed sibling Rva0055FB37Write.cpp.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <sstream>
// basic_stringbuf<char>'s constructor is the rowed body 0x001F6813
// (stlport_narrow_ostringstream_dtor.cpp); declared so this unit does not emit
// its own constructor chain with a non-retail basic_streambuf<char> constructor.
namespace _STL { template <> basic_stringbuf<char, char_traits<char>, allocator<char> >::basic_stringbuf(int); }
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_ostream<char, char_traits<char> >::basic_ostream(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> basic_ostream<char, char_traits<char> >::~basic_ostream(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> void basic_stringbuf<char, char_traits<char>, allocator<char> >::_M_append_buffer() const; }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::append(unsigned int, char); }
namespace _STL { template <> void basic_ios<char, char_traits<char> >::clear(int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> locale basic_ios<char, char_traits<char> >::imbue(locale const &); }
namespace _STL { template <> void basic_ios<char, char_traits<char> >::init(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::push_back(char); }
namespace _STL { template <> basic_streambuf<char, char_traits<char> > * basic_ios<char, char_traits<char> >::rdbuf(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > basic_ostringstream<char, char_traits<char>, allocator<char> >::str() const; }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > basic_stringbuf<char, char_traits<char>, allocator<char> >::str() const; }
namespace _STL { template <> char basic_ios<char, char_traits<char> >::widen(char) const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$append@PBD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAEAAV01@PBD0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> template <> basic_string<char,char_traits<char>,allocator<char> > & basic_string<char,char_traits<char>,allocator<char> >::append<char const *>(char const *,char const *,forward_iterator_tag const &); }
// Suppress this TU's non-retail copy of ??1?$basic_ostringstream@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@UAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_ostringstream<char,char_traits<char>,allocator<char> >::~basic_ostringstream(); }
// Suppress this TU's non-retail copy of ?xsputn@?$basic_stringbuf@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@MAEHPBDH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> int basic_stringbuf<char,char_traits<char>,allocator<char> >::xsputn(char const *,int); }
// Suppress this TU's non-retail copy of ??$uninitialized_copy@PADPAD@_STL@@YAPADPAD00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * uninitialized_copy<char *,char *>(char *,char *,char *); }

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

void Rva003A5DA0WriteWindHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);

// The wind-motion name table rowed at 0x00C1B6C4 (Rva003A547EXfer.cpp).
namespace FXParticleSystem { extern const char * const WindMotionNames[]; }
extern "C" const float kG1;
extern "C" const float kG2;
extern "C" const float kG3;
extern "C" const float kG4;
extern "C" const float kG5;
extern "C" const float kG6;
extern "C" const float kG8;
extern "C" const float kG9;

void Rva001F82ABWrite(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    char const **value);
void Rva003A5D34Write(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    float const &value);

namespace FXParticleSystem {
class WindModuleTemplate {
public:
    void rva003A5E78(File *file, unsigned int flags);
private:
    char m_pad[12];
    int m_windMotion;                       // +0x0C
    float m_windStrength;                   // +0x10
    float m_windFullStrengthDist;           // +0x14
    float m_windZeroStrengthDist;           // +0x18
    float m_1C;
    float m_20;
    float m_windAngleChangeMin;             // +0x24
    float m_windAngleChangeMax;             // +0x28
    float m_2C;
    float m_windPingPongStartAngleMin;      // +0x30
    float m_windPingPongStartAngleMax;      // +0x34
    float m_38;
    float m_windPingPongEndAngleMin;        // +0x3C
    float m_windPingPongEndAngleMax;        // +0x40
    bool m_44;
    float m_turbulenceAmplitude;            // +0x48
    float m_turbulenceFrequency;            // +0x4C
};

void WindModuleTemplate::rva003A5E78(File *file, unsigned int flags)
{
    Rva003A5DA0WriteWindHeader(this, file, &flags);
    _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
    if (m_windMotion != 1)
        Rva001F82ABWrite(oss, flags, "WindMotion", const_cast<const char **>(&FXParticleSystem::WindMotionNames[m_windMotion]));
    if (m_windStrength != kG1)
        Rva003A5D34Write(oss, flags, "WindStrength", m_windStrength);
    if (m_windFullStrengthDist != kG2)
        Rva003A5D34Write(oss, flags, "WindFullStrengthDist", m_windFullStrengthDist);
    if (m_windZeroStrengthDist != kG3)
        Rva003A5D34Write(oss, flags, "WindZeroStrengthDist", m_windZeroStrengthDist);
    if (m_windAngleChangeMin != kG4)
        Rva003A5D34Write(oss, flags, "WindAngleChangeMin", m_windAngleChangeMin);
    if (m_windAngleChangeMax != kG5)
        Rva003A5D34Write(oss, flags, "WindAngleChangeMax", m_windAngleChangeMax);
    if (m_windPingPongStartAngleMin != 0.0f)
        Rva003A5D34Write(oss, flags, "WindPingPongStartAngleMin", m_windPingPongStartAngleMin);
    if (m_windPingPongStartAngleMax != kG6)
        Rva003A5D34Write(oss, flags, "WindPingPongStartAngleMax", m_windPingPongStartAngleMax);
    if (m_windPingPongEndAngleMin != kG8)
        Rva003A5D34Write(oss, flags, "WindPingPongEndAngleMin", m_windPingPongEndAngleMin);
    if (m_windPingPongEndAngleMax != kG9)
        Rva003A5D34Write(oss, flags, "WindPingPongEndAngleMax", m_windPingPongEndAngleMax);
    if (m_turbulenceAmplitude != 0.0f)
        Rva003A5D34Write(oss, flags, "TurbulenceAmplitude", m_turbulenceAmplitude);
    if (m_turbulenceFrequency != 0.0f)
        Rva003A5D34Write(oss, flags, "TurbulenceFrequency", m_turbulenceFrequency);
    Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
    Rva003AFC6BWrite(file, &flags);
}
}
