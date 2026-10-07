// cl: /DNDEBUG /MD /EHsc /O1 /G7
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ghidra FUN_00685ced gives a 58-byte boundary. The target accepts one
// interface pointer, asks virtual slots +0x28, +0x4c, and +0x7c to write
// through a two-byte local and the owner's +4/+0xC fields. The interface and
// owner identities are not established, so both views are address-derived.

class Rva00285CEDInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void rva00285CEDSlot10(void *out) = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void rva00285CEDSlot19(void *out) = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void rva00285CEDSlot31(void *out) = 0;
};

class Rva00285CEDHost
{
public:
	void rva00285CED(void *interfaceObject);

private:
	char m_unknown00[0x10];
};

struct Rva00285CEDFlags
{
	unsigned char first;
	unsigned char second;
};

void Rva00285CEDHost::rva00285CED(void *interfaceObject)
{
	Rva00285CEDFlags flags = { 1, 1 };
	Rva00285CEDInterface *input = (Rva00285CEDInterface *)interfaceObject;
	input->rva00285CEDSlot10(&flags);
	input->rva00285CEDSlot19((char *)this + 4);
	input->rva00285CEDSlot31((char *)this + 0xC);
}
