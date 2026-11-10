// Rva001041BDASlot1.cpp -- Palantir/Rva0010461F vtable slot 1, retail 0x00104BDA (409B).
// Landed 409/409 from the exact bank: the identity transform is passed as an
// argument temporary (Matrix3D 12-float ctor) and the receiver is re-read through
// self->m_model, so cl builds the argument slot first (retail's early lea),
// keeps the 12 matrix stores before the vtable load, and re-reads the receiver
// after them. The dtor of the same class lives in
// Rva001041D8Dtor.cpp; this TU owns only slot 1.
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00104BDA@Rva0010461F@@UAEXXZ @0x00104BDA 409B
// vtable slot 1 of the 0x88-byte Rva0010461F object whose dtor is
// 0x001041D8 and whose ctor 0x0010461F is rowed (Rva001041D8Dtor.cpp).
// Body: when the owned asset-registry pointer 0x00E099F8 is non-null, build a
// pointer set containing the "palantir" receiver and hand it to the rowed
// bfmeMarkReceiverPayloads; then create the "palantir" render object
// (Create_Render_Obj), give it the identity transform (RenderObjClass slot
// 21), allocate the 0x108-byte scene 0x001040D5 (base SimpleSceneClass 0x00142960, vtable
// 0x00BCF6F0), set its ambient light (SceneClass slot 6, rowed 0x0006E265) and
// add the model (SimpleSceneClass slot 2, rowed 0x001413A0), allocate the
// 0x3FC-byte CameraClass (rowed ctor 0x00134AB0) and set its clip/view planes
// and aspect ratio, then call the rowed forwarder 0x002D55CA.
// Set ctor 0x000D3A71 / insert view 0x0006C995 / tree dtor 0x0006BF2A are the
// pinned pointer-set family. The Palantir identity is the dtor file's
// donor/structural lead; names stay address-derived.
#include <set>
// Suppress this TU's non-retail copy of ??1?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@_STL@@U?$less:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL {
template <> _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::~_Rb_tree();
template <> set<Rva001408C0Target *, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::set();
}

class Rva009EB960;
// Owned by W3DDisplayDtor.cpp: the asset registry the W3DDisplay dtor deletes.
extern Rva009EB960 *Rva0134FAA0;

struct Rva001408C0Target
{
	int opaque;
};

typedef _STL::set<Rva001408C0Target *, _STL::less<Rva001408C0Target *>, _STL::allocator<Rva001408C0Target *> > PtrSet001408C0;

struct AssetList00208F90
{
	PtrSet001408C0 m_set;
	int m_zero0C;
	bool m_flag;
	AssetList00208F90() : m_zero0C(0), m_flag(true) {}
};

class Rva0006C995 : public AssetList00208F90
{
public:
	Rva0006C995 *rva0006C995(Rva001408C0Target *p);
};

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"
#include "../../../../Libraries/Source/WWVegas/WW3D2/SimpleSceneClass.h"

void bfmeMarkReceiverPayloads(int value);

struct Matrix3D
{
	float m[3][4];
	Matrix3D(float a,float b,float c,float d,float e,float f,float g,float h,float i,float j,float k,float l)
	{ m[0][0]=a;m[0][1]=b;m[0][2]=c;m[0][3]=d;m[1][0]=e;m[1][1]=f;m[1][2]=g;m[1][3]=h;m[2][0]=i;m[2][1]=j;m[2][2]=k;m[2][3]=l; }
};

class RenderObjClass
{
public:
	virtual void slot00();
	virtual void slot01();
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
	virtual void Set_Transform(const Matrix3D &m); // slot 21 (+0x54)
};

RenderObjClass *Create_Render_Obj(const char *name);

class Rva001040D5 : public SimpleSceneClass
{
public:
	__declspec(dllimport) __forceinline Rva001040D5() {}
	virtual ~Rva001040D5();
};

class CameraClass
{
public:
	CameraClass();
	void Set_Clip_Planes(float nearz, float farz);
	void Set_View_Plane(float horizontal, float vertical);
	void Set_Aspect_Ratio(float ratio);
private:
	char m_pad[0x3FC];
};

class Rva002D55CAForwarder
{
public:
	void rva002D55CA();
};

class Rva0010461F
{
public:
	virtual void rva00104BDA();

private:
	char m_pad00[0x10];
	Rva001040D5 *m_scene;
	CameraClass *m_camera;
	RenderObjClass *m_model;
};

void Rva0010461F::rva00104BDA()
{
	Rva0010461F *self = this;
	const char *name = "palantir";
	if (Rva0134FAA0 != 0)
	{
		Rva0006C995 receivers;
		receivers.rva0006C995((Rva001408C0Target *)(const void *)name);
		bfmeMarkReceiverPayloads((int)&receivers);
	}

	RenderObjClass *model = Create_Render_Obj(name);
	self->m_model = model;
	if (model != 0 && (RenderObjClass *)self->m_model == model)
	{
		((RenderObjClass *)self->m_model)->Set_Transform(Matrix3D(1.0f,0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f,0.0f, 0.0f,0.0f,1.0f,0.0f));
	}

	self->m_scene = new Rva001040D5;
	Vector3 ambient(0.0f, 0.0f, 0.0f);
	self->m_scene->Set_Ambient_Light(ambient);
	if (self->m_model != 0)
		self->m_scene->Add_Render_Object(self->m_model);

	self->m_camera = new CameraClass;
	self->m_camera->Set_Clip_Planes(0.1f, 5000.0f);
	self->m_camera->Set_View_Plane(0.87266463f, -1.0f);
	self->m_camera->Set_Aspect_Ratio(1.0f);

	((Rva002D55CAForwarder *)self)->rva002D55CA();
}
