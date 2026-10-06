// cl: /MD /Oy-
// ??0Rva00331EAD@@QAE@HH@Z @0x00331EAD 36B
// 12-byte record ctor storing two ints then initing the freelist member at +8
// via rowed 0x29FB3B init with the dead-arg idiom ((char*)&a+3). Callers at
// 0x328ED and 0x32975 build a stack temp for vector search-insert.
class Rva0029FB3BMember
{
public:
	void *init(void *context);
};

class Rva00331EAD
{
	int m_00;
	int m_04;
	Rva0029FB3BMember m_08;

public:
	Rva00331EAD(int a, int b);
};

Rva00331EAD::Rva00331EAD(int a, int b)
{
	m_00 = a;
	m_04 = b;
	Rva0029FB3BMember *member = (Rva0029FB3BMember *)((char *)this + 8);
	void *context = (void *)((char *)&a + 3);
	member->init(context);
}
