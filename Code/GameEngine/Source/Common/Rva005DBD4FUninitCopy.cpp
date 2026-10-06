// cl: /DNDEBUG /MD
// ?Rva005DBD4FUninitCopy@@YAPAVRva005DBCD1@@PAV1@00ABU__false_type@_STL@@@Z @0x005DBD4F 41B null-guarded uninitialized copy
// via placement new with rowed copy ctor 0x005DBCD1 and stride 8. Evidence: callers 0x005DC4D7 0x005DC525 push four args
// (first last result plus tag at ebp+0x1b) and clean 0x10; sibling fill_n at 0x005DBD78 shares null guard and stride.
class Rva005DBCD1
{
public:
	Rva005DBCD1(const Rva005DBCD1 &other);
	virtual ~Rva005DBCD1();
	short m_field04;
	short m_field06;
};

inline void *__cdecl operator new(unsigned int, void *p) { return p; }

namespace _STL
{
struct __false_type {};
}

Rva005DBCD1 *__cdecl Rva005DBD4FUninitCopy(Rva005DBCD1 *first, Rva005DBCD1 *last, Rva005DBCD1 *result, const _STL::__false_type &)
{
	Rva005DBCD1 *cur = result;
	for (; first != last; ++first, ++cur)
	{
		if (cur != 0)
			new (cur) Rva005DBCD1(*first);
	}
	return cur;
}
