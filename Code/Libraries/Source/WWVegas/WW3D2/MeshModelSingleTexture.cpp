// cl: /Oy- /DNDEBUG /MD
// Reference meshmdl.h current-description single-texture forwarding shape.
// BFME2 D206A is a complete 35B owning-handle return via CurMatDesc at +0x94.
// Its callee is the MeshMatDesc peek D2026, as ZH meshmdl.h forwards.
// Keep the callee out of this TU so the retail call and register saves survive.
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {};
template<class T> class RefCountPtr {
public:
    T *p;
    RefCountPtr(const RefCountPtr&);
    ~RefCountPtr() { if(p) p->Release_Ref(); }
};
class MeshMatDescClass {
public:
    RefCountPtr<TextureClass> Peek_Single_Texture(int pass,int stage) const;
};
class MeshModelClass {
    char prefix[0x94];
    MeshMatDescClass *CurMatDesc;
public:
    RefCountPtr<TextureClass> Peek_Single_Texture(int pass,int stage) const;
};
RefCountPtr<TextureClass> MeshModelClass::Peek_Single_Texture(int pass,int stage) const {
    return CurMatDesc->Peek_Single_Texture(pass,stage);
}
