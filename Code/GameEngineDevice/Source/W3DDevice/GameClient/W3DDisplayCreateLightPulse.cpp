// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /EHsc /arch:SSE
// Native0004423C..00044325 RET18,233B. ZH W3DDisplay::createLightPulse
// supplies the dynamic-light range/color/fade semantics. Target uses21.0f
// floor, light AmbientD4/DiffuseE0/FarStart100/FarEnd104 and decay145/146.
// Existing pool6F94A, enabled42F30 and frame-fade6DF81 providers agree.
// Display vslotBC LightPulseFXNugget consumers prove Coord3D/RGBColor ABI;
// light slot58 is RenderObjClass Set_Position. Direct Vector3 temporary
// passed by const reference preserves native LEA and third-store schedule.
struct Vector3
{
	float x;
	float y;
	float z;
 Vector3(){}
 Vector3(float a,float b,float c):x(a),y(b),z(c){}
};


#include "Lib/Coord3D.h"
struct RGBColor{float red,green,blue;};
class W3DDynamicLight
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void Set_Position(const Vector3 &v);
	void setEnabled(bool enabled);
	void setFrameFade(unsigned int frameIncreaseTime, unsigned int decayFrameTime);

public:
	unsigned char m_pad4[0xD4 - 4];
	Vector3 Ambient;
	Vector3 Diffuse;
	unsigned char m_padEC[0x100 - 0xEC];
	float FarAttenStart;
	float FarAttenEnd;
	unsigned char m_pad108[0x145 - 0x108];
	bool m_b145;
	bool m_b146;
};

class RTS3DScene
{
public:
	W3DDynamicLight *rva0006F94A(void);
};

class W3DDisplay
{
public:
	void createLightPulse(const Coord3D *pos, const RGBColor *color, float a, float b, unsigned int c, unsigned int d);

	static RTS3DScene *m_3DScene;
};



void W3DDisplay::createLightPulse(const Coord3D *pos, const RGBColor *color, float a, float b, unsigned int c, unsigned int d)
{
	float range = a + b;
	if (21.0f > range)
		return;
	W3DDynamicLight *light = m_3DScene->rva0006F94A();
	light->setEnabled(true);
	Vector3 tmp;
	tmp.x = color->red;
	tmp.y = color->green;
	tmp.z = color->blue;
	Vector3 *ambient = &light->Ambient;
	ambient->x = tmp.x;
	ambient->y = tmp.y;
	ambient->z = tmp.z;
	tmp.x = color->red;
	tmp.y = color->green;
	tmp.z = color->blue;
	Vector3 *diffuse = &light->Diffuse;
	diffuse->x = tmp.x;
	diffuse->y = tmp.y;
	diffuse->z = tmp.z;
light->Set_Position(Vector3(pos->x,pos->y,pos->z));
	light->FarAttenStart = a;
	light->FarAttenEnd = range;
	light->setFrameFade(c, d);
	light->m_b145 = true;
	light->m_b146 = true;
}
