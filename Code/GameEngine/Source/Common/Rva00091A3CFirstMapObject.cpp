// cl: /MD /DNDEBUG
// Retail 0x00091A3C, 8 bytes (Ghidra-unlisted, between two small float
// getters): return the head of the shared map-object list read through the
// holder BfmeTheMapObjectListHolder (retail [0x00E00940], defined in
// GameLogicInit.cpp; W3DRoadBuffer::addMapObjects walks the same head). The
// Zero Hour counterpart is the static MapObject::getFirstMapObject inline;
// this copy's owner is not established, so the name is address-derived. No
// direct caller found.
class MapObject;

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/BfmeMapObjectListHolder.h"

extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;

MapObject *Rva00091A3CGetFirstMapObject(void)
{
	return BfmeTheMapObjectListHolder->m_head;
}
