// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Reference: Open-BFME-1 968ca36c3265b295297e6aed45a6bd89ffe59c40,
// game/GameEngine/Source/GameLogic/AI/PathfindLayerResetFull.cpp.
// Target identity: the adjacent verified PathfindLayer::getCell and
// DoBoundsOverlap bodies share cells +4, dimensions +8/+C and triggers +38.
// Target adaptation: bridge +34, triggers +38, trigger ID +3C; +2C becomes
// -1 and +30 is retained. The original name of this 66-byte wrapper and its
// 105-byte allocation-clear helper remain unknown.

void __cdecl operator delete(void *pointer);

// Native vslot zero is called with flags zero; its returned pointer is
// passed to the rowed global operator delete. Only that ABI is asserted.
class Rva00366DECVirtual
{
public:
	virtual void *slot0(unsigned int flags);
};

class PathfindLayer
{
public:
	void rva00366DEC();
	void rva003667D4();
private:
	unsigned char m_head[0x18];
	int m_startX;
	int m_startY;
	int m_endX;
	int m_endY;
	int m_layer;
	int m_zone;
	int m_unknown30;
	void *m_bridge;
	Rva00366DECVirtual *m_triggers;
	int m_triggerObjectID;
};

// Native 0x00366DEC..0x00366E2E, RET 0.
void PathfindLayer::rva00366DEC()
{
	m_bridge = 0;
	rva003667D4();
	m_layer = 1;
	if (m_triggers)
		::operator delete(m_triggers->slot0(0));
	m_triggers = 0;
	m_startX = -1;
	m_startY = -1;
	m_endX = -1;
	m_endY = -1;
	m_zone = -1;
	m_triggerObjectID = -1;
}
