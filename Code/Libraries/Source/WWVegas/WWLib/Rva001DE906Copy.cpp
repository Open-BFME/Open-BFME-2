// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva001DE906Copy@@YAPAVRva001DE727@@PAV1@00@Z @0x001DE906 50B array copy of 0x30-sized Rva001DE727 via rowed operator= 0x001DE727.
// Evidence: chain lane callee rowed; caller 0x001DEE1F; count via sub plus idiv 0x30; loop via operator= plus add 0x30.
// ?Rva001DE938CopyBackward@@YAPAVRva001DE727@@PAV1@00@Z @0x001DE938 50B array copy-backward of 0x30-sized Rva001DE727 via rowed operator= 0x001DE727.
// Evidence: chain lane callee rowed; caller 0x001DEE3C; count via sub plus idiv 0x30; loop via operator= plus sub 0x30.
// ?Rva001DE8E9Fill@@YAXPAVRva001DE727@@0ABV1@@Z @0x001DE8E9 29B range fill of 0x30-sized Rva001DE727 via rowed operator= 0x001DE727.
// Evidence: chain lane callee rowed; callers 0x001DF35A 0x001DF39A in 0x001DF2D3 push three args caller-cleans.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <vector>

class Rva001DE727
{
public:
	Rva001DE727 &operator=(const Rva001DE727 &that);
private:
	char m_body[0x30];
};

Rva001DE727 *Rva001DE906Copy(Rva001DE727 *first, Rva001DE727 *last, Rva001DE727 *result)
{
	int n = (int)(last - first);
	if (n <= 0)
		return result;
	int count = n;
	do
	{
		*result = *first;
		++first;
		++result;
	} while (--count != 0);
	return result;
}

Rva001DE727 *Rva001DE938CopyBackward(Rva001DE727 *first, Rva001DE727 *last, Rva001DE727 *result)
{
	int n = (int)(last - first);
	if (n <= 0)
		return result;
	int count = n;
	do
	{
		--last;
		--result;
		*result = *last;
	} while (--count != 0);
	return result;
}

void __cdecl Rva001DE8E9Fill(Rva001DE727 *first, Rva001DE727 *last, const Rva001DE727 &value)
{
	for (; first != last; ++first)
		*first = value;
}
