// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Reference: Open-BFME-1 968ca36c3265b295297e6aed45a6bd89ffe59c40,
// game/GameEngine/Source/GameLogic/AI/PathfindLayerResetFull.cpp.
// Target identity: the adjacent verified PathfindLayer::getCell and
// DoBoundsOverlap bodies share cells +4, dimensions +8/+C and triggers +38.
// Target adaptation: bridge +34, triggers +38, trigger ID +3C; +2C becomes
// -1 and +30 is retained. The original name of this 66-byte wrapper and its
// 105-byte allocation-clear helper remain unknown.

void __cdecl operator delete(void *pointer);
void __cdecl operator delete[](void *pointer);

struct ICoord2D
{
	int x;
	int y;
};

// The primitive virtual order is measured by the rowed Common/System/Xfer.cpp
// providers: ICoord2D slot 19, int slot 31, bool slot 36. Version1 is the
// existing 23-byte provider at 0x000053EE. Other entries are ABI placeholders.
class Xfer
{
public:
	void Version1();
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual Xfer &xferICoord2D(ICoord2D &value);
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual Xfer &xferInt(int &value);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual Xfer &xferBool(bool &value);
};

class PathfindCell
{
public:
	void rva0052DED3();
	void rva0052D84C(Xfer *xfer);
private:
	unsigned char m_storage[0x10];
};

// Reuse the established provider's linker spelling for the native 75-byte
// vector destructor at 0x002E70E8 (16-byte elements, destructor 0x0052DD64).
// This adapter asserts that measured destruction ABI, not that pathfinding
// cells carry the provider's file-info payload identity.
class MixFileInfoBuffer;
class MixFileCreator
{
public:
	struct FileInfoStruct
	{
		~FileInfoStruct();
		MixFileInfoBuffer *m_buffer;
		unsigned long m_crc;
		unsigned long m_offset;
		unsigned long m_size;
	};
};

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
	void rva003666FD(Xfer *xfer);
private:
	void *m_blockOfMapCells;
	PathfindCell **m_layerCells;
	int m_width;
	int m_height;
	int m_xOrigin;
	int m_yOrigin;
	ICoord2D m_startCell;
	ICoord2D m_endCell;
	int m_layer;
	int m_zone;
	bool m_destroyed;
	unsigned char m_pad31[3];
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
	m_startCell.x = -1;
	m_startCell.y = -1;
	m_endCell.x = -1;
	m_endCell.y = -1;
	m_zone = -1;
	m_triggerObjectID = -1;
}

// Native 0x003667D4..0x0036683D, RET 0. Reference algorithm:
// game/GameEngine/Source/GameLogic/AI/PathfindLayerApplyZone.cpp bfmeReset
// at the same donor revision. Target adds the zone reset at +0x2C.
void PathfindLayer::rva003667D4()
{
	if (m_layerCells)
	{
		for (int i = 0; i < m_width; ++i)
		{
			for (int j = 0; j < m_height; ++j)
			{
				PathfindCell *cell = &m_layerCells[i][j];
				cell->rva0052DED3();
			}
		}
		delete[] m_layerCells;
		m_layerCells = 0;
	}
	if (m_blockOfMapCells)
		delete[] static_cast<MixFileCreator::FileInfoStruct *>(m_blockOfMapCells);
	m_zone = -1;
	m_blockOfMapCells = 0;
	m_width = 0;
	m_height = 0;
	m_xOrigin = 0;
	m_yOrigin = 0;
}

// Native 0x003666FD..0x003667D4, RET 4. Donor at the revision above:
// game/GameEngine/Source/GameLogic/AI/PathfindLayerXfer.cpp. Target uses the
// out-of-line Version1 helper, BFME2 primitive slots, bool +30 and ID +3C;
// the donor's additional field30 transfer is absent. Method name is unresolved.
void PathfindLayer::rva003666FD(Xfer *xfer)
{
	xfer->Version1();
	if (m_layerCells)
	{
		for (int x = 0; x < m_width; ++x)
		{
			for (int y = 0; y < m_height; ++y)
				m_layerCells[x][y].rva0052D84C(xfer);
		}
	}
	xfer->xferInt(m_width);
	xfer->xferInt(m_height);
	xfer->xferInt(m_xOrigin);
	xfer->xferInt(m_yOrigin);
	xfer->xferICoord2D(m_startCell);
	xfer->xferICoord2D(m_endCell);
	int layer = m_layer;
	xfer->xferInt(layer);
	xfer->xferInt(m_zone);
	xfer->xferBool(m_destroyed);
	xfer->xferInt(m_triggerObjectID);
}
