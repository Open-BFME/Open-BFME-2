// cl: /O1 /MD /G7
// ?rva005328E2@PathfindZoneManager@@QAEXPAURva005312BERect@@@Z @ 0x005328E2 (230B): __thiscall grid alloc outer/inner from rect, new Item[outer*inner] + new Item*[outer], fill row pointers, set flag at +0x1BA31.
// Evidence: offsets 0x1BA34/0x1BA38/0x1BA3C/0x1BA40 shared with Rva005312BEClear.cpp siblings; rect 16B copy to +0x1BA44 matches Rva005312BERect x0/y0/x1/y1; (x1-x0+16)/16 + (y1-y0+16)/16 via idiv 16; 0x44 elt with eh-vector ctor; caller at 0x002E8E8E.
class Rva00531132
{
public:
	void rva00531132(bool add, int value);
	int rva0053117F(int index);
	int m_count;
	int m_items[12];
};
void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *p);
extern "C" void __cdecl free(void *block);
class Rva005312BEItem
{
public:
	Rva005312BEItem();
	~Rva005312BEItem();
	Rva00531132 m_set;
	unsigned char m_cleared;
	unsigned char m_35;
	char m_pad36[2];
	void *m_p38;
	char m_pad3C[0x44 - 0x3C];
};
// ??0Rva005312BEItem@@QAE@XZ present-unmatched
Rva005312BEItem::Rva005312BEItem()
{
	m_set.m_count = 0;
	m_cleared = 0;
	m_35 = 0;
}
Rva005312BEItem::~Rva005312BEItem()
{
	if (m_p38 != 0)
		free(m_p38);
}
struct Rva005312BERect
{
	int x0;
	int y0;
	int x1;
	int y1;
};
class PathfindZoneManager
{
public:
	void rva005328E2(Rva005312BERect *r);
	char m_pad[0x1BA30];
	unsigned char m_flag1BA30;
	unsigned char m_flag1BA31;
	char m_pad3[0x1BA34 - 0x1BA32];
	Rva005312BEItem *m_pData;
	Rva005312BEItem **m_ppItems;
	int m_outer;
	int m_inner;
	Rva005312BERect m_rect;
};
void PathfindZoneManager::rva005328E2(Rva005312BERect *r)
{
	m_rect = *r;
	m_outer = (r->x1 - r->x0 + 16) / 16;
	m_inner = (r->y1 - r->y0 + 16) / 16;
	int total = m_outer * m_inner;
	m_pData = new Rva005312BEItem[total];
	m_ppItems = (Rva005312BEItem **)new unsigned char[m_outer * 4];
	for (int i = 0; i < m_outer; ++i)
		m_ppItems[i] = m_pData + i * m_inner;
	m_flag1BA31 = 1;
}
