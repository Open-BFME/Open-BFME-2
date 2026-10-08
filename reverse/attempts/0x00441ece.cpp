// ??0AptMpGameSetup@@QAE@PAVMpGameSetupOwner@@H@Z
// partial score=0.99 date=2026-10-08
// cl: /O1 /G7 /vmg /vmm /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Target-only constructor view. WB names AptMpGameSetup; native780 proves
// initialization order and offsets. Proper destructor/vtable ownership and
// callback43E6C9 ABI remain unresolved; declarations below are trial views.
#include <vector>
#include <string.h>
#include "ascii_string.h"
struct TargetRef00217D4C { void *vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class Rva0043F103 {public: TargetRef00217D4C *rva0043F103(int);};
class MpGameSetupOwner;
class Rva002D2C34 {public:void rva002D2C34();};
class __declspec(novtable) Rva005248D0 {
public: Rva005248D0(){((Rva002D2C34*)this)->rva002D2C34();} virtual ~Rva005248D0();
private:unsigned char pad[0x54];
};
struct SetupGameRef {
 TargetRef00217D4C* pointer;
 SetupGameRef(TargetRef00217D4C*p):pointer(p){if(p)++p->references;}
 ~SetupGameRef(){if(pointer)ReleaseTreeHintRef00217D4C(pointer);}
};
class Rva0043DA65;
class AptMapPreview {public:AptMapPreview(Rva0043DA65*);~AptMapPreview();private:unsigned char span[0x70];};
class Rva0043DABD {public:Rva0043DABD(TargetRef00217D4C*);virtual ~Rva0043DABD();private:unsigned char pad[0xb8-4];};
class Rva0043DAE0 {public:Rva0043DAE0(TargetRef00217D4C*);virtual ~Rva0043DAE0();private:unsigned char pad[0xb4-4];};
class Rva0057FE6B {public:Rva0057FE6B(TargetRef00217D4C*,int,bool);virtual ~Rva0057FE6B();private:unsigned char pad[0x6c-4];};
class GameWindow;
class MpGameSetupComboRef {
public:MpGameSetupComboRef();~MpGameSetupComboRef();GameWindow* window;
};
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)();
struct FunctorBinding {
 FunctorTarget* target;unsigned int pad;FunctorMethod method;
 FunctorBinding(FunctorMethod m,FunctorTarget*t):target(t),method(m){}
};
class Rva0057BC63FunctorHolder {public:Rva0057BC63FunctorHolder(const FunctorBinding&);TargetRef00217D4C* pointer;};
struct TreeHintRef00217D4C:public Rva0057BC63FunctorHolder {
 TreeHintRef00217D4C(FunctorBinding binding):Rva0057BC63FunctorHolder(binding){}
 TreeHintRef00217D4C(const TreeHintRef00217D4C& other):Rva0057BC63FunctorHolder(other){if(pointer)++pointer->references;}
 ~TreeHintRef00217D4C(){if(pointer)ReleaseTreeHintRef00217D4C(pointer);}
};
class Rva0043F20C {public:void rva0043F20C(TreeHintRef00217D4C);};
class Rva0057E97A {public:void rva0057E9ED(unsigned int,int);};
class Image;
class ImageCollection {public:const Image* findImageByName(const AsciiString&);};
extern ImageCollection* TheMappedImageCollection;
class GlobalData {public:unsigned char pad[0x9d4];int modeFlags;};
extern GlobalData* TheGlobalData;
extern unsigned char g_Va00E03340;
extern int g_Va00E0333C;
class AptMpGameSetup:public Rva005248D0 {
public:
 AptMpGameSetup(MpGameSetupOwner*,int);
 virtual ~AptMpGameSetup();
 void rva0043E6C9();
private:
 MpGameSetupOwner* owner58;
 SetupGameRef game5c;
 AptMapPreview map60;
 Rva0043DABD rulesD0;
 unsigned char gap188[8];
 Rva0043DAE0 clans190;
 Rva0057FE6B chat244;
 void* saved2b0;
 int pendingHero2b4;
 bool flag2b8,flag2b9,flag2ba,flag2bb,flag2bc,flag2bd,flag2be,flag2bf,flag2c0,flag2c1,flag2c2,flag2c3,flag2c4;
 int time2c8,seconds2cc,unknown2d0;
 GameWindow* player2d4[8];
 MpGameSetupComboRef colors2f4[8];
 GameWindow* team314[8];
 GameWindow* templates334[8];
 GameWindow* handicap354[8];
 GameWindow* heroes374[8];
 GameWindow* mapList394;
 _STL::vector<AsciiString> maps398;
 int flags3a4,humans3a8,sort3ac,prevSort3b0;
 unsigned char pingcache3b4[4];
 const Image* ping3b8;const Image* ping3bc;const Image* ping3c0;
 _STL::vector<bool> available3c4;
 int count3d8;
 bool optional3dc;
};
AptMpGameSetup::AptMpGameSetup(MpGameSetupOwner*owner,int flags):
 owner58(owner),game5c(((Rva0043F103*)owner)->rva0043F103(0)),
 map60((Rva0043DA65*)((Rva0043F103*)owner)->rva0043F103(1)),
 rulesD0(((Rva0043F103*)owner)->rva0043F103(1)),
 clans190(((Rva0043F103*)owner)->rva0043F103(1)),
 chat244(((Rva0043F103*)owner)->rva0043F103(1),flags,true),
 saved2b0(0),pendingHero2b4(-3),flag2b8(false),flag2b9(false),flag2ba(false),flag2bc(false),flag2bd(false),flag2be(false),flag2bf(false),
 flag2c0(false),flag2c1(false),flag2c2(false),flag2c3(false),flag2c4(false),time2c8(0),seconds2cc(0),unknown2d0(0),mapList394(0),
 flags3a4(flags),humans3a8(0),sort3ac(2),prevSort3b0(0),count3d8(0),optional3dc(true)
{
 g_Va00E0333C=(int)this;
 memset(player2d4,0,sizeof(player2d4));
 memset(team314,0,sizeof(team314));
 memset(templates334,0,sizeof(templates334));
 memset(handicap354,0,sizeof(handicap354));
 memset(heroes374,0,sizeof(heroes374));
 memset(pingcache3b4,0,16);
 ping3b8=TheMappedImageCollection->findImageByName(AsciiString("AptPing03"));
 ping3bc=TheMappedImageCollection->findImageByName(AsciiString("AptPing02"));
 ping3c0=TheMappedImageCollection->findImageByName(AsciiString("AptPing01"));
 ((Rva0043F20C*)&map60)->rva0043F20C(FunctorBinding(reinterpret_cast<FunctorMethod>(&AptMpGameSetup::rva0043E6C9),reinterpret_cast<FunctorTarget*>(this)));
 if(TheGlobalData->modeFlags&3) flags3a4&=~0x40;
 if(flags3a4&0x40) {if(!g_Va00E03340) flags3a4&=~0x40;}
 if(!(flags3a4&0x40)) ((Rva0057E97A*)&rulesD0)->rva0057E9ED(1,3);
}
