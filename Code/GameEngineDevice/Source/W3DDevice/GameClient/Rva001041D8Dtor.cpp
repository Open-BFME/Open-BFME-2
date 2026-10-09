// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
// ??1Rva001041D8@@UAE@XZ retail 0x001041D8..0x001042C1 (233 bytes EH).
// Destructor of the 0x88-byte object whose constructor is the rowed
// ??0Rva0010461F@@QAE@XZ (0x0010461F; same vtables 0x00BCF770 / 0x00BCF760
// stored here and there) and whose scalar deleting destructor 0x00104723
// and -0xC thunk 0x001042C7 are rowed under Rva001041D8. Body: when both the
// scene (+0x14) and the model (+0x1C) exist and the model is in a scene
// (render object slot 123 = Is_In_Scene as in HLodClassDetachAdditional)
// the scene removes it (slot 3); then the model (+0x1C) the +0x18 object and
// the scene release their references (RefCountClass word at +4 and
// Delete_This in slot 0) and are cleared. Member destruction follows: the
// three Coord2D[4] arrays (eh vector destructor iterator with the exported
// Coord2D dtor) the texture slot (+0x24; TextureClass::Release_Ref
// 0x0061ED10) then the out-of-line base ~Rva002D3573 (0x002D3573).
// Evidence (target): vtable slot 1 0x00104BDA creates the model through the
// asset manager (0x00536175) sets its transform (slot 21) allocates a
// 0x108-byte scene (ctor 0x00542960 then vtable 0x00BCF6F0) and adds the
// model through scene slot 2. Identity lead (unproven): the Snapshot-side
// vtable slot 2 (GetSnapshotName) is 0x001042C1 returning "Palantir" and the
// base Rva002D3573 has a WorldBuilder lead Palantir::Palantir; this looks
// like the W3D Palantir (radar) implementation. No WorldBuilder twin exists.
// Names are address-derived.
#include "Common/Snapshot.h"

// class-gate: allow Coord2D the element dtor 0x000B3FD0 runs through the eh vector destructor iterator; BFME 2's Coord2D exports it (rowed ??1Coord2D@@QAE@XZ) and the canonical data-only header declares none
class Coord2D
{
public:
	Coord2D();
	~Coord2D();

	float x;
	float y;
};

class TextureClass
{
public:
	void Release_Ref();
};

struct Rva001041D8TextureSlot
{
	~Rva001041D8TextureSlot()
	{
		if (Ptr)
			Ptr->Release_Ref();
	}
	TextureClass *Ptr;
};

class Rva001041D8RefCounted
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}
private:
	int m_numRefs;
};

