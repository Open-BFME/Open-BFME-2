// cl: /DNDEBUG /MD /EHsc /Os
// ?update@Rva005EA454@@QAEXXZ @0x005EA454 27B
// Banked attempt reverse/attempts/0x005ea454.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
// ?update@Rva005EA454@@QAEXXZ, retail 0x005EA454, 27 bytes.
// Target evidence: calls the pinned 0x00574192 routine on this+0x08, reads a
// pointer at this+0x04, tests its dword at +0x10, then conditionally tail-jumps
// to 0x005EA125. These nested object roles are structural inferences; retain
// the address-derived owner name.

struct Rva00574192
{
	void rva00574192();
};

struct Rva005EA125
{
	void rva005EA125();
};

struct Rva005EA454Context
{
	unsigned char m_unmodelled_000[0x10];
	int m_flag;
};

struct Rva005EA454
{
	unsigned char m_unmodelled_000[0x04];
	Rva005EA454Context *m_context;

	void update();
};

void Rva005EA454::update()
{
	reinterpret_cast<Rva00574192 *>(reinterpret_cast<char *>(this) + 0x08)->rva00574192();
	if (m_context->m_flag != 0)
		return;
	reinterpret_cast<Rva005EA125 *>(m_context)->rva005EA125();
}
