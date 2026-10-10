// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Tail-jumps the 0x00DF29B4 map object (unsigned to pointer) to the tree
// clear rowed at 0x001364CE; the tree view is address-derived.
#include <map>
class Rva001363CC
{
public:
	void rva001364CE();
};
extern _STL::map<unsigned int, void *> g_00DF29B4;
void Rva0013676D()
{
	((Rva001363CC *)&g_00DF29B4)->rva001364CE();
}
