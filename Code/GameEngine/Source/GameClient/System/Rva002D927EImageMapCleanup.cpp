// cl: /O1 /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Clean BFME1 Image.cpp (f98983a7) supplies map teardown semantics.
// Retail 2D927E jumps to the rowed Image tree destructor at 2D922A;
// ImageCollection's EH action 777ADB reaches it on the map at this+0xC;
// the original wrapper name and template spelling remain unknown.
#include <map>
class Image;
typedef _STL::pair<const unsigned, Image *> ImagePair;
typedef _STL::_Rb_tree<unsigned, ImagePair, _STL::_Select1st<ImagePair>, _STL::less<unsigned>, _STL::allocator<ImagePair> > ImageTree;
class Rva002D927EImageTree
{
public:
    void rva002D927ECleanup();
private:
    ImageTree value;
};
void Rva002D927EImageTree::rva002D927ECleanup()
{
    value.~ImageTree();
}
