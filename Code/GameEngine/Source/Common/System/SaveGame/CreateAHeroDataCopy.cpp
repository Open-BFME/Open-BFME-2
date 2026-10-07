// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// CreateAHeroData is identified by retail typeName0x409353 and vtable0xC38D88.
// Its copy and destructor establish this0x140-byte Snapshot-derived layout.
// Container identities follow the independently recovered copy-call chains:
// int/int trees21CF2C; AsciiString payload tree40884B; bit-vector389413;
// int/vector<unsigned> tree21E146. Unknown application fields stay offset-named.
#include <memory>
#include <vector>
#include <map>

#include "ascii_string.h"
#include "unicode_string.h"
class Xfer;
class Snapshot {
public:
    Snapshot() {}
    Snapshot(const Snapshot &o) {}
    virtual ~Snapshot();
protected:
    virtual void crc(Xfer *xfer) = 0;
    virtual void xfer(Xfer *xfer) = 0;
    virtual void loadPostProcess() = 0;
};
struct TreeHintPayload001F8ACB { unsigned int value; };
bool operator<(const AsciiString &, const AsciiString &);
// Scalar-vector copy is supplied by the complete retail 0x002CFAB9 provider.
namespace _STL {
template <> vector<unsigned int>::vector(const vector<unsigned int> &);
}

typedef _STL::map<int,int> IntegerMap;
typedef _STL::map<AsciiString,TreeHintPayload001F8ACB> StringPayloadMap;
typedef _STL::map<int,_STL::vector<unsigned int> > IntegerVectorMap;

// Recovered separately: default5C39DE/13 and assignment406E22/37.
// The implicit destructor is the complete5-byte release tail at48BA39.
struct BfmeHeroElement005C39DE {
    AsciiString text;
    unsigned int word4, word8;
    BfmeHeroElement005C39DE();
    BfmeHeroElement005C39DE &operator=(const BfmeHeroElement005C39DE &);
};
class CreateAHeroData;
// Retail searches the pointer registry atVA DFE358 and appends if absent.
void RegisterCreateAHeroAtRva0021D517(CreateAHeroData *);

class CreateAHeroData : public Snapshot {
    unsigned int word04;
    UnicodeString text08;
    unsigned int word0C, word10;
    IntegerMap map14, map20;
    unsigned int word2C, word30, word34, word38;
    _STL::vector<AsciiString> strings3C;
    unsigned char flag48;
    AsciiString text4C;
    StringPayloadMap map50;
    _STL::vector<bool> bits5C;
    unsigned char flag70, flag71;
    IntegerVectorMap map74;
    BfmeHeroElement005C39DE elements80[15];
    unsigned int word134, word138, word13C;
public:
    CreateAHeroData(const CreateAHeroData &o)
        : Snapshot(o), word04(o.word04), text08(o.text08),
          word0C(o.word0C), word10(o.word10), map14(o.map14), map20(o.map20),
          word2C(o.word2C), word30(o.word30), word34(o.word34), word38(0x2FF),
          strings3C(o.strings3C), flag48(o.flag48), text4C(o.text4C),
          map50(o.map50), bits5C(o.bits5C), flag70(0), flag71(o.flag71),
          map74(o.map74), elements80(), word134(o.word134),
          word138(o.word138), word13C(o.word13C)
    {
        for (int i = 0; i < 15; ++i)
            elements80[i] = o.elements80[i];
        RegisterCreateAHeroAtRva0021D517(this);
    }
    virtual ~CreateAHeroData();
    virtual void crc(Xfer *xfer);
    virtual void xfer(Xfer *xfer);
    virtual void loadPostProcess();
};
template void _STL::_Construct<CreateAHeroData,CreateAHeroData>(CreateAHeroData *,const CreateAHeroData &);
