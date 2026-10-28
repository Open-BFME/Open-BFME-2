// cl: /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /O1 /Op /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// stlport46
//
// Native4E52DC walks a circular list and calls4E50C8 on each node's member.
// The separate4E7277 notification state gate calls the verified UpdateNotice
// provider before tail-calling4E6846. Their existing31B/36B rows stay exact.

// Native4E50C8..4E52DC complete532B. The existing circular-list walker
// calls this subobject at node+8. Retail accesses establish center+0 radius18
// opacity24 length bounds28/2C color30 and two STLport lists34/38.
// Shadow manager and ShadowTypeInfo use existing native owners. The original
// application class/method names remain unknown. Farm's explicit float cast
// on the x result is equivalent to compound assignment; no volatile or barrier.
#include "ascii_string.h"
#include "Coord3D.h"
#include <math.h>
#include <string.h>
#pragma intrinsic(memcpy)
#include <list>
class Shadow{public:
 struct ShadowTypeInfo{ShadowTypeInfo();~ShadowTypeInfo();AsciiString m_first,m_second;int m_type;float m_floatC,m_float10,m_float14,m_float18,m_float1C,m_float20;unsigned char m_byte24,m_byte25,m_byte26;};
 void setColor(int);void setOpacity(int);
 char pad0[8];Coord3D position;char pad14[12];float rotation;char pad24[64];bool flag64;
};
class CloudShadowFactoryView{public:virtual void slot0();virtual void slot1();virtual Shadow*create(Shadow::ShadowTypeInfo*);};
class ProjectedShadowManager;extern ProjectedShadowManager *TheProjectedShadowManager;
float normalizeAngle(float);

namespace _STL{template<> inline __declspec(noinline) _List_node<Shadow*>*list<Shadow*>::_M_create_node(Shadow*const&value){_List_node<Shadow*>*node=this->_M_node.allocate(1);_Construct(&node->_M_data,value);return node;}}
struct AngleRange{float first,last;};
class Rva004E50C8{public:void rva004E50C8();Coord3D center;char pad0C[12];float radius;char pad1C[8];float opacity,minLength,maxLength;int color;_STL::list<Shadow*>shadows;_STL::list<AngleRange>angles;};


struct TerrainClaimNode
{
	TerrainClaimNode *m_next;
	char m_pad[4];
	Rva004E50C8 m_sub;
};

class Rva004E52DC
{
public:
	void rva004E52DC();

private:
	void *m_00;
	TerrainClaimNode *m_04;
};

// ?rva004E52DC@Rva004E52DC@@QAEXXZ @0x004E52DC 31B.
void Rva004E52DC::rva004E52DC()
{
	for (TerrainClaimNode *node = m_04->m_next; node != m_04; node = node->m_next)
		node->m_sub.rva004E50C8();
}

class Rva004E6846
{
public:
	void rva004E6846();
};

// Native4E7277 calls the already verified577B UpdateNotice at4E701E.
class InGameNotificationBoxMovieClip { public: void UpdateNotice(); };

class Rva004E7277
{
public:
	void rva004E7277();
	void *rva004E7392(Rva004E7277 *arg);
	void rva004E72C0(void *arg);

private:
	void *m_00;
	void *m_04;
	int m_08;
	char m_pad0C[0x40 - 0x0C];
	int m_40;
};

// ?rva004E7277@Rva004E7277@@QAEXXZ @0x004E7277 36B.
void Rva004E7277::rva004E7277()
{
	if (m_08 == 0)
		return;
	if (m_40 != 0)
		((InGameNotificationBoxMovieClip *)this)->UpdateNotice();
	if (m_08 == 3)
		((Rva004E6846 *)this)->rva004E6846();
}

void Rva004E50C8::rva004E50C8(){
 Shadow::ShadowTypeInfo info;
 info.m_first="TerrainClaimSegment";info.m_byte25=0;info.m_byte26=1;info.m_type=64;
 for(_STL::list<AngleRange>::iterator node=angles.begin();node._M_node!=angles.end()._M_node;++node){
  float begin=(*node).first;float end=(*node).last;
  float circumference=radius*6.28318548f;
  float difference=end-begin;
  float length=circumference*(difference*0.159154937f);
  int count=(int)(length/circumference*32.0f);
  int byMaximum=(int)(length/maxLength);
  if(count<byMaximum)count=byMaximum;
  int byMinimum=(int)(length/minLength);
  if(count>byMinimum)count=byMinimum;
  float pieceLength=length/(float)count;
  info.m_floatC=info.m_float10=pieceLength;
  float step=difference/(float)count;
  for(float angle=begin;angle<end-step*0.100000001f;angle+=step){
    float mid=angle+step*0.5f;
    float localRadius=radius-pieceLength*0.5f;
    Coord3D point;memcpy(&point.x,&center.x,4);memcpy(&point.y,&center.y,4);point.z=center.z;
    point.x=(float)(point.x+(sin((double)mid)*localRadius));point.y+=cos((double)mid)*localRadius;
    Shadow*shadow=((CloudShadowFactoryView*)TheProjectedShadowManager)->create(&info);
    if(shadow){
     shadow->rotation=normalizeAngle(-mid);
     shadow->setColor(color);
     shadow->position=point;shadow->flag64=true;
     shadow->setOpacity((int)(opacity*255.0f));
     shadows.push_front(shadow);
    }
  }
 }
}
