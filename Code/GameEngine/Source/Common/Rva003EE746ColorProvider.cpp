// Living-world region effects observer and colour-provider lifetimes.
// Target 3EEAFB constructor164: 88B observer with map+8 and RGB groups+20/+2C/+38.
// WB1036DE0 and named SyncRegion establish the existing manager identity.
// BFDF68 observer slots RET12/12/8/8; C363C8 overrides only slot0.
// C363B8 provider has scalar destructor and pure colour; C363C0 implements colour.
// Provider scalar destructor C66C calls the folded 7C51E derived destructor.
// cl: /O1 /MD /EHsc /arch:SSE /Ireference/shims/bfme2_ascii
struct Rva003EE746Color {Rva003EE746Color(float r,float g,float b):red(r),green(g),blue(b){} float red,green,blue;};
struct Rva003EE746Region {char pad[0x13c];int id0,id1;};
struct S3Campaign {char pad[0x20];Rva003EE746Color color;};
class Rva00DFE1C8Host {public:char pad[0x268];S3Campaign*campaign;};
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;
class Rva002E2903Player {public:char pad[0x184];Rva003EE746Color color;};
class Rva002BA8F1Logic {public:Rva002E2903Player*find(int,unsigned*);};
struct Rva0059E647World;
class LivingWorldLogic; extern LivingWorldLogic*TheLivingWorldLogic;
class Rva003EE711 {public:virtual ~Rva003EE711(){};virtual Rva003EE746Color color(const Rva003EE746Region*)=0;};
class Rva003EE746ColorProvider:public Rva003EE711 {public:Rva003EE746ColorProvider(int*s):selector(s){} virtual Rva003EE746Color color(const Rva003EE746Region*);int*selector;};
// ?color@Rva003EE746ColorProvider@@UAE?AURva003EE746Color@@PBURva003EE746Region@@@Z
Rva003EE746Color Rva003EE746ColorProvider::color(const Rva003EE746Region*r) {
 int id;
 switch(*selector){case 0:id=r->id0;break;case 1:id=r->id1;break;default:id=-1;break;}
 if(id==-1){S3Campaign*c=((Rva00DFE1C8Host*)TheLivingWorldManager)->campaign;return *(const Rva003EE746Color*)((char*)c+0x20);}
 Rva002E2903Player*p=((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(id,0);
 if(p)return p->color;
 return Rva003EE746Color(1.0f,1.0f,1.0f);
}

#include "ascii_string.h"
class Rva004E35A3 {public:Rva004E35A3();char bytes[12];};
class Rva004E2E58 {public:__forceinline Rva004E2E58(){((Rva004E35A3*)this)->Rva004E35A3::Rva004E35A3();}~Rva004E2E58();char bytes[12];};
class S3RegionObserverBase {public:
 virtual void rva003EF13E(int,int,int){}virtual void event1(int,int,int){}virtual void event2(int,int){}virtual void event3(int,int){}
 __declspec(noinline) ~S3RegionObserverBase(){}
};
struct S3ColorGroup {S3ColorGroup(float a,float b,float c):x(a),y(b),z(c){}float x,y,z;};
class LivingWorldRegionEffectsManager:public S3RegionObserverBase {public:
 LivingWorldRegionEffectsManager(const AsciiString&);
 virtual void rva003EF13E(int,int,int); void SyncRegion(int);
 int u4;Rva004E2E58 map8;int u14;AsciiString name18;int u1c;
 S3ColorGroup group20,group2c,group38;
 int selector44;Rva003EE711*active48;Rva003EE746ColorProvider provider4c;bool flag54;
};
// ??0LivingWorldRegionEffectsManager@@QAE@ABVAsciiString@@@Z
LivingWorldRegionEffectsManager::LivingWorldRegionEffectsManager(const AsciiString&n)
 :u4(0),u14(0),name18(n),u1c(0),group20(1,1,1),group2c(1,1,1),group38(0.95f,0.95f,0.95f),selector44(0),provider4c(&selector44),flag54(true){active48=&provider4c;}
typedef char S3RegionRecordSize[sizeof(LivingWorldRegionEffectsManager)==88?1:-1];

// ?rva003EF13E@LivingWorldRegionEffectsManager@@UAEXHHH@Z
void LivingWorldRegionEffectsManager::rva003EF13E(int a,int,int){SyncRegion(a);}
