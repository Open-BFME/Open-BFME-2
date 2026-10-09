// ?Rva000471AD@W3DDisplay@@UAEXPBVImage@@MMMMMK@Z
// partial score=0.6132989794 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/GameEngineDevice/Source/W3DDevice/GameClient
#include "BFME2ParticleTextureHandles.h"
extern "C" float __cdecl atan2f(float,float);
extern "C" double __cdecl tan(double);
const float ClockPi=3.14159265358979323846f;
class Vector2{public:float X,Y;Vector2(){}Vector2(float x,float y):X(x),Y(y){}Vector2&operator=(const Vector2&v){X=v.X;Y=v.Y;return *this;}};
class RectClass{public:float Left,Top,Right,Bottom;};
class Image{public:const RectClass*Get_Image_Coords()const{return &uv;}char gap[0x14];RectClass uv;};
BFME2ParticleTextureHandle Rva000470D5(const Image*);
class Rva000456C9{public:void rva000456C9(const RefCountPtr<TextureClass>*);};
class Render2DClass{public:void Add_Tri(const Vector2&,const Vector2&,const Vector2&,const Vector2&,const Vector2&,const Vector2&,unsigned long);unsigned state;char gap04[0x44];bool active;};
class W3DDisplay{public:virtual void Rva000471AD(const Image*,float,float,float,float,float,unsigned long);char gap04[0x164];Render2DClass*render;};
void W3DDisplay::Rva000471AD(const Image*image,float startX,float startY,float endX,float endY,float percent,unsigned long color)
{
 if(!image)return;
 const RectClass*uv=image->Get_Image_Coords();if(!uv)return;
 static float halfPi=ClockPi*0.5f;
 static float threeHalfPi=ClockPi*1.5f;
 static float twoPi=ClockPi*2.0f;
 float angle=twoPi-(twoPi*percent)*0.01f;
 if(angle<=0)return;if(angle>twoPi)angle=twoPi;
 render->state=2;render->active=true;
 ((Rva000456C9*)render)->rva000456C9((const RefCountPtr<TextureClass>*)&Rva000470D5(image));
 float width=endX-startX,height=endY-startY;
 Vector2 center;float halfHeight=height*0.5f;center.Y=halfHeight+startY;
 float ratioWidthHeight=width/height,ratioHeightWidth=height/width;
 float halfU=(uv->Right-uv->Left)*0.5f,halfV=(uv->Bottom-uv->Top)*0.5f;
 float halfWidth=width*0.5f;center.X=halfWidth+startX;
 Vector2 centerUV;centerUV.X=uv->Left+halfU;centerUV.Y=uv->Top+halfV;
 float cornerAngle=atan2f(width,height);
 Vector2 next(startX,startY),nextUV(uv->Left,uv->Top);
 Vector2 previous(center.X,startY),previousUV(centerUV.X,uv->Top);
 bool done=false;
 if(angle<=cornerAngle){double t=tan((double)angle);next.X=center.X-halfHeight*t;nextUV.X=centerUV.X-halfU*t*ratioHeightWidth;done=true;}
 render->Add_Tri(center,next,previous,centerUV,nextUV,previousUV,color);if(done)return;
 previous=next;previousUV=nextUV;next.Y=endY;nextUV.Y=uv->Bottom;
 if(angle<=ClockPi-cornerAngle){
  if(angle>halfPi){double t=tan((double)(angle-halfPi));next.Y=center.Y+halfWidth*t;nextUV.Y=centerUV.Y+halfV*t*ratioWidthHeight;}
  else{double t=tan((double)(halfPi-angle));next.Y=center.Y-halfWidth*t;nextUV.Y=centerUV.Y-halfV*t*ratioWidthHeight;}done=true;
 }
 render->Add_Tri(center,next,previous,centerUV,nextUV,previousUV,color);if(done)return;
 previous=next;previousUV=nextUV;next.X=endX;nextUV.X=uv->Right;
 if(angle<=ClockPi+cornerAngle){
  if(angle>ClockPi){double t=tan((double)(angle-ClockPi));next.X=center.X+halfHeight*t;nextUV.X=centerUV.X+halfU*t*ratioHeightWidth;}
  else{double t=tan((double)(ClockPi-angle));next.X=center.X-halfHeight*t;nextUV.X=centerUV.X-halfU*t*ratioHeightWidth;}done=true;
 }
 render->Add_Tri(center,next,previous,centerUV,nextUV,previousUV,color);if(done)return;
 previous=next;previousUV=nextUV;next.Y=startY;nextUV.Y=uv->Top;
 if(angle<=twoPi-cornerAngle){
  if(angle>threeHalfPi){double t=tan((double)(angle-threeHalfPi));next.Y=center.Y-halfWidth*t;nextUV.Y=centerUV.Y-halfV*t*ratioWidthHeight;}
  else{double t=tan((double)(threeHalfPi-angle));next.Y=center.Y+halfWidth*t;nextUV.Y=centerUV.Y+halfV*t*ratioWidthHeight;}done=true;
 }
 render->Add_Tri(center,next,previous,centerUV,nextUV,previousUV,color);if(done)return;
 previous=next;previousUV=nextUV;
 double t=tan((double)(twoPi-angle));next.X=center.X+halfHeight*t;nextUV.X=centerUV.X+halfU*t*ratioHeightWidth;
 render->Add_Tri(center,next,previous,centerUV,nextUV,previousUV,color);
}
