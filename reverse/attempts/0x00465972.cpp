// ?privateRedeployOccupants@OpenContain@@AAEXPBV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@PAV?$map@HHU?$less@H@_STL@@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@3@@Z
// partial score=0.6520633097584074 date=2026-10-09
// Bank: target model-condition map values consume19 words (native value+0x14 forwarded to model worker); unsigned find call at RVA357180, not the signed int/int worker. Correct ABI still needs final provider resolution.
// cl: /O1 /GF- /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /I. /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// stlport
// OpenContain privateRedeployOccupants: WB1198D60 names owner/function; native465972..465EF1 RET8 proves full boundary.
// BF1 9cbfb551 / GeneralsMD OpenContain putObjAtNextFirePoint supplies purpose; native bulk algorithm is target-specific.
#include <map>
#include <list>
#include <stdlib.h>
#include "ascii_string.h"
// Read-only BF1/GeneralsMD matrix3d.h supplies the 3-by-4 float copy contract.
// Native32 arrays each invoke three16B default row constructors.
class Vector4{public:Vector4(){}float X,Y,Z,W;};
class Matrix3D{public:Vector4 rows[3];__forceinline Matrix3D(){}__forceinline Matrix3D &operator=(const Matrix3D &r){
 rows[0].X=r.rows[0].X;rows[0].Y=r.rows[0].Y;rows[0].Z=r.rows[0].Z;rows[0].W=r.rows[0].W;
 rows[1].X=r.rows[1].X;rows[1].Y=r.rows[1].Y;rows[1].Z=r.rows[1].Z;rows[1].W=r.rows[1].W;
 rows[2].X=r.rows[2].X;rows[2].Y=r.rows[2].Y;rows[2].Z=r.rows[2].Z;rows[2].W=r.rows[2].W;return *this;}
 const float *operator[](int i)const{return (const float*)&rows[i];}};
#include "Lib/Coord3D.h"
enum ObjectStatusTypes{STATUS_DUMMY=-1};enum WhichTurretType{TURRET_DUMMY=-1};
class Object;
class Thing{public:void setTransformMatrix(const Matrix3D*);void setPosition(const Coord3D*);};
class Rva00463235{public:AsciiString rva00463235(Thing*);};
class Rva001E42F2{public:void rva001E42F2(const int*);};
class Rva001E431E{public:void rva001E431E(const int*);};
class Rva000B6253{public:Rva000B6253(int,unsigned,unsigned,unsigned,unsigned,unsigned);operator const int*()const{return words;}int words[19];};
class Object{public:bool testStatus(ObjectStatusTypes)const;void setStatus(ObjectStatusTypes,bool);int getMultiLogicalBonePosition(const char*,int,Coord3D*,Matrix3D*,bool,int)const;bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*)const;bool getSingleLogicalBonePositionOnTurret(WhichTurretType,const char*,Coord3D*,Matrix3D*)const;
 char pad[8];Matrix3D transform;char pad38[0x74-0x38];int id;};
struct RedeployStatusMask{unsigned words[4];bool test(int bit)const{return (unsigned char)(words[bit>>5]>>(bit&31))&1;}};
template<int N>class RedeploySlots:public RedeploySlots<N-1>{public:virtual void slot(char(*)[N])=0;};template<>class RedeploySlots<0>{};
class RedeployContain27:public RedeploySlots<27>{public:virtual void placement(Object*,bool);};
class RedeployContain44:public RedeploySlots<44>{public:virtual RedeployStatusMask getStatus(Object*);};
class Rva004650A0:public _STL::map<int,AsciiString>{public:AsciiString &rva004650A0(const int&);};
struct RedeployModelMask{unsigned words[19];};
struct RedeployModuleData{char pad[0x4C];_STL::map<unsigned,RedeployModelMask> conditions;char pad58[0x85-0x4C-sizeof(_STL::map<unsigned,RedeployModelMask>)];bool turret;};
class OpenContain:public RedeploySlots<14>{public:virtual bool orient(Object*);private:Object *getObject()const{return owner;}void privateRedeployOccupants(const _STL::list<Object*>*,_STL::map<int,int>*);
 const RedeployModuleData *data;Object *owner;char pad0C[0x20-0x0C];char contain[4];char pad24[0x3C-0x24];Rva004650A0 names;};
