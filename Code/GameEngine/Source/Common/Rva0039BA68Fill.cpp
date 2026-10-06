// cl: /DNDEBUG /MD /EHsc
// ?Rva0039BA68Fill@@YAXPAVRva0039B893@@0ABV1@@Z @0x0039BA68 29B range fill
// assigning the same value to each Rva0039B893 slot via the rowed operator=
// at 0x0039B900 with stride 0x14. Evidence: chain from just-landed assign;
// two callers 0x0039C492/0x0039C4D2 each push three args and caller cleans.

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

void __cdecl Rva0039BA68Fill(Rva0039B893 *first, Rva0039B893 *last, const Rva0039B893 &value)
{
	for (; first != last; ++first)
		*first = value;
}
