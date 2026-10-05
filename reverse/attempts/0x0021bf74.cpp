// ?method@Rva0021BF74@@QAEHHHH@Z
// partial score=0.7 date=2026-10-05
// Family-5 indexed vector dispatchers (50B each): each holder method
// bounds-checks idx against (end-begin)>>5 of the raw vector at +0x14C and
// tail-calls the 32-byte element's two-int method, returning -1 when out of
// range. Elements and callees are opaque address-named pins; holder, vector
// and element identities are unproven.
struct RawVec32
{
	char *m_begin;
	char *m_end;
};

class Elem0021BF42
{
public:
	int g(int a, int b);
};

class Rva0021BF42
{
public:
	int method(int p1, int idx, int p3);
private:
	char m_pad[0x14C];
	RawVec32 m_vec; // +0x14C
};

int Rva0021BF42::method(int p1, int idx, int p3)
{
	if ((unsigned int)idx >= (unsigned int)((m_vec.m_end - m_vec.m_begin) >> 5))
		return -1;
	Elem0021BF42 *e = (Elem0021BF42 *)(m_vec.m_begin + (idx << 5));
	return e->g(p1, p3);
}

class Elem0021BF74
{
public:
	int g(int a, int b);
};

class Rva0021BF74
{
public:
	int method(int p1, int idx, int p3);
private:
	char m_pad[0x14C];
	RawVec32 m_vec; // +0x14C
};

int Rva0021BF74::method(int p1, int idx, int p3)
{
	if ((unsigned int)idx >= (unsigned int)((m_vec.m_end - m_vec.m_begin) >> 5))
		return -1;
	Elem0021BF74 *e = (Elem0021BF74 *)(m_vec.m_begin + (idx << 5));
	return e->g(p1, p3);
}

class Elem0021BFA6
{
public:
	int g(int a, int b);
};

class Rva0021BFA6
{
public:
	int method(int p1, int idx, int p3);
private:
	char m_pad[0x14C];
	RawVec32 m_vec; // +0x14C
};

int Rva0021BFA6::method(int p1, int idx, int p3)
{
	if ((unsigned int)idx >= (unsigned int)((m_vec.m_end - m_vec.m_begin) >> 5))
		return -1;
	Elem0021BFA6 *e = (Elem0021BFA6 *)(m_vec.m_begin + (idx << 5));
	return e->g(p1, p3);
}
