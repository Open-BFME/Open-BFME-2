// cl: /O1 /MD /DNDEBUG
//
// ?setHidden@W3DModelDraw@@UAEX_N@Z
// retail 0x000B6F6D, 145 bytes (Ghidra boundary), slot 16 of the
// W3DModelDraw-family vtable 0x00BCBFC0 (pinned).
//
// Donor: GeneralsMD W3DModelDraw.cpp setHidden. BFME 2 adds two guards in
// front (an unhide is ignored while the byte at +0x4D is set, and nothing
// happens while +0x28E is set unless the module data's +0x15E allows it),
// records the hidden flag at +0x4C, and stores !hidden as the shadow flag
// (+0x4A) where Zero Hour stored hidden. Render object +0x50 (Set_Hidden
// at vtable byte offset 0x194), shadow +0x58 and terrain decal +0x5C
// (enableShadowRender inline, flag +4), track render object +0x60.

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x, y, z;
};

class RenderObjClass
{
public:
	// Slots before Set_Hidden (byte offset 0x194); not needed here.
	virtual void vslot000(); virtual void vslot001(); virtual void vslot002(); virtual void vslot003();
	virtual void vslot004(); virtual void vslot005(); virtual void vslot006(); virtual void vslot007();
	virtual void vslot008(); virtual void vslot009(); virtual void vslot010(); virtual void vslot011();
	virtual void vslot012(); virtual void vslot013(); virtual void vslot014(); virtual void vslot015();
	virtual void vslot016(); virtual void vslot017(); virtual void vslot018(); virtual void vslot019();
	virtual void vslot020(); virtual void vslot021(); virtual void vslot022(); virtual void vslot023();
	virtual void vslot024(); virtual void vslot025(); virtual void vslot026(); virtual void vslot027();
	virtual void vslot028(); virtual void vslot029(); virtual void vslot030(); virtual void vslot031();
	virtual void vslot032(); virtual void vslot033(); virtual void vslot034(); virtual void vslot035();
	virtual void vslot036(); virtual void vslot037(); virtual void vslot038(); virtual void vslot039();
	virtual void vslot040(); virtual void vslot041(); virtual void vslot042(); virtual void vslot043();
	virtual void vslot044(); virtual void vslot045(); virtual void vslot046(); virtual void vslot047();
	virtual void vslot048(); virtual void vslot049(); virtual void vslot050(); virtual void vslot051();
	virtual void vslot052(); virtual void vslot053(); virtual void vslot054(); virtual void vslot055();
	virtual void vslot056(); virtual void vslot057(); virtual void vslot058(); virtual void vslot059();
	virtual void vslot060(); virtual void vslot061(); virtual void vslot062(); virtual void vslot063();
	virtual void vslot064(); virtual void vslot065(); virtual void vslot066(); virtual void vslot067();
	virtual void vslot068(); virtual void vslot069(); virtual void vslot070(); virtual void vslot071();
	virtual void vslot072(); virtual void vslot073(); virtual void vslot074(); virtual void vslot075();
	virtual void vslot076(); virtual void vslot077(); virtual void vslot078(); virtual void vslot079();
	virtual void vslot080(); virtual void vslot081(); virtual void vslot082(); virtual void vslot083();
	virtual void vslot084(); virtual void vslot085(); virtual void vslot086(); virtual void vslot087();
	virtual void vslot088(); virtual void vslot089(); virtual void vslot090(); virtual void vslot091();
	virtual void vslot092(); virtual void vslot093(); virtual void vslot094(); virtual void vslot095();
	virtual void vslot096(); virtual void vslot097(); virtual void vslot098(); virtual void vslot099();
	virtual void vslot100();
	virtual void Set_Hidden(int onoff);
};

class Shadow
{
public:
	void enableShadowRender(Bool isEnabled) { m_isEnabled = isEnabled; }
private:
	void *m_vtable;
	Bool m_isEnabled;
};

class TerrainTracksRenderObjClass
{
public:
	void addCapEdgeToTrack(Real x, Real y);
};

class Drawable
{
public:
	const Coord3D *getPosition() const;
};

struct W3DModelDrawModuleData
{
	unsigned char m_pad00[0x15E];
	Bool m_unknown15E;
};

class W3DModelDraw
{
public:
	virtual void setHidden(Bool hidden);

private:
	Drawable *getDrawable() const { return m_drawable; }
	void doStartOrStopParticleSys();

	const W3DModelDrawModuleData *m_moduleData;
	Drawable *m_drawable;
	unsigned char m_pad0C[0x4A - 0x0C];
	Bool m_shadowEnabled;
	unsigned char m_pad4B;
	Bool m_hidden;
	Bool m_unknown4D;
	unsigned char m_pad4E[0x50 - 0x4E];
	RenderObjClass *m_renderObject;
	unsigned char m_pad54[0x58 - 0x54];
	Shadow *m_shadow;
	Shadow *m_terrainDecal;
	TerrainTracksRenderObjClass *m_trackRenderObject;
	unsigned char m_pad64[0x28E - 0x64];
	Bool m_unknown28E;
};

void W3DModelDraw::setHidden(Bool hidden)
{
	if (!hidden && m_unknown4D)
		return;
	if (m_unknown28E && !m_moduleData->m_unknown15E)
		return;

	m_hidden = hidden;

	if (m_renderObject)
		m_renderObject->Set_Hidden(hidden);

	if (m_shadow)
		m_shadow->enableShadowRender(!hidden);

	m_shadowEnabled = !hidden;

	if (m_terrainDecal)
		m_terrainDecal->enableShadowRender(!hidden);

	if (m_trackRenderObject && hidden)
	{	const Coord3D* pos = getDrawable()->getPosition();
		m_trackRenderObject->addCapEdgeToTrack(pos->x,pos->y);
	}

	doStartOrStopParticleSys();
}
