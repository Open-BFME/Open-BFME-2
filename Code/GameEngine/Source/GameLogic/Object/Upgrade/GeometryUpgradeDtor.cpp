// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1GeometryUpgrade@@UAE@XZ, retail 0x004B6C55, 53 bytes. Behavior-side
// module dtor: destroys the AsciiString upgrade-name at +0x1C via the
// folded StringBase<char> teardown at 0x00036410, then calls the
// UpgradeModule base dtor (twin pin ??1UpgradeModule@@MAE@XZ at 0x0046089D,
// ICF-folded under the rowed ??1FireWeaponWhenDeadBehavior@@MAE@XZ there).
// No vptr stores: novtable suppresses the derived store retail lacks
// (ReplaceSelfUpgradeDtor precedent). Identity is vtable 0x008589C0 of the
// rowed ctor 0x004B6A5E plus size 0x20 from the rowed friend_newModuleInstance
// 0x0025060A (0x1C UpgradeModule footprint + 4 string) plus sole caller ??_G
// 0x004B6C39 slot 0 plus BFME1 GeometryUpgradeDestructor donor (same member
// then base shape).

template <typename T>
class StringBase
{
public:
	~StringBase();

private:
	T *m_data;
};

class UpgradeModule
{
protected:
	virtual ~UpgradeModule();

private:
	unsigned char m_pad[0x1C - 4];
};

class __declspec(novtable) GeometryUpgrade : public UpgradeModule
{
public:
	virtual ~GeometryUpgrade();

private:
	StringBase<char> m_upgradeName; // +0x1C
};

GeometryUpgrade::~GeometryUpgrade()
{
}
