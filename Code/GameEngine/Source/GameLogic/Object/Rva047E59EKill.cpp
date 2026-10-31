// cl: /MD /DNDEBUG /EHsc
// ?rva047E59E@Rva047E59E@@QAEXXZ @0x0047E59E 54B: when the owner's +0x130 counter is set and
// the global table's +0x40 limit is not exceeded, kill the object at this-8 with (8, 6); then tail
// into TransportContain::update (0x00468749) with this.
enum DamageType;
enum DeathType;

class Object
{
public:
	void kill(DamageType d, DeathType t);
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

// The update interface this receiver shares (0x00468749).
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class TransportContain : public UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class GameLogic;
extern GameLogic *TheGameLogic;

class Rva047E59E
{
public:
	void rva047E59E();

private:
	char m_pad00[0x130];
	int m_130;
};

// ?rva047E59E@Rva047E59E@@QAEXXZ @0x0047E59E
void Rva047E59E::rva047E59E()
{
	if (m_130 != 0)
	{
		char *far = *(char **)((char *)this - 0xC);
		int total = *(int *)(far + 0x278) + m_130;
		if ((unsigned int)total <= (unsigned int)*(int *)((char *)TheGameLogic + 0x40))
		{
			Object *obj = *(Object **)((char *)this - 8);
			obj->kill((DamageType)8, (DeathType)6);
		}
	}
	static_cast<TransportContain &>(*(UpdateModuleInterface *)this).TransportContain::update();
}
