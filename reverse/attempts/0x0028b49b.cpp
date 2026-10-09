// ?appendToList@Object@@QAEXPAPAV1@0@Z
// partial score=0.85 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc

// ?isInList@Object@@QBE_NPAPAV1@@Z, retail 0x0028B47C (31 bytes).
// Object::isInList checks the intrusive list links at +0x8C/+0x90.
// Evidence: BFME1 donor Object.cpp:3124 `Bool result = m_prev || m_next ||
// *pListHead == this`, and the sole retail caller GameLogic::friend_awakenUpdateModule
// (0x0024297F) passes &GameLogic+0xAC as pListHead with this=obj.
//
// 0x0028B4CE follows isInList and BFME's two-list prepend 0x0028B49B in
// retail as setLayer does in Zero Hour's Object.cpp; its body changed shape
// in BFME, so the name stays address-derived.

typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class Object;

class TerrainLogic
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(); virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(); virtual void vslot13(); virtual void vslot14(); virtual void vslot15();
	virtual void vslot16(); virtual void vslot17(); virtual void vslot18(); virtual void vslot19();
	virtual void vslot20(); virtual void vslot21(); virtual void vslot22(); virtual void vslot23();
	virtual void vslot24(); virtual void vslot25(); virtual void vslot26(); virtual void vslot27();
	virtual void vslot28(); virtual void vslot29(); virtual void vslot30(); virtual void vslot31();
	virtual void vslot32(); virtual void vslot33(); virtual void vslot34(); virtual void vslot35();
	virtual void vslot36(); virtual void vslot37(); virtual void vslot38(); virtual void vslot39();
	virtual void vslot40(); virtual void vslot41(); virtual void vslot42();
	virtual Bool vslot43(Object *obj, int layer, Bool flag);
};
extern TerrainLogic *TheTerrainLogic;

// The object at Object+0xA4 (see ObjectRvaSmallGetters.cpp).
class Rva004DD843
{
public:
	void rva004DE2ED();
};

class Object
{
public:
	Bool isInList(Object **pListHead) const;
	void appendToList(Object **pListHead, Object **pListTail);
	void rva0028B4CE(PathfindLayerEnum layer);

private:
	unsigned char m_pre[0x8C];
	Object *m_next; // +0x8C
	Object *m_prev; // +0x90
	unsigned char m_pad94[0xA4 - 0x94];
	Rva004DD843 *m_a4; // +0xA4
	unsigned char m_padA8[0x40C - 0xA8];
	PathfindLayerEnum m_layer; // +0x40C
};

Bool Object::isInList(Object **pListHead) const
{
	Bool result = m_prev || m_next || *pListHead == this;
	return result;
}

// ?appendToList@Object@@QAEXPAPAV1@0@Z, retail 0x0028B49B (51B): BFME's
// head/tail form of Zero Hour's Object::prependToList. Its only retail caller
// GameLogic::registerObject (0x00242AE9) passes &GameLogic+0xAC / +0xB0; the
// new object is linked after the old tail and becomes the head of an empty list.
void Object::appendToList(Object **pListHead, Object **pListTail)
{
	Object *tail = *pListTail;
	m_next = 0;
	Object *&prev = m_prev;
	prev = tail;
	if (prev)
		prev->m_next = this;

	if (*pListHead == 0)
		*pListHead = this;
	*pListTail = this;
}

// ?rva0028B4CE@Object@@QAEXW4PathfindLayerEnum@@@Z, retail 0x0028B4CE (67B):
// the +0x40C layer setter in setLayer's position. On a change away from a
// non-ground layer it calls TheTerrainLogic's slot 43 with (this, old
// layer, true) - the arguments of Zero Hour's debug-only
// objectInteractsWithBridgeLayer check - then stores the layer and notifies
// the Object+0xA4 object through the pinned 0x004DE2ED.
void Object::rva0028B4CE(PathfindLayerEnum layer)
{
	if (layer != m_layer)
	{
		if (m_layer != LAYER_GROUND)
			TheTerrainLogic->vslot43(this, m_layer, true);
		m_layer = layer;
		if (m_a4)
			m_a4->rva004DE2ED();
	}
}
