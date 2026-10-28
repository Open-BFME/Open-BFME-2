// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ?rva00477BA2@HordeTransportContain@@QAEXPAVOldContain@@PAVObject@@@Z,
// retail 0x00477BA2..0x00477D61 (447 bytes, RET 8).
// Target facts: the WorldBuilder twin 0x011A13C0 carries the
// HordeTransportContain.cpp source file string (retail literal 0x00C45F38,
// line 702), the 32-matrix/32-index bone query on the contain's owner
// (+8, getMultiLogicalBonePosition then getSingleLogicalBonePosition), the
// int-keyed slot map at +0x48 (end() cached before find(), then operator[]),
// the old-contain removal slot 0xA8, the +0x20 interface slot 0xA4, the
// setTransformMatrix call, and the fling: the transform's X column with Z
// forced to 1, scaled by a random 3..8 magnitude, copied memberwise into a
// Coord3D for the +0x25C physics consumer, around the model-condition bit
// 127 set; the rider is then killed. Statement order and the separate
// magnitude local follow the twin and the rowed sibling
// HordeSiegeEngineContain::removeAndApplyForce (0x0047CE0C). The method's
// original name and the exact type of the index-array argument (passed
// through the pinned int ABI) remain unresolved; class views model only the
// accessed prefixes and virtual slots.
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include <map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<int>::operator()(int const &x,int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool>::pair(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > const &, bool const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator++(); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator--(); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(pair<int const, int> const &); }
// Call retail's hinted insert_unique (0x00422EC0) instead of emitting this unit's own copy.
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, pair<int const, int> const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$l:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> pair<_Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::iterator, bool> _Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::insert_unique(const pair<const int, int> &); }
struct Vector4 {float x,y,z,w; __declspec(noinline) Vector4() {} };
struct Rva00477BA2Vector;
class Matrix3D {public:__forceinline Matrix3D(){} inline Rva00477BA2Vector Get_X_Vector() const; Vector4 rows[3];};
struct Rva00477BA2Vector {float x,y,z; Rva00477BA2Vector(float xx,float yy,float zz):x(xx),y(yy),z(zz){} void operator*=(float n){x*=n;y*=n;z*=n;} };
inline Rva00477BA2Vector Matrix3D::Get_X_Vector() const {return Rva00477BA2Vector(rows[0].x,rows[1].x,rows[2].x);}
class Thing {public:void setTransformMatrix(const Matrix3D*);};
enum DamageType{DAMAGE=8}; enum DeathType{DEATH=0};
class Rva003909FAObj
{
public:
	void consume(void *,int,int);
};
class PhysicsBehavior
{
public:
	void rva00390629(bool);
};
class Rva00477BA2Flags {public:unsigned int word[19];unsigned int test(unsigned int b)const{return word[b>>5]&(1U<<(b&31));}void set(unsigned int b){word[b>>5]|=1U<<(b&31);}};
class Object: public Thing {public:
 int getMultiLogicalBonePosition(const char*,int,Coord3D*,Matrix3D*,bool,int)const;
 bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*)const;
 void rva0028AE6D(); void kill(DamageType,DeathType);
 const Matrix3D*getTransformMatrix()const{return &matrix;}
 char pad0[8]; Matrix3D matrix; Coord3D position; float orientation;
 char pad48[0x74-0x48]; int id;
 char pad78[0x10C-0x78]; Rva00477BA2Flags flags;
 char pad158[0x25C-0x158]; PhysicsBehavior*physics;
};
int GetGameLogicRandomValue(int,int,char*,int);
class Rva00463235
{
public:
	AsciiString rva00463235(Thing *);
};
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
 Object*getObject()const{return owner;}
 char pad0[8]; Object*owner;
 char padC[0x48-0xC]; _STL::map<int,int> slots;
};
void HordeTransportContain::rva00477BA2(OldContain*old,Object*object){
 Matrix3D matrices[32]; int indices[32];
 int count=0; int index=0;
 AsciiString bone= reinterpret_cast<Rva00463235*>(this)->rva00463235(object);
 count=getObject()->getMultiLogicalBonePosition(bone.str(),32,0,matrices,true,reinterpret_cast<int>(indices));
 if(count==0 && getObject()->getSingleLogicalBonePosition(bone.str(),0,&matrices[0]))count=1;
 int id=object->id;
 _STL::map<int,int>::iterator end=slots.end();
 _STL::map<int,int>::iterator it=slots.find(id);
 if(it!=end)index=slots[id];
 if(index>=count)index=0;
 if(old)old->removing(object);
 reinterpret_cast<NotifyContain*>(reinterpret_cast<char*>(this)+0x20)->n41(object,false);
 object->setTransformMatrix(&matrices[index]);
 PhysicsBehavior*physics=object->physics;
 if(physics){
  const Matrix3D*matrix3D=object->getTransformMatrix();
  Rva00477BA2Vector direction(matrix3D->rows[0].x,matrix3D->rows[1].x,matrix3D->rows[2].x);
  direction.z=1.0f;
  float magnitude=(float)GetGameLogicRandomValue(3,8,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeTransportContain.cpp",702);
  direction*=magnitude;
  Coord3D force; force.x=direction.x; force.y=direction.y; force.z=direction.z;
  physics->rva00390629(true);
  if(!object->flags.test(127)){object->flags.set(127);object->rva0028AE6D();}
  reinterpret_cast<Rva003909FAObj*>(physics)->consume(&force,0,0);
 }
 object->kill(DAMAGE,DEATH);
}
