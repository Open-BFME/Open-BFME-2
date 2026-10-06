// ?rva0040C0FE@Rva0040AAD5@@QAE_NABURva0040C0C7Element@@@Z
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0040C0FE@Rva0040AAD5@@QAE_NABURva0040C0C7Element@@@Z, retail 0x0040C0FE 39B:
// Rva0040AAD5 add-unique: search vector at +0xC by first-field key via rowed 0x0040AAD5;
// when missing push the 40B element via rowed push_back 0x0040C0C7 and answer true,
// else false. Unlocks 0x0040C125.
//
// Evidence: unlock lane; callee rva0040AAD5 0x0040AAD5 (same this, int key [edi]) and
// push_back 0x0040C0C7 (vector at this+0xC, element edi); caller unclaimed 0x0040C125;
// layout as stlport_pod_vector_bodies.cpp (vector at +0xC, 40B stride).
namespace _STL
{
template <class T> class allocator {};
template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &e);
};
}
struct BfmePod40
{
	int a[10];
};
struct Rva0040C0C7Element
{
	int m_00;
	int m_pad[9];
};
class Rva0040AAD5
{
public:
	BfmePod40 *rva0040AAD5(int key);
	bool rva0040C0FE(const Rva0040C0C7Element &elem);
private:
	int m_pad00[3];
	_STL::vector<Rva0040C0C7Element> m_vec0C;
};
bool Rva0040AAD5::rva0040C0FE(const Rva0040C0C7Element &elem)
{
	if (rva0040AAD5(elem.m_00) == 0)
	{
		_STL::vector<Rva0040C0C7Element> *vec =
			(_STL::vector<Rva0040C0C7Element> *)((char *)this + 0x0C);
		vec->push_back(elem);
		return true;
	}
	return false;
}
