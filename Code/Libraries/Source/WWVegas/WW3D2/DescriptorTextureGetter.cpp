// cl: /G7 /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Target texture-slot view; the original class and method names are unknown.
// Callers establish the +0x78 slot table and release the owning result through
// TextureClass::Release_Ref at 0x61ED10. Its refcount is a WORD at +4.
class TextureRefObjectView
{
public:
    void *VTable;
    unsigned short RefCount;
    void Add_Ref() { ++RefCount; }
};

struct BfmeTextureHandleView
{
    TextureRefObjectView *Ptr;
    BfmeTextureHandleView(TextureRefObjectView *p) : Ptr(p) {
        if (Ptr)
            Ptr->Add_Ref();
    }
    ~BfmeTextureHandleView();
};

class DescriptorTextureView
{
    char unknown0[0x78];
    TextureRefObjectView *Texture[4][2];
public:
    BfmeTextureHandleView Get_Handle(int pass, int stage) const;
};

BfmeTextureHandleView DescriptorTextureView::Get_Handle(int pass, int stage) const
{
    return BfmeTextureHandleView(Texture[pass][stage]);
}
