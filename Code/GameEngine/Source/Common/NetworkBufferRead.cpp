// cl: /EHsc /MD
//
// ?NetworkBufferRead@@YAPADPADPAV?$StringBase@D@@0@Z @0x00447FD5 88B.
// Checked string append: dst->set(static at 0x00BBAC1C), then append src chars
// via concat until null with limit checks, return past null (src/limit on
// early-out). Evidence: unlock lane; callees set 0x000055F5 concat 0x000369A0
// rowed; caller at 0x00448461; neighbours share flags.
#include "../../../../reference/shims/bfme2_ascii/string_base.h"

// WorldBuilder NetworkBufferRead, WB VA 0x014A89F0 (align lead, score 1.5).
char *__cdecl NetworkBufferRead(char *src, StringBase<char> *dst, char *limit)
{
	dst->set("");
	if (limit != 0) {
		if (src >= limit)
			return src;
		if (limit - src < 1)
			return src;
	}
	while (*src != 0) {
		if (limit != 0) {
			if (src >= limit)
				return limit;
		}
		char tmp = *src;
		dst->concat(&tmp, 1);
		++src;
	}
	return src + 1;
}
