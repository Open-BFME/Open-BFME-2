// cl: /O1 /G7 /MD /EHsc /arch:SSE /Ireference/shims/bfme2_ascii
// Retail 0x005B1019..0x005B1275, 604 bytes, no stack arguments.
// WB 0x01570850 has this camera refresh inside AptMyHero.cpp; its Vector3
// label comes from an inlined Rotate_Z assertion, not the owner identity.
// Callers 0x005B1288 and SwitchToPendingHero 0x005B1E71 retain the AptMyHero
// receiver. The method name remains address-derived.
//
// The view/index and current-choice locals preserve WB's scalar staging.
// They select retail's info-in-EBX, view-in-EAX/ESI and preset-in-EDX shape.
// Use the toolchain's sinf/cosf wrappers: direct casts of sin/cos schedule the
// cosine store too early. Rotate_Z follows the ZH Vector3 overloads available
// at BFME1 reference cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
// The position scalar accessor preserves retail's Y-then-X load order.
// Camera record and virtual slot declarations retain the existing witnessed
// providers; no additional callee names, global addresses or pins are needed.
// ?rva005B1019@AptMyHero@@QAEXXZ

#include "ascii_string.h"
struct BfmePod8 {
	int a;
	float b;
};
class Object;
class Rva004076EE {
	public:
	Object *rva004076EE();
};
struct Rva005B0473View {
	char pad[0x68];
	int field68;
};
class Thing {
	public:
	void setOrientation(float);
	char pad[0x38];
	float posX,posY,posZ;
	float getX()const{
		return posX;
	}
};
class Rva002195E6;
class CreateAHeroManager {
	public:
	const Rva002195E6 *GetViewInfo(unsigned int,unsigned int);
};
extern CreateAHeroManager *TheCreateAHeroManager;
class Rva005B01D3 {
	public:
	float rva005B0569(float);
	float rva005B0588(float);
	float rva005B05A8(float);
	float rva005B05C8(float);
	float rva005B05E8(float);
};
struct MyHeroCameraPreset {
	float field00,field04,field08,field0C,field10;
};
struct MyHeroCameraView2 {
	char pad00[0x18];
	MyHeroCameraPreset preset18;
	char pad2C[4];
	MyHeroCameraPreset preset30;
	char pad44[4];
	MyHeroCameraPreset preset48;
	char pad5C[8];
	float field64;
};
struct ThreeInts;
class Rva0008A234 {
	public:
	Rva0008A234(const StringBase<char>&,const ThreeInts*,float,float,float,float,float,float);
	int field00;
	AsciiString name04;
	char pad08[0x2c-8];
	unsigned char field2C;
};
class View;
extern View *TheTacticalView;
class MyHeroTacticalView {
	public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60(int,Rva0008A234*,int,bool,float,float);
};
#include <math.h>
struct MyHeroOffset {
	float X,Y,Z;
	MyHeroOffset(float xCoord,float yCoord,float zCoord){
		X=xCoord;
		Y=yCoord;
		Z=zCoord;
	}
	__forceinline void Rotate_ZF(float angle){
		Rotate_Z(sinf(angle),cosf(angle));
	}
	__forceinline void Rotate_Z(float s_angle,float c_angle){
		float originalX=X;
		float originalY=Y;
		X=c_angle*originalX-s_angle*originalY;
		Y=s_angle*originalX+c_angle*originalY;
	}
};
struct CameraPosition {
	float x,y,z;
	CameraPosition(float initialX,float initialY,float initialZ):x(initialX),y(initialY),z(initialZ){
	}
	CameraPosition &operator+=(const CameraPosition &p){
		x+=p.x;
		y+=p.y;
		z+=p.z;
		return *this;
	}
};
class AptMyHero {
public:
	BfmePod8 *GetObjectInfo(int);
private:
	char pad00[0xc];
	int field0C,field10;
	char pad14[0x140-0x14];
	void *holder140;
	char pad144[0x168-0x144];
	float field168,field16C;
	int field170;
	public:
	Rva005B0473View *rva005B0473();
	void rva005B1019();
};
void AptMyHero::rva005B1019(){
	Thing *object=(Thing *)reinterpret_cast<Rva004076EE *>(this)->rva004076EE();
	if(!object)return;
	Rva005B0473View *firstView=rva005B0473();
	int firstIndex=firstView->field68;
	BfmePod8 *info=GetObjectInfo(firstIndex);
	object->setOrientation(field168+info->b);
	int b=field10;
	int classIndex=field0C;
	const MyHeroCameraView2 *view=reinterpret_cast<const MyHeroCameraView2 *>(TheCreateAHeroManager->GetViewInfo(classIndex,b));
	float interpolationFactor=field16C;
	const MyHeroCameraPreset *preset=&view->preset18;
	bool useLerp=true;
	if(field170){
		useLerp=false;
		int currentChoice=*(int *)((char *)holder140+0x410);
		if(currentChoice==((int *)((char *)holder140+0x418))[3])preset=&view->preset30;
		else preset=&view->preset48;
	}
	Rva005B01D3 *lerp=(Rva005B01D3 *)view;
	float offsetY=useLerp?lerp->rva005B05E8(interpolationFactor):preset->field10;
	float pitch=useLerp?lerp->rva005B0569(interpolationFactor):preset->field00;
	float zoom=useLerp?lerp->rva005B0588(interpolationFactor):preset->field04;
	float floor=useLerp?lerp->rva005B05A8(interpolationFactor):preset->field08;
	float m_offsetX=useLerp?lerp->rva005B05C8(interpolationFactor):preset->field0C;
	float fovZoom=0.83f;
	float roll=0;
	float rot=view->field64;
	float angle=rot+info->b;
	MyHeroOffset offset(m_offsetX,offsetY,0.0f);
	offset.Rotate_ZF(angle);
	CameraPosition pos(object->getX(),object->posY,object->posZ);
	pos+=CameraPosition(offset.X,offset.Y,offset.Z);
	Rva0008A234 camera(*(const StringBase<char> *)&AsciiString("TempCamera"),(const ThreeInts *)&pos,floor,angle+1.5707964f,pitch,zoom,fovZoom,roll);
	((MyHeroTacticalView *)TheTacticalView)->slot60(0,&camera,0,true,0.0f,0.0f);
}
