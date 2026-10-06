// cl: /DNDEBUG /MD /EHsc
// ?Rva0039B8D8FillN@@YAPAVRva0039B893@@PAV1@IABV1@ABU__false_type@_STL@@@Z @0x0039B8D8 40B fill_n over Rva0039B893 via rowed copy ctor.
// Null-skipping counted loop with 0x14 stride returning one-past-last.
// Evidence: callees rowed copy ctor 0x0039B893; callers 0x0039BA85 (27B pushes 4 args caller-cleans) and 0x0039C1C3 (186B same ebp+0x1b false_type as rowed 0x0039BA22); stride matches sizeof Rva0039B893.

typedef int Int;
typedef short Short;

namespace _STL
{
struct __false_type
{
};
}

class Rva0039B893
{
public:
	Rva0039B893(const Rva0039B893 &other) throw();
	virtual ~Rva0039B893();

	Int m_field04;
	Int m_field08;
	Short m_field0C;
	Short m_field0E;
	Short m_field10;
};

inline void *__cdecl operator new(unsigned int, void *p) { return p; }
inline void __cdecl operator delete(void *, void *) {}

Rva0039B893 *__cdecl Rva0039B8D8FillN(Rva0039B893 *first, unsigned int n, const Rva0039B893 &value, const _STL::__false_type &)
{
	Rva0039B893 *cur = first;
	while (n > 0)
	{
		if (cur != 0)
			new (cur) Rva0039B893(value);
		++cur;
		--n;
	}
	return cur;
}
