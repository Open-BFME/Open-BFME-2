// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG
// Small bodies from .text gaps no Ghidra function covers (forty-first
// batch; see GapBodiesGE01.cpp), from the /O2 /arch:SSE /G7 retail region
// 0x001164F5..0x0012617B (reverse/retail_inventory/flag_regions.csv), plus two
// neighbours whose bytes show the same form. Each begins after its
// neighbour's padding or ret and ends in its own ret. Retail bytes establish
// every shape; owning classes are not recovered, so each keeps an
// address-derived name and a view of only the members it touches. Callees
// and globals use the ledger's existing spellings.

class Debug;
extern Debug *theDebug;

// --- 0x0011C300 (27B): forward three words to theDebug's slot 30 (+0x78).
class GapDebugView30
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29();
	virtual void slot30(int a, int b, int c);
};

void rva0011C300(int a, int b, int c)
{
	((GapDebugView30 *)theDebug)->slot30(a, b, c);
}

// --- 0x0010EFBD (16B): vtable 0x00BCFAA4 over a base that clears +4.
class GapClearedBase
{
public:
	GapClearedBase() : m_04(0) {}
	virtual ~GapClearedBase() {}
private:
	int m_04;
};

class Rva0010EFBD : public GapClearedBase
{
public:
	Rva0010EFBD();
	virtual ~Rva0010EFBD() {}
};

Rva0010EFBD::Rva0010EFBD()
{
}

// --- 0x001189C0 (45B): reset six render-state words.
extern int G00DEC4A8;
extern int G00DEC4A4;
extern int G00DEC4A0;
extern int G00DB5FBC;
extern int G00DB5FC0;
extern int G00DB5FC4;


// --- 0x0011C690 (28B): bounds-checked byte of the 0x76-entry +0x1B9 table.
class Rva0011C690
{
public:
	char rva0011C690(int i) const;
private:
	char m_pad00[0x1B9];
	char m_table[0x76];										// +0x1B9
};

char Rva0011C690::rva0011C690(int i) const
{
	if (i >= 0 && i < 0x76)
		return m_table[i];
	return 0;
}

// --- 0x00120670 / 0x00120690 (29B each), 0x001206B0 (26B): primitive draws
// through the rowed DX8Wrapper::Draw 0x001203C0: types 2, 3 and 1 with
// counts n*2, n+1 and n. Draw is private (as in ZH), so the callers are friends.
class DX8Wrapper
{
	friend void rva00120670(unsigned int start, unsigned int count);
	friend void rva00120690(unsigned int start, unsigned int count);
	friend void rva001206B0(unsigned int start, unsigned int count);
	static void Draw(unsigned int type, unsigned int a, unsigned int count, unsigned int start, unsigned int vertices, bool flag);
};

void rva00120670(unsigned int start, unsigned int count)
{
	DX8Wrapper::Draw(2, 0, count, start, count * 2, false);
}

void rva00120690(unsigned int start, unsigned int count)
{
	DX8Wrapper::Draw(3, 0, count, start, count + 1, false);
}

void rva001206B0(unsigned int start, unsigned int count)
{
	DX8Wrapper::Draw(1, 0, count, start, count, false);
}

// --- 0x0011F620 (19B): the DX8 device recursion depth when this thread
// owns the device, else the calling thread's id (rowed ThreadClass call).
class ThreadClass
{
public:
	static unsigned int _Get_Current_Thread_ID();
};

extern volatile unsigned long bfmeDX8DeviceOwner;
extern volatile int bfmeDX8DeviceRecursion;

unsigned int rva0011F620()
{
	unsigned int id = ThreadClass::_Get_Current_Thread_ID();
	if (id == bfmeDX8DeviceOwner)
		id = bfmeDX8DeviceRecursion;
	return id;
}

