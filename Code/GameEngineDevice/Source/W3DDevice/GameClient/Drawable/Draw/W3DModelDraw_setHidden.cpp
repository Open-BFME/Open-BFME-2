// cl: /MD /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
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

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"

class Shadow
{
public:
	void enableShadowRender(Bool isEnabled) { m_isEnabled = isEnabled; }
private:
	void *m_vtable;
	Bool m_isEnabled;
};

class Rva00084206Track
{
public:
	void addCapEdgeToTrack(Real x, Real y);
};

#include "../../../../../../GameEngine/Include/GameClient/Drawable.h"

struct W3DModelDrawModuleData
{
	unsigned char m_pad00[0x15E];
	Bool m_affectedByStealth;
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
	Rva00084206Track *m_trackRenderObject;
	unsigned char m_pad64[0x28E - 0x64];
	Bool m_unknown28E;
};

void W3DModelDraw::setHidden(Bool hidden)
{
	if (!hidden && m_unknown4D)
		return;
	if (m_unknown28E && !m_moduleData->m_affectedByStealth)
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
