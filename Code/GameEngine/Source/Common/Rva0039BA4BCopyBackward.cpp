// cl: /DNDEBUG /MD /EHsc
// ?Rva0039BA4BCopyBackward@@YAXPAVRva0039B893@@00@Z @0x0039BA4B 29B wrapper
// forwarding first/last/result to the rowed five-arg copy-backward at
// 0x0039B92D with a stack tag at ebp-1 plus null distance. Evidence: chain
// from just-landed 0x0039B92D; sole caller 0x0039C485 pushes four args.

typedef int Int;
typedef short Short;

class Rva0039B893
{
public:
	Rva0039B893 &operator=(const Rva0039B893 &other);
	virtual ~Rva0039B893();

	Int m_field04;
	Int m_field08;
	Short m_field0C;
	Short m_field0E;
	Short m_field10;
};

struct RandomAccessTag
{
	char _x;
};

Rva0039B893 *__cdecl Rva0039B92DCopyBackward(Rva0039B893 *first, Rva0039B893 *last, Rva0039B893 *result, const RandomAccessTag &tag, int *dist);

void __cdecl Rva0039BA4BCopyBackward(Rva0039B893 *first, Rva0039B893 *last, Rva0039B893 *result)
{
	RandomAccessTag tag;
	Rva0039B92DCopyBackward(first, last, result, tag, 0);
}
