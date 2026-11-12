// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small table-reached bodies from .text gaps no ledger row covers (seat-3
// batch C; see GapBodiesS3A.cpp). Each body is reached only through a retail
// table in .rdata; retail bytes establish every shape. Owning classes are not
// recovered unless a callee names them, so each keeps an address-derived name
// and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.

#include "GameLogicObjectLookupView.h"

class Object;
class ThingTemplate;
struct Coord3D;

// --- 0x00575CDF / 0x00575D12 (51B each): from a +0x04 interface, build a
// fresh 0x14-byte rowed 0x0057551C / 0x00575540 record over the whole object
// and both arguments and hand it to the +0x2C holder's rowed 0x00575674.
#include "../../Include/Common/Rva00575674.h"

class Rva0057551C
{
public:
	Rva0057551C(void *owner, void *a, void *b) throw();	// 0x0057551C
private:
	char m_pad[0x14];
};

class Rva00575540
{
public:
	Rva00575540(void *owner, void *a, void *b) throw();	// 0x00575540
private:
	char m_pad[0x14];
};

#include "../../Include/Common/Rva00575CDFBase0.h"

#include "../../Include/Common/Rva00575CDFIface.h"

class Rva00575CDF : public Rva00575CDFBase0, public Rva00575CDFIface
{
public:
	virtual void rva00575CDF(void *a, void *b);
	virtual void rva00575D12(void *a, void *b);
private:
	char m_pad08[0x2C - 8];
	Rva00575674 m_holder;									// +0x2C
};

void Rva00575CDF::rva00575CDF(void *a, void *b)
{
	m_holder.rva00575674((Object *)new Rva0057551C(this, a, b));
}

void Rva00575CDF::rva00575D12(void *a, void *b)
{
	m_holder.rva00575674((Object *)new Rva00575540(this, a, b));
}

// --- 0x004A6AB5 / 0x004A6ADB / 0x004A6B06: an AIUpdateInterface subclass's
// privateIdle / privateDock / privateHarvest overrides. Each runs the rowed
// base command; a player-sourced command also sets the +0x3E4 interface's
// slot 13, remembers the dock's id (+0x3EC) or the harvest point (+0x3F0,
// flagged at +0x3FC).
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

class AIUpdateInterface
{
protected:
	virtual void privateIdle(CommandSourceType cmdSource);						// 0x0026D5FB
	virtual void privateDock(Object *obj, CommandSourceType cmdSource);			// 0x0026481B
	virtual void privateHarvest(const Coord3D *pos, CommandSourceType cmdSource);	// 0x00264853
	char m_pad004[0x3E4 - 4];
};

#include "../../Include/Common/Rva004A6AB5Iface.h"

#include "../../Include/Common/Rva004A6AB5Pos.h"

struct Rva004A6AB5ObjectView
{
	char m_pad[0x74];
	int m_id;												// +0x74
};

class Rva004A6AB5 : public AIUpdateInterface, public Rva004A6AB5Iface
{
protected:
	virtual void privateIdle(CommandSourceType cmdSource);
	virtual void privateDock(Object *obj, CommandSourceType cmdSource);
	virtual void privateHarvest(const Coord3D *pos, CommandSourceType cmdSource);
private:
	int m_dockID;											// +0x3EC
	Rva004A6AB5Pos m_harvestPos;							// +0x3F0
	bool m_hasHarvestPos;									// +0x3FC
};

void Rva004A6AB5::privateIdle(CommandSourceType cmdSource)
{
	if (cmdSource == CMD_FROM_PLAYER)
		s13(true);
	AIUpdateInterface::privateIdle(cmdSource);
}

void Rva004A6AB5::privateDock(Object *obj, CommandSourceType cmdSource)
{
	AIUpdateInterface::privateDock(obj, cmdSource);
	if (cmdSource == CMD_FROM_PLAYER && obj)
		m_dockID = ((Rva004A6AB5ObjectView *)obj)->m_id;
}

void Rva004A6AB5::privateHarvest(const Coord3D *pos, CommandSourceType cmdSource)
{
	AIUpdateInterface::privateHarvest(pos, cmdSource);
	if (cmdSource == CMD_FROM_PLAYER && pos)
	{
		m_harvestPos = *(const Rva004A6AB5Pos *)pos;
		m_hasHarvestPos = true;
	}
}

// --- 0x00481A6E (48B): an UpdateModule slot: for the local player's
// (ThePlayerList +0x18) notice run own slot 13 and sleep forever, else wake
// next frame.
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };

class PlayerList;
extern PlayerList *ThePlayerList;

struct Rva00481A6EPlayerListView
{
	char m_pad[0x18];
	void *m_local;											// +0x18
};

#include "../../Include/GameLogic/Module/UpdateModule.h"

class Rva00481A6E : public UpdateModule
{
public:
	virtual void s13();
	virtual void rva00481A6E(int unused, void *player);
};

void Rva00481A6E::rva00481A6E(int, void *player)
{
	if (player == ((Rva00481A6EPlayerListView *)ThePlayerList)->m_local)
	{
		s13();
		setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
	}
	else
		setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}

// --- 0x003B8DD7 (60B): when TheLivingWorldLogic's +0xB0 holder has a
// campaign (+0x08), run TheLivingWorldManager's rowed 0x00210F96 and the
// campaign's rowed 0x0020F3E8 over the holder, then slot 1 of the current
// (+0x04) entry of the +0x08 table.
class LivingWorldRegionManager;

