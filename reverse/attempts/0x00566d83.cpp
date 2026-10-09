// ?ParseLivingWorldCampaignAct@@YAXPAVINI@@PAX1PBX@Z
// partial score=1.0 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP=
// Native 566BF6..566D7B (389B), named act parser 566D83 and its WB
// twin 1438E40 establish the 184B act record and constructor relationship.
// Existing destructor 56616B independently supplies the 16 member cleanup
// offsets. The original record name remains unproven: keep its address name.
// BF1 9cbfb551fe20 ParseLivingWorldCampaignAct.cpp is a semantic lead only;
// its 220B record and unadmitted ctor do not establish the BF2 layout.
// Fourteen 12B vector headers initialize through the existing 211E58 owner.
// Storage views retain actual cleanup owners; element identities are not
// inferred from an empty header. The ten clears call existing rowed providers.
#include "ascii_string.h"
struct BfmeE16{float x,y,z,w;};
namespace _STL {
template<class T>class allocator{public:allocator(){}};
 template<class T,class A>class _Vector_base{public:_Vector_base(const A&)throw(); T *begin,*end,*capacity;};
 template<class T,class A>class vector{public:~vector();T *erase(T*,T*); __forceinline void clear(){erase(begin,end);} T *begin,*end,*capacity;};
}
typedef _STL::allocator<BfmeE16> Alloc; typedef _STL::_Vector_base<BfmeE16,Alloc> Header;
struct Rva0052CB26:Header{__forceinline Rva0052CB26()throw():Header(Alloc()){} ~Rva0052CB26();};
struct Rva0052CA6C:Header{__forceinline Rva0052CA6C()throw():Header(Alloc()){} ~Rva0052CA6C();};
struct Rva004FABE2:Header{__forceinline Rva004FABE2()throw():Header(Alloc()){} ~Rva004FABE2();};
struct Rva0052CC25:Header{__forceinline Rva0052CC25()throw():Header(Alloc()){} ~Rva0052CC25();};
struct Rva0052CCC4:Header{__forceinline Rva0052CCC4()throw():Header(Alloc()){} ~Rva0052CCC4();};
struct Rva0052CD03:Header{__forceinline Rva0052CD03()throw():Header(Alloc()){} ~Rva0052CD03();};
struct Rva0052CD42:Header{__forceinline Rva0052CD42()throw():Header(Alloc()){} ~Rva0052CD42();};
struct Rva0052CDE1:Header{__forceinline Rva0052CDE1()throw():Header(Alloc()){} ~Rva0052CDE1();};
struct Rva0052D1CD:Header{__forceinline Rva0052D1CD()throw():Header(Alloc()){} ~Rva0052D1CD();};
struct Rva0052D20C:Header{__forceinline Rva0052D20C()throw():Header(Alloc()){} ~Rva0052D20C();};
struct AsciiVec:Header{__forceinline AsciiVec()throw():Header(Alloc()){} __forceinline ~AsciiVec(){reinterpret_cast<_STL::vector<AsciiString,_STL::allocator<AsciiString> >*>(this)->~vector();}};
struct Rva00565865Element;
struct Rva00566A42Element;
struct Rva005658CBElement;
struct Rva00565964Element;
struct Rva00565931Element;
struct Rva005658FEElement;
struct Rva00565997Element;
class Rva00564B1A; class Rva00565898{public:Rva00564B1A *rva00565898(Rva00564B1A*,Rva00564B1A*);__forceinline void clear(){rva00565898(begin,end);} Rva00564B1A *begin,*end,*capacity;}; class Rva00566695;class Rva00566B81Vector{public:Rva00566695 *EraseRange(Rva00566695*,Rva00566695*);__forceinline void clear(){EraseRange(begin,end);} Rva00566695 *begin,*end,*capacity;};
class Rva0056616B {
public:
 Rva0056616B(const AsciiString&);
 virtual ~Rva0056616B();
AsciiString m_04;
Rva0052CB26 m_08;
Rva0052CA6C m_14;
Rva004FABE2 m_20;
Rva0052CC25 m_2C;
Rva0052CCC4 m_38;
AsciiVec m_44;
AsciiString m_50;
Rva0052CD03 m_54;
Rva0052CD42 m_60;
Rva0052CCC4 m_6C;
Rva0052CDE1 m_78;
Rva0052CDE1 m_84;
Rva0052D1CD m_90;
Rva0052D20C m_9C;
Rva0052CC25 m_A8;
bool m_B4;
};
Rva0056616B::Rva0056616B(const AsciiString &name):m_04(name),m_B4(false) {
reinterpret_cast<_STL::vector<Rva00565865Element,_STL::allocator<Rva00565865Element> >*>(&m_08)->clear();
reinterpret_cast<_STL::vector<Rva00566A42Element,_STL::allocator<Rva00566A42Element> >*>(&m_20)->clear();
reinterpret_cast<Rva00565898*>(&m_2C)->clear();
reinterpret_cast<_STL::vector<Rva005658CBElement,_STL::allocator<Rva005658CBElement> >*>(&m_38)->clear();
reinterpret_cast<_STL::vector<Rva00565964Element,_STL::allocator<Rva00565964Element> >*>(&m_78)->clear();
reinterpret_cast<_STL::vector<Rva00565931Element,_STL::allocator<Rva00565931Element> >*>(&m_6C)->clear();
reinterpret_cast<_STL::vector<Rva005658FEElement,_STL::allocator<Rva005658FEElement> >*>(&m_54)->clear();
reinterpret_cast<Rva00566B81Vector*>(&m_60)->clear();
reinterpret_cast<_STL::vector<AsciiString,_STL::allocator<AsciiString> >*>(&m_44)->clear();
reinterpret_cast<_STL::vector<Rva00565997Element,_STL::allocator<Rva00565997Element> >*>(&m_A8)->clear();
}

Rva0056616B::~Rva0056616B() {}

struct FieldParse;
class INI { public: const char *getNextToken(const char *seps=0); void initFromINI(void*,const FieldParse*); };
class INIException { public: INIException(int,const char*,...); INIException(const INIException&); ~INIException(); private:int code;const char *message; };
struct Rva0052D801Record;
class Rva0052D83B { public:void rva0052D83B(const Rva0052D801Record &); };
extern const FieldParse CampaignActFieldParseTable[];
void ParseLivingWorldCampaignAct(INI *ini,void *instance,void*,const void*) {
 if(!ini || !instance) throw INIException(3,"ParseLivingWorldCampaignAct::Invalid data passed in.");
 AsciiString name(ini->getNextToken());
 if(!name.getLength()) throw INIException(3,"ParseLivingWorldCampaignAct::No act name specified.");
 Rva0056616B record(name);
 ini->initFromINI(&record,CampaignActFieldParseTable);
 ((Rva0052D83B*)instance)->rva0052D83B((const Rva0052D801Record&)record);
}
