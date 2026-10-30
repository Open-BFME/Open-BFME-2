// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ZH Vector3::Quick_Distance/Quick_Length and WWMath::Fabs at BF1 cee35b7d8
// guide the distance approximation; native 276952..276B32 RET8 and WB C9E310
// independently prove its use in the tornado-bone helper. Native offsets
// count8/drawC/matrices10 and the refresh/getPosition/normalize calls are
// established by this body and its rowed neighbours. Original method name
// remains unknown. Input and output are three-float coordinates.
// Retail differs from the donor's last swap: after comparing mid/low it
// assigns mid=low but preserves low. Both native arithmetic coefficients and
// the resulting distance behaviour are kept. WB is a debug relationship lead
// and does not override the full retail body. A named final matrix pointer
// gives the witnessed base+10 LEA; initialize normal.z before normal.x/y to
// preserve the native zero/load/store order. No new pin or alias.
#include "../../../Libraries/Include/Lib/Coord3D.h"
class Matrix3D { public: int v[12]; };
class Drawable {public:const Coord3D *getPosition() const;};
class Rva002768AC {
public:
 void rva002768AC();
 bool rva00276952(const Coord3D *,Coord3D *);
private:
 void *m_vtable;
 unsigned m_time4;
 int m_count8;
 Drawable *m_drawC;
 Matrix3D m_mats[16];
};
__forceinline float tornadoAbs(float f){ int bits=*(int *)&f; bits&=0x7fffffff; return *(float *)&bits; }
__forceinline float tornadoQuickDistance(const Coord3D &lhs,const Coord3D &rhs){
 Coord3D delta; delta.x=lhs.x-rhs.x;delta.y=lhs.y-rhs.y;delta.z=lhs.z-rhs.z;
 float max=tornadoAbs(delta.x),mid=tornadoAbs(delta.y),min=tornadoAbs(delta.z),temp;
 if(max<mid){temp=max;max=mid;mid=temp;}
 if(max<min){temp=max;max=min;min=temp;}
 if(mid<min){mid=min;}
 return max+0.34375f*mid+0.25f*min;
}
bool Rva002768AC::rva00276952(const Coord3D *position,Coord3D *out){
 if(!m_drawC)return false;
 rva002768AC();
 if(!m_count8)return false;
 Coord3D pos={position->x,position->y,position->z};
 pos.x-=m_drawC->getPosition()->x;pos.y-=m_drawC->getPosition()->y;pos.z-=m_drawC->getPosition()->z;
 float best=2000.0f; unsigned which=0xffff;
 Coord3D bone={0,0,0};
 for(unsigned i=0;i<(unsigned)m_count8;++i){
  bone.x=*(float *)&m_mats[i].v[3];bone.y=*(float *)&m_mats[i].v[7];bone.z=*(float *)&m_mats[i].v[11];
  float distance=tornadoQuickDistance(pos,bone);
  if(distance<best){best=distance;which=i;}else if(distance>best+100.0f)break;
 }
 if(which==0xffff)return false;
 const Matrix3D *mat=&m_mats[which];
 bone.x=*(float *)&mat->v[3];bone.y=*(float *)&mat->v[7];bone.z=*(float *)&mat->v[11];
 Coord3D normal;normal.z=0.0f;normal.x=bone.x-pos.x;normal.y=bone.y-pos.y;
 normal.normalize();float x=normal.x;normal.x=normal.y;normal.y=-x;
 *out=normal;return true;
}
