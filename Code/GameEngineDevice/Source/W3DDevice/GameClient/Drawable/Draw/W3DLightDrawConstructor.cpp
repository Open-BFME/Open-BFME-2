// cl: /DNDEBUG /MD /EHsc
// ??0W3DLightDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0x000CF91D 287B
// Evidence: LINK toss names it (friend_newModuleInstance 0x00064E1E calls it);
// donor reference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLightDrawConstructor.cpp
// (BFME1 retail 0x007583A0 same shape); vtable g_00BCD728; base ctor row 0x000B19A1 via existing DrawModule twin pin.
// BFME2 deltas vs donor: far-attenuation flag bit at +0xC8 (retail or dword); setEnabled and setFrameFade are
// out-of-line rows; refcount at +0x04 via RefCountClass copied from W3DLightDrawDestructor.cpp.

class Thing;
class ModuleData;

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3(void) { }
	Vector3(const Vector3 &value) { X = value.X; Y = value.Y; Z = value.Z; }
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3 &operator=(const Vector3 &value)
	{
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		return *this;
	}
};

typedef unsigned int UnsignedInt;
typedef bool Bool;

class RefCountClass
{
public:
	void Release_Ref() const
	{
		--m_numRefs;
		if (m_numRefs == 0)
			const_cast<RefCountClass *>(this)->Delete_This();
	}
	void Add_Ref(void) { ++m_numRefs; }
	virtual void Delete_This();
protected:
	virtual ~RefCountClass();
private:
	mutable int m_numRefs; // +0x04
};

class RenderObjClass : public RefCountClass
{
protected:
	virtual ~RenderObjClass();
};

class LightClass : public RenderObjClass
{
protected:
	virtual ~LightClass();
};

class W3DDynamicLight : public LightClass
{
public:
	void setEnabled(Bool enabled);
	void Set_Ambient(const Vector3 &color) { m_ambient = color; }
	void Set_Diffuse(const Vector3 &color) { m_diffuse = color; }
	void Set_Far_Attenuation_Range(double start, double end)
	{
		m_farAttenStart = (float)start;
		m_farAttenEnd = (float)end;
	}
	void setFrameFade(UnsignedInt increase, UnsignedInt decay);
	void setFarAttenuationEnabled(void)
	{
		*(UnsignedInt *)((char *)this + 0xC8) |= 1;
	}
	// Slots 0-1 are the RefCountClass virtuals above. Slots 2-21 are padding:
	// only Set_Position's index (22 -> retail call [eax+0x58]) is asserted.
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void Set_Position(const Vector3 &position);
private:
	char m_pad08[0xCC];
	Vector3 m_ambient; // +0xD4
	Vector3 m_diffuse; // +0xE0
	char m_padEC[0x14];
	float m_farAttenStart; // +0x100
	float m_farAttenEnd; // +0x104
};

class WWMath
{
public:
	static float Random_Float(void);
};

class RTS3DScene
{
public:
	W3DDynamicLight *getADynamicLight(void);
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class DrawableModule
{
protected:
	virtual ~DrawableModule();

	void *m_moduleData; // +0x04
	void *m_drawable; // +0x08
};

class DrawModule : public DrawableModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);
protected:
	virtual ~DrawModule() {}
};

struct LightColorRGB
{
	float m_red; // +0x00
	float m_green; // +0x04
	float m_blue; // +0x08
};

class W3DLightDrawModuleData
{
public:
	virtual void moduleDataAnchor(void);

	char m_base[4];
	LightColorRGB m_ambientColor;
	LightColorRGB m_diffuseColor;
	LightColorRGB m_specularColor;
	float m_radius;
};

class W3DLightDraw : public DrawModule
{
public:
	W3DLightDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DLightDraw();
private:
	W3DDynamicLight *m_light; // +0x0C
	float m_phase; // +0x10
	float m_radius; // +0x14
	float m_angle; // +0x18
	float m_height; // +0x1C
};

W3DLightDraw::W3DLightDraw(Thing *thing, const ModuleData *moduleData)
	: DrawModule(thing, moduleData)
{
	m_radius = 0.0f;
	m_angle = 0.0f;
	m_height = 0.0f;
	m_phase = WWMath::Random_Float() * 30.0f;
	m_light = W3DDisplay::m_3DScene->getADynamicLight();
	if (m_light)
	{
		m_light->Add_Ref();
		const W3DLightDrawModuleData *data =
			(const W3DLightDrawModuleData *)moduleData;
		m_light->setEnabled(true);
		m_light->Set_Ambient(Vector3(data->m_ambientColor.m_red, data->m_ambientColor.m_green, data->m_ambientColor.m_blue));
		m_light->Set_Diffuse(Vector3(data->m_diffuseColor.m_red, data->m_diffuseColor.m_green, data->m_diffuseColor.m_blue));
		m_light->Set_Position(Vector3(0.0f, 0.0f, 0.0f));
		m_light->setFrameFade(0, 0);
		m_light->Set_Far_Attenuation_Range(1.0, data->m_radius);
		m_light->setFarAttenuationEnabled();
	}
}
