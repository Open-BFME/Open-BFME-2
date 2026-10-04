// cl: /O1 /DNDEBUG /MD
//
// ?onDestroy@Object@@QAEXXZ @0x0028FC1D (98B), Zero Hour Object::onDestroy
// with BFME 2's changes: removeFromContain gains a second argument (FALSE,
// contain slot 41 / 0xA4) on the container (+0x274) contain module (+0x250);
// a new step 0x0028DAB9 (unnamed: when byte +0x480 is set it hands the
// object to its controlling player and clears it); slots 1..8 of the object
// at +0x84 are each called through 0x00271BCC with (slot, 1); then the
// behaviors (+0x244, NULL-terminated) get onDelete (slot 8) as in ZH.
// ZH's trailing handlePartitionCellMaintenance is gone. The +0x84 type and
// both helpers' identities are unknown (address-derived names).

typedef bool Bool;

class Object;

class ContainModuleInterfaceSlots
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40();
};

class ContainModuleInterface : public ContainModuleInterfaceSlots
{
public:
	virtual void removeFromContain(Object *obj, Bool exposeStealthUnits) = 0; // slot 41
};

class BehaviorModule
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
	virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
	virtual void onDelete() = 0; // slot 8
};

class Rva00271BCC
{
public:
	void rva00271BCC(int slot, int value);
};

class Object
{
public:
	void onDestroy();
	ContainModuleInterface *getContain() const { return m_contain; }

private:
	void rva0028DAB9();

	unsigned char m_pad000[0x84];
	Rva00271BCC *m_rva84;                   // +0x84
	unsigned char m_pad088[0x244 - 0x88];
	BehaviorModule **m_behaviors;           // +0x244
	unsigned char m_pad248[0x250 - 0x248];
	ContainModuleInterface *m_contain;      // +0x250
	unsigned char m_pad254[0x274 - 0x254];
	Object *m_containedBy;                  // +0x274
};

void Object::onDestroy()
{
	if (m_containedBy && m_containedBy->getContain())
		m_containedBy->getContain()->removeFromContain(this, false);

	rva0028DAB9();

	Rva00271BCC *rva84 = m_rva84;
	if (rva84)
	{
		for (int i = 1; i < 9; ++i)
			rva84->rva00271BCC(i, 1);
	}

	for (BehaviorModule **b = m_behaviors; *b; ++b)
		(*b)->onDelete();
}
