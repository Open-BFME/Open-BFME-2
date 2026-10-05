// cl: /O1 /MD /DNDEBUG
//
// ?addLocomotor@LocomotorSet@@QAEXPBVLocomotorTemplate@@_N@Z
// retail 0x001E88CE, 92 bytes (Ghidra FUN_005e88ce), pinned from
// AIUpdateInterface::chooseLocomotorSetExplicit.
//
// Donor: GeneralsMD Locomotor.cpp LocomotorSet::addLocomotor. BFME 2 passes
// a second argument through to TheLocomotorStore->newLocomotor (0x001E4A81),
// pushes through the out-of-line pointer-vector push_back 0x004DFCB0 (the
// ledger's folded vector<const ModuleData*> copy) and, besides the
// downhill-only flag (template +0xD3 -> set +0x14), raises a second flag
// (template +0x150 -> set +0x15) whose meaning is unknown.
// Layout: locomotors vector +4, valid surfaces +0x10; the locomotor keeps
// its template at +4, legal surfaces at template +0x14. Retail pushes a
// stack copy of the pointer made before the null test and keeps using the
// register copy afterwards; the separate `pushed` local reproduces that.

typedef bool Bool;
typedef int Int;

class LocomotorTemplate
{
public:
	Int getLegalSurfaces() const { return m_surfaces; }
	Bool getIsDownhillOnly() const { return m_downhillOnly; }
	Bool getUnknown150() const { return m_unknown150; }
private:
	unsigned char m_pad00[0x14];
	Int m_surfaces;
	unsigned char m_pad18[0xD3 - 0x18];
	Bool m_downhillOnly;
	unsigned char m_padD4[0x150 - 0xD4];
	Bool m_unknown150;
};

class Locomotor
{
public:
	Int getLegalSurfaces() const { return m_template->getLegalSurfaces(); }
	Bool getIsDownhillOnly() const { return m_template->getIsDownhillOnly(); }
	Bool getUnknown150() const { return m_template->getUnknown150(); }
private:
	void *m_vtable;
	const LocomotorTemplate *m_template;
};

class LocomotorStore
{
public:
	Locomotor *newLocomotor(const LocomotorTemplate *tmpl, Bool flag);
};
extern LocomotorStore *TheLocomotorStore;	// VA 0x00DFDC5C

struct LocomotorPtrVector
{
	void push_back(Locomotor *const &loco);

	Locomotor **m_start;
	Locomotor **m_finish;
	Locomotor **m_endOfStorage;
};

class LocomotorSet
{
public:
	void addLocomotor(const LocomotorTemplate *lt, Bool flag);
private:
	void *m_vtable;
	LocomotorPtrVector m_locomotors;
	Int m_validLocomotorSurfaces;
	Bool m_downhillOnly;
	Bool m_unknown15;
};

void LocomotorSet::addLocomotor(const LocomotorTemplate *lt, Bool flag)
{
	Locomotor *loco = TheLocomotorStore->newLocomotor(lt, flag);
	Locomotor *pushed = loco;
	if (loco)
	{
		m_locomotors.push_back(pushed);
		m_validLocomotorSurfaces |= loco->getLegalSurfaces();
		if (loco->getIsDownhillOnly())
		{
			m_downhillOnly = true;
		}
		if (loco->getUnknown150())
		{
			m_unknown15 = true;
		}
	}
}
