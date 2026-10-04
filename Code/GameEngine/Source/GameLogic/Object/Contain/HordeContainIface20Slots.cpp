// cl: /O1 /DNDEBUG /MD
//
// HordeContain overrides in the contain interface its pinned ctor 0x0046F543
// installs at +0x20 (vtable 0x00C44EC8; the slots below 0x00468000 there are
// OpenContain's and TransportContain's). Compiled with the +0x20 subobject
// this: [ecx-0x18] is the owning Object at +0x08. Names are by address.
//
// Slots 11, 26 and 45 hand the same slot of the contain interface (Object
// +0x250) of the Object our Object's +0x274 names, when there is one; slot 11
// answers true and slot 45 false without it. Slots 30 and 31 (one folded body)
// answer the +0x11C interface of this object, null-checked as cl converts.

class Object;

template <int N> class Rva00469626Slots : public Rva00469626Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00469626Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class Rva00469626HordeIface
{
public:
	virtual void rva00469626HordeIfaceAnchor() = 0;
};

class ContainModuleInterface : public Rva00469626Slots<11>
{
public:
	virtual bool rva00469626() = 0;
	virtual void gap12() = 0; virtual void gap13() = 0; virtual void gap14() = 0;
	virtual void gap15() = 0; virtual void gap16() = 0; virtual void gap17() = 0;
	virtual void gap18() = 0; virtual void gap19() = 0; virtual void gap20() = 0;
	virtual void gap21() = 0; virtual void gap22() = 0; virtual void gap23() = 0;
	virtual void gap24() = 0; virtual void gap25() = 0;
	virtual void rva004697A8(int a1, int a2, int a3) = 0;
	virtual void gap27() = 0; virtual void gap28() = 0; virtual void gap29() = 0;
	virtual Rva00469626HordeIface *rva0046F7B9() = 0;
	virtual Rva00469626HordeIface *rva0046F7B9Slot31() = 0;
	virtual void gap32() = 0; virtual void gap33() = 0; virtual void gap34() = 0;
	virtual void gap35() = 0; virtual void gap36() = 0; virtual void gap37() = 0;
	virtual void gap38() = 0; virtual void gap39() = 0; virtual void gap40() = 0;
	virtual void gap41() = 0; virtual void gap42() = 0; virtual void gap43() = 0;
	virtual void gap44() = 0;
	virtual bool rva00469602() = 0;
};

class Object
{
public:
	unsigned char m_pad000[0x250];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x274 - 0x254];
	Object *m_274; // +0x274
};

class ModuleData;

class UpdateModuleView
{
public:
	virtual ~UpdateModuleView();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};

class TransportContainView : public UpdateModuleView, public ContainModuleInterface
{
	unsigned char m_pad24[0x11C - 0x24];
};

class HordeContain : public TransportContainView, public Rva00469626HordeIface
{
public:
	virtual bool rva00469626();
	virtual void rva004697A8(int a1, int a2, int a3);
	virtual Rva00469626HordeIface *rva0046F7B9();
	virtual bool rva00469602();
};

// ?rva00469626@HordeContain@@UAE_NXZ @0x00469626: slot 11.
bool HordeContain::rva00469626()
{
	Object *other = m_object->m_274;
	if (other)
	{
		ContainModuleInterface *contain = other->m_contain;
		if (contain)
			return contain->rva00469626();
	}
	return true;
}

// ?rva004697A8@HordeContain@@UAEXHHH@Z @0x004697A8: slot 26 (argument types not
// established).
void HordeContain::rva004697A8(int a1, int a2, int a3)
{
	Object *me = m_object;
	if (me)
	{
		Object *other = me->m_274;
		if (other)
		{
			ContainModuleInterface *contain = other->m_contain;
			if (contain)
				contain->rva004697A8(a1, a2, a3);
		}
	}
}

// ?rva0046F7B9@HordeContain@@UAEPAVRva00469626HordeIface@@XZ @0x0046F7B9: slots
// 30 and 31.
Rva00469626HordeIface *HordeContain::rva0046F7B9()
{
	return this;
}

// ?rva00469602@HordeContain@@UAE_NXZ @0x00469602: slot 45.
bool HordeContain::rva00469602()
{
	Object *other = m_object->m_274;
	if (other)
	{
		ContainModuleInterface *contain = other->m_contain;
		if (contain)
			return contain->rva00469602();
	}
	return false;
}
