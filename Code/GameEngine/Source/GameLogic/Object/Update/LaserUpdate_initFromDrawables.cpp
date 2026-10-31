// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Update
//
// LaserUpdate helper — retail 0x00604460 (80B).
// If both drawable args are live, store their IDs at +0x4C/+0x50 and forward
// arg1, parent position, target position, arg4 into LaserUpdate::initLaser,
// the 776-byte body at 0x00603FE0 (ILT 0x00024FC3).

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

class Object;

// Drawable::getID is ICF-folded onto the matched dword getter row at 0x0055A88B
// (DispDwordFieldGetters.cpp); called here by that row name.
class Rva0055A88BDwordField
{
public:
	int get() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Matrix3D;
class Rva00603BB0ObjectView;
class Drawable
{
public:
	bool rva00272835(int, int);
	__forceinline bool getCurrentWorldspaceClientBonePositions(const char *name, Matrix3D &matrix) const { return const_cast<Drawable *>(this)->rva00272835(reinterpret_cast<int>(name),reinterpret_cast<int>(&matrix)); }
	void setPosition(const Coord3D *);
	const Coord3D *getPosition() const;
	Rva00603BB0ObjectView *getObject() const { return m_object; }
	char m_unmodelled_000[0xfc]; // +0x00
	Rva00603BB0ObjectView *m_object; // +0xFC
};

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};
enum NameKeyType
{
	NK_UNKNOWN = 0
};

class LaserUpdateModuleData;

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

protected:
	const LaserUpdateModuleData *m_moduleData;
	Drawable *m_drawable;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LaserUpdate.h
class LaserUpdate : public Rva0049B47C
{
public:
	virtual ~LaserUpdate();
	Drawable *getDrawable() const { return m_drawable; }
	const LaserUpdateModuleData *getLaserUpdateModuleData() const { return m_moduleData; }
	float getCurrentLaserRadius() const;
	void initLaser(const Object *primary, const Coord3D *parentPos,
		const Coord3D *targetPos, int sizeDeltaFrames);
	void initFromDrawables(void *primary, Drawable *parent, Drawable *target, void *d);
	static NameKeyType rva000363102();

	Coord3D m_startPos;
	Coord3D m_endPos;
	bool m_dirty;
	char m_pad25[3];
	ParticleSystemID m_particleSystemID;
	ParticleSystemID m_targetParticleSystemID;
	bool m_widening;
	bool m_decaying;
	char m_pad32[2];
	unsigned m_widenStartFrame;
	unsigned m_widenFinishFrame;
	float m_currentWidthScalar;
	unsigned m_decayStartFrame;
	unsigned m_decayFinishFrame;
	unsigned m_rva00603BB0ExpiryFrame;
	unsigned m_parentID;
	unsigned m_targetID;
};

// ?initFromDrawables@LaserUpdate@@QAEXPAXPAVDrawable@@10@Z
void LaserUpdate::initFromDrawables(void *primary, Drawable *parent, Drawable *target, void *d)
{
	if (parent)
	{
		if (target)
		{
			m_parentID = ((const Rva0055A88BDwordField *)parent)->get();
			m_targetID = ((const Rva0055A88BDwordField *)target)->get();
			initLaser((const Object *)primary, parent->getPosition(),
				target->getPosition(), (int)d);
		}
	}
}
