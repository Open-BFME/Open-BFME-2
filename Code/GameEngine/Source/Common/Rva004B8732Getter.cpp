// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?rva004B8851@SpawnUnitBehavior@@UBE?AVAsciiString@@XZ @0x004B8851 30B.
// Target evidence: the only reference to this body is slot 0 of the one-slot
// vtable 0x00C59120 that SpawnUnitBehavior's ctor 0x004B87E3 and its dtor
// 0x004B8732 (still the placeholder Rva004B8732) install at +0x20, the +0x20
// interface base of the class; the slot's name is not established, hence the
// address name. It is defined below, on the class view update() uses. cl 7.1 compiles an override of a non-primary base's
// virtual with the base subobject's this and folds the adjustment into the
// member accesses, which is why retail reads the module data pointer (+4) as
// [ecx-0x1C]. Returns by value (hidden pointer, StringBase<char> copy ctor 0x000365F0 through the shared AsciiString shim) the AsciiString at +8 of the module data.
#include "ascii_string.h"
class Thing;
class ModuleData;
class Object;

// Retail 0x004B886F, 341 bytes: SpawnUnitBehavior::update, the once-a-second
// tick of the same module (slot 0 of its UpdateModuleInterface table
// 0x00C59124 at +0x10, so `this` is the +0x10 subobject and the module data
// and object read at -0xC and -8). It answers the logic frame rate
// either way. WorldBuilder 0x01242D70 gives the shape: a controlling player
// who may build, with the object neither of two kinds (bits 3 and 5 of the
// first flag word), answers the production queue (a second queued entry of
// this module's type is cancelled through slot +0x28) or, with no queue,
// asks the player's build gate (0x002A7557) for the module's thing and
// orders its command button (source 2), clearing the pending flag at +0x14.
class CommandButton;
class ThingTemplate;
class Player;
class GameLogic;
struct Rva002A7557In;
extern int BfmeLogicFramesPerSecond;
extern GameLogic *TheGameLogic;

class Rva002A7461
{
public:
	bool rva002A7557(Rva002A7557In *p, int unused);

private:
	int m_pad0;
	int m_base4;
	int m_base8;
};

struct XProductionInfo
{
	unsigned char m_pad00[0x64];
	AsciiString m_64;
};

struct XProductionEntry
{
	unsigned char m_pad00[8];
	XProductionInfo *m_08;
	int m_pad0C;
	int m_productionID;
};

class XProductionQueue
{
public:
#define XS(n) virtual void xs##n();
	XS(0) XS(1) XS(2) XS(3) XS(4) XS(5) XS(6) XS(7) XS(8) XS(9)
	virtual void cancel(int id);
	XS(11) XS(12) XS(13) XS(14) XS(15) XS(16)
	virtual unsigned int count();
	XS(18) XS(19) XS(20)
	virtual XProductionEntry *front();
#undef XS
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void doCommandButton(const CommandButton *button, int source, bool flags);
	void *rva0028BC58(int which);
	unsigned char m_pad000[0x114];
	unsigned int m_flags114;
};

struct XPlayerView
{
	unsigned char m_pad00[0x60];
	Rva002A7461 m_60;
	unsigned char m_pad6C[0x735 - 0x6C];
	unsigned char m_735;
};

struct XModuleData
{
	unsigned char m_pad00[8];
	AsciiString m_08;
	AsciiString m_commandButtonName;
	unsigned char m_pad10[0x1C - 0x10];
	bool m_1C;
};

struct XLogicFrameView
{
	unsigned char m_pad00[0x40];
	unsigned int m_frame;
};

#include "../../Include/GameClient/ControlBar.h"
#include "../../Include/Common/ThingFactory.h"
extern ControlBar *TheControlBar;
extern ThingFactory *TheThingFactory;

struct XB00 { virtual void f00(); const XModuleData *m_data; Object *m_object; };
struct XB0C { virtual void f0C(); };
// UpdateModuleInterface::update's return type (UpdateModule.h): an int-sized
// enum, returned in eax like an int.
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
struct XB10 { virtual UpdateSleepTime update() = 0; unsigned char m_pad[12]; };
class XIface20 { public: virtual AsciiString rva004B8851() const = 0; };
class SpawnUnitBehavior : public XB00, public XB0C, public XB10, public XIface20
{
public:
	virtual UpdateSleepTime update();
	virtual AsciiString rva004B8851() const;

private:
	bool m_flag;
};

AsciiString SpawnUnitBehavior::rva004B8851() const
{
	return m_data->m_08;
}

UpdateSleepTime SpawnUnitBehavior::update()
{
	Object *object = m_object;
	const XModuleData *data = m_data;
	XPlayerView *player = (XPlayerView *)object->getControllingPlayer();
	int frames = BfmeLogicFramesPerSecond;
	if (!player || ((XLogicFrameView *)TheGameLogic)->m_frame < (unsigned int)frames || player->m_735 == 0)
		return (UpdateSleepTime)frames;
	unsigned int flags = object->m_flags114;
	if ((unsigned char)(flags >> 3) & 1)
		return (UpdateSleepTime)frames;
	if ((unsigned char)(flags >> 5) & 1)
		return (UpdateSleepTime)frames;
	XProductionQueue *queue = (XProductionQueue *)object->rva0028BC58(0);
	if (queue && queue->count() > 0)
	{
		if (queue->count() > 1)
		{
			XProductionEntry *entry = queue->front();
			XProductionInfo *info = entry->m_08;
			bool same = info != 0 && info->m_64.compare(rva004B8851()) == 0;
			if (same)
				queue->cancel(entry->m_productionID);
		}
	}
	else
	{
		Rva002A7461 *gate = &player->m_60;
		if (gate)
		{
			const ThingTemplate *thing = TheThingFactory->findTemplate(data->m_08);
			if (thing && gate->rva002A7557((Rva002A7557In *)thing, 0))
			{
				const CommandButton *button = TheControlBar->findCommandButton(data->m_commandButtonName);
				if (!data->m_1C || m_flag)
				{
					if (button)
						object->doCommandButton(button, 2, false);
					m_flag = false;
				}
			}
		}
	}
	return (UpdateSleepTime)BfmeLogicFramesPerSecond;
}
