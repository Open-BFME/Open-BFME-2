// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0040B1A8Fill@@YAPAVRva0040AEE3@@PAV1@IABV1@@Z @ 0x0040B1A8 (37B). Fill range of Rva0040AEE3 via Construct helper.
// Evidence: retail loops calling rowed ?Rva0040B14EConstruct 0x0040B14E stride 0x10 count in edi jbe; caller 0x0040B89F; neighbours share vector+int layout.
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

void __cdecl Rva0040B14EConstruct(Rva0040AEE3 *p, const Rva0040AEE3 &src);

Rva0040AEE3 *__cdecl Rva0040B1A8Fill(Rva0040AEE3 *first, unsigned int count, const Rva0040AEE3 &val)
{
	Rva0040AEE3 *cur = first;
	for (unsigned int n = count; n > 0; --n) {
		Rva0040B14EConstruct(cur, val);
		++cur;
	}
	return cur;
}
