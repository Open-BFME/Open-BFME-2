// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva0055F368@Rva0055F368@@QAEXPAVFile@@I@Z @0x0055F368 326B chain lane writeINI via WriteHeader.
// Evidence: vslot 3 of DefaultModuleTemplate $02 0x0081BCC0 and ConcreteModuleTag $02 0x0081BF60; calls rowed WriteHeader 0x0055F290 then ostringstream then rowed t4IsZero float Gravity via rowed float Write 0x003A5D34 then rowed IsZero 0x001F3744 VelocityDamping via rowed 0x001F8B5F then rowed RGB IsZero 0x0055CCEF DriftVelocity via rowed Vec 0x001F89E2 then bool Swirly ParticlesAttachToBone via rowed 0x001F89C3 then rowed str plus FileWrite 0x001F458B plus free plus footer 0x003AFC6B.
#include <sstream>
#include "ascii_string.h"

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

void Rva0055F290WriteHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);

int __cdecl t4IsZero005F4180(const float *v);
void Rva003A5D34Write(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    float const &value);

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
void Rva001F8B5FWrite(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    const S001F87D5 &value);

struct RGBColor {
    float red;
    float green;
    float blue;
};
struct Vec001F8810 {
    float x;
    float y;
    float z;
};
int Rva0055CCEFIsZero(const RGBColor &color);
void Rva001F89E2Write(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    const Vec001F8810 &value);
void Rva001F89C3Write(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    bool const *value);

class Rva0055F368 {
public:
    void rva0055F368(File *file, unsigned int flags);
private:
    char m_pad[12];
    Vec001F8810 m_driftVelocity;
    float m_gravity;
    S001F87D5 m_velocityDamping;
    bool m_swirly;
    bool m_particlesAttachToBone;
};

void Rva0055F368::rva0055F368(File *file, unsigned int flags)
{
    Rva0055F290WriteHeader(this, file, &flags);
    _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
    if (!(unsigned char)t4IsZero005F4180(&m_gravity))
        Rva003A5D34Write(oss, flags, "Gravity", m_gravity);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_velocityDamping))
        Rva001F8B5FWrite(oss, flags, "VelocityDamping", m_velocityDamping);
    if (!(unsigned char)Rva0055CCEFIsZero((const RGBColor &)m_driftVelocity))
        Rva001F89E2Write(oss, flags, "DriftVelocity", m_driftVelocity);
    Rva001F89C3Write(oss, flags, "Swirly", &m_swirly);
    Rva001F89C3Write(oss, flags, "ParticlesAttachToBone", &m_particlesAttachToBone);
    Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
    Rva003AFC6BWrite(file, &flags);
}
