// cl: /DNDEBUG /MD
// ?Rva0039BA22UninitCopy@@YAPAVRva0039B893@@PAV1@00ABU__false_type@_STL@@@Z @0x0039BA22 41B null-guarded uninitialized copy
// via placement new with rowed copy ctor 0x0039B893 and stride 0x14. Evidence: callers 0x0039C204 0x0039C252 push four args
// (first last result plus tag at ebp+0x1b) and clean 0x10; sibling fill_n at 0x0039B8D8 shares null guard and stride.

typedef int Int;
typedef short Short;

class Rva0039B893
{
public:
	Rva0039B893(const Rva0039B893 &other);
	Rva0039B893 &operator=(const Rva0039B893 &other);
	virtual ~Rva0039B893();

	Int m_field04;
	Int m_field08;
	Short m_field0C;
	Short m_field0E;
	Short m_field10;
};

inline void *__cdecl operator new(unsigned int, void *p) { return p; }

namespace _STL
{
struct __false_type {};
}

Rva0039B893 *__cdecl Rva0039BA22UninitCopy(Rva0039B893 *first, Rva0039B893 *last, Rva0039B893 *result, const _STL::__false_type &)
{
	Rva0039B893 *cur = result;
	for (; first != last; ++first, ++cur)
	{
		if (cur != 0)
			new (cur) Rva0039B893(*first);
	}
	return cur;
}
