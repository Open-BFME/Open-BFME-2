// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00357E14@Rva00357E14@@QAEXABUBfmeFloat4Record00469C61@@@Z, retail 0x00357E14 28B chain.
// Evidence: rowed list<BfmeFloat4Record> insert 0x1DD86F, begin double-deref shape.
#include <list>

struct BfmeFloat4Record00469C61
{
	unsigned char m_data[16];
};

bool operator==(const BfmeFloat4Record00469C61 &, const BfmeFloat4Record00469C61 &);
bool operator<(const BfmeFloat4Record00469C61 &, const BfmeFloat4Record00469C61 &);

class Rva00357E14
{
public:
	void rva00357E14(const BfmeFloat4Record00469C61 &rec);

private:
	_STL::list<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> > m_list; // +0
};

void Rva00357E14::rva00357E14(const BfmeFloat4Record00469C61 &rec)
{
	m_list.insert(m_list.begin(), rec);
}
