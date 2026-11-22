// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?get@Rva002E0CD4@@QBEHXZ @0x002E0CD4 46B.
// Honest address name: __thiscall getter with 7 callers and no callees.
// Byte-exact model: int a = inner->m_8 + m_294 + m_260; int b = inner->m_C;
// returns min(a,b) via *(a < b ? &a : &b) which forces the retail EBP frame
// with lea-eax pointer select and leave.
// Evidence: 7 UNCLAIMED callers incl 0x002D4748 0x002E112A 0x002E1155;
// prev 0x002E0856 Disp8DivMov getter and next 0x002E18C3 lookup share /O1.

#include "../../Include/Common/Rva002E0CD4.h"

// ?rva002E0CAC@Rva002E0CD4@@QBEHXZ @0x002E0CAC 40B.
int Rva002E0CD4::rva002E0CAC() const
{
	int a = m_40->m_10 + m_290;
	int b = m_40->m_14;
	return *(a < b ? &a : &b);
}

int Rva002E0CD4::get() const
{
	int a = m_40->m_8 + m_294 + m_260;
	int b = m_40->m_C;
	return *(a < b ? &a : &b);
}

// ?rva002E14DD@Rva002E0CD4@@QBEHXZ @0x002E14DD 12B.
// Sibling getter: get() minus m_40->m_8. Evidence: calls rowed get at
// 0x002E0CD4 then sub [ecx+8]; callers 0x002A7318 0x002D486E.
int Rva002E0CD4::rva002E14DD() const
{
	return get() - m_40->m_8;
}

