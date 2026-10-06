// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@UTreeHintRef00217D4C@@V?$allocator@UTreeHintRef00217D4C@@@_STL@@@_STL@@QAE@XZ retail 0x000806B4 63B
// Evidence: same 63B EH shape as EvaMessage vector dtor 0x000B0254 via Destroy 0x005F97BC plus free 0x00030830; callers 0x0008227E 0x00083943 0x00083A3A
#include <vector>

struct TreeHintRef00217D4C
{
	~TreeHintRef00217D4C();
};

template _STL::vector<TreeHintRef00217D4C>::~vector();
