// cl: /DNDEBUG /MD /EHsc
// ?Rva0039BA85FillN@@YAXPAVRva0039B893@@IABV1@@Z @0x0039BA85 27B uninitialized_fill_n wrapper over rowed 0x0039B8D8.
// Forwards first/count/value plus local false_type tag; caller-cleans 4 pushes.
// Evidence: callee rowed 0x0039B8D8 FillN; caller 0x0039C4A4 in 226B body; same ebp-1 tag pattern as 0x0039C1C3 ebp+0x1b.

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

Rva0039B893 *__cdecl Rva0039B8D8FillN(Rva0039B893 *first, unsigned int n, const Rva0039B893 &value, const _STL::__false_type &);

void __cdecl Rva0039BA85FillN(Rva0039B893 *first, unsigned int n, const Rva0039B893 &value)
{
	_STL::__false_type tag;
	Rva0039B8D8FillN(first, n, value, tag);
}
