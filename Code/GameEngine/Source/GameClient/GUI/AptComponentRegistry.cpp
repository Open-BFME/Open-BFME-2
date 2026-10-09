// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Primary semantic source: Open-BFME-1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d
// game/GameEngine/Source/GameClient/GUI/WindowManagerRegisterAptCallbacks00464080.cpp.
// Target evidence: native4121D1..41267F RET0 and WB1092680 retain the same
// sequence with LivingWorldMap/ColorPicker/TestComponent additions. Existing
// BFME2 holder constructors prove the one-pointer references; each erased
// callback address is read from retail's actual registration, not donor names.
// The context remains thirteen opaque words as in the donor; its complete
// emitted initializer is a relocation-free 43B twin of the existing22239C
// owner. That fold proves initialization and ABI, not the target's type name.
// Registry and owned shutdown411B52 independently use the same window table
// and load-screen singleton; no donor global address is carried here.
#include "ascii_string.h"
typedef void (__cdecl *AptCallback)();
struct FunctorWrapperHead {void*vtable;unsigned refs;};
struct TargetRef00217D4C;void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class Rva00380AB1 {public:Rva00380AB1(void*);FunctorWrapperHead*m_ptr;};
class Rva0023E8D8 {public:Rva0023E8D8(void*);FunctorWrapperHead*m_ptr;};
class Rva004106FA {public:Rva004106FA(const int*);FunctorWrapperHead*m_ptr;};
class AptCustomRender;class AptCommandMap;class AptScreenInitGadgets;
template<class T>class AptRef;
template<>class AptRef<AptCustomRender>:public Rva00380AB1 {public:AptRef(AptCallback f):Rva00380AB1(&f){}AptRef(const AptRef&that):Rva00380AB1(that){if(m_ptr)++m_ptr->refs;}~AptRef(){if(m_ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_ptr);}};
template<>class AptRef<AptCommandMap>:public Rva0023E8D8 {public:AptRef(AptCallback f):Rva0023E8D8(&f){}AptRef(const AptRef&that):Rva0023E8D8(that){if(m_ptr)++m_ptr->refs;}~AptRef(){if(m_ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_ptr);}};
template<>class AptRef<AptScreenInitGadgets>:public Rva004106FA {public:AptRef(AptCallback f):Rva004106FA(reinterpret_cast<const int*>(&f)){}AptRef(const AptRef&that):Rva004106FA(that){if(m_ptr)++m_ptr->refs;}~AptRef(){if(m_ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_ptr);}};
class AptPlayer {public:void AddCustomRender(const AsciiString&,AptRef<AptCustomRender>);void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);};
class BfmeAptWindowManager;extern BfmeAptWindowManager*g_bfmeAptWindowManager;
void _bfme_setAptScreenRef(const AsciiString&,AptRef<AptScreenInitGadgets>);
class Coord2D;
void Rva00411EC3(const Coord2D*,const Coord2D*,const char*,const char*);
void Rva004120B3(const Coord2D*,const Coord2D*,const char*,const char*);
void Rva00412111(const Coord2D*,const Coord2D*,const char*,const char*);
void DisableComponents(const char*);void EnableComponents(const char*);
// Addresses are carried in the erased callback representation; these are
// not invoked here and their original callback signatures remain open.
void Rva0056D7A4();void Rva000B3FD0(int,char*const*);
namespace _STL {
 template<class T>struct less;
 template<class A,class B>struct pair;
 template<class T>class allocator;
 template<class K,class V,class C,class A>class map {public:V&operator[](const K&);};
}
struct TreeHintPayload00410B17 {int m_val;};
typedef _STL::map<AsciiString,TreeHintPayload00410B17,_STL::less<AsciiString>,_STL::allocator<_STL::pair<const AsciiString,TreeHintPayload00410B17> > > WindowPathMap;
extern unsigned g_Va00E03020;
class AptShutdownReceiverView;extern AptShutdownReceiverView*AptShutdownReceiverInstance;
class Rva0051268C;Rva0051268C*__stdcall Rva002D1E55Create(void*);
struct Rva004121D1Context {
 Rva004121D1Context();
 unsigned word00,word04,word08,word0C,word10,word14,word18,word1C,word20,word24,word28,word2C,word30;
};
void Rva004121D1RegisterAptComponents() {
 {AsciiString name("GameWindow");((AptPlayer*)g_bfmeAptWindowManager)->AddCustomRender(name,reinterpret_cast<AptCallback>(Rva00411EC3));}
 {AsciiString name("HorzSlider");((AptPlayer*)g_bfmeAptWindowManager)->AddCustomRender(name,reinterpret_cast<AptCallback>(Rva00411EC3));}
 {AsciiString name("ComboBox");((AptPlayer*)g_bfmeAptWindowManager)->AddCustomRender(name,reinterpret_cast<AptCallback>(Rva00411EC3));}
 {AsciiString name("ImageComboBox");((AptPlayer*)g_bfmeAptWindowManager)->AddCustomRender(name,reinterpret_cast<AptCallback>(Rva00411EC3));}
 {AsciiString name("CheckBox");((AptPlayer*)g_bfmeAptWindowManager)->AddCustomRender(name,reinterpret_cast<AptCallback>(Rva00411EC3));}
 {AsciiString name("TextEntry");((AptPlayer*)g_bfmeAptWindowManager)->AddCustomRender(name,reinterpret_cast<AptCallback>(Rva00411EC3));}
 {AsciiString name("ListBox");((AptPlayer*)g_bfmeAptWindowManager)->AddCustomRender(name,reinterpret_cast<AptCallback>(Rva00411EC3));}
 {AsciiString name("PushButton");((AptPlayer*)g_bfmeAptWindowManager)->AddCustomRender(name,reinterpret_cast<AptCallback>(Rva00411EC3));}
 {AsciiString name("BinkMovie");((AptPlayer*)g_bfmeAptWindowManager)->AddCustomRender(name,reinterpret_cast<AptCallback>(Rva00411EC3));}
 {AsciiString name("LivingWorldMap");((AptPlayer*)g_bfmeAptWindowManager)->AddCustomRender(name,reinterpret_cast<AptCallback>(Rva00411EC3));}
 {AsciiString name("View3D");((AptPlayer*)g_bfmeAptWindowManager)->AddCustomRender(name,reinterpret_cast<AptCallback>(Rva004120B3));}
 {AsciiString name("ColorPicker");((AptPlayer*)g_bfmeAptWindowManager)->AddCustomRender(name,reinterpret_cast<AptCallback>(Rva00412111));}
 {AsciiString name("DisableComponents");((AptPlayer*)g_bfmeAptWindowManager)->AddCommandMap(name,reinterpret_cast<AptCallback>(DisableComponents));}
 {AsciiString name("EnableComponents");((AptPlayer*)g_bfmeAptWindowManager)->AddCommandMap(name,reinterpret_cast<AptCallback>(EnableComponents));}
 {AsciiString name("BinkMovieInit");_bfme_setAptScreenRef(name,Rva0056D7A4);}
 {AsciiString name("TestComponent");_bfme_setAptScreenRef(name,reinterpret_cast<AptCallback>(Rva000B3FD0));}
 ((WindowPathMap*)&g_Va00E03020)->operator[](AsciiString("apt/combobox.wnd")).m_val=0;
 ((WindowPathMap*)&g_Va00E03020)->operator[](AsciiString("apt/horzslider.wnd")).m_val=0;
 Rva004121D1Context context;context.word04=0x08000000;
 AptShutdownReceiverInstance=reinterpret_cast<AptShutdownReceiverView*>(Rva002D1E55Create(&context));
}
// ?Rva004121D1Context::Rva004121D1Context present-unmatched (full43B relocation-free ICF twin at22239C; existing ArcInfoStruct owner retained)
Rva004121D1Context::Rva004121D1Context():word00(0),word04(0),word08(0),word0C(0),word10(0),word14(0),word18(0),word1C(0),word20(0),word24(0),word28(0),word2C(0),word30(0){}
