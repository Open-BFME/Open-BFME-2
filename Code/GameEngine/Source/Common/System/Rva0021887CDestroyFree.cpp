// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva0021887C@Rva0021887C@@QAEXXZ @0x0021887C 30B: destroy GeometryRecord range then free storage.
// Evidence: pushes [this+4]/[this] to rowed _Destroy<GeometryRecord*> 0x00217B1E; reloads [this] and frees via rowed free 0x00030830; callers 0x00218B20/0x0006454B.
// ?rva0021887C@Rva0021887C@@QAEXXZ @0x0021887C present-unmatched
struct GeometryRecord;

namespace _STL
{
template <class T> void _Destroy(T first, T last);
}

extern "C" void __cdecl free(void *ptr);

class Rva0021887C
{
public:
	void rva0021887C();
private:
	GeometryRecord *m_first;
	GeometryRecord *m_last;
};

void Rva0021887C::rva0021887C()
{
	_STL::_Destroy(m_first, m_last);
	GeometryRecord *first = m_first;
	if (first != 0)
		free(first);
}
