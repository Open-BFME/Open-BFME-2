// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?setModelName@W3DDebrisDraw@@UAEXVAsciiString@@HW4ShadowType@@@Z retail
// 0x000B1EEB..0x000B207F (404 bytes EH RET 0x0C). WB 0x00957710 is
// W3DDebrisDraw::setModelName (W3DDebrisDraw.cpp). It is the
// DebrisDrawInterface (+0x0C) override: this points at the interface, so
// the drawable is [this-4] and the members sit at +0x04..+0x38 from it (layout
// as in the rowed W3DDebrisDrawDestructor.cpp). The rowed setAnimNames 0x000B207F follows it.
// Zero Hour body adapted to the BFME 2 interfaces:
// - the model comes from the pinned cdecl loader 0x00137364 with the 16-byte
//   option block (rowed copy 0x0013101E; mode 1 plus color | 0xFF000000
//   when a color is given);
// - it is added to W3DDisplay::m_3DScene (slot 2), given the drawable's +0x248
//   info (Set_User_Data slot 86) and an identity transform (Set_Transform slot 21);
// - a Shadow::ShadowTypeInfo built and destroyed by its rowed ctor/dtor
//   0x00079514/0x000793FA (BFME 2's two-string 0x28-byte layout with the
//   20.0f default) gets the type and zero sizes. It goes to the rowed
//   W3DShadowManager::addShadow; otherwise the pinned 0x000518E0 handler
//   removes the old shadow.
// The emptiness test reads the string header's length word inline, as retail
// does. The present-unmatched setModelName draft in W3DDebrisDraw.cpp covers
// the same symbol.
#include "ascii_string.h"

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef Int Color;

enum ShadowType
{
	SHADOW_NONE = 0
};

class W3DDebrisDrawPoint
{
public:
	Real X;
	Real Y;
	Real Z;
	W3DDebrisDrawPoint(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
};

class W3DDebrisDrawRow
{
public:
	Real X;
	Real Y;
	Real Z;
	Real W;
	void Set(Real x, Real y, Real z, Real w) { X = x; Y = y; Z = z; W = w; }
};

class W3DDebrisDrawTransform
{
public:
	W3DDebrisDrawTransform() {}
	void Set(const W3DDebrisDrawPoint &position)
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, position.X);
		Row[1].Set(0.0f, 1.0f, 0.0f, position.Y);
		Row[2].Set(0.0f, 0.0f, 1.0f, position.Z);
	}
	W3DDebrisDrawRow Row[3];
};

class RenderObjClass
{
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20)
	virtual void Set_Transform(const W3DDebrisDrawTransform &m);					// slot 21
	V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V10(3) V10(4) V10(5) V10(6) V10(7)
	V(80) V(81) V(82) V(83) V(84) V(85)
	virtual void Set_User_Data(void *value, Bool recursive = false);	// slot 86
#undef V10
#undef V
};

class RTS3DScene
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void Add_Render_Object(RenderObjClass *obj);			// slot 2
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class Drawable
{
public:
	const Real getScale() const;
	void *getDrawableInfo() { return m_drawableInfo; }
private:
	unsigned char m_pad00[0x248];
	unsigned char m_drawableInfo[4];				// +0x248
};

// Option block of the pinned render-object loader 0x00137364 (rowed copy 0x0013101E).
class Rva0013101E
{
public:
	Rva0013101E() : m_a(0), m_b(0), m_c(0), m_d1(0), m_d2(0), m_d3(0) {}
	unsigned m_a : 3;
	unsigned m_b : 27;
	unsigned m_c : 1;
	unsigned m_keep : 1;
	unsigned m_d1;
	unsigned m_d2;
	unsigned m_d3;
};

RenderObjClass *Rva00137364CreateRenderObj(const char *name, float scale, const Rva0013101E &options);

