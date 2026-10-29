// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport46
#include <memory>
//
// ??0Rva000BB491@@QAE@ABV0@@Z retail 0x000BB491 27B
// Derived copy constructor over the rowed Rva000B9074 base at +0 via its
// rowed copy ctor at 0x000B9074 plus an int tail at +0x14. Evidence:
// chain from 0x000B9074 plus 6 callers plus string-record neighbours.
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
	void releaseBuffer();
	~StringBase() { releaseBuffer(); }
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

class Rva000BB491 : public Rva000B9074
{
public:
	Rva000BB491(const Rva000BB491 &o);
	~Rva000BB491();
private:
	int m_14;
};

Rva000BB491::Rva000BB491(const Rva000BB491 &o)
	: Rva000B9074(o)
	, m_14(o.m_14)
{
}

// Native copy layout above and25B rangeBDD08 bind this string-only lifetime.
__declspec(noinline) inline Rva000BB491::~Rva000BB491() {}

// Native typed range teardown requires the real element destructor out of line.
template void _STL::_Destroy<Rva000BB491 *>(Rva000BB491 *, Rva000BB491 *);
