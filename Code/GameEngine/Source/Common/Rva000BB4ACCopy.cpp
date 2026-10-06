// cl: /MD
//
// ??0Rva000BB4AC@@QAE@ABV0@@Z retail 0x000BB4AC 34B
// Copy constructor over the rowed Rva000B9074 base at +0 plus a refcounted
// pointer at +0x14 with AddRef at +0x2C. Evidence: chain from 0x000B9074
// plus 2 callers plus contiguous prev row 0x000BB491 in same page.
template <typename T>
class StringBase
{
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_data[1];
	};

	Header *m_data;

	StringBase(const StringBase &o);

	friend class Rva000B9074;
};

class Rva000B9074
{
public:
	Rva000B9074(const Rva000B9074 &o);
private:
	int m_0;
	int m_4;
	int m_8;
	unsigned char m_C;
	char m_padD[3];
	StringBase<char> m_str10;
};

class Rva000BB4ACRef
{
public:
	char m_pad[0x2C];
	int m_ref;
};

class Rva000BB4AC : public Rva000B9074
{
public:
	Rva000BB4AC(const Rva000BB4AC &o);
private:
	Rva000BB4ACRef *m_ptr;
};

Rva000BB4AC::Rva000BB4AC(const Rva000BB4AC &o)
	: Rva000B9074(o)
	, m_ptr(o.m_ptr)
{
	if (m_ptr)
		++m_ptr->m_ref;
}
