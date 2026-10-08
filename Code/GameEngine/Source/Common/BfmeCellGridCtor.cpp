// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
// ??0BfmeCellGrid@@QAE@HHMM@Z @0x0056C266 383B. CellGrid ctor (width,height,cellSize,offset).
// Evidence: donor reference/open-bfme-1/game/GameEngine/Source/GameLogic/System/CellGrid.cpp
// CellGrid::CellGrid plus CELL_GRID_ALLOCATION_FAILURE string
// "Could not create Cell Grid for VictorySystem!"; layout width+0 height+4 count+8
// size+0xC offset+0x10 cells+0x14 values+0x18 matches donor; element stride 0xA8
// is Rva00404781 (float[20]+float[20]+2 uints, ctor 0x00404AA5 via vector ctor,
// empty dtor folded at 0xB3FD0); callers at 0x00404EF4/0x00404F45.

void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *block);
extern "C" void *__cdecl memset(void *dst, int val, unsigned int n);
void _bfme_debugRecordCallsite(int kind);

class Rva00404781
{
public:
	Rva00404781();
	~Rva00404781();
	void rva0040475C();
	float m_a[20];
	float m_b[20];
	unsigned int m_flags0;
	unsigned int m_flags1;
};

// ??0Rva00404781@@QAE@XZ present-unmatched
Rva00404781::Rva00404781()
{
	rva0040475C();
}

// ??1Rva00404781@@QAE@XZ present-unmatched
Rva00404781::~Rva00404781()
{
}

class Debug
{
public:
	static bool SkipNext(bool skip);
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual Debug &slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(int report);
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual Debug &slot6C(int first, int second, int third);
};

extern Debug *theDebug;

class CellGrid
{
public:
	CellGrid(int width, int height, float cellSize, float offset);
	void rva0056C065();
private:
	int m_width;
	int m_height;
	unsigned int m_cellCount;
	float m_cellSize;
	float m_offset;
	Rva00404781 *m_cells;
	unsigned int *m_cellValues;
};

// BFME1 9cbfb551 BfmeCellGrid::_bfme_reset supplies the operation. Native
// 56C065..56C0A5 and WB1449F40 independently prove the field accesses and
// delete[] calls. The rowed BFME2 constructor proves 168-byte cells and
// the two owned buffers; the original cleanup method name is unresolved.
// ?rva0056C065@CellGrid@@QAEXXZ present-unmatched
void CellGrid::rva0056C065()
{
	if (m_cells) {
		delete[] m_cells;
		m_cells = 0;
	}
	m_width = 0;
	m_height = 0;
	m_cellCount = 0;
	m_offset = 0.0f;
	m_cellSize = 0.0f;
	if (m_cellValues) {
		delete[] m_cellValues;
		m_cellValues = 0;
	}
}

CellGrid::CellGrid(int width, int height, float cellSize, float offset)
{
	m_width = width;
	m_height = height;
	m_cellCount = width * height;
	m_cellSize = cellSize;
	m_offset = offset;
	m_cells = 0;
	if (m_cellCount != 0) {
		m_cells = new Rva00404781[m_cellCount];
		for (unsigned int cellIndex = 0; cellIndex < m_cellCount; ++cellIndex) {
			for (unsigned int playerIndex = 0; playerIndex < 20; ++playerIndex) {
				m_cells[cellIndex].m_a[playerIndex] = 0.0f;
				m_cells[cellIndex].m_b[playerIndex] = 0.0f;
			}
			m_cells[cellIndex].m_flags0 = 0;
			m_cells[cellIndex].m_flags1 = 0;
		}
		if (m_cells == 0) {
			_bfme_debugRecordCallsite(1);
			theDebug->slot60();
			theDebug->slot6C(0, 0, 0).slot38("Could not create Cell Grid for VictorySystem!").slot4C(1);
		}
		m_cellValues = new unsigned int[m_cellCount];
		if (m_cellValues == 0) {
			_bfme_debugRecordCallsite(1);
			theDebug->slot60();
			theDebug->slot6C(0, 0, 0).slot38("Could not create Cell Grid for VictorySystem!").slot4C(1);
		}
		memset(m_cellValues, 0, m_cellCount * sizeof(*m_cellValues));
	}
}
