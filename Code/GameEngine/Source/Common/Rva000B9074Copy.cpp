// cl: /MD
//
// ??0Rva000B9074@@QAE@ABV0@@Z retail 0x000B9074 47B
// Copy constructor copying three dwords plus a byte then placement
// constructing the StringBase at +0x10 via the pinned copy ctor at
// 0x000365F0. Evidence: 2 small callers plus string-record neighbours.
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

Rva000B9074::Rva000B9074(const Rva000B9074 &o)
	: m_0(o.m_0)
	, m_4(o.m_4)
	, m_8(o.m_8)
	, m_C(o.m_C)
	, m_str10(o.m_str10)
{
}
