// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0040B218Copy@@YAPAVRva0040AEE3@@PAV1@00@Z @ 0x0040B218 (47B). Copy range of Rva0040AEE3 via operator=.
// Evidence: retail computes (last-first)>>4 then loops calling rowed ??4Rva0040AEE3 0x0040AEFE; caller 0x0040B350 passes 5 args (tag+0) proving __copy shape; stride 0x10 from vector+int layout.
#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};

class Rva0040AEE3
{
public:
	Rva0040AEE3(const Rva0040AEE3 &other);
	Rva0040AEE3 &operator=(const Rva0040AEE3 &other);
private:
	_STL::vector<ScienceType> m_0000;
	int m_000C;
};

Rva0040AEE3 *__cdecl Rva0040B218Copy(Rva0040AEE3 *first, Rva0040AEE3 *last, Rva0040AEE3 *result)
{
	for (int n = last - first; n > 0; --n) {
		*result = *first;
		++first;
		++result;
	}
	return result;
}
