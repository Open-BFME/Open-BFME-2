// ??0Rva003EEAFBRecord@@QAE@ABVAsciiString@@@Z
// partial score=1.0 date=2026-10-09
// cl: /O1 /MD /EHsc /arch:SSE /Ireference/shims/bfme2_ascii
struct Rva003EE746Color {Rva003EE746Color(float r,float g,float b):red(r),green(g),blue(b){} float red,green,blue;};
struct Rva003EE746Region {char pad[0x13c];int id0,id1;};
struct S3Campaign {char pad[0x20];Rva003EE746Color color;};
class Rva00DFE1C8Host {public:char pad[0x268];S3Campaign*campaign;};
extern Rva00DFE1C8Host *g_00DFE1C8;
class Rva002E2903Player {public:char pad[0x184];Rva003EE746Color color;};
class Rva002BA8F1Logic {public:Rva002E2903Player*find(int,unsigned*);};
struct Rva0059E647World;
extern Rva0059E647World*g_rva0059E647World;
class S3ColorProviderBase {public:virtual ~S3ColorProviderBase(){};virtual Rva003EE746Color color(const Rva003EE746Region*)=0;};
class Rva003EE746ColorProvider:public S3ColorProviderBase {public:Rva003EE746ColorProvider(int*s):selector(s){} virtual Rva003EE746Color color(const Rva003EE746Region*);int*selector;};
Rva003EE746Color Rva003EE746ColorProvider::color(const Rva003EE746Region*r) {
 int id;
 switch(*selector){case 0:id=r->id0;break;case 1:id=r->id1;break;default:id=-1;break;}
 if(id==-1)return g_00DFE1C8->campaign->color;
 Rva002E2903Player*p=((Rva002BA8F1Logic*)g_rva0059E647World)->find(id,0);
 if(p)return p->color;
 return Rva003EE746Color(1.0f,1.0f,1.0f);
}

#include "ascii_string.h"
class Rva004E35A3 {public:Rva004E35A3();char bytes[12];};
class Rva004E2E58 {public:__forceinline Rva004E2E58(){((Rva004E35A3*)this)->Rva004E35A3::Rva004E35A3();}~Rva004E2E58();char bytes[12];};
class S3RegionObserverBase {public:
 virtual void event0(int,int,int){}virtual void event1(int,int,int){}virtual void event2(int,int){}virtual void event3(int,int){}
 __declspec(noinline) ~S3RegionObserverBase(){}
};
struct S3ColorGroup {S3ColorGroup(float a,float b,float c):x(a),y(b),z(c){}float x,y,z;};
class Rva003EEAFBRecord:public S3RegionObserverBase {public:
 Rva003EEAFBRecord(const AsciiString&);
 virtual void event0(int,int,int);virtual void event1(int,int,int);virtual void event2(int,int);virtual void event3(int,int);
 int u4;Rva004E2E58 map8;int u14;AsciiString name18;int u1c;
 S3ColorGroup group20,group2c,group38;
 int selector44;S3ColorProviderBase*active48;Rva003EE746ColorProvider provider4c;bool flag54;
};
Rva003EEAFBRecord::Rva003EEAFBRecord(const AsciiString&n)
 :u4(0),u14(0),name18(n),u1c(0),group20(1,1,1),group2c(1,1,1),group38(0.95f,0.95f,0.95f),selector44(0),provider4c(&selector44),flag54(true){active48=&provider4c;}
typedef char S3RegionRecordSize[sizeof(Rva003EEAFBRecord)==88?1:-1];
