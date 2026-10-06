// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ??0Rva000D3A17@@QAE@XZ @0x000D3A8A 157B
// Evidence: chain from rowed 0x000D3A17 which this ctor calls with rowed 0x000D1C83
// two ehvec_ctor arrays at +0x18 +0x94 10x0xC then zeroes +0x00..+0x0C stamps
// +0x10=0x7530 +0x14=0xEA60 clears first-dword loop then helpers then flag
// +0x10C=1. Caller 0x0006CD0F.

struct Rva000D3A8AElemA
{
	Rva000D3A8AElemA();
	~Rva000D3A8AElemA();
	void *m_ptr; // +0x00
	int m_04; // +0x04
	int m_08; // +0x08
};

struct Rva000D3A8AElemB
{
	Rva000D3A8AElemB();
	~Rva000D3A8AElemB();
	void *m_head; // +0x00
	int m_04; // +0x04
	int m_08; // +0x08
};

class Rva000D1C83
{
public:
	void rva000D1C83();
};

class Rva000D3A17
{
public:
	Rva000D3A17();
	void rva000D3A17();

private:
	void *m_00; // +0x00
	void *m_04; // +0x04
	int m_08; // +0x08
	int m_0c; // +0x0C
	int m_10; // +0x10
	int m_14; // +0x14
	Rva000D3A8AElemA m_refs[10]; // +0x18
	int m_90; // +0x90
	Rva000D3A8AElemB m_sets[10]; // +0x94
	unsigned char m_10c; // +0x10C
};

Rva000D3A17::Rva000D3A17()
{
	m_10c = 0;
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0c = 0;
	m_14 = 0xea60;
	m_10 = 0x7530;
	for (int i = 0; i < 10; ++i)
		m_refs[i].m_ptr = 0;
	rva000D3A17();
	((Rva000D1C83 *)this)->rva000D1C83();
	m_10c = 1;
}