void OpenContain::privateRedeployOccupants(const _STL::list<Object*> *objects,_STL::map<int,int> *oldPoints){
 AsciiString lastBone("");bool multiple=true;Matrix3D firePoints[32];int indices[32];int loaded=0;
 for(_STL::list<Object*>::const_iterator it=objects->begin();it!=objects->end();++it){
  Object *object=*it;if(object->testStatus((ObjectStatusTypes)0x28))continue;
  AsciiString bone=((Rva00463235*)this)->rva00463235((Thing*)object);
  if(bone!=lastBone){loaded=getObject()->getMultiLogicalBonePosition(bone.str(),32,0,firePoints,true,(int)indices);lastBone=bone;
   if(!loaded){if(getObject()->getSingleLogicalBonePosition(bone.str(),0,firePoints)){loaded=1;multiple=false;}}
  }
  int objectID=object->id;int point=-1;
  if(oldPoints->find(objectID)!=oldPoints->end()){int oldPoint=(*oldPoints)[objectID];if(oldPoint<loaded)point=oldPoint;}
  else{int p;bool taken=false;for(p=0;p<loaded;++p){taken=false;AsciiString candidate(bone);
    if(multiple){char suffix[8];_itoa(p+1,suffix,10);if(point<10){char zero='0';((StringBase<char>*)&candidate)->concat(&zero,1);}candidate+=suffix;}
    for(Rva004650A0::const_iterator n=names.begin();n!=names.end();++n){if(n->second==candidate){taken=true;break;}}
    if(!taken)break;
   }
   if(!taken){point=p;(*oldPoints)[objectID]=point;}
  }
  Matrix3D placement;
  if(point!=-1){
   if(((RedeployContain44*)&contain)->getStatus(object).test(1)&&!((RedeployContain44*)&contain)->getStatus(object).test(61))object->setStatus((ObjectStatusTypes)5,false);
   AsciiString fullBone(bone);
   if(multiple){char suffix[8];_itoa(point+1,suffix,10);if(point<10){char zero='0';((StringBase<char>*)&fullBone)->concat(&zero,1);}fullBone+=suffix;}
   int boneObjectID=object->id;names.rva004650A0(boneObjectID)=fullBone;
   if(data->turret){getObject()->getSingleLogicalBonePositionOnTurret((WhichTurretType)0,fullBone.str(),0,&placement);}
   else{placement=firePoints[point];((Rva001E42F2*)object)->rva001E42F2(Rva000B6253(0,0xC2,0xC3,0xC4,0xC5,0xC6));
    unsigned boneIndex=indices[point];_STL::map<unsigned,RedeployModelMask>::const_iterator mod=data->conditions.find(boneIndex);if(mod!=data->conditions.end())((Rva001E431E*)object)->rva001E431E((const int*)mod->second.words);
   }
   ((RedeployContain27*)contain)->placement(object,((RedeployContain44*)&contain)->getStatus(0).test(61));
  }else{
   if(((RedeployContain44*)&contain)->getStatus(object).test(1)&&!((RedeployContain44*)&contain)->getStatus(object).test(61))object->setStatus((ObjectStatusTypes)5,true);
   placement=owner->transform;((RedeployContain27*)contain)->placement(object,true);
  }
  if(!((RedeployContain44*)&contain)->getStatus(0).test(61)&&orient(object))((Thing*)object)->setTransformMatrix(&placement);
  else{Coord3D pos;pos.x=placement[0][3];pos.y=placement[1][3];pos.z=placement[2][3];((Thing*)object)->setPosition(&pos);}
 }
}
