// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva002A77C1@Rva002A7611Holder@@QAEXHW4ObjectID@@PBX@Z @0x002A77C1 87B.
// Rva002A7611Holder::rva002A77C1(int value, ObjectID id, const void *block):
// add twin of 0x002A7611 remove. Constructs a 12-byte record at [ebp-0x18]
// via rowed ??0Rva002A7400, fills value/id/*block, push_backs it into the
// +0x20 vector (rowed _STL push_back 0x002A778D), then releases the local's
// +8 filter via rowed ??1Rva00360D26Member. Evidence: sole caller
// CommandPointsUpgrade::upgradeImplementation 0x004B86AE passes
// data+0x118/id/&data+0x11C; holder layout +0x20 vector from twin
// Rva002A7611Remove.cpp; element 12B from retail frame.
enum ObjectID
{
	INVALID_ID = 0
};

class Rva00360D26Member
{
public:
	~Rva00360D26Member();
	unsigned int m_handle;
};

class Rva002A7400
{
public:
	Rva002A7400();
	int m_value;
	ObjectID m_id;
	Rva00360D26Member m_filter;
};

struct Rva002A76A0Element
{
	int m_value;
	ObjectID m_id;
	Rva00360D26Member m_filter;
};

namespace _STL
{
template <typename T> class allocator
{
};
template <typename T, typename U> class vector
{
public:
	void push_back(const T &item);
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class Rva002A7611Holder
{
public:
	void rva002A77C1(int value, ObjectID id, const void *block);
private:
	unsigned char m_pad[0x20];
	_STL::vector<Rva002A76A0Element, _STL::allocator<Rva002A76A0Element> > m_vec;
};

void Rva002A7611Holder::rva002A77C1(int value, ObjectID id, const void *block)
{
	Rva002A7400 tmp;
	tmp.m_id = id;
	tmp.m_value = value;
	tmp.m_filter.m_handle = *(const unsigned int *)block;
	m_vec.push_back(*(const Rva002A76A0Element *)&tmp);
}
