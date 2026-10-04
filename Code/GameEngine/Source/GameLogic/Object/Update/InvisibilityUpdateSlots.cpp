// cl: /O1 /DNDEBUG /MD
//
// InvisibilityUpdate pieces around the interface its matched ctor 0x004A382D
// installs at +0x20 (vtable 0x00C52518; primary 0x00C52534). Names are by
// address.
//
// ?rva004A3877@InvisibilityUpdate@@UAEPAVRva004A3A09Iface@@XZ, retail
// 0x004A3877, 12 bytes: primary slots 10 and 11 (one folded body), the +0x20
// interface of this object, null-checked as cl converts.
//
// ?rva004A3A09@InvisibilityUpdate@@UAE_NXZ, retail 0x004A3A09, 23 bytes: +0x20
// slot 0, whether the module data exists and has its +0x1D0 flag.
//
// ?rva004A39D0@InvisibilityUpdate@@QAEX_N@Z, retail 0x004A39D0, 57 bytes (the
// pinned toggle ToggleHiddenSpecialAbilityUpdate slots 23/24 call): unless the
// module data's +0x1D0 flag is set, raising wakes the module next frame and
// sets +0x24 once; lowering clears +0x24.

class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

struct InvisibilityUpdateModuleData
{
	unsigned char m_pad000[0x1D0];
	bool m_1D0; // +0x1D0
};

template <int N> class Rva004A3877Slots : public Rva004A3877Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004A3877Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class Rva004A3A09Iface
{
public:
	virtual bool rva004A3A09() = 0;
};

class UpdateModule : public Rva004A3877Slots<10>
{
public:
	virtual Rva004A3A09Iface *rva004A3877() = 0;
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	const InvisibilityUpdateModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};

class InvisibilityUpdate : public UpdateModule, public Rva004A3A09Iface
{
public:
	virtual Rva004A3A09Iface *rva004A3877();
	virtual bool rva004A3A09();
	void rva004A39D0(bool on);
private:
	bool m_24; // +0x24
};

// ?rva004A3877@InvisibilityUpdate@@UAEPAVRva004A3A09Iface@@XZ @0x004A3877
Rva004A3A09Iface *InvisibilityUpdate::rva004A3877()
{
	return this;
}

// ?rva004A3A09@InvisibilityUpdate@@UAE_NXZ @0x004A3A09
bool InvisibilityUpdate::rva004A3A09()
{
	const InvisibilityUpdateModuleData *data = m_moduleData;
	return data && data->m_1D0;
}

// ?rva004A39D0@InvisibilityUpdate@@QAEX_N@Z @0x004A39D0
void InvisibilityUpdate::rva004A39D0(bool on)
{
	if (m_moduleData->m_1D0)
		return;
	if (on)
	{
		if (!m_24)
		{
			setWakeFrame(m_object, UPDATE_SLEEP_NONE);
			m_24 = true;
		}
	}
	else if (m_24)
		m_24 = false;
}
