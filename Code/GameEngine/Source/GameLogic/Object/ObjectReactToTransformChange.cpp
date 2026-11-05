// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x00292D49, 362B: Object::reactToTransformChange (thiscall, ret 0xC).
// Body: Zero Hour's (GeneralsMD GameEngine/Source/GameLogic/Object/Object.cpp).
// Target evidence: the _isnan checks on the position (+0x38) feeding
// GameLogic::destroyObject, the drawable at +0x84 restamped with the logic
// frame and given the transform at +8 via Thing::setTransformMatrix, and the
// rowed isPosDifferent/isAngleDifferent (angle +0x44) from the same ZH file
// (ObjectTransformDiff.cpp). BFME 2 deltas: the change notification is an
// Object virtual (slot 6) plus the contain module at +0x250 (slot 3); objects
// with a fire-logic index (+0x49C >= 0) re-register with the fire logic
// system (0x00287C39/0x00287C21); a moved object fills an unset float at
// +0x1C4 with its height, calls 0x00291EB1 (ZH
// setTriggerAreaFlagsForChangeInPosition), sets or clears the off-map bit
// (0x08 at +0x438) against TheTerrainLogic->getExtent (slot 8), then calls
// 0x0028B98B.

#include <float.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"

typedef float Real;
typedef int Int;

class Matrix3D;

#include "../../../../Libraries/Include/Lib/Region3D.h"

// TU-local no-Z containment test (identical inlined bytes): the canonical
// Region3D::isInRegionNoZ's out-of-line copy could lose to a first-in-order copy.
static inline bool isInRegionNoZRV( const Region3D &region, const Coord3D *query )
{
	return query->x > region.lo.x && region.hi.x > query->x && query->y > region.lo.y && region.hi.y > query->y;
}

#include "../../../Include/GameLogic/TerrainLogic.h"

extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;

#include "../../Common/Thing/thing.h"
#include "../../../Include/GameClient/Drawable.h"

inline void Drawable::markTransformChanged( unsigned int frame )
{
	m_3A4 = frame;
	m_3A8 = false;
	m_3A9 = false;
}


#include "../../../Include/GameLogic/Module/ContainModule.h"

struct Rva00287C21Other;

#include "../../../Include/GameLogic/FireLogicSystem.h"

class Rva002872BA;
extern Rva002872BA *TheTriggerManager;

bool isPosDifferent( const Coord3D *a, const Coord3D *b );
bool isAngleDifferent( Real a, Real b );

class Object
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void onTransformChanged();

	void reactToTransformChange( const Matrix3D *oldMtx, const Coord3D *oldPos, Real oldAngle );
	void setTriggerAreaFlagsForChangeInPosition();
	void rva0028B98B();

	const Coord3D *getPosition() const { return &m_pos; }
	Real getOrientation() const { return m_angle; }
	const Matrix3D *getTransformMatrix() const { return (const Matrix3D *)m_transform; }
	ContainModuleInterface *getContain() const { return m_contain; }

	unsigned char m_pad04[0x08 - 0x04];
	unsigned char m_transform[0x30];
	Coord3D m_pos;
	Real m_angle;
	unsigned char m_pad48[0x84 - 0x48];
	Drawable *m_drawable;
	unsigned char m_pad88[0x1C4 - 0x88];
	Real m_baseHeight;
	unsigned char m_pad1C8[0x250 - 0x1C8];
	ContainModuleInterface *m_contain;
	unsigned char m_pad254[0x438 - 0x254];
	unsigned char m_privateStatus;
	unsigned char m_pad439[0x49C - 0x439];
	Int m_fireLogicIndex;
};

enum
{
	OFF_MAP = 0x08
};

void Object::reactToTransformChange( const Matrix3D * /*oldMtx*/, const Coord3D *oldPos, Real oldAngle )
{
	if( _isnan( getPosition()->x ) || _isnan( getPosition()->y ) || _isnan( getPosition()->z ) )
	{
		TheGameLogic->destroyObject( this );
	}
	if( m_drawable )
	{
		m_drawable->markTransformChanged( TheGameLogic->getFrame() );
		m_drawable->setTransformMatrix( getTransformMatrix() );
	}

	bool posDiff = isPosDifferent( oldPos, getPosition() );
	bool angDiff = isAngleDifferent( oldAngle, getOrientation() );

	if( posDiff || angDiff )
	{
		onTransformChanged();

		if( getContain() )
			getContain()->containReactToTransformChange();

		if( m_fireLogicIndex >= 0 )
		{
			((FireLogicSystem *)TheTriggerManager)->UnregisterObject( (Rva00287C21Other *)this );
			((FireLogicSystem *)TheTriggerManager)->RegisterObject( (Rva00287C21Other *)this );
		}

		if( posDiff )
		{
			if( m_baseHeight == 0.0f )
				m_baseHeight = getPosition()->z;

			setTriggerAreaFlagsForChangeInPosition();

			Region3D mapExtent;
			TheTerrainLogic->getExtent( &mapExtent );
			if( isInRegionNoZRV( mapExtent, getPosition() ) )
				m_privateStatus &= ~OFF_MAP;
			else
				m_privateStatus |= OFF_MAP;

			rva0028B98B();
		}
	}
}