#include "../../Include/GameLogic/LivingWorldRegionCampaign.h"

#include "../../Include/GameLogic/LivingWorldManager.h"

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern LivingWorldManager *TheLivingWorldManager;

#include "../../Include/Common/Rva003B8DD7Holder.h"

struct Rva003B8DD7LogicView
{
	char m_pad[0xB0];
	Rva003B8DD7Holder *m_holder;							// +0xB0
};

#include "../../Include/Common/Rva003B8DD7Entry.h"

#include "../../Include/Common/Rva003B8DD7.h"

void Rva003B8DD7::rva003B8DD7()
{
	Rva003B8DD7Holder *holder = ((Rva003B8DD7LogicView *)TheLivingWorldLogic)->m_holder;
	if (holder->m_campaign)
	{
		TheLivingWorldManager->rva00210F96();
		holder->m_campaign->rva0020F3E8((LivingWorldRegionManager *)holder);
		m_entries[m_index]->s1();
	}
}

// --- 0x0039A245 (43B): from a +0x30 interface, when the +0x04 data's +0x3E
// flag is set and the rowed 0x00395F57 check allows it, start the rowed
// CastleBehavior::initiateUnpack with no template.
#include "../../Include/GameLogic/Rva00395F57.h"

class CastleBehavior
{
public:
	void initiateUnpack(bool flag, const ThingTemplate *tmpl);	// 0x00399C6C
};

struct Rva0039A245Data
{
	char m_pad[0x3E];
	bool m_summoned;												// +0x3E
};

class Rva0039A245Base0
{
public:
	virtual void b0();
	Rva0039A245Data *m_data;								// +0x04
	char m_pad08[0x30 - 8];
};

class Rva0039A245Iface
{
public:
	virtual void rva0039A245();
};

class Rva0039A245 : public Rva0039A245Base0, public Rva0039A245Iface
{
public:
	virtual void rva0039A245();
};

void Rva0039A245::rva0039A245()
{
	if (m_data && m_data->m_summoned)
	{
		if (((Rva00395F57 *)this)->canUnpack(true))
			((CastleBehavior *)this)->initiateUnpack(false, 0);
	}
}

// --- 0x004A9617 / 0x004A6A81 (53B / 52B): whether the level read through
// +0xE0 / +0x04 (999999 when absent) is 2 or 4, or 2, 4 or 5.
#include "../../Include/Common/Rva004A9617Level.h"

#include "../../Include/Common/Rva004A9617Holder.h"

class Rva004A9617
{
public:
	virtual bool rva004A9617();
private:
	char m_pad04[0xE0 - 4];
	Rva004A9617Holder *m_holder;							// +0xE0
};

bool Rva004A9617::rva004A9617()
{
	if (m_holder)
	{
		switch (m_holder->level())
		{
		case 0:
		case 1:
			return false;
		case 2:
			return true;
		case 3:
			return false;
		case 4:
			return true;
		}
	}
	return false;
}

class Rva004A6A81
{
public:
	virtual bool isCurrentlyFerryingSupplies();
private:
	Rva004A9617Holder *m_holder;							// +0x04
};

bool Rva004A6A81::isCurrentlyFerryingSupplies()
{
	if (m_holder)
	{
		switch (m_holder->level())
		{
		case 0:
		case 1:
			return false;
		case 2:
			return true;
		case 3:
			return false;
		case 4:
		case 5:
			return true;
		}
	}
	return false;
}

// --- 0x004B0303 (27B): from a +0x88 interface, the object's slot 17 when
// its +0x04 data's +0xC8 flag is set.
#include "../../Include/Common/Rva004B0303Data.h"

#include "../../Include/Common/Rva004B0303Base0.h"

// --- 0x004B5B82 (42B): from a +0x1C interface, when the +0x04 data's +0x129
// flag is set run slots 10 and 9 (true) of the +0x10 base; then latch +0x20.
#include "../../Include/Common/Rva004B5B82Data.h"

#include "../../Include/Common/Rva004B5B82Base0.h"

#include "../../Include/Common/Rva004B5B82Base10.h"

#include "../../Include/Common/Rva004B5B82Iface.h"

class Rva004B5B82 : public Rva004B5B82Base0, public Rva004B5B82Base10, public Rva004B5B82Iface
{
public:
	virtual void rva004B5B82();
private:
	bool m_latched;											// +0x20
};

// --- 0x004E55B9 (64B): when the id names a live object and the flag is set,
// add its position (+0x38) with the float and its indicator colour through
// the rowed ResourceEntryCollector 0x004E5559.

#include "../GameLogic/Object/object.h"



#include "../../Include/GameClient/ResourceEntryCollector.h"

// --- 0x004E6882 (22B): 1 when +0x40 is set, or +0x44 is set while the +0x08
// state is not 4. Native vtable862440 slot4 identifies the named movie clip;
// the constructor and destructor install this same five-slot table.
class UnicodeString;
class Rva002217EA;
#include "../../Include/GameClient/InGameNotificationBoxMovieClip.h"

int InGameNotificationBoxMovieClip::rva004E6882()
{
	return m_field40 != 0 || (m_field44 != 0 && m_field08 != 4);
}