// The shadow descriptor this function fills: Shadow::ShadowTypeInfo, whose
// rowed ctor 0x00079514 and dtor 0x000793FA give its 0x28-byte BFME 2 layout
// (two strings / type +8 / sizes / 20.0f default).
class Shadow
{
public:
	struct ShadowTypeInfo
	{
		ShadowTypeInfo();
		~ShadowTypeInfo();
		AsciiString m_first;
		AsciiString m_second;
		Int m_type;										// +0x08
		Real m_sizeX;									// +0x0C
		Real m_sizeY;									// +0x10
		Real m_offsetX;									// +0x14
		Real m_offsetY;									// +0x18
		Real m_float1C;									// +0x1C
		Real m_float20;									// +0x20
		unsigned char m_byte24;
		unsigned char m_byte25;
		unsigned char m_byte26;
	};
};

class Gen0003AC38
{
public:
	void handle(void *object);
};

class W3DShadowManager
{
public:
	Shadow *addShadow(RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);
};
extern W3DShadowManager *TheW3DShadowManager;

// BFME 2 tests the shared string's length word inline (null header or zero length).
struct W3DDebrisDrawNameView
{
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
	};
	Header *m_data;
	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
};

class W3DDebrisDrawModuleBase
{
protected:
	virtual ~W3DDebrisDrawModuleBase();
	void *m_moduleData;								// +0x04
	Drawable *m_drawable;							// +0x08
public:
	Drawable *getDrawable() const { return m_drawable; }
};

class DebrisDrawInterface
{
public:
	virtual void setModelName(AsciiString name, Color color, ShadowType t) = 0;
};

class W3DDebrisDraw : public W3DDebrisDrawModuleBase, public DebrisDrawInterface
{
public:
	virtual void setModelName(AsciiString name, Color color, ShadowType t);
private:
	AsciiString m_modelName;						// +0x10
	Color m_modelColor;								// +0x14
	AsciiString m_animInitial;
	AsciiString m_animFlying;
	AsciiString m_animFinal;
	RenderObjClass *m_renderObject;					// +0x24
	RenderObjClass *m_anims[3];
	void *m_fxFinal;								// +0x34
	unsigned char m_pad38[0x44 - 0x38];
	Shadow *m_shadow;								// +0x44
};

void W3DDebrisDraw::setModelName(AsciiString name, Color color, ShadowType t)
{
	if (m_renderObject == 0 && !reinterpret_cast<const W3DDebrisDrawNameView &>(name).isEmpty())
	{
		Rva0013101E options;
		if (color != 0)
		{
			options.m_a = 1;
			options.m_b = 0;
			options.m_c = 0;
			options.m_d2 = 0;
			options.m_d3 = 0;
			options.m_d1 = color | 0xFF000000;
		}
		m_renderObject = Rva00137364CreateRenderObj(name.str(), getDrawable()->getScale(), options);
		if (m_renderObject)
		{
			W3DDisplay::m_3DScene->Add_Render_Object(m_renderObject);
			m_renderObject->Set_User_Data(getDrawable()->getDrawableInfo());
			W3DDebrisDrawTransform transform;
			transform.Set(W3DDebrisDrawPoint(0, 0, 0));
			m_renderObject->Set_Transform(transform);
		}

		if (t != SHADOW_NONE)
		{
			Shadow::ShadowTypeInfo shadowInfo;
			shadowInfo.m_type = t;
			shadowInfo.m_sizeX = 0;
			shadowInfo.m_sizeY = 0;
			shadowInfo.m_float1C = 0;
			m_shadow = TheW3DShadowManager->addShadow(m_renderObject, &shadowInfo, 0);
		}
		else
		{
			if (TheW3DShadowManager && m_shadow)
			{
				reinterpret_cast<Gen0003AC38 *>(TheW3DShadowManager)->handle(m_shadow);
				m_shadow = 0;
			}
		}

		m_modelName = name;
		m_modelColor = color;
	}
}
