// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0034311ECheck@@YA_NPAVObject@@@Z, retail 0x0034311E, 48 bytes.
// Cdecl predicate on one Object*: t = o; if o->rva002931BA() then
// t = o->rva002931F5(false); return t == 0 || t->containedBy (+0x274) != 0.
// Evidence: callees 0x002931BA and 0x002931F5 are matched Object members
// (ObjectRva002931BA.cpp, ObjectRva002931F5.cpp); the +0x274 field is
// containedBy in the same ledger row set. Caller 0x0034AA17 (inside
// AIAttackFireWeaponState::onEnter, 0x0034A879) proves the single stack arg.
// Identity name is address-derived; it is not a retail symbol.

typedef bool Bool;

#include "object.h"

Bool Rva0034311ECheck(Object *object)
{
	Object *target = object;
	if (object->rva002931BA())
		target = object->rva002931F5(false);
	if (target != 0 && target->m_containedBy == 0)
		return false;
	return true;
}
