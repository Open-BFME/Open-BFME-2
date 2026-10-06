// ?canAcceptNewRepair@DozerAIUpdate@@UAE_NPAVObject@@@Z
// partial score=0.9 date=2026-10-06
// Banked near miss for DozerAIUpdate::canAcceptNewRepair (0x00489895, 126B), in
// Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate.cpp:
// remove the stale present-unmatched marker above the ZH body, and replace the
// two ZH isKindOf(KINDOF_BRIDGE_TOWER) calls (they call Thing::isKindOf out of
// line) with this inline test of BFME 2's bit 24 at template +0x108. Everything
// else matches; retail hoists 0x1000000 into ecx and tests the dword twice
// (b9 00 00 00 01 / 85 8a 08 01 00 00) where this narrows each test to
// test byte [reg+0x10B],1.
static inline Bool bfmeIsKindOf( const Object *obj, Int kindOf )
{
	const ThingTemplate *tmpl = *(const ThingTemplate **)((const char *)obj + 4);
	const UnsignedInt *mask = (const UnsignedInt *)((const char *)tmpl + 0x108);
	return ( mask[ kindOf >> 5 ] & ( 1 << ( kindOf & 31 ) ) ) != 0;
}
// ...
//		if( bfmeIsKindOf( currentRepair, 24 ) && bfmeIsKindOf( obj, 24 ) )
