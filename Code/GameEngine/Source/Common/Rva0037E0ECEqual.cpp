// cl: /DNDEBUG /MD /EHsc
//
// ?Rva0037E0ECEqual@@YA_NPBX0@Z, retail 0x0037E0EC, 114 bytes.
// Equality over float plus AsciiString plus 0x80-byte helper plus two ints
// plus the +0x94 Rva0037E09A subobject. Evidence: calls rowed compare
// 0x000069D6 and rowed 0x0037DC8AEqual and just-landed 0x0037E09A.

template <typename T> class StringBase
{
	void *m_data;
public:
	int compare(const StringBase &other) const;
};

class Rva0037E09A
{
	int m_00;
	int m_04;
	int m_08;
	StringBase<unsigned short> m_wide;
	StringBase<char> m_narrow;
	unsigned char m_14;
public:
	bool rva0037E09A(const Rva0037E09A &other);
};

bool __cdecl Rva0037DC8AEqual(const void *a, const void *b);

struct Rva0037E0ECOuter
{
	char m_pad00[4]; // +0x00
	StringBase<char> m_s04; // +0x04
	float m_f08; // +0x08
	int m_c0C; // +0x0C
	char m_h10[0x80]; // +0x10
	int m_90; // +0x90
	Rva0037E09A m_94; // +0x94
};

bool __cdecl Rva0037E0ECEqual(const void *a, const void *b)
{
	Rva0037E0ECOuter *lhs = (Rva0037E0ECOuter *)a;
	Rva0037E0ECOuter *rhs = (Rva0037E0ECOuter *)b;
	return lhs->m_f08 == rhs->m_f08 && lhs->m_s04.compare(rhs->m_s04) == 0 && Rva0037DC8AEqual(&lhs->m_h10, &rhs->m_h10) && lhs->m_c0C == rhs->m_c0C && lhs->m_90 == rhs->m_90 && lhs->m_94.rva0037E09A(rhs->m_94);
}
