// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva003EF80FInsertSorted@@YGXPAV?$vector@PAVRva002C589B@@V?$allocator@PAVRva002C589B@@@_STL@@@_STL@@PAVRva002C589B@@@Z
// retail 0x003EF80F (80 bytes, ret 8). Owner unproven (address token): keeps the pointer vector ordered by
// the float at +0x24, inserting before the first element that is greater and appending when none is. The
// element type stands in with the opaque Rva002C589B, whose pointer-vector push_back (0x004DFCB0) and insert
// (0x003B67B3) folds are already rowed.
#include <vector>

class Rva002C589B
{
public:
	char m_pad00[0x24];
	float m_24;
};

void __stdcall Rva003EF80FInsertSorted(_STL::vector<Rva002C589B *> *list, Rva002C589B *item)
{
	for (unsigned int i = 0; i < list->size(); ++i) {
		if ((*list)[i]->m_24 > item->m_24) {
			list->insert(list->begin() + i, item);
			return;
		}
	}
	list->push_back(item);
}
