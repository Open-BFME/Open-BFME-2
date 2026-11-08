// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
//
// ?rva000B3D39@W3DModelDraw@@UAEXXZ, retail 0x000B3D39 (329 bytes): slot 62
// (+0xF8) of the W3DModelDraw vftable 0x007CBC40 and of the six derived draw
// vftables (0x007C69E8, 0x007CA188, 0x007CC0B8, 0x007CC748, 0x007CCCE0,
// 0x007CDD58 hold it too).  WorldBuilder twin 0x00947F20 is unnamed
// (callgraph lead), so the method name stays address-derived.
// Unless the rowed 0x000B3A68 gate holds, with a drawable (+0x08) and a
// render object (+0x50): when the module data's +0x135 flag is set the level
// comes from the rowed 0x000B2BA3 query on the drawable and a change is
// stored in +0xC0 and pushed with Drawable::rva00274176(true).  Otherwise,
// when the render object's slot 81 reports 3 or the +0x134 flag is set, the
// camera distance (TheTacticalView slot 71 minus the drawable position,
// Coord3D::GetLengthEstimate 0x00003ACE) is banded by the +0x12C/+0x130
// thresholds into 0/1/2; state 3 hands the band to the render object's
// slot 79 and records it in +0xBC/+0xC0, otherwise a new band is stored in
// +0xC0 and pushed with rva00274176(false).

// Coord3D: shared header/view; no private copy.
#include "../../../../../../Libraries/Include/Lib/Coord3DInline.h"


#include "../../../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"

#include "../../../../../../GameEngine/Include/GameClient/View.h"
extern View *TheTacticalView;

#include "../../../../../../GameEngine/Include/GameClient/Drawable.h"

struct Rva000B2BE5Src;
int Rva000B2BA3Get(const Rva000B2BE5Src *src, bool *out);	// 0x000B2BA3

class Rva000B3A68
{
public:
	unsigned char rva000B3A68();
};

struct Rva000B3D39ModuleData
{
	char m_pad000[0x12C];
	float m_nearDistance;	// +0x12C
	float m_farDistance;	// +0x130
	bool m_useCameraDistance;	// +0x134
	bool m_useDrawableQuery;	// +0x135
};

class W3DModelDraw
{
public:
	virtual void rva000B3D39();

private:
	const Rva000B3D39ModuleData *getModuleData() const { return m_moduleData; }
	Drawable *getDrawable() const { return m_drawable; }

	const Rva000B3D39ModuleData *m_moduleData;	// +0x04
	Drawable *m_drawable;	// +0x08
	char m_pad0C[0x50 - 0x0C];
	RenderObjClass *m_renderObject;	// +0x50
	char m_pad54[0xBC - 0x54];
	int m_appliedLevel;	// +0xBC
	int m_level;	// +0xC0
};

void W3DModelDraw::rva000B3D39()
{
	if (((Rva000B3A68 *)this)->rva000B3A68())
		return;
	Drawable *draw = m_drawable;
	if (!draw || !m_renderObject)
		return;

	const Rva000B3D39ModuleData *d = getModuleData();
	int state = m_renderObject->Get_LOD_Count();
	if (d->m_useDrawableQuery)
	{
		int level = Rva000B2BA3Get((const Rva000B2BE5Src *)getDrawable(), 0);
		if (level != m_level)
		{
			m_level = level;
			draw->rva00274176(true);
		}
		return;
	}

	if (state != 3 && !d->m_useCameraDistance)
		return;

	int level = 0;
	Coord3D delta;
	delta.set(&TheTacticalView->get3DCameraPosition());
	delta.sub(draw->getPosition());
	float dist = delta.GetLengthEstimate();
	if (dist < d->m_nearDistance)
		level = 0;
	else if (dist > d->m_farDistance)
		level = 2;
	else
		level = 1;

	if (state == 3)
	{
		m_renderObject->Set_LOD_Level(level);
		m_appliedLevel = level;
		m_level = level;
	}
	else if (level != m_appliedLevel)
	{
		m_level = level;
		draw->rva00274176(false);
	}
}
