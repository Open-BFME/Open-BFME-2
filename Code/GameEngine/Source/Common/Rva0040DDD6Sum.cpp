// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0040DDD6@Rva0040DDD6@@QAEHXZ @0x0040DDD6 64B. Vector sum-and-erase: iterate
// backwards over m_vec at +0x40, skip entries whose pointee +0xC4 is 0, sum
// pointee +0x90, erase via rowed 0x0040DC1F. Evidence: 4-push erase shape,
// callers 0x003191B7, neighbours Rva0040DC1FErase and ModuleNameGetters.
struct Rva004F69C3
{
	int m_00;
	void *m_04;
	~Rva004F69C3();
};
namespace _STL {
template<class T> class allocator {};
template<class T, class A> class vector {
public:
	typedef T *iterator;
	iterator erase(iterator pos);
	T *m_start;
	T *m_finish;
	T *m_end;
};
}
struct Pointee090C4
{
	char m_pad[0x90];
	int m_90;
	char m_pad2[0xC4 - 0x90 - 4];
	unsigned char m_C4;
};
class Rva0040DDD6
{
public:
	int rva0040DDD6();
private:
	char m_pad[0x40];
	_STL::vector<Rva004F69C3, _STL::allocator<Rva004F69C3> > m_vec;
};
int Rva0040DDD6::rva0040DDD6()
{
	_STL::vector<Rva004F69C3, _STL::allocator<Rva004F69C3> > *vec = &m_vec;
	int n = vec->m_finish - vec->m_start;
	int sum = 0;
	for (int i = n - 1; i >= 0; --i) {
		if (((Pointee090C4*)m_vec.m_start[i].m_04)->m_C4 == 0)
			continue;
		sum += ((Pointee090C4*)m_vec.m_start[i].m_04)->m_90;
		m_vec.erase(&m_vec.m_start[i]);
	}
	return sum;
}
