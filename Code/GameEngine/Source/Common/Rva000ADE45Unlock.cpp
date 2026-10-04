// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva000ADE45Copy@@YAPAUBfmeStringRecord00063BE4@@PAU1@00@Z, retail 0x000ADE45, 29 bytes.
// Free copy wrapper over rowed __copy 0x00332F29 with tag and null distance.
// Evidence: unlock lane; caller 0x00335C9B; prev/next TU flags.
#include <algorithm>
struct BfmeStringRecord00063BE4 {
	unsigned int word0, word1, word2, word3, word4, word5, word6;
	char text[4];
	unsigned char tail0, tail1;
};
BfmeStringRecord00063BE4 *__cdecl Rva000ADE45Copy(BfmeStringRecord00063BE4 *a, BfmeStringRecord00063BE4 *b, BfmeStringRecord00063BE4 *c)
{
	return _STL::__copy(a, b, c, _STL::random_access_iterator_tag(), (int *)0);
}
