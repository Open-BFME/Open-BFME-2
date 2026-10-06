// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002E6FDF@Rva002E6FDF@@QAEPAV1@XZ @0x002E6FDF 59B.
// Honest address name: unclaimed __thiscall clearer returning this with 11 callers
// and no donor string vtable or export to prove a real identity. Byte-exact model:
// zeroes struct up to +0x34 with -1 at +0x24 (or under /O1). Evidence: callers
// 0x002E931F lea ecx [ebx+8] and 0x002ECC0D lea ecx [ebp-0x4C] both ignore return;
// prev 0x002E6F8B in Rva002E6F8BClear.cpp and next 0x002E7178 in
// PathfindShimAddObject.cpp share /O1 frameless shape. _ReadWriteBarrier pins the
// or store in source order with no emitted bytes.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva002E6FDF
{
public:
	Rva002E6FDF *rva002E6FDF();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	unsigned char m_10;
	unsigned char m_11;
	char m_pad12[2];
	int m_14;
	int m_18;
	int m_1C;
	unsigned char m_20;
	unsigned char m_21;
	char m_pad22[2];
	int m_24;
	unsigned char m_28;
	char m_pad29[3];
	int m_2C;
	unsigned char m_30;
	unsigned char m_31;
	unsigned char m_32;
	char m_pad33[1];
	int m_34;
};

Rva002E6FDF *Rva002E6FDF::rva002E6FDF()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_11 = 0;
	m_14 = 0;
	m_18 = 0;
	_ReadWriteBarrier();
	m_24 = -1;
	m_1C = 0;
	m_20 = 0;
	m_21 = 0;
	m_28 = 0;
	m_2C = 0;
	m_31 = 0;
	m_32 = 0;
	m_30 = 0;
	m_34 = 0;
	return this;
}
