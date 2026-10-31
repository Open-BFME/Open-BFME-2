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
class Rva00575674
{
public:
	void rva00575674(Object *obj);							// 0x00575674
};

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

class Rva00575CDFBase0
{
public:
	virtual void b0();
};

class Rva00575CDFIface
{
public:
	virtual void rva00575CDF(void *a, void *b);
	virtual void rva00575D12(void *a, void *b);
};

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

class Rva004A6AB5Iface
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12();
	virtual void s13(bool on);
	int m_3E8;
};

struct Rva004A6AB5Pos
{
	int x, y, z;
};

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

class UpdateModule
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13();
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);	// 0x0044DF71
	int m_04;
	Object *m_object;										// +0x08
};

class Rva00481A6E : public UpdateModule
{
public:
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

class LivingWorldRegionCampaign
{
public:
	void rva0020F3E8(LivingWorldRegionManager *mgr);		// 0x0020F3E8
};

class LivingWorldManager
{
public:
	void rva00210F96();										// 0x00210F96
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern LivingWorldManager *TheLivingWorldManager;

struct Rva003B8DD7Holder
{
	int m_00;
	int m_04;
	LivingWorldRegionCampaign *m_campaign;					// +0x08
};

struct Rva003B8DD7LogicView
{
	char m_pad[0xB0];
	Rva003B8DD7Holder *m_holder;							// +0xB0
};

class Rva003B8DD7Entry
{
public:
	virtual void s0();
	virtual void s1();
};

class Rva003B8DD7
{
public:
	virtual void rva003B8DD7();
private:
	int m_index;											// +0x04
	Rva003B8DD7Entry **m_entries;							// +0x08
};

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
class Rva00395F57
{
public:
	bool canUnpack(bool flag);								// 0x00395F57
};

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
struct Rva004A9617Level
{
	int m_00;
	unsigned int m_level;									// +0x04
};

struct Rva004A9617Holder
{
	int m_00;
	Rva004A9617Level *m_level;								// +0x04
	unsigned int level() const { return m_level ? m_level->m_level : 999999; }
};

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
struct Rva004B0303Data
{
	char m_pad[0xC8];
	bool m_C8;												// +0xC8
};

class Rva004B0303Base0
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17();
	Rva004B0303Data *m_data;								// +0x04
	char m_pad08[0x88 - 8];
};

class Rva004B0303Iface
{
public:
	virtual void rva004B0303();
};

class Rva004B0303 : public Rva004B0303Base0, public Rva004B0303Iface
{
public:
	virtual void rva004B0303();
};

void Rva004B0303::rva004B0303()
{
	if (m_data->m_C8)
		s17();
}

// --- 0x004B5B82 (42B): from a +0x1C interface, when the +0x04 data's +0x129
// flag is set run slots 10 and 9 (true) of the +0x10 base; then latch +0x20.
struct Rva004B5B82Data
{
	char m_pad[0x129];
	bool m_129;												// +0x129
};

class Rva004B5B82Base0
{
public:
	virtual void b0();
	Rva004B5B82Data *m_data;								// +0x04
	int m_08;
	int m_0C;
};

class Rva004B5B82Base10
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8();
	virtual void s9(bool on);
	virtual void s10();
	int m_14;
	int m_18;
};

class Rva004B5B82Iface
{
public:
	virtual void rva004B5B82();
};

class Rva004B5B82 : public Rva004B5B82Base0, public Rva004B5B82Base10, public Rva004B5B82Iface
{
public:
	virtual void rva004B5B82();
private:
	bool m_latched;											// +0x20
};

void Rva004B5B82::rva004B5B82()
{
	if (m_data->m_129)
	{
		s10();
		s9(true);
	}
	m_latched = true;
}

// --- 0x004E55B9 (64B): when the id names a live object and the flag is set,
// add its position (+0x38) with the float and its indicator colour through
// the rowed ResourceEntryCollector 0x004E5559.

class Object
{
public:
	int getIndicatorColor() const;							// 0x0028B026
	char m_pad000[0x38];
	char m_position[0x0C];									// +0x38
};

extern GameLogic *TheGameLogic;

class ResourceEntryCollector
{
public:
	void addEntry(const Coord3D *pos, float value, int color);	// 0x004E5559
	virtual void rva004E55B9(ObjectID id, float value, bool show);
};

void ResourceEntryCollector::rva004E55B9(ObjectID id, float value, bool show)
{
	Object *obj = TheGameLogic->findObjectByID(id);
	if (obj && show)
		addEntry((const Coord3D *)obj->m_position, value, obj->getIndicatorColor());
}

// --- 0x004E6882 (22B): 1 when +0x40 is set, or +0x44 is set while the +0x08
// state is not 4. Native vtable862440 slot4 identifies the named movie clip;
// the constructor and destructor install this same five-slot table.
class UnicodeString;
class Rva002217EA;
class InGameNotificationBoxMovieClip
{
public:
    virtual unsigned char rva00578522() const;
    virtual void rva004E6B7D(bool);
    virtual void rva004E725F(const UnicodeString &, const Rva002217EA &, int);
    virtual void DoClose();
    virtual int rva004E6882();
private:
	int m_04;
	int m_state;											// +0x08
	char m_pad0C[0x40 - 0x0C];
	int m_40;												// +0x40
	int m_44;												// +0x44
};

int InGameNotificationBoxMovieClip::rva004E6882()
{
	return m_40 != 0 || (m_44 != 0 && m_state != 4);
}
