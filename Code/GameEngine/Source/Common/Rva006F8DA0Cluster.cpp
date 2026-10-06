// cl: /MD /Oy /EHs
//
// ??1Rva006F8D70@@UAE@XZ @0x006F8DA0 103B: complete destructor of the
// Rva006F8D70 family (vtable 0x008EC9CC, deleting dtor 0x006F8D70, size 0x20).
// Target evidence: destroys the sub-object at +0x1C through the pinned
// destructor 0x006F84F0, stores the shared vtable 0x008EC9CC (DIR32, masked),
// then destroys the +0x10 pointer through rowed 0x0070A840 and releases it
// with size 0x14 through the pinned 0xE176E8 pool. The base sub-object body is
// the rowed Rva006F8460 dtor at 0x006F8460 and is inlined here; the base is
// renamed Rva006F8460Base so this TU does not re-emit that rowed symbol.
// /Oy is what the bytes force: retail carries the frame-pointer-less manual
// SEH prolog (`push -1 / push scope / mov eax,fs:[0]`) and no ebp frame.
// Names are address-derived; the near file's Rva006DE350 scaffold is only the
// deleting-dtor recipe and does not describe these members.

class Rva0070A840
{
public:
	~Rva0070A840();
};

class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

#define ThePool (*(Rva006DB270 *const *)0x00E176E8)

class Rva006F84F0
{
public:
	~Rva006F84F0();
};

class Rva006F8460Base
{
public:
	virtual ~Rva006F8460Base()
	{
		Rva0070A840 *p = m_10;
		if (p != 0) {
			p->~Rva0070A840();
			ThePool->freeBlock(p, 0x14);
		}
	}

private:
	char m_pad[0x0C];
	Rva0070A840 *m_10;
};

class __declspec(novtable) Rva006F8D70 : public Rva006F8460Base
{
public:
	virtual ~Rva006F8D70();

private:
	char m_pad14[0x8];
	Rva006F84F0 m_1c;
};

Rva006F8D70::~Rva006F8D70()
{
}
