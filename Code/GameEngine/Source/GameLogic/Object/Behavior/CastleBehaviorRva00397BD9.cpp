// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
// ?onStateChanged@Rva00397BD9@@UAEXHHH@Z, retail 0x00397BD9..0x00397C94 (187B,
// EH): a Ghidra-unlisted slot of the +0x10 interface table 0x00C1A168 next
// to CastleBehavior's rowed 0x0039922D. On state 3 with the data flag +0x19
// set and the owner controlled by the local player (ThePlayerList +0x10), it
// holds the rowed 0x00395534 guard while it finds the +0x18 object, applies
// the rowed 0x00395C80 callback through its CastleBehavior module (rowed
// 0x003974CE) and, when that reports 1, fires TheEva event 5 at the owner's
// position; it then latches +0x25. States below 2 clear the latch. Fields are
// named by offset relative to the complete module.
#include "../../../Common/GameLogicObjectLookupView.h"

class Player;
class Module;
enum NameKeyType { NAMEKEY_INVALID = 0 };
struct Coord3D;

class Rva00397BD9;

class Object
{
	friend class Rva00397BD9;
public:
	Player *getControllingPlayer() const;					// 0x0028AFA9
protected:
	Module *findModule(NameKeyType key) const;				// 0x0028B6D6
public:
	char m_pad00[0x38];
	char m_position[0x0C];									// +0x38
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();						// 0x003955DA
};

class Rva003974CE
{
public:
	int apply(int (*fn)(Object *, int), int arg);			// 0x003974CE
};

int rva00395C80(Object *obj);								// 0x00395C80

// Eva::reportEvaEvent uses the target enum and two nullable position pointers.
enum EvaEventID { EVA_INVALID = -1 };

#include "../../../../Include/GameClient/Eva.h"

extern Eva *TheEva;

class PlayerList;
extern PlayerList *ThePlayerList;

struct Rva00397BD9PlayerListView
{
	char m_pad[0x10];
	Player *m_local;										// +0x10
};

extern GameLogic *TheGameLogic;

// The scope guard built around the lookup (ctor 0x00395534, dtor 0x00395561).
class Rva00395561
{
public:
	Rva00395561();
	~Rva00395561();
private:
	int m_00;
};

struct Rva00397BD9Data
{
	char m_pad[0x19];
	bool m_evaEnabled;												// +0x19
};

class Rva00397BD9Base0
{
public:
	virtual void b0();
	Rva00397BD9Data *m_data;								// +0x04
	Object *m_object;										// +0x08
	int m_0C;
};

class Rva00397BD9Iface
{
public:
	virtual void onStateChanged(int a, int b, int state);
	int m_14;
	ObjectID m_targetID;									// +0x18
	char m_pad1C[0x25 - 0x1C];
	bool m_latched;											// +0x25
};

class Rva00397BD9 : public Rva00397BD9Base0, public Rva00397BD9Iface
{
public:
	virtual void onStateChanged(int a, int b, int state);
};

void Rva00397BD9::onStateChanged(int, int, int state)
{
	if (state == 3)
	{
		if (m_data->m_evaEnabled)
		{
			Player *localPlayer = ((Rva00397BD9PlayerListView *)ThePlayerList)->m_local;
			if (localPlayer == m_object->getControllingPlayer())
			{
				Rva00395561 guard;
				Object *target = TheGameLogic->findObjectByID(m_targetID);
				if (target)
				{
					Module *module = target->findModule(CastleBehavior::rva0003955DA());
					if (module && ((Rva003974CE *)module)->apply((int (*)(Object *, int))rva00395C80, 0) == 1)
						TheEva->reportEvaEvent(static_cast<EvaEventID>(5), (const Coord3D *)m_object->m_position, 0);
				}
			}
		}
		m_latched = true;
	}
	else if (state < 2)
		m_latched = false;
}
