// cl: /DNDEBUG /MD /GX
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// W3DTankDraw::xfer, ported from Zero Hour's GameEngineDevice/Source/W3DDevice/
// GameClient/Drawable/Draw/W3DTankDraw.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of ??_7W3DTankDraw
// 0x00BCCBE8: the version, then the base model draw's xfer. In BFME 2 that
// base is W3DScriptedModelDraw (slot 3 of its vftable 0x00BCA090,
// 0x000C5C04). As in ZH, there is no data of its own.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../../../../GameEngine/Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../../../reference/shims/wwmath/Vector2.h"
class ParticleSystem;
ParticleSystem *Make001FCBD7();
class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw();
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &that) throw();
	ParticleSystem *m_system; // +0x00
	void *m_previous; // +0x04
	void *m_next; // +0x08
};
class BfmeParticleSystemHandle : public RvaSmartPtr12
{
public:
	BfmeParticleSystemHandle()
	{
		m_system = 0;
		m_previous = 0;
		m_next = 0;
	}
	~BfmeParticleSystemHandle() throw()
	{
		if (m_system != 0)
			rva0004CBC0();
	}
	operator bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		if (!m_system)
			return Make001FCBD7();
		return m_system;
	}
	// A volatile read keeps retail's redundant null-or-Make chases.
	__forceinline ParticleSystem *const volatile &systemRef() const
	{
		return *(ParticleSystem *const volatile *)&m_system;
	}
	__forceinline ParticleSystem *getRaw() const
	{
		return *(ParticleSystem *const volatile *)&m_system;
	}
	ParticleSystem *get() const
	{
		ParticleSystem *p = getRaw();
		if (!p)
			p = Make001FCBD7();
		return p;
	}
};
class W3DTankDrawModuleData;
struct DrawableView;
class Xfer;
class Matrix3D;
class Thing;
class ModuleData;
class RenderObjClass;
class DrawModuleBase
{
public:
	virtual ~DrawModuleBase();
	const W3DTankDrawModuleData *m_moduleData; // +0x04
	DrawableView *m_drawable; // +0x08
};
class DrawInterfaceA
{
public:
	virtual void a();
};
class DrawInterfaceB
{
public:
	virtual void b();
};
class W3DModelDraw : public DrawModuleBase, public DrawInterfaceA, public DrawInterfaceB
{
public:
	virtual void setHidden(bool h);
	virtual void setFullyObscuredByShroud(bool v);
	virtual void doDrawModule(const Matrix3D *transformMtx);
protected:
	virtual void loadPostProcess(void);
	char m_pad14[0x49 - 0x14];
	bool m_fullyObscuredByShroud; // +0x49
	char m_pad4A[0x2E8 - 0x4A];
};
class W3DScriptedModelDraw : public W3DModelDraw
{
public:
	W3DScriptedModelDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DScriptedModelDraw();
protected:
	virtual void xfer(Xfer *xfer);
};
enum NameKeyType
{
	NK_UNKNOWN = 0
};

struct Material_Override
{
	int Struct_ID;
	Vector2 customUVOffset;
};

class W3DTankDraw : public W3DScriptedModelDraw
{
public:
	W3DTankDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DTankDraw();
	virtual void a();
	virtual void b();
	virtual void setHidden(bool h);
	virtual void setFullyObscuredByShroud(bool v);
	virtual void doDrawModule(const Matrix3D *transformMtx);
	virtual NameKeyType getModuleNameKey() const;
	void rva000CE09E();
	void rva000CE0EA();
protected:
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);
	BfmeParticleSystemHandle m_treadDebrisLeft;
	BfmeParticleSystemHandle m_treadDebrisRight;
	RenderObjClass *m_prevRenderObj;
	enum { MAX_TREADS_PER_TANK = 4 };
	struct TreadObjectInfo
	{
		TreadObjectInfo();
		RenderObjClass *m_robj;
		int m_type;
		Material_Override m_materialSettings;
	};
	TreadObjectInfo m_treads[MAX_TREADS_PER_TANK];
	int m_treadCount;
	Coord3D m_lastDirection;
	const W3DTankDrawModuleData *getW3DTankDrawModuleData() const { return m_moduleData; }
	void createEmitters(void);
	void tossEmitters(void);
	void updateTreadObjects(void);
	void updateTreadPositions(float uvDelta);
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void W3DTankDraw::xfer( Xfer *xfer )
{

	// version
	Xfer::Version version( 1, 1 );
	*xfer == version;

	// extend base class
	W3DScriptedModelDraw::xfer( xfer );

	// John A and Mark W say there is no data to save here

}  // end xfer
