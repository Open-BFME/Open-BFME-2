// cl: /MD
// ?Rva00396943Construct@@YA?AURva0039627D@@PAPAXABUBfmeStringRecord004071F7@@@Z @0x00396943 27B
// Chain from 0x0039627D: by-value return (hidden dst pointer at [ebp+8]).
// Caller at 0x003998D7 does call/add esp,0xc/push eax (hidden + 2 args).
// Callee rowed in Rva0039627DCtor.cpp.
struct BfmeStringRecord004071F7 {
	unsigned char m_body[12];
	BfmeStringRecord004071F7(const BfmeStringRecord004071F7 &other);
	~BfmeStringRecord004071F7();
};

struct Rva0039627D {
	void *m_00;
	BfmeStringRecord004071F7 m_04;
	Rva0039627D(void **p, const BfmeStringRecord004071F7 &rec);
};

struct Rva0039627D __cdecl Rva00396943Construct(void **p, const struct BfmeStringRecord004071F7 &rec)
{
	return Rva0039627D(p, rec);
}
