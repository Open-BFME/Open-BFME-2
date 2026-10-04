// cl: /O1 /DNDEBUG /MD
//
// DamageFilteredCreateObjectDie's +0x14 damage-module interface overrides
// (table 0x00C4AA84, installed by the matched ctor 0x00485F87, which also
// zeroes +0x18 and sets +0x1C to -1; the matched xfer saves both), so `this`
// is that subobject (module data at -0x10).
//   slot 0, retail 0x004860E9 (77 bytes), onDamage: for damage whose +0x18
//           value equals the module data's +0x40, records the frame (+0x18)
//           and, when the source Object (+0x08) and its controlling Player
//           still exist, the Player's +0x54 value (+0x1C).
//   slot 1, retail 0x00485EF6 (7 bytes): clears the recorded frame; its
//           argument is unused.
// Slot names by address.
enum ObjectID
{
	INVALID_ID = 0
};
class Player
{
public:
	unsigned char m_pad00[0x54];
	int m_54;			// +0x54
};
class Object
{
public:
	Player *getControllingPlayer() const;
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	unsigned int getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	unsigned int m_frame;		// +0x40
};
extern GameLogic *TheGameLogic;
class DamageInfo
{
public:
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID;		// +0x08
	unsigned char m_pad0C[0x18 - 0x0C];
	int m_18;			// +0x18
};
struct DamageFilteredCreateObjectDieModuleData
{
	unsigned char m_pad00[0x40];
	int m_40;			// +0x40
};
class ModuleData;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	void *m_object;			// +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};
class DieModuleInterface
{
public:
	virtual void d00() = 0;
};
class DieModule : public ModuleBase, public BehaviorModuleInterface, public DieModuleInterface
{
};
class Rva00C4AA84Iface
{
public:
	virtual void rva004860E9(DamageInfo *damageInfo) = 0;
	virtual void rva00485EF6(void *arg) = 0;
};
class DamageFilteredCreateObjectDie : public DieModule, public Rva00C4AA84Iface
{
public:
	virtual void rva004860E9(DamageInfo *damageInfo);
	virtual void rva00485EF6(void *arg);
private:
	unsigned int m_frame;		// +0x18
	int m_playerValue;		// +0x1C
};
void DamageFilteredCreateObjectDie::rva004860E9(DamageInfo *damageInfo)
{
	if (damageInfo == 0)
		return;
	const DamageFilteredCreateObjectDieModuleData *data =
		(const DamageFilteredCreateObjectDieModuleData *)m_moduleData;
	if (data && data->m_40 == damageInfo->m_18)
	{
		m_frame = TheGameLogic->getFrame();
		Object *source = TheGameLogic->findObjectByID(damageInfo->m_sourceID);
		if (source)
		{
			Player *player = source->getControllingPlayer();
			if (player)
				m_playerValue = player->m_54;
		}
	}
}
void DamageFilteredCreateObjectDie::rva00485EF6(void *arg)
{
	m_frame = 0;
}
