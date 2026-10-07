// ?rva002F462C@Pathfinder@@QAEXXZ
// partial score=0.95 date=2026-10-07
// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
// ?rva002F462C@Pathfinder@@QAEXXZ @0x002F462C 338B
// evidence: unlock callers 0x002F6F06 plus 0x002FEB41 via AI plus 0x10; rowed Pathfinder 0x002F40E7 plus 0x002F370D; Path dtor 0x00364A89; layer reset 0x00366DEC 16 layers; zone reset 0x005335D3
class Path
{
public:
	~Path();
};

class PathfindLayer
{
public:
	void rva00366DEC();
};

class PathfindZoneManager
{
public:
	void rva005335D3();
};

class Rva002EE9B7
{
public:
	void rva002EE9B7();
};

void __cdecl operator delete(void *p);
void __cdecl operator delete[](void *p);

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

struct ListNode5C
{
	virtual void *func(int);
	ListNode5C *m_next;
};

struct ListNode3C
{
	virtual void *func(int);
	char m_pad04[0x38];
	ListNode3C *m_next;
};

class Pathfinder
{
public:
	int rva002F40E7();
	int rva002F370D();
	void rva002F462C();

private:
	char m_pad00[0x8];
	bool m_08;
	char m_pad09[0x3];
	MixFileCreator::FileInfoStruct *m_0C;
	char *m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	bool m_38;
	char m_pad39[0x3];
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	float m_4C;
	float m_50;
	float m_54;
	Path *m_58;
	ListNode5C *m_5C;
	char m_pad60[0x400];
	char m_pad460[0x1BEB4 - 0x460];
	bool m_1BEB4;
	bool m_1BEB5;
	bool m_1BEB6;
	char m_pad1BEB7;
	int m_1BEB8;
	float m_1BEBC[0x40];
	char m_pad1BFBC[0x1C0BC - 0x1BFBC];
	ListNode3C *m_1C0BC[0x40];
	char m_pad1C1BC[0x1C9E0 - 0x1C1BC];
	int m_1C9E0;
	int m_1C9E4;
	char m_pad1C9E8[0x1D1E8 - 0x1C9E8];
	int m_1D1E8;
	int m_1D1EC;
};

void Pathfinder::rva002F462C()
{
	m_08 = false;
	rva002F40E7();
	if (m_0C != 0)
		delete[] m_0C;
	m_0C = 0;
	delete[] m_10;
	m_10 = 0;
	m_20 = 0;
	m_1C = 0;
	m_18 = 0;
	m_14 = 0;
	m_30 = 0;
	m_2C = 0;
	m_28 = 0;
	m_24 = 0;
	rva002F370D();
	m_34 = 0;
	m_3C = 0;
	m_40 = 0;
	m_44 = 0;
	m_48 = 0;
	m_4C = 0.0f;
	m_50 = 0.0f;
	m_54 = 0.0f;
	if (m_58 != 0)
		delete m_58;
	ListNode5C *head = m_5C;
	m_58 = 0;
	while (head != 0)
	{
		ListNode5C *next = head->m_next;
		head->m_next = 0;
		operator delete(head->func(0));
		head = next;
	}
	m_5C = 0;
	for (int i = 0; i < 0x10; i++)
		((PathfindLayer *)((char *)this + 0x60 + i * 0x40))->rva00366DEC();
	((PathfindZoneManager *)((char *)this + 0x460))->rva005335D3();
	m_1BEB4 = false;
	m_1BEB5 = false;
	m_1BEB6 = false;
	((Rva002EE9B7 *)((char *)this + 0x1C1C0))->rva002EE9B7();
	m_1BEB8 = 0;
	for (int i = 0; i < 0x40; i++)
	{
		ListNode3C *h = m_1C0BC[i];
		m_1BEBC[i] = 0.0f;
		while (h != 0)
		{
			ListNode3C *n = h->m_next;
			h->m_next = 0;
			operator delete(h->func(0));
			h = n;
		}
		m_1C0BC[i] = 0;
	}
	m_1D1EC = 0;
	m_1D1E8 = 0;
	m_1C9E4 = 0;
	m_1C9E0 = 0;
	m_38 = false;
	*(int *)((char *)this + 0x1C1BC) = 0;
}
