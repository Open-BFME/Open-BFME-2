// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva0055FB37@Rva0055FB37@@QAEXPAVFile@@I@Z @0x0055FB37 504B chain lane writeINI via WriteHeader.
// Evidence: vslot 3 of DefaultModuleTemplate $01 0x0081BCF0 and ConcreteModuleTag $01 0x0081BF84; calls rowed WriteHeader 0x0055FA5F then ostringstream then 8x rowed IsZero 0x001F3744 gated SizeRate SizeRateDamping AngleZ AngularRateZ AngularDamping AngleXY AngularRateXY AngularDampingXY via rowed 0x001F8B5F plus Rotation enum via rowed 0x001F82AB with table g_00C1B6D8 then rowed str plus FileWrite 0x001F458B plus free plus footer 0x003AFC6B.
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

void Rva0055FA5FWriteHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);

extern const char *g_00C1B6D8[];

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
void Rva001F82ABWrite(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    char const **value);

class Rva0055FB37 {
public:
    void rva0055FB37(File *file, unsigned int flags);
private:
    char m_pad[12];
    S001F87D5 m_sizeRate;
    S001F87D5 m_sizeRateDamping;
    S001F87D5 m_angleZ;
    S001F87D5 m_angularRateZ;
    S001F87D5 m_angularDamping;
    int m_rotation;
    S001F87D5 m_angleXY;
    S001F87D5 m_angularRateXY;
    S001F87D5 m_angularDampingXY;
};

void Rva0055FB37::rva0055FB37(File *file, unsigned int flags)
{
    Rva0055FA5FWriteHeader(this, file, &flags);
    _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_sizeRate))
        Rva001F8B5FWrite(oss, flags, "SizeRate", m_sizeRate);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_sizeRateDamping))
        Rva001F8B5FWrite(oss, flags, "SizeRateDamping", m_sizeRateDamping);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_angleZ))
        Rva001F8B5FWrite(oss, flags, "AngleZ", m_angleZ);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_angularRateZ))
        Rva001F8B5FWrite(oss, flags, "AngularRateZ", m_angularRateZ);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_angularDamping))
        Rva001F8B5FWrite(oss, flags, "AngularDamping", m_angularDamping);
    if (m_rotation != 1)
        Rva001F82ABWrite(oss, flags, "Rotation", &g_00C1B6D8[m_rotation]);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_angleXY))
        Rva001F8B5FWrite(oss, flags, "AngleXY", m_angleXY);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_angularRateXY))
        Rva001F8B5FWrite(oss, flags, "AngularRateXY", m_angularRateXY);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_angularDampingXY))
        Rva001F8B5FWrite(oss, flags, "AngularDampingXY", m_angularDampingXY);
    Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
    Rva003AFC6BWrite(file, &flags);
}

// Native5625C5..56285E is a complete665B INI serializer. The retail
// field-parse table C6C710 independently agrees with all12 variable names
// and offsets0C..90 and the Rotation field9C. BF1 donor874e38488c7d
// DefaultModuleTemplate_writeINI and the verified BF2 sibling55FB37 give
// the writer/ostringstream pattern; original class/method name unproven.
class Rva005625C5 {
public:void rva005625C5(File *file,unsigned flags);
private:char pad[12];
 S001F87D5 m_StartSizeX;
 S001F87D5 m_StartSizeY;
 S001F87D5 m_StartSizeZ;
 S001F87D5 m_SizeRateX;
 S001F87D5 m_SizeRateY;
 S001F87D5 m_SizeRateZ;
 S001F87D5 m_SizeDampingX;
 S001F87D5 m_SizeDampingY;
 S001F87D5 m_SizeDampingZ;
 S001F87D5 m_AngleZ;
 S001F87D5 m_AngularRateZ;
 S001F87D5 m_AngularDamping;
 int rotation;
};
void Rva005625C5::rva005625C5(File *file,unsigned flags) {
 Rva0055FA5FWriteHeader(this,file,&flags);
 _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
 if(!Rva001F3744IsZero((const S001F3744*)&m_StartSizeX))
  Rva001F8B5FWrite(oss,flags,"StartSizeX",m_StartSizeX);
 if(!Rva001F3744IsZero((const S001F3744*)&m_StartSizeY))
  Rva001F8B5FWrite(oss,flags,"StartSizeY",m_StartSizeY);
 if(!Rva001F3744IsZero((const S001F3744*)&m_StartSizeZ))
  Rva001F8B5FWrite(oss,flags,"StartSizeZ",m_StartSizeZ);
 if(!Rva001F3744IsZero((const S001F3744*)&m_SizeRateX))
  Rva001F8B5FWrite(oss,flags,"SizeRateX",m_SizeRateX);
 if(!Rva001F3744IsZero((const S001F3744*)&m_SizeRateY))
  Rva001F8B5FWrite(oss,flags,"SizeRateY",m_SizeRateY);
 if(!Rva001F3744IsZero((const S001F3744*)&m_SizeRateZ))
  Rva001F8B5FWrite(oss,flags,"SizeRateZ",m_SizeRateZ);
 if(!Rva001F3744IsZero((const S001F3744*)&m_SizeDampingX))
  Rva001F8B5FWrite(oss,flags,"SizeDampingX",m_SizeDampingX);
 if(!Rva001F3744IsZero((const S001F3744*)&m_SizeDampingY))
  Rva001F8B5FWrite(oss,flags,"SizeDampingY",m_SizeDampingY);
 if(!Rva001F3744IsZero((const S001F3744*)&m_SizeDampingZ))
  Rva001F8B5FWrite(oss,flags,"SizeDampingZ",m_SizeDampingZ);
 if(!Rva001F3744IsZero((const S001F3744*)&m_AngleZ))
  Rva001F8B5FWrite(oss,flags,"AngleZ",m_AngleZ);
 if(!Rva001F3744IsZero((const S001F3744*)&m_AngularRateZ))
  Rva001F8B5FWrite(oss,flags,"AngularRateZ",m_AngularRateZ);
 if(!Rva001F3744IsZero((const S001F3744*)&m_AngularDamping))
  Rva001F8B5FWrite(oss,flags,"AngularDamping",m_AngularDamping);
 if(rotation!=1)Rva001F82ABWrite(oss,flags,"Rotation",&g_00C1B6D8[rotation]);
 Rva001F458BWrite(*file,(const Rva001F458BText&)oss.str());
 Rva003AFC6BWrite(file,&flags);
}
