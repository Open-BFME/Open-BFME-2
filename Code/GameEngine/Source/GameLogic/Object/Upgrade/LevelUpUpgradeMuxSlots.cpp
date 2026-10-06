// cl: /DNDEBUG /MD
//
// LevelUpUpgrade's UpgradeMux overrides (+0x10 vtable 0x00C57418; the recipe
// of RemoveUpgradeUpgradeRemovalImplementation.cpp), the experience tracker
// being the Object's +0x264 (its level at +0x24).
// Retail 0x004B3E7F (33 bytes), slot 2: false once the tracker's level has
// reached the module data's +0x11C cap, else the UpgradeMux base 0x004CE2B0
// (tail jump; rowed as Rva004CE2B0::rva004CE2B0 and pinned for UpgradeMux by
// address). The slot is named after that base.
// Retail 0x004B3E15 (106 bytes), slot 10 upgradeImplementation: grants the
// lower of the module data's +0x118 level count and the room left under the
// cap through the tracker's 0x0039B4EC (with 1, 0), then, when the Object's
// 0x0029439D result exists, runs its slot 49 once per level granted.
typedef bool Bool;
class ModuleData;
class Rva00406F9C;
class ExperienceTracker
{
public:
	Bool rva0039B4EC(int levels, Bool flag1, Bool flag2);
	unsigned char m_pad00[0x24];
	int m_level;			// +0x24
};
template <int N> class Rva004B3E15Slots : public Rva004B3E15Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004B3E15Slots<0>
{
};
class Rva004B3E15Target : public Rva004B3E15Slots<49>
{
public:
	virtual void rvaSlot49() = 0;
};
class Object
{
public:
	void *rva0029439D();
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
private:
	unsigned char m_pad000[0x264];
	ExperienceTracker *m_experienceTracker;	// +0x264
};
struct LevelUpUpgradeModuleData
{
	unsigned char m_pad00[0x118];
	int m_levels;			// +0x118
	int m_levelCap;			// +0x11C
};
template <class T> inline const T &lowerOf(const T &a, const T &b)
{
	return (a < b) ? a : b;
}
class ObjectModuleBase
{
public:
	virtual ~ObjectModuleBase();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};
class UpgradeMux
{
public:
	virtual Bool isAlreadyUpgraded() const = 0;
	virtual void m01() = 0;
	virtual Bool rva004CE2B0(Rva00406F9C *arg);
	virtual void m03() = 0;
	virtual void m04() = 0;
	virtual void m05() = 0;
	virtual void m06() = 0;
	virtual void m07() = 0;
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(Bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};
class UpgradeModule : public ObjectModuleBase, public UpgradeModuleInterface, public UpgradeMux
{
};
class LevelUpUpgrade : public UpgradeModule
{
public:
	virtual Bool rva004CE2B0(Rva00406F9C *arg);
protected:
	virtual void upgradeImplementation();
	const LevelUpUpgradeModuleData *getData() const
	{
		return (const LevelUpUpgradeModuleData *)m_moduleData;
	}
};
Bool LevelUpUpgrade::rva004CE2B0(Rva00406F9C *arg)
{
	if (m_object->getExperienceTracker()->m_level >= getData()->m_levelCap)
		return false;
	return UpgradeMux::rva004CE2B0(arg);
}
void LevelUpUpgrade::upgradeImplementation()
{
	const LevelUpUpgradeModuleData *data = getData();
	int wanted = data->m_levels;
	Object *object = m_object;
	ExperienceTracker *tracker = object->getExperienceTracker();
	int room = data->m_levelCap - tracker->m_level;
	int levels = lowerOf(wanted, room);
	if (levels >= 1)
		tracker->rva0039B4EC(levels, true, false);
	if (object->rva0029439D() && levels > 0)
	{
		do
		{
			((Rva004B3E15Target *)object->rva0029439D())->rvaSlot49();
		} while (--levels);
	}
}
