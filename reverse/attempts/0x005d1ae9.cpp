// ?rva005D1AE9@Rva005D1AE9@@QAEXXZ
// partial score=0.9 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva005D1AE9@Rva005D1AE9@@QAEXXZ @0x005D1AE9 24B.
// Calls empty 0x00B3FD0 (reuses pinned empty), loads bool via +0x10->+0x1C
// with mov-al shape, then calls pinned 0x005CCB7B (void,int) with it.
// Ret void, this only. Address-derived.
class Rva000B3FD0Empty
{
public:
	void rva000B3FD0Empty();
};

class Rva005CCB7B
{
public:
	void rva005CCB7B(bool b);
};

struct Rva005D1AE9Mid
{
	unsigned char m_pad[0x1C];
	bool m_1C;
};

class Rva005D1AE9
{
public:
	void rva005D1AE9();
protected:
	unsigned char m_pad[0x10];
	Rva005D1AE9Mid *m_10;
};

void Rva005D1AE9::rva005D1AE9()
{
	((Rva000B3FD0Empty *)this)->rva000B3FD0Empty();
	bool b = m_10->m_1C;
	((Rva005CCB7B *)this)->rva005CCB7B(b);
}
