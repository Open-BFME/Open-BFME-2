// cl: /O1 /MD /EHsc
// ??1WeaponSet@@UAE@XZ retail 0x002C7311 81B
// Zero Hour WeaponSet::~WeaponSet shape: delete each of the six weapon slots
// at +8 when set; then the inline Snapshot-style base dtor restores BBB554.
// Retail deletes through the slot-0 deleting dtor with flag 0 followed by the
// global ??3@YAXPAX@Z (a global-scope delete). Identity from the pin (slot 2
// of vtable 0x00C0089C returns "WeaponSet"); six slots at +8 as in the rowed
// WeaponSetRvaSlotSearch.cpp. Helper class names are local.

class WeaponSetSlot
{
public:
	virtual ~WeaponSetSlot();
};

class WeaponSetSnapshotBase
{
public:
	virtual ~WeaponSetSnapshotBase() {}
};

class WeaponSet : public WeaponSetSnapshotBase
{
public:
	virtual ~WeaponSet();

private:
	int m_04;
	WeaponSetSlot *m_weapons[6]; // +0x08
};

WeaponSet::~WeaponSet()
{
	for (int i = 0; i < 6; ++i)
		if (m_weapons[i])
			::delete m_weapons[i];
}
