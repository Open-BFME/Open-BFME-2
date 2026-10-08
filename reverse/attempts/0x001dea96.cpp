// ?iniParsePredefinedEvaEvent@Eva@@SAXPAVINI@@@Z
// partial score=0.9 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /DNDEBUG /MD /arch:SSE /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Existing 80-byte status clearer at 0x001DCD3C, moved here so Eva's
// element reset loop can see its register effects. Retail writes the 0x34-byte
// status layout; retain the observed write order and the existing barrier.
// -1 is the immutable float at .rdata RVA 0x007BB9AC (data_ledger.csv), so use
// the verified compiler literal rather than an address-named global.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva001DCD3C
{
public:
    void rva001DCD3C();
private:
    volatile float m_00;
    volatile float m_04;
    volatile float m_08;
    volatile float m_0C;
    volatile float m_10;
    volatile float m_14;
    volatile float m_18;
    volatile float m_1C;
    volatile unsigned char m_20;
    volatile unsigned char m_21;
    volatile unsigned char m_22;
    volatile unsigned char m_pad23;
    volatile float m_24;
    volatile float m_28;
    volatile float m_2C;
    volatile int m_30;
};
void Rva001DCD3C::rva001DCD3C()
{
    float v = -1.0f;
    float zero = 0.0f;
    m_00 = v;
    m_04 = v;
    _ReadWriteBarrier();
    m_20 = 0;
    m_08 = zero;
    m_0C = zero;
    m_10 = zero;
    m_21 = 0;
    m_14 = zero;
    m_18 = zero;
    m_1C = zero;
    m_22 = 0;
    m_24 = zero;
    m_28 = zero;
    m_2C = zero;
    m_30 = 0;
}


#include <vector>
#include <utility>
#include "ascii_string.h"
class INI { public: const char *getNextToken(const char*); char pad[8]; int loadType; };
class INIException { public: char *message; int code; INIException(int,const char*,...); INIException(const INIException&); ~INIException(); };
struct Rva00414BDBElement { ~Rva00414BDBElement(); };
class Rva001DE6E1 { public: Rva001DE6E1(); ~Rva001DE6E1() { reinterpret_cast<Rva00414BDBElement*>(this)->~Rva00414BDBElement(); } char data[48]; };
struct Rva001DF3F1Element { char bytes[48]; };
struct BfmePod52 { ~BfmePod52() {} BfmePod52(){reinterpret_cast<Rva001DCD3C*>(this)->rva001DCD3C();} int a[13]; };
namespace _STL {
 template<> void vector<Rva001DF3F1Element>::push_back(const Rva001DF3F1Element&);
 template<> void vector<BfmePod52>::push_back(const BfmePod52&);
}
struct NoCaseTreeValue4 { int value; NoCaseTreeValue4(int n):value(n){} };
typedef _STL::pair<const AsciiString,NoCaseTreeValue4> NocasePair;
struct InsertResult { void *node; void *table; unsigned char inserted; };
class Rva001DE556 { public: InsertResult *rva001DE84F(InsertResult*,const NocasePair&); };
class Rva00056F61 { public: void *rva00056F61(const AsciiString*); };
class Rva001DE727 { public: Rva001DE727 &operator=(const Rva001DE727&); char data[48]; };
void __stdcall Rva001DCFC9Parse(INI*,void*);
class Eva {
public:
 int rva001DE78E(const AsciiString*);
 static void iniParseNewEvaEvent(INI*);
 static void iniParsePredefinedEvaEvent(INI*);
 static void iniParseEvaEventForwardReference(INI*);
 char pad[0x1c];
 _STL::vector<Rva001DF3F1Element> current, defaults;
 char table34[20],table48[20];
 _STL::vector<BfmePod52> status;
};
extern Eva *TheEva;

void Eva::iniParsePredefinedEvaEvent(INI *ini) {
 AsciiString name(ini->getNextToken(0));
 void *node=reinterpret_cast<Rva00056F61*>(TheEva->table48)->rva00056F61(&name);
 if(!node) throw INIException(3,"'%s' is not a predefined Eva event name",name.str());
 int index=*reinterpret_cast<int*>(reinterpret_cast<char*>(node)+8);
 if(index<0 || index>=22) throw INIException(3,"'%s' is not a predefined Eva event name",name.str());
 Rva001DF3F1Element *destination;
 if(ini->loadType==2) {
  if(index==0) throw INIException(3,"You cannot redefine the default Eva event in a map.ini");
  destination=TheEva->current.begin()+index;
 } else destination=TheEva->defaults.begin()+index;
 if(index!=0) *reinterpret_cast<Rva001DE727*>(destination)=*reinterpret_cast<const Rva001DE727*>(TheEva->defaults.begin());
 Rva001DCFC9Parse(ini,destination);
}
void Eva::iniParseEvaEventForwardReference(INI *ini) {
 AsciiString name(ini->getNextToken(0));
 if(!name.compareNoCase("None")) throw INIException(3,"Cannot use 'None' as a new Eva event's name");
 if(ini->loadType==2) {
  int index=TheEva->rva001DE78E(&name);
  if(index==-1) {
   index=TheEva->current.size();
   TheEva->current.push_back(reinterpret_cast<const Rva001DF3F1Element&>(Rva001DE6E1()));
   TheEva->current.end()[-1].bytes[46]=1;
   NocasePair p(name,NoCaseTreeValue4(index)); InsertResult out;
   reinterpret_cast<Rva001DE556*>(TheEva->table34)->rva001DE84F(&out,p);
   TheEva->status.push_back(BfmePod52());
  } else if(index<22) throw INIException(3,"'%s' is a predefined Eva event name, and cannot be used as a new event name",name.str());
 } else {
  void *node=reinterpret_cast<Rva00056F61*>(TheEva->table48)->rva00056F61(&name);
  if(node) {
   if(*reinterpret_cast<int*>(reinterpret_cast<char*>(node)+8)<22) throw INIException(3,"'%s' is a predefined Eva event name, and cannot be used as a new event name",name.str());
  } else {
   int index=TheEva->defaults.size();
   TheEva->defaults.push_back(reinterpret_cast<const Rva001DF3F1Element&>(Rva001DE6E1()));
   TheEva->defaults.end()[-1].bytes[46]=1;
   NocasePair p(name,NoCaseTreeValue4(index)); InsertResult out;
   reinterpret_cast<Rva001DE556*>(TheEva->table48)->rva001DE84F(&out,p);
  }
 }
}
