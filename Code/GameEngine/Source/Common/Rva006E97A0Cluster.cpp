// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Singleton releaser sitting between the S4 two-member destructors and the
// 0x006E9xxx block. Clears the pointer at 0x00E1818C after one slot-1 virtual
// call on its object (vtable+4, no stack arguments). No callee is named and the
// only relocation is the masked DIR32 global, so the body is the evidence;
// identity is unproven and the names are this image's address.

class Rva006E97A0Object
{
public:
	virtual void slot0();
	virtual void slot1();
};

extern Rva006E97A0Object *g_pRva006E97A0Object;	// 0x00E1818C

// ?Rva006E97A0@@YAXXZ @ 0x006E97A0 (26B)
void Rva006E97A0(void)
{
	if (g_pRva006E97A0Object) {
		g_pRva006E97A0Object->slot1();
		g_pRva006E97A0Object = 0;
	}
}
