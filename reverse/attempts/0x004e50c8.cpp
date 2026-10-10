// ?rva004E50C8@Rva004E50C8@@QAEXXZ
// partial score=0.967997 date=2026-10-10
// cl: /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /O1 /Op /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// stlport
#include "ascii_string.h"
#include "Coord3D.h"
#include <math.h>
#include <string.h>
#pragma intrinsic(memcpy)
extern "C"void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <list>
class Shadow{public:
 struct ShadowTypeInfo{ShadowTypeInfo();~ShadowTypeInfo();AsciiString m_first,m_second;int m_type;float m_floatC,m_float10,m_float14,m_float18,m_float1C,m_float20;unsigned char m_byte24,m_byte25,m_byte26;};
 void rva00330995(int);void setOpacity(int);
 char pad0[8];Coord3D position;char pad14[12];float rotation;char pad24[64];bool flag64;
};
class CloudShadowFactoryView{public:virtual void slot0();virtual void slot1();virtual Shadow*create(Shadow::ShadowTypeInfo*);};
class AudioManager0029E159;extern AudioManager0029E159*g_00DEC2D4;
float normalizeAngle(float);

namespace _STL{template<> inline __declspec(noinline) _List_node<Shadow*>*list<Shadow*>::_M_create_node(Shadow*const&value){_List_node<Shadow*>*node=this->_M_node.allocate(1);_Construct(&node->_M_data,value);return node;}}
struct AngleNode{AngleNode*next,*prev;float first,last;};
class Rva004E50C8{public:void rva004E50C8();Coord3D center;char pad0C[12];float radius;char pad1C[8];float opacity,minLength,maxLength;int color;_STL::list<Shadow*>shadows;AngleNode*angles;};
void Rva004E50C8::rva004E50C8(){
 Shadow::ShadowTypeInfo info;
 info.m_first="TerrainClaimSegment";info.m_byte25=0;info.m_byte26=1;info.m_type=64;
 for(AngleNode*node=angles->next;node!=angles;node=node->next){
  float begin=node->first,end=node->last;
  float circumference=radius*6.28318548f;
  float difference=end-begin;
  float length=difference*0.159154937f*circumference;
  int byAngle=(int)(length/circumference*32.0f);
  int byMaximum=(int)(length/maxLength);
  int count=byAngle<byMaximum?byMaximum:byAngle;_ReadWriteBarrier();
  int byMinimum=(int)(length/minLength);count=count>byMinimum?byMinimum:count;
  float pieceLength=length/(float)count;
  float step=difference/(float)count;
  end-=step*0.100000001f;
  info.m_floatC=info.m_float10=pieceLength;
  float angle=begin;
  if(angle<end){
   float halfStep=step*0.5f,halfLength=pieceLength*0.5f;
   do{
    float mid=angle+halfStep,localRadius=radius-halfLength;
    Coord3D point;memcpy(&point.x,&center.x,4);memcpy(&point.y,&center.y,4);point.z=center.z;
    point.x+=sin((double)mid)*localRadius;point.y+=cos((double)mid)*localRadius;
    Shadow*shadow=((CloudShadowFactoryView*)g_00DEC2D4)->create(&info);
    if(shadow){
     shadow->rotation=normalizeAngle(-mid);
     shadow->rva00330995(color);
     shadow->position=point;shadow->flag64=true;
     shadow->setOpacity((int)(opacity*255.0f));
     shadows.push_front(shadow);
    }
    angle+=step;
   }while(angle<end);
  }
 }
}
