// ?method@Rva002E0B30@@QAE_NXZ
// partial score=0.8 date=2026-10-05
// Family-2 chained bool searches (70B each): each holder scans its pointer
// array and returns true on the first element whose predicate holds. The two
// 0x002B members call the fellow 0x002E members as their element predicate;
// the 0x002E members call a rowed (0x00318B94) or pinned (0x00318F42) leaf.
// Holder, element and predicate identities are unproven.
class Rva00318B94
{
public:
	unsigned char rva00318B94();
};

class Mbr002E0B30
{
public:
	unsigned char pred();
};

class Rva002E0AEA
{
public:
	bool method();
private:
	char m_pad[0x1B8];
	char *m_begin; // +0x1B8
	char *m_end; // +0x1BC
};

bool Rva002E0AEA::method()
{
	for (int i = 0; i < ((m_end - m_begin) >> 2); ++i)
		if (((Rva00318B94 **)m_begin)[i]->rva00318B94())
			return true;
	return false;
}

class Rva002E0B30
{
public:
	bool method();
private:
	char m_pad[0x1B8];
	char *m_begin; // +0x1B8
	char *m_end; // +0x1BC
};

bool Rva002E0B30::method()
{
	for (int i = 0; i < ((m_end - m_begin) >> 2); ++i)
		if (((Mbr002E0B30 **)m_begin)[i]->pred())
			return true;
	return false;
}

class Rva002B4B3D
{
public:
	bool method();
private:
	char m_pad[0x8C];
	char *m_begin; // +0x8C
	char *m_end; // +0x90
};

bool Rva002B4B3D::method()
{
	for (int i = 0; i < ((m_end - m_begin) >> 2); ++i)
		if (((Rva002E0AEA **)m_begin)[i]->method())
			return true;
	return false;
}

class Rva002B4B83
{
public:
	bool method();
private:
	char m_pad[0x8C];
	char *m_begin; // +0x8C
	char *m_end; // +0x90
};

bool Rva002B4B83::method()
{
	for (int i = 0; i < ((m_end - m_begin) >> 2); ++i)
		if (((Rva002E0B30 **)m_begin)[i]->method())
			return true;
	return false;
}
