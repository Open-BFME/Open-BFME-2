// cl: /Oy- /DNDEBUG /MD
// EA Zero Hour meshmatdesc.h single-texture getter, adapted to BFME2 handles.
// Retail D2026: complete 37B body; texture slots at +0x78 with pass/stage indexing.
// The out-of-line handle copy at 424BB is the existing 21B AssetReference copy
// body: copies one pointer and increments its WORD reference count at +4.
// This owning getter is called from model accessor D206A and the material remapper.
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {};
template<class T> class RefCountPtr {
public:
    T *p;
    RefCountPtr(const RefCountPtr&);
    ~RefCountPtr() { if(p) p->Release_Ref(); }
};
class MeshMatDescClass {
    char prefix[0x78];
    RefCountPtr<TextureClass> Textures[4][2];
public:
    RefCountPtr<TextureClass> Get_Single_Texture(int pass,int stage) const;
};
RefCountPtr<TextureClass> MeshMatDescClass::Get_Single_Texture(int pass,int stage) const {
    return Textures[pass][stage];
}