class Rva001041D8RenderObj : public Rva001041D8RefCounted
{
public:
#define RENDER_SLOT(n) virtual void slot##n();
	RENDER_SLOT(001) RENDER_SLOT(002) RENDER_SLOT(003) RENDER_SLOT(004)
	RENDER_SLOT(005) RENDER_SLOT(006) RENDER_SLOT(007) RENDER_SLOT(008)
	RENDER_SLOT(009) RENDER_SLOT(010) RENDER_SLOT(011) RENDER_SLOT(012)
	RENDER_SLOT(013) RENDER_SLOT(014) RENDER_SLOT(015) RENDER_SLOT(016)
	RENDER_SLOT(017) RENDER_SLOT(018) RENDER_SLOT(019) RENDER_SLOT(020)
	RENDER_SLOT(021) RENDER_SLOT(022) RENDER_SLOT(023) RENDER_SLOT(024)
	RENDER_SLOT(025) RENDER_SLOT(026) RENDER_SLOT(027) RENDER_SLOT(028)
	RENDER_SLOT(029) RENDER_SLOT(030) RENDER_SLOT(031) RENDER_SLOT(032)
	RENDER_SLOT(033) RENDER_SLOT(034) RENDER_SLOT(035) RENDER_SLOT(036)
	RENDER_SLOT(037) RENDER_SLOT(038) RENDER_SLOT(039) RENDER_SLOT(040)
	RENDER_SLOT(041) RENDER_SLOT(042) RENDER_SLOT(043) RENDER_SLOT(044)
	RENDER_SLOT(045) RENDER_SLOT(046) RENDER_SLOT(047) RENDER_SLOT(048)
	RENDER_SLOT(049) RENDER_SLOT(050) RENDER_SLOT(051) RENDER_SLOT(052)
	RENDER_SLOT(053) RENDER_SLOT(054) RENDER_SLOT(055) RENDER_SLOT(056)
	RENDER_SLOT(057) RENDER_SLOT(058) RENDER_SLOT(059) RENDER_SLOT(060)
	RENDER_SLOT(061) RENDER_SLOT(062) RENDER_SLOT(063) RENDER_SLOT(064)
	RENDER_SLOT(065) RENDER_SLOT(066) RENDER_SLOT(067) RENDER_SLOT(068)
	RENDER_SLOT(069) RENDER_SLOT(070) RENDER_SLOT(071) RENDER_SLOT(072)
	RENDER_SLOT(073) RENDER_SLOT(074) RENDER_SLOT(075) RENDER_SLOT(076)
	RENDER_SLOT(077) RENDER_SLOT(078) RENDER_SLOT(079) RENDER_SLOT(080)
	RENDER_SLOT(081) RENDER_SLOT(082) RENDER_SLOT(083) RENDER_SLOT(084)
	RENDER_SLOT(085) RENDER_SLOT(086) RENDER_SLOT(087) RENDER_SLOT(088)
	RENDER_SLOT(089) RENDER_SLOT(090) RENDER_SLOT(091) RENDER_SLOT(092)
	RENDER_SLOT(093) RENDER_SLOT(094) RENDER_SLOT(095) RENDER_SLOT(096)
	RENDER_SLOT(097) RENDER_SLOT(098) RENDER_SLOT(099) RENDER_SLOT(100)
	RENDER_SLOT(101) RENDER_SLOT(102) RENDER_SLOT(103) RENDER_SLOT(104)
	RENDER_SLOT(105) RENDER_SLOT(106) RENDER_SLOT(107) RENDER_SLOT(108)
	RENDER_SLOT(109) RENDER_SLOT(110) RENDER_SLOT(111) RENDER_SLOT(112)
	RENDER_SLOT(113) RENDER_SLOT(114) RENDER_SLOT(115) RENDER_SLOT(116)
	RENDER_SLOT(117) RENDER_SLOT(118) RENDER_SLOT(119) RENDER_SLOT(120)
	RENDER_SLOT(121) RENDER_SLOT(122)
#undef RENDER_SLOT
	virtual bool Is_In_Scene(); // slot 123 (+0x1EC)
};

class Rva001041D8Scene : public Rva001041D8RefCounted
{
public:
	virtual void slot001();
	virtual void Add_Render_Object(Rva001041D8RenderObj *obj); // slot 2
	virtual void Remove_Render_Object(Rva001041D8RenderObj *obj); // slot 3
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[8];
};

class Rva002D3573 : public GameEngineDeletingBase, public Snapshot
{
public:
	virtual ~Rva002D3573();

private:
	void *m_holder; // +0x10
};

class Rva001041D8 : public Rva002D3573
{
public:
	virtual ~Rva001041D8();

private:
	Rva001041D8Scene *m_scene; // +0x14
	Rva001041D8RefCounted *m_18;
	Rva001041D8RenderObj *m_model; // +0x1C
	const void *m_edgeImage; // +0x20
	Rva001041D8TextureSlot m_edgeTexture; // +0x24
	Coord2D m_28[4];
	Coord2D m_48[4];
	Coord2D m_68[4];
};

Rva001041D8::~Rva001041D8()
{
	if (m_scene != 0 && m_model != 0 && m_model->Is_In_Scene())
		m_scene->Remove_Render_Object(m_model);
	if (m_model != 0)
	{
		m_model->Release_Ref();
		m_model = 0;
	}
	if (m_18 != 0)
	{
		m_18->Release_Ref();
		m_18 = 0;
	}
	if (m_scene != 0)
	{
		m_scene->Release_Ref();
		m_scene = 0;
	}
}
