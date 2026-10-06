// cl: /DNDEBUG /MD /EHsc
// ?Rva0039B92DCopyBackward@@YAPAVRva0039B893@@PAV1@00ABURandomAccessTag@@PAH@Z @0x0039B92D 50B copy-backward
// assigning via rowed operator= 0x0039B900 with stride 0x14. Evidence: chain
// from just-landed assign; caller 0x0039BA5E pushes five args (first last
// result plus tag at ebp-1 plus null distance) and caller cleans.

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

Rva0039B893 *__cdecl Rva0039B92DCopyBackward(Rva0039B893 *first, Rva0039B893 *last, Rva0039B893 *result, const RandomAccessTag &tag, int *dist)
{
	int n = last - first;
	if (n <= 0)
		return result;
	for (int i = n; i != 0; --i)
	{
		--last;
		--result;
		*result = *last;
	}
	return result;
}
