// ?rva00709C10@Rva00709C10Owner@@QAEXHPAVRva8D0D80ValueOwner@@@Z
// partial score=0.92 date=2026-10-04
// ?rva00709C10@Rva00709C10Owner@@QAEXPAVRva8D0D80ValueOwner@@H@Z
// cl: /O2 /MD
// 0x00709C10 (129 bytes). SEH-framed Apt handler: publishes the global result
// table if not live, copies the argument-indexed name out of the owner's +0x30
// table into an EAStringC, and adds that name and its data to the global table.
//
// Identity correction: retail reads the *index* from [esp+0x1C] and the *value*
// from [esp+0x18], so the true parameter order is (value, index), not the
// (index, value) the address-derived label carried. The corrected symbol is
// ?rva00709C10@Rva00709C10Owner@@QAEXPAVRva8D0D80ValueOwner@@H@Z.
//
// Callees: 0x006FBED0 ?rva006FBED0@Rva8D0D80Result@@QAEXXZ lazy publisher,
// 0x006D4C80 EAStringC(char*) ctor, 0x0070B410 Rva8D0D80Table::add,
// 0x006D3010 EAStringC dtor.
class Rva8D0D80String;
class Rva8D0D80Value;

class EAStringC
{
public:
	EAStringC(const char *s);
	~EAStringC();

private:
	char *m_data;
};

class Rva8D0D80Table
{
public:
	void add(Rva8D0D80String *name, Rva8D0D80Value *value);
};

class Rva8D0D80ResultTableBlock
{
public:
	char m_pad08[8];
	Rva8D0D80Table m_table;
};

extern Rva8D0D80ResultTableBlock *g_rva00E1835C;

class Rva8D0D80Result
{
public:
	void rva006FBED0();
};

class Rva8D0D80ValueOwner;

class Rva00709C10Owner
{
public:
	void rva00709C10(Rva8D0D80ValueOwner *value, int index);

private:
	char m_pad[0x30];
	char *m_names;
};

struct Rva00709C10NameBlock
{
	char m_pad[8];
	char **m_rows;
};

void Rva00709C10Owner::rva00709C10(Rva8D0D80ValueOwner *value, int index)
{
	if (g_rva00E1835C == 0)
		reinterpret_cast<Rva8D0D80Result *>(this)->rva006FBED0();

	char *const name_text = reinterpret_cast<const Rva00709C10NameBlock *>(m_names)->m_rows[index];

	EAStringC name(name_text);

	g_rva00E1835C->m_table.add((Rva8D0D80String *)&name, (Rva8D0D80Value *)value);
}
