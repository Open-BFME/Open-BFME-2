// cl: /DNDEBUG /MD /EHsc

// ?isInList@Object@@QBE_NPAPAV1@@Z, retail 0x0028B47C (31 bytes).
// Object::isInList checks the intrusive list links at +0x8C/+0x90.
// Evidence: BFME1 donor Object.cpp:3124 `Bool result = m_prev || m_next ||
// *pListHead == this`, and the sole retail caller GameLogic::friend_awakenUpdateModule
// (0x0024297F) passes &GameLogic+0xAC as pListHead with this=obj.
//
// 0x0028B4CE follows isInList and appendToList (0x0028B49B) in retail as
// setLayer does in Zero Hour's Object.cpp; its body changed shape in BFME,
// so the name stays address-derived.

typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class Object;

#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

// The object at Object+0xA4 (see ObjectRvaSmallGetters.cpp).
class PathfinderPosGoalManager
{
public:
	bool rva004DE2ED();	// rowed 0x004DE2ED returns bool; this caller ignores it
};

class Object
{
public:
	Bool isInList(Object **pListHead) const;
	void appendToList(Object **pListHead, Object **pListTail);
	void setLayer(PathfindLayerEnum layer);

private:
	unsigned char m_pre[0x8C];
	Object *m_next; // +0x8C
	Object *m_prev; // +0x90
	unsigned char m_pad94[0xA4 - 0x94];
	PathfinderPosGoalManager *m_a4; // +0xA4
	unsigned char m_padA8[0x40C - 0xA8];
	PathfindLayerEnum m_layer; // +0x40C
};

Bool Object::isInList(Object **pListHead) const
{
	Bool result = m_prev || m_next || *pListHead == this;
	return result;
}

// ?appendToList@Object@@QAEXPAPAV1@0@Z, retail 0x0028B49B (51B).
// Name, file and statement order from the WorldBuilder debug build
// (0xCD0980, Object.cpp:5969..5978): the asserts there name pListTail and
// m_prev->m_next, fixing +0x90 as m_prev and +0x8C as m_next. Retail loads
// *pListTail before clearing m_next, so m_prev is assigned first.
void Object::appendToList(Object **pListHead, Object **pListTail)
{
	m_prev = *pListTail;
	m_next = 0;
	if (m_prev)
		m_prev->m_next = this;
	if (*pListHead == 0)
		*pListHead = this;
	*pListTail = this;
}

// ?setLayer@Object@@QAEXW4PathfindLayerEnum@@@Z, retail 0x0028B4CE (67B):
// the +0x40C layer setter in setLayer's position. On a change away from a
// non-ground layer it calls TheTerrainLogic's slot 43 with (this, old
// layer, true) - the arguments of Zero Hour's debug-only
// objectInteractsWithBridgeLayer check - then stores the layer and notifies
// the Object+0xA4 object through the pinned 0x004DE2ED.
void Object::setLayer(PathfindLayerEnum layer)
{
	if (layer != m_layer)
	{
		if (m_layer != LAYER_GROUND)
			TheTerrainLogic->objectInteractsWithBridgeLayer(this, m_layer, true);
		m_layer = layer;
		if (m_a4)
			m_a4->rva004DE2ED();
	}
}
