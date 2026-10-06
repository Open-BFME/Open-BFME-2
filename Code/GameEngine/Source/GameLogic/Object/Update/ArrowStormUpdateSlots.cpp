// cl: /DNDEBUG /MD
//
// ArrowStormUpdate's slot-15 and slot-17 overrides (vftable 0x00C4D700,
// slot-2 name getter "ArrowStormUpdate"). Each first runs the base
// SpecialAbilityUpdate slot (pinned rva00450D9A / triggerAbilityEffect) and carries
// that slot's address name, which cl 7.1 needs to place the override; the
// method identities are not established. The +0x88 list is the one the
// rowed ArrowStormUpdate::xfer transfers.
//
// ?triggerAbilityEffect@ArrowStormUpdate@@UAEXXZ, retail 0x00490A74, 81 bytes.
// Slot 17: with module data +0xDC clear and an empty list, sets the flag at
// +0x98; otherwise retries the pinned bool member 0x0049083C up to module
// data +0xD4 times, keeping its result in +0x98, until it succeeds.
//
// ?rva00450D9A@ArrowStormUpdate@@UAEXXZ, retail 0x00490D0A, 53 bytes.
// Slot 15: resets the list (rowed 0x0026549E), zeroes +0x8C/+0x90/+0x94 and
// the flag at +0x98, then tail-calls the pinned member 0x00490AC5.

class ModuleData;

struct Rva0029FB3BNode
{
	Rva0029FB3BNode *m_next;
	Rva0029FB3BNode *m_previous;
	int m_value;
};

class Rva0029FB3BMember
{
public:
	bool empty() const { return m_node->m_next == m_node; }
	void reset();
	Rva0029FB3BNode *m_node;
};

struct ArrowStormUpdateModuleData
{
	unsigned char m_pad00[0xD4];
	int m_D4;
	unsigned char m_padD8[0xDC - 0xD8];
	bool m_DC;
};

class SpecialAbilityUpdate
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual void rva00450D9A();
	virtual void s16();
	virtual void triggerAbilityEffect();
protected:
	const ModuleData *m_moduleData; // +0x04
	unsigned char m_pad08[0x88 - 0x08];
};

class ArrowStormUpdate : public SpecialAbilityUpdate
{
public:
	virtual void rva00450D9A();
	virtual void triggerAbilityEffect();

private:
	bool rva0049083C();
	void rva00490AC5();

	Rva0029FB3BMember m_88;
	int m_8C;
	int m_90;
	int m_94;
	bool m_98;
};

// ?triggerAbilityEffect@ArrowStormUpdate@@UAEXXZ @0x00490A74
void ArrowStormUpdate::triggerAbilityEffect()
{
	SpecialAbilityUpdate::triggerAbilityEffect();
	const ArrowStormUpdateModuleData *data = (const ArrowStormUpdateModuleData *)m_moduleData;
	if (!data->m_DC && m_88.empty())
	{
		m_98 = true;
		return;
	}
	for (int i = 0; i < data->m_D4; )
	{
		bool done = rva0049083C();
		++i;
		m_98 = done;
		if (done)
			break;
	}
}

// ?rva00450D9A@ArrowStormUpdate@@UAEXXZ @0x00490D0A
void ArrowStormUpdate::rva00450D9A()
{
	SpecialAbilityUpdate::rva00450D9A();
	m_88.reset();
	m_8C = 0;
	m_90 = 0;
	m_94 = 0;
	m_98 = false;
	rva00490AC5();
}
