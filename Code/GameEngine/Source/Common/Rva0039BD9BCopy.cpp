// cl: /DNDEBUG /MD /EHsc
// ?Rva0039BD9BCopy@@YAXPAVRva0039B893@@00@Z @0x0039BD9B 29B wrapper forwarding
// first/last/result to the rowed five-arg forward copy at 0x0039BAA0 with a
// stack tag at ebp-1 plus null distance. Evidence: chain from just-landed
// 0x0039BAA0; three callers push four args each.

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

Rva0039B893 *__cdecl Rva0039BAA0Copy(Rva0039B893 *first, Rva0039B893 *last, Rva0039B893 *result, const RandomAccessTag &tag, int *dist);

void __cdecl Rva0039BD9BCopy(Rva0039B893 *first, Rva0039B893 *last, Rva0039B893 *result)
{
	RandomAccessTag tag;
	Rva0039BAA0Copy(first, last, result, tag, 0);
}
