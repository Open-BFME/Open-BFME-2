// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ??0Rva002E0EF7@@QAE@XZ @0x002E0EF7 39B.
// Default ctor: stores vtable 0x00804948, zeroes members, sets +0x1C to -1.
// Evidence: vtable store plus or [eax+0x1C],-1 idiom; callers 0x002E1D22
// 0x002E277A 0x0052C505; prev shares /O1.
struct Rva002E0EF7
{
	virtual void anchor();
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	unsigned char m_24;
	Rva002E0EF7();
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
Rva002E0EF7::Rva002E0EF7()
{
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	_ReadWriteBarrier();
	m_1C = -1;
	m_18 = 0;
	m_20 = 0;
	m_24 = 0;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?anchor@Rva002E0EF7@@UAEXXZ=??_GRva002E0F1E@@UAEPAXI@Z")
