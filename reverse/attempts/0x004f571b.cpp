// ?rva004F571B@TunnelTracker@@QAE_NPAVObject@@@Z
// partial score=0.85 date=2026-10-08
// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// TunnelTracker contain-list bodies, ported from Zero Hour's
// GameEngine/Source/Common/RTS/TunnelTracker.cpp (GeneralsMD tree vendored
// under reference/open-bfme-1/inputs/reference).
//  - getContainMax, retail 0x004F5385 (12 bytes): TheGlobalData's
//    m_maxTunnelCapacity (+0xA98 in BFME 2). TunnelContain reaches it through
//    tail jumps at 0x0046652F and 0x0047DE0D.
//  - addToContainList, retail 0x004F56E5 (23 bytes): TunnelContain reaches it
//    through tail jumps at 0x00466481 and 0x0047DC83. The append is the
//    out-of-line four-byte list push_back 0x0005548F.
//  - healObject, retail 0x004F53C3 (115 bytes): the callback whose address
//    healObjects (the rowed 0x004F558C) hands to iterateContained. The
//    DamageInfo is the 0x7C BFME 2 layout with its pinned constructor
//    0x00263895 (damage type 7 HEALING at +0x10, death type 1 NONE at +0x1C,
//    amount at +0x20); body module Object +0x254 (getMaxHealth slot 6,
//    attemptHealing slot 1); contained-by frame Object +0x27C.
// BFME 2 layout (target evidence, matching TunnelTracker::xfer): tunnel ids
// +0x08, contain list +0x10, contain list size +0x18, tunnel count +0x1C.
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Object;

enum ObjectID
{
	INVALID_ID = 0
};

class DamageInfoInput
{
public:
	char m_pad00[0x10];
	Int m_damageType; // +0x10
	char m_pad14[0x1C - 0x14];
	Int m_deathType; // +0x1C
	Real m_amount; // +0x20
};

class DamageInfo
{
public:
	DamageInfo();
	DamageInfoInput in;
	char m_pad24[0x7C - 0x24];
};

enum
{
	DAMAGE_HEALING = 7,
	DEATH_NONE = 1
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void attemptHealing(DamageInfo *damageInfo);
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getMaxHealth() const;
};

class Object
{
public:
	BodyModuleInterface *getBodyModule() const { return m_body; }
	void onContainedBy(Object *container);
	// Contained-by frame, read directly (an inline getContainedByFrame here
	// would be a second COMDAT copy beside GarrisonContain's Zero Hour
	// header view, which reads ZH's +0x1B8).
	char m_pad00[0x74];
	ObjectID m_id; // +0x74
	char m_pad78[0x254 - 0x78];
	BodyModuleInterface *m_body; // +0x254
	char m_pad258[0x274 - 0x258];
	Object *m_containedBy; // +0x274
	char m_pad278[0x27C - 0x278];
	UnsignedInt m_containedByFrame; // +0x27C
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	UnsignedInt getFrame() const { return m_frame; }
private:
	char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

class GlobalData
{
public:
	char m_pad00[0xA98];
	Int m_maxTunnelCapacity; // +0xA98
};
extern GlobalData *TheWritableGlobalData; // 0x00DFE758
#define TheGlobalData TheWritableGlobalData

// The contain list's append is the STLport four-byte list push_back body
// 0x0005548F (ICF-shared with list<int>), not the separate list<Object*>
// instance 0x001EC03C, so the list is modelled as its own class here.
class TunnelContainedItemsList
{
public:
	void push_back(Object *const &obj);
private:
	void *m_node;
};
typedef TunnelContainedItemsList ContainedItemsList;

// Native 0x00466398 descriptor: two pointers returned by hidden result word.
class Rva0036AE51ListView
{
public:
 void *a;
 _STL::list<Object *> *b;
};
class Rva00466398
{
public:
 Rva0036AE51ListView rva00466398();
};

class TunnelTracker
{
public:
	Int getContainMax() const;
	void addToContainList( Object *obj );
	bool rva004F571B(Object *deadTunnel);
	static void healObject( Object *obj, void *frames );
private:
	char m_pad00[0x08];
	_STL::list<int> m_tunnelIDs; // +0x08
	char m_pad0C[0x10 - 0x0C];
	ContainedItemsList m_containList; // +0x10
	char m_pad14[0x18 - 0x14];
	Int m_containListSize; // +0x18
	UnsignedInt m_tunnelCount; // +0x1C
};

// ------------------------------------------------------------------------
Int TunnelTracker::getContainMax() const
{
	return TheGlobalData->m_maxTunnelCapacity;
}

// ------------------------------------------------------------------------
void TunnelTracker::addToContainList( Object *obj )
{
	m_containList.push_back(obj);
	++m_containListSize;
}

// ------------------------------------------------------------------------
	// heal one object within the tunnel network system
void TunnelTracker::healObject( Object *obj, void *frames)
{

	//get the number of frames to heal
	Real *framesForFullHeal = (Real*)frames;

	// setup the healing damageInfo structure with all but the amount
	DamageInfo healInfo;
	healInfo.in.m_damageType = DAMAGE_HEALING;
	healInfo.in.m_deathType = DEATH_NONE;

	// get body module of the thing to heal
	BodyModuleInterface *body = obj->getBodyModule();

	// if we've been in here long enough ... set our health to max
	if( TheGameLogic->getFrame() - obj->m_containedByFrame >= *framesForFullHeal )
	{

		// set the amount to max just to be sure we're at the top
		healInfo.in.m_amount = body->getMaxHealth();

		// set max health
		body->attemptHealing( &healInfo );

	}  // end if
	else
	{
		healInfo.in.m_amount = body->getMaxHealth() / *framesForFullHeal;

		// do the healing
		body->attemptHealing( &healInfo );

	}  // end else
}


// 0x004F571B, 129B RET4. Adapt the banked ZH onTunnelDestroyed port:
// BFME2 leaves the last-tunnel cave-in to the caller and returns whether
// the count is zero. Native callback arguments and Object +274 establish
// the contained-object walk. Prior bank: 0x004f571b.cpp, 2026-10-04.
bool TunnelTracker::rva004F571B(Object *deadTunnel)
{
 --m_tunnelCount;
 int id = deadTunnel->m_id;
 m_tunnelIDs.remove(id);
 if (m_tunnelCount > 0)
 {
  Object *validTunnel = TheGameLogic->findObjectByID(static_cast<ObjectID>(m_tunnelIDs.front()));
  _STL::list<Object *> *list = reinterpret_cast<Rva00466398 *>(this)->rva00466398().b;
  for (_STL::list<Object *>::iterator it = list->begin(); it != list->end(); )
  {
   Object *object = *it;
   ++it;
   if (object->m_containedBy == deadTunnel)
    object->onContainedBy(validTunnel);
  }
 }
 return m_tunnelCount == 0;
}
