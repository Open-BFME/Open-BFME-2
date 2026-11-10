// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ??RRva00422CA8@@QBE_NHH@Z retail 0x00422CA8 65B.
// Sort/heap comparator for 0x20-byte slot structs: each int element is a
// pointer to a 32-byte record with ObjectID at +0x04. Looks both IDs up via
// TheGameLogic (global 0x00DFE78C) findObjectByID row 0x00049DC5 and orders
// ascending on Object template pointer at +0x04 (same slot ObjectIsSelectable
// and ObjectDidEnterOrExit document). Null on either side returns false.
// Evidence: 8 sort-helper callers all lea ecx for thiscall plus two int pushes
// (0x00423098 upper_bound 0x00423134 median 0x004231A0 partition 0x00423262
// push_heap 0x00423349 adjust_heap 0x004238AE insert 0x004239BF sift
// 0x00424C21 sort); 0x0042550E builds vector of 0x20 records then sorts it
// with this predicate; Q4Sort int-by-value comparator precedent for
// pointer-as-int sort keys; combined OR null check gives retail je-je layout.

#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"

#include "../../../../GameEngine/Source/GameLogic/Object/object.h"

extern GameLogic *TheGameLogic;


struct Elem32
{
	int m_0; // +0x00
	int m_id; // +0x04 ObjectID
	char m_pad[0x20 - 8];
};

#include "Rva00422CA8.h"

bool Rva00422CA8::operator()(int a, int b) const
{
	GameLogic *logic = TheGameLogic;
	Object *ob = logic->findObjectByID((ObjectID)((Elem32 *)b)->m_id);
	Object *oa = logic->findObjectByID((ObjectID)((Elem32 *)a)->m_id);
	if (oa == 0 || ob == 0)
		return false;
	return (unsigned int)oa->m_template < (unsigned int)ob->m_template;
}
