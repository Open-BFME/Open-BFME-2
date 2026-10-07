// cl: /O1 /arch:SSE /G7 /MD /EHs-c- /Ob1 /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??4Rva0031E4BA@@QAEAAV0@ABV0@@Z @0x0031E4BA 822B.
// Target evidence: sequential member assignment and return this; caller31EBDE.
// Member types carry ledger callee spellings; original owner and member names
// remain unknown. First16-byte record is assigned through the existing FX row;
// that callee's donor name does not establish this owner's subsystem identity.
#include "ascii_string.h"
#include <vector>
class FXParticleSystem {
public:
    class StreakDrawModuleTemplate {
    public:
        StreakDrawModuleTemplate &operator=(const StreakDrawModuleTemplate &);
    private:
        unsigned int fields[4];
    };
};
struct Rva0026F4F4Element { unsigned words[1]; bool operator<(const Rva0026F4F4Element&)const; bool operator==(const Rva0026F4F4Element&)const; };
struct Rva0021C21BElement { char bytes[4]; };
struct BfmeAsciiScalarValue8 {
    AsciiString text; unsigned int value;
    BfmeAsciiScalarValue8();
    BfmeAsciiScalarValue8(const BfmeAsciiScalarValue8 &);
    BfmeAsciiScalarValue8 &operator=(const BfmeAsciiScalarValue8 &);
};
namespace _STL { template <> vector<AsciiString> &vector<AsciiString >::operator=(const vector<AsciiString> &); }
namespace _STL { template <> vector<Rva0026F4F4Element> &vector<Rva0026F4F4Element >::operator=(const vector<Rva0026F4F4Element> &); }
namespace _STL { template <> vector<Rva0021C21BElement> &vector<Rva0021C21BElement >::operator=(const vector<Rva0021C21BElement> &); }
namespace _STL { template <> vector<BfmeAsciiScalarValue8> &vector<BfmeAsciiScalarValue8 >::operator=(const vector<BfmeAsciiScalarValue8> &); }
struct Block16 { unsigned int words[4]; };
struct Block28 { unsigned int words[7]; };
struct Block76 { unsigned int words[19]; };
struct Block128 { unsigned int words[32]; };
class Rva0031E4BA {
public:
    Rva0031E4BA &operator=(const Rva0031E4BA &other);
private:
    FXParticleSystem::StreakDrawModuleTemplate m000;
    AsciiString m010;
    unsigned int m014;
    unsigned int m018;
    unsigned int m01c;
    unsigned int m020;
    unsigned int m024;
    _STL::vector<Rva0026F4F4Element> m028;
    bool m034;
    char pad035[3];
    _STL::vector<AsciiString> m038;
    unsigned int m044;
    AsciiString m048;
    unsigned int m04c;
    AsciiString m050;
    AsciiString m054;
    _STL::vector<AsciiString> m058;
    _STL::vector<AsciiString> m064;
    AsciiString m070;
    AsciiString m074;
    AsciiString m078;
    AsciiString m07c;
    unsigned int m080;
    unsigned int m084;
    unsigned int m088;
    unsigned int m08c;
    Block16 m090;
    unsigned int m0a0;
    _STL::vector<Rva0021C21BElement> m0a4;
    unsigned int m0b0;
    _STL::vector<AsciiString> m0b4;
    unsigned int m0c0;
    unsigned int m0c4;
    _STL::vector<BfmeAsciiScalarValue8> m0c8;
    _STL::vector<BfmeAsciiScalarValue8> m0d4;
    _STL::vector<BfmeAsciiScalarValue8> m0e0;
    _STL::vector<Rva0026F4F4Element> m0ec;
    unsigned int m0f8;
    unsigned int m0fc;
    bool m100;
    bool m101;
    bool m102;
    bool m103;
    bool m104;
    bool m105;
    bool m106;
    bool m107;
    unsigned int m108;
    bool m10c;
    char pad10d[3];
    Block28 m110;
    bool m12c;
    char pad12d[3];
    unsigned int m130;
    unsigned int m134;
    bool m138;
    char pad139[3];
    Block76 m13c;
    _STL::vector<AsciiString> m188;
    Block76 m194;
    Block76 m1e0;
    unsigned int m22c;
    unsigned int m230;
    _STL::vector<Rva0021C21BElement> m234;
    AsciiString m240;
    unsigned int m244;
    AsciiString m248;
    Block128 m24c;
};
Rva0031E4BA &Rva0031E4BA::operator=(const Rva0031E4BA &other)
{
    m000 = other.m000;
    m010 = other.m010;
    m014 = other.m014;
    m018 = other.m018;
    m01c = other.m01c;
    m020 = other.m020;
    m024 = other.m024;
    m028 = other.m028;
    m034 = other.m034;
    m038 = other.m038;
    m044 = other.m044;
    m048 = other.m048;
    m04c = other.m04c;
    m050 = other.m050;
    m054 = other.m054;
    m058 = other.m058;
    m064 = other.m064;
    m070 = other.m070;
    m074 = other.m074;
    m078 = other.m078;
    m07c = other.m07c;
    m080 = other.m080;
    m084 = other.m084;
    m088 = other.m088;
    m08c = other.m08c;
    m090 = other.m090;
    m0a0 = other.m0a0;
    m0a4 = other.m0a4;
    m0b0 = other.m0b0;
    m0b4 = other.m0b4;
    m0c0 = other.m0c0;
    m0c4 = other.m0c4;
    m0c8 = other.m0c8;
    m0d4 = other.m0d4;
    m0e0 = other.m0e0;
    m0ec = other.m0ec;
    m0f8 = other.m0f8;
    m0fc = other.m0fc;
    m100 = other.m100;
    m101 = other.m101;
    m102 = other.m102;
    m103 = other.m103;
    m104 = other.m104;
    m105 = other.m105;
    m106 = other.m106;
    m107 = other.m107;
    m108 = other.m108;
    m10c = other.m10c;
    m110 = other.m110;
    m12c = other.m12c;
    m130 = other.m130;
    m134 = other.m134;
    m138 = other.m138;
    m13c = other.m13c;
    m188 = other.m188;
    m194 = other.m194;
    m1e0 = other.m1e0;
    m22c = other.m22c;
    m230 = other.m230;
    m234 = other.m234;
    m240 = other.m240;
    m244 = other.m244;
    m248 = other.m248;
    m24c = other.m24c;
    return *this;
}
