// ?rva00477BA2@HordeTransportContain@@QAEXPAVOldContain@@PAVObject@@@Z
// partial score=0.92 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// Native477BA2..477D61 RET8 447B; source literal HordeContain/HordeTransportContain.cpp at845F38. Matrix3D32 arrays and32 output indices; owner8, Object74 ID/25Cphysics, flagbit127; slots48 uses verified int-key map providers. Existing last-argument int ABI carries output-index-array address; exact parameter type remains to be reconciled in provider. No new alias or pin claimed.
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include <map>
struct Vector4 {float x,y,z,w; __declspec(noinline) Vector4() {} };
class Matrix3D {public:__forceinline Matrix3D(){} Vector4 rows[3];};
struct RvaVector {float x,y,z; RvaVector(float xx,float yy,float zz):x(xx),y(yy),z(zz){} RvaVector operator*(float n) const {return RvaVector(x*n,y*n,z*n);} };
class Thing {public:void setTransformMatrix(const Matrix3D*);};
enum DamageType{DAMAGE=8}; enum DeathType{DEATH=0};
class Rva003909FAObj {public:void consume(void*,int,int);};
class PhysicsBehavior {public:void rva00390629(bool);};
class RvaFlags {public:unsigned int word[19];unsigned int test(unsigned int b)const{return word[b>>5]&(1U<<(b&31));}void set(unsigned int b){word[b>>5]|=1U<<(b&31);}};
class Object: public Thing {public:
 int getMultiLogicalBonePosition(const char*,int,Coord3D*,Matrix3D*,bool,int)const;
 bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*)const;
 void rva0028AE6D(); void kill(DamageType,DeathType);
 char pad0[8]; Matrix3D matrix; Coord3D position; float orientation;
 char pad48[0x74-0x48]; int id;
 char pad78[0x10C-0x78]; RvaFlags flags;
 char pad158[0x25C-0x158]; PhysicsBehavior*physics;
};
int GetGameLogicRandomValue(int,int,char*,int);
class Rva00463235 {public:AsciiString rva00463235(Thing*);};
class OldContain {public:
virtual void d0();
virtual void d1();
virtual void d2();
virtual void d3();
virtual void d4();
virtual void d5();
virtual void d6();
virtual void d7();
virtual void d8();
virtual void d9();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
virtual void d14();
virtual void d15();
virtual void d16();
virtual void d17();
virtual void d18();
virtual void d19();
virtual void d20();
virtual void d21();
virtual void d22();
virtual void d23();
virtual void d24();
virtual void d25();
virtual void d26();
virtual void d27();
virtual void d28();
virtual void d29();
virtual void d30();
virtual void d31();
virtual void d32();
virtual void d33();
virtual void d34();
virtual void d35();
virtual void d36();
virtual void d37();
virtual void d38();
virtual void d39();
virtual void d40();
virtual void d41();
virtual void removing(Object*);
};
class NotifyContain {public:
virtual void n0();
virtual void n1();
virtual void n2();
virtual void n3();
virtual void n4();
virtual void n5();
virtual void n6();
virtual void n7();
virtual void n8();
virtual void n9();
virtual void n10();
virtual void n11();
virtual void n12();
virtual void n13();
virtual void n14();
virtual void n15();
virtual void n16();
virtual void n17();
virtual void n18();
virtual void n19();
virtual void n20();
virtual void n21();
virtual void n22();
virtual void n23();
virtual void n24();
virtual void n25();
virtual void n26();
virtual void n27();
virtual void n28();
virtual void n29();
virtual void n30();
virtual void n31();
virtual void n32();
virtual void n33();
virtual void n34();
virtual void n35();
virtual void n36();
virtual void n37();
virtual void n38();
virtual void n39();
virtual void n40();
virtual void n41(Object*,bool);
};
class HordeTransportContain {public:
 void rva00477BA2(OldContain*,Object*);
 char pad0[8]; Object*owner;
 char padC[0x48-0xC]; _STL::map<int,int> slots;
};
void HordeTransportContain::rva00477BA2(OldContain*old,Object*object){
 Matrix3D matrices[32]; int indices[32]; int index=0;
 AsciiString bone= reinterpret_cast<Rva00463235*>(this)->rva00463235(object);
 Object*container=owner;
 int count=container->getMultiLogicalBonePosition(bone.str(),32,0,matrices,true,reinterpret_cast<int>(indices));
 if(!count && container->getSingleLogicalBonePosition(bone.str(),0,&matrices[0]))count=1;
 int id=object->id;
 if(slots.find(id)!=slots.end())index=slots[id];
 if(index>=count)index=0;
 if(old)old->removing(object);
 reinterpret_cast<NotifyContain*>(reinterpret_cast<char*>(this)+0x20)->n41(object,false);
 object->setTransformMatrix(&matrices[index]);
 PhysicsBehavior*physics=object->physics;
 if(physics){
  RvaVector direction(object->matrix.rows[0].x,object->matrix.rows[1].x,1.0f);
  int r=GetGameLogicRandomValue(3,8,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeTransportContain.cpp",702);
  RvaVector force=direction*(float)r;
  physics->rva00390629(true);
  if(!object->flags.test(127)){object->flags.set(127);object->rva0028AE6D();}
  reinterpret_cast<Rva003909FAObj*>(physics)->consume(&force,0,0);
 }
 object->kill(DAMAGE,DEATH);
}
