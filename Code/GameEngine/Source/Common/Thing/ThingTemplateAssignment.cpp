// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
// Retail 2D1101..2D1AB4, called by ThingFactory::newOverride at 2D1AB4.
// WB A93F30 and ZH ThingTemplate's default assignment establish purpose.
// Target accesses/call providers establish member extents, not unknown names.
// Reference revision 9cbfb551fe20dae985f91f2319d8997287b6a705: ZH
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
// and BFME1 game/GameEngine/Source/Common/Thing/ThingTemplateCopyAssignment.cpp.
// BFME1's 0x4D4 layout is a semantic lead, not a target layout: BFME2 is
// 0x640, as independently established by ThingFactory::newOverride's allocation.
// The inherited prefix is preserved by the existing folded Overridable
// assignment at 1FD28E; no copy of offsets 00..0F appears in this operation.
// Prefix ownership beyond the known vptr/next/override remains uncertain.
// Calls prove string records 14/20 and 2C..54, geometry A0, containers FC
// and 2E4..3F8; POD aggregate copies prove sizes 1C/10/80/C. The scalar
// tail's application names/types remain unreconstructed (widths are target facts).
// Declared library views call already verified providers, emitting no substitute
// container implementation. Inline adapters retain their existing ABI names.
class Overridable { public: virtual ~Overridable(); Overridable& operator=(const Overridable&); private: void* next04; bool override08; unsigned char gap09[7]; };
struct Rva002CEF2A { AsciiString name; int words[2]; Rva002CEF2A& operator=(const Rva002CEF2A&); };
struct Rva002CEF4B { AsciiString name; StringBase<unsigned short> wide; Rva002CEF4B& operator=(const Rva002CEF4B&); };
struct BfmeCopyElementA { unsigned char bytes[0x5C]; BfmeCopyElementA* bfmeAssign(BfmeCopyElementA*); __forceinline BfmeCopyElementA& operator=(const BfmeCopyElementA&b){ bfmeAssign(const_cast<BfmeCopyElementA*>(&b));return *this;} };
struct Rva002CF5D4 { unsigned char bytes[0x1C0]; Rva002CF5D4& operator=(const Rva002CF5D4&); };
class BfmeThingBVA { public: unsigned char bytes[0x14]; BfmeThingBVA* bfmeGoBVA(BfmeThingBVA*); __forceinline BfmeThingBVA& operator=(const BfmeThingBVA&b){bfmeGoBVA(const_cast<BfmeThingBVA*>(&b));return *this;} };
struct Rva002D0136 { void* header; int count; char compareAndPad[4]; Rva002D0136& operator=(const Rva002D0136&); };
struct Rva002D01A9 { void* header; int count; char compareAndPad[4]; Rva002D01A9& operator=(const Rva002D01A9&); };
struct Rva002D021C { void* header; int count; char compareAndPad[4]; Rva002D021C& operator=(const Rva002D021C&); };
struct NoCaseTreeValue4; struct BfmeStringNoCaseLess; struct Rva002D07F4Element; class LocomotorTemplate; enum LocomotorSetType { LOCOMOTORSET_NORMAL=0 };
namespace _STL {
template<class T> class allocator {};
template<class T> struct less {};
template<class P> struct _Select1st {};
template<class K,class V> struct pair { K first; V second; };
template<class T,class A> class vector { void* start; void* finish; void* end; public: vector& operator=(const vector&); };
template<class K,class V,class S,class C,class A> class _Rb_tree { void* header; int count; char compareAndPad[4]; public: _Rb_tree& operator=(const _Rb_tree&); _Rb_tree& rva002D0E69(const _Rb_tree&); };
}
struct Rva002D0EDCElement;
typedef _STL::vector<Rva002D0EDCElement,_STL::allocator<Rva002D0EDCElement> > VRva002D0EDCElement;
struct BfmeStringRecord002CF4C6;
typedef _STL::vector<BfmeStringRecord002CF4C6,_STL::allocator<BfmeStringRecord002CF4C6> > VBfmeStringRecord002CF4C6;
class ProductionPrerequisite;
typedef _STL::vector<ProductionPrerequisite,_STL::allocator<ProductionPrerequisite> > VProductionPrerequisite;
struct BfmeObject872;
typedef _STL::vector<BfmeObject872,_STL::allocator<BfmeObject872> > VBfmeObject872;
struct BfmeContainerRecord002CF46E;
typedef _STL::vector<BfmeContainerRecord002CF46E,_STL::allocator<BfmeContainerRecord002CF46E> > VBfmeContainerRecord002CF46E;
struct Rva0021C21BElement;
typedef _STL::vector<Rva0021C21BElement,_STL::allocator<Rva0021C21BElement> > VRva0021C21BElement;
struct BfmeFixedObject260;
typedef _STL::vector<BfmeFixedObject260,_STL::allocator<BfmeFixedObject260> > VBfmeFixedObject260;
typedef _STL::vector<AsciiString,_STL::allocator<AsciiString> > VAsciiString;
typedef _STL::_Rb_tree<Rva002D07F4Element,_STL::pair<const Rva002D07F4Element,int> ,_STL::_Select1st<_STL::pair<const Rva002D07F4Element,int> >,_STL::less<Rva002D07F4Element>,_STL::allocator<_STL::pair<const Rva002D07F4Element,int> > > ShortTree;
typedef _STL::_Rb_tree<AsciiString,_STL::pair<const AsciiString,NoCaseTreeValue4> ,_STL::_Select1st<_STL::pair<const AsciiString,NoCaseTreeValue4> >,BfmeStringNoCaseLess,_STL::allocator<_STL::pair<const AsciiString,NoCaseTreeValue4> > > NoCaseTree;
typedef _STL::_Rb_tree<LocomotorSetType,_STL::pair<const LocomotorSetType,_STL::vector<const LocomotorTemplate*,_STL::allocator<const LocomotorTemplate*> > > ,_STL::_Select1st<_STL::pair<const LocomotorSetType,_STL::vector<const LocomotorTemplate*,_STL::allocator<const LocomotorTemplate*> > > >,_STL::less<LocomotorSetType>,_STL::allocator<_STL::pair<const LocomotorSetType,_STL::vector<const LocomotorTemplate*,_STL::allocator<const LocomotorTemplate*> > > > > LocomotorTree;
struct LocomotorMapView { LocomotorTree tree; __forceinline LocomotorMapView& operator=(const LocomotorMapView&b){tree.rva002D0E69(b.tree);return *this;} };
struct Words28 { unsigned int words[7]; };
struct Words16 { unsigned int words[4]; };
struct Words128 { unsigned int words[32]; };
struct Words12 { unsigned int words[3]; };
class ThingTemplate : public Overridable { public:
unsigned int m010;
Rva002CEF2A m014;
Rva002CEF2A m020;
Rva002CEF4B m02C;
Rva002CEF4B m034;
Rva002CEF4B m03C;
Rva002CEF4B m044;
Rva002CEF4B m04C;
Rva002CEF4B m054;
AsciiString m05C;
AsciiString m060;
AsciiString m064;
AsciiString m068;
AsciiString m06C;
AsciiString m070;
AsciiString m074;
AsciiString m078;
AsciiString m07C[5];
AsciiString m090;
AsciiString m094;
AsciiString m098;
AsciiString m09C;
BfmeCopyElementA m0A0;
VRva002D0EDCElement m0FC;
Words28 m108;
Rva002CF5D4 m124;
VBfmeStringRecord002CF4C6 m2E4;
VBfmeStringRecord002CF4C6 m2F0;
VBfmeStringRecord002CF4C6 m2FC;
VBfmeStringRecord002CF4C6 m308;
Words16 m314;
VProductionPrerequisite m324;
VAsciiString m330;
VAsciiString m33C;
VAsciiString m348;
unsigned int m354;
VBfmeObject872 m358;
Rva002D0136 m364;
VBfmeContainerRecord002CF46E m370;
Rva002D01A9 m37C;
ShortTree m388;
NoCaseTree m394;
Rva002D021C m3A0;
LocomotorMapView m3AC;
VRva0021C21BElement m3B8;
BfmeThingBVA m3C4[2];
VBfmeFixedObject260 m3EC;
VBfmeFixedObject260 m3F8;
Words128 m404;
unsigned int m484;
unsigned int m488;
unsigned int m48C;
unsigned int m490;
unsigned int m494;
unsigned int m498;
unsigned int m49C;
unsigned int m4A0;
unsigned int m4A4;
unsigned int m4A8;
unsigned int m4AC;
unsigned int m4B0;
unsigned int m4B4;
unsigned int m4B8;
unsigned int m4BC;
unsigned int m4C0;
unsigned int m4C4;
unsigned int m4C8;
unsigned int m4CC;
unsigned int m4D0;
unsigned int m4D4;
unsigned int m4D8;
unsigned int m4DC;
unsigned int m4E0;
unsigned int m4E4;
unsigned int m4E8;
unsigned int m4EC;
unsigned int m4F0;
unsigned int m4F4;
unsigned int m4F8;
unsigned int m4FC;
unsigned int m500;
unsigned int m504;
unsigned int m508;
unsigned int m50C;
unsigned int m510;
unsigned int m514;
unsigned int m518;
unsigned int m51C;
unsigned int m520;
unsigned int m524;
unsigned int m528;
unsigned int m52C;
unsigned int m530;
unsigned int m534;
unsigned int m538;
unsigned int m53C;
unsigned int m540;
unsigned int m544;
unsigned int m548;
unsigned int m54C;
unsigned int m550;
unsigned int m554;
unsigned int m558;
unsigned int m55C;
unsigned int m560;
unsigned int m564;
unsigned int m568;
unsigned int m56C;
unsigned int m570;
unsigned int m574;
unsigned int m578;
unsigned int m57C;
unsigned int m580;
unsigned int m584;
unsigned int m588;
unsigned int m58C;
unsigned int m590;
unsigned int m594;
unsigned int m598;
unsigned int m59C;
unsigned int m5A0;
unsigned int m5A4;
unsigned int m5A8;
unsigned int m5AC;
unsigned int m5B0;
unsigned int m5B4;
unsigned int m5B8;
unsigned int m5BC;
unsigned int m5C0;
unsigned int m5C4;
unsigned int m5C8;
unsigned int m5CC;
unsigned int m5D0;
unsigned int m5D4;
unsigned short m5D8;
unsigned short m5DA;
unsigned short m5DC;
unsigned short m5DE;
unsigned short m5E0;
unsigned short m5E2;
bool m5E4;
bool m5E5;
bool m5E6;
bool m5E7;
bool m5E8;
bool m5E9;
bool m5EA;
bool m5EB;
bool m5EC;
bool m5ED;
bool m5EE;
bool m5EF;
bool m5F0;
bool m5F1;
bool m5F2;
bool m5F3;
bool m5F4;
bool m5F5;
bool m5F6;
bool m5F7;
bool m5F8;
bool m5F9;
bool m5FA;
bool m5FB;
bool m5FC;
bool m5FD;
bool m5FE;
unsigned int m600;
unsigned int m604;
unsigned int m608;
unsigned int m60C;
unsigned int m610;
bool m614;
unsigned int m618;
unsigned int m61C;
Words12 m620;
unsigned int m62C;
bool m630;
bool m631;
bool m632;
bool m633;
bool m634;
bool m635;
unsigned int m638;
unsigned int m63C;
};
typedef char ThingTemplateSizeCheck[sizeof(ThingTemplate)==0x640?1:-1];
// The source language implicit assignment is the recovered body. This
// non-retail anchor merely causes MSVC to emit it, like the existing library
// instantiation anchors; it does not contribute claimed progress.
// ?s4EmitThingTemplateAssignment absent-from-retail
void s4EmitThingTemplateAssignment(ThingTemplate*dst,const ThingTemplate&src){*dst=src;}
