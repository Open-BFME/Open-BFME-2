// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// WorkOrder::WorkOrder, retail 0x004F10E6 (48 bytes), after Zero Hour's
// inline constructor in GameEngine/Include/GameLogic/AIPlayer.h (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference). Called by
// TeamInQueue::xfer when it loads a work order list. The vftable is the one
// whose name getter returns "WorkOrder" (slot 3 is the rowed WorkOrder::xfer);
// the layout is WorkOrderXfer.cpp's.
// Zero Hour's initializers (no thing, no factory, no next, 0 completed, 1
// required, not a resource gatherer; m_required is left alone) are followed
// by BFME 2's fields (target evidence): +0x1C = 1, the AsciiString at +0x20
// empty, +0x2C = -1, and the two flags at +0x28/+0x29 cleared after it (in
// the constructor body, as retail stores them last). +0x24 is not set.
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
#define NULL 0

enum ObjectID
{
	INVALID_ID = 0
};

class Xfer;
class ThingTemplate;

class WorkOrder
{
public:
	WorkOrder();
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
public:
	const ThingTemplate *m_thing;						///< 0x04
	ObjectID m_factoryID;								///< 0x08
	WorkOrder *m_next;									///< 0x0C
	Int m_numCompleted;									///< 0x10
	Int m_numRequired;									///< 0x14
	Bool m_required;									///< 0x18
	Bool m_isResourceGatherer;							///< 0x19
	Int m_bfmeInt1C;									///< 0x1C
	AsciiString m_bfmeString20;							///< 0x20
	UnsignedInt m_bfmeUnsigned24;						///< 0x24
	Bool m_bfmeFlag28;									///< 0x28
	Bool m_bfmeFlag29;									///< 0x29
	Int m_bfmeInt2C;									///< 0x2C
};

WorkOrder::WorkOrder() :
	m_thing(NULL),
	m_factoryID(INVALID_ID),
	m_next(NULL),
	m_numCompleted(0),
	m_numRequired(1),
	m_isResourceGatherer(false),
	m_bfmeInt1C(1),
	m_bfmeInt2C(-1)
{
	m_bfmeFlag28 = false;
	m_bfmeFlag29 = false;
}
