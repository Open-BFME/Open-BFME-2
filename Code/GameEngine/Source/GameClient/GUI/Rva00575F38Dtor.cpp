// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??1Rva00575F38@@UAE@XZ retail 0x00575F38..0x00576021 (233 bytes EH).
// The destructor the scalar deleting dtor 0x005760E9 calls (vtable
// 0x00C6E720). WorldBuilder twin 0x014D3330 (unnamed) has the same shape.
// Five bases: +0x00 Base0_00576C4B (reset to 0x00BDBA74) +0x04
// VBase00C6EE28 (0x00C6EE28) +0x08 BfmeCtorVirtualBase001B3A20 (0x00C078DC)
// +0x0C the rowed Rva005CD1A9 (out-of-line dtor 0x005CD1A9) and +0x14
// Rva005753E9 (0x00C6E5C4); the derived vtables are 0x00C6E720 0x00C6E700
// 0x00C6E6EC 0x00C6E6E4 and 0x00C6E6B8. Target evidence: the +0x18 owner's
// +0x04 object gives (rowed getter 0x00574AAC) the receiver of the rowed
// 0x005CB84A(0); when the rowed check 0x002B254F on TheLivingWorldLogic
// passes the +0x14 base is erased (rowed 0x002B7250 on the +0x04 list of
// the object returned by 0x002B256E called on TheLivingWorldLogic); then
// the members die: +0x40 (rowed Rva005CD651 dtor) +0x30 (0x005CD7DA)
// +0x2C and +0x28 (pinned Gen_uw_000ad6f4 dtor 0x000AD6F4) and +0x24
// (0x0055076F). Class identity is address-derived.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class CreateAHeroData;

class Rva002B254F
{
public:
	int rva002B254F();
};

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *data);
};

struct Rva002B256EOwner
{
	void *m_00;
	Rva002B7250 m_list; // +0x04
};

class Rva002B256E
{
public:
	void *rva002B256E();
};

class Rva005CB84A
{
public:
	void rva005CB84A(int value);
};

class Rva00574AACAddDwordField
{
public:
	int get() const;
};

struct Rva00575F38Owner
{
	void *m_00;
	Rva00574AACAddDwordField *m_04; // +0x04
};

class Base0_00576C4B
{
public:
	virtual ~Base0_00576C4B() {}
};

class VBase00C6EE28
{
public:
	virtual ~VBase00C6EE28() {}
};

class BfmeCtorVirtualBase001B3A20
{
public:
	virtual ~BfmeCtorVirtualBase001B3A20() {}
};

class Rva005CD1A9
{
public:
	virtual ~Rva005CD1A9();

private:
	int m_04;
};

class Rva005753E9
{
public:
	virtual ~Rva005753E9() {}

protected:
	Rva00575F38Owner *m_owner; // +0x18 (base +0x04)
	int m_1C;
	int m_20;
};

class Rva0055076F
{
public:
	~Rva0055076F() { rva0055076F(); }
	void rva0055076F();

private:
	void *m_p;
};

class Gen_uw_000ad6f4
{
public:
	~Gen_uw_000ad6f4();

private:
	void *m_p;
};

class Rva005CD7DA
{
public:
	~Rva005CD7DA() { rva005CD7DA(); }
	void rva005CD7DA();

private:
	void *m_data[4];
};

class Rva005CD651
{
public:
	virtual ~Rva005CD651();
};

class Rva00575F38 : public Base0_00576C4B, public VBase00C6EE28, public BfmeCtorVirtualBase001B3A20,
	public Rva005CD1A9, public Rva005753E9
{
public:
	virtual ~Rva00575F38();

private:
	Rva0055076F m_24;      // +0x24
	Gen_uw_000ad6f4 m_28;  // +0x28
	Gen_uw_000ad6f4 m_2C;  // +0x2C
	Rva005CD7DA m_30;      // +0x30
	Rva005CD651 m_40;      // +0x40
};

Rva00575F38::~Rva00575F38()
{
	reinterpret_cast<Rva005CB84A *>(m_owner->m_04->get())->rva005CB84A(0);
	if ((unsigned char)reinterpret_cast<Rva002B254F *>(TheLivingWorldLogic)->rva002B254F())
	{
		reinterpret_cast<Rva002B256EOwner *>(reinterpret_cast<Rva002B256E *>(TheLivingWorldLogic)->rva002B256E())->m_list.rva002B7250(
			reinterpret_cast<CreateAHeroData *>(static_cast<Rva005753E9 *>(this)));
	}
}
