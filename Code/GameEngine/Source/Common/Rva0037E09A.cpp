// cl: /DNDEBUG /MD /EHsc
//
// ?rva0037E09A@Rva0037E09A@@QAE_NABV1@@Z, retail 0x0037E09A, 82 bytes.
// Equality over three ints plus wide and narrow StringBase compares plus a
// trailing byte. Evidence: caller 0x0037E0EC passes the +0x94 subobject by
// address; rowed compares 0x00006A7A wide and 0x000069D6 narrow.

template <typename T> class StringBase
{
	void *m_data;
public:
	int compare(const StringBase &other) const;
};

class Rva0037E09A
{
	int m_00; // +0x00
	int m_04; // +0x04
	int m_08; // +0x08
	StringBase<unsigned short> m_wide; // +0x0C
	StringBase<char> m_narrow; // +0x10
	unsigned char m_14; // +0x14
public:
	bool rva0037E09A(const Rva0037E09A &other);
};

bool Rva0037E09A::rva0037E09A(const Rva0037E09A &other)
{
	return m_00 == other.m_00 && m_04 == other.m_04 && m_08 == other.m_08 && m_wide.compare(other.m_wide) == 0 && m_narrow.compare(other.m_narrow) == 0 && m_14 == other.m_14;
}
