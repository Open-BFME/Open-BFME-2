// cl: /DNDEBUG /MD
// EA BFME1 matinfo.h texture accessors, adapted to BFME2 owning handles.
// Retail Textures vector data is at +0x24. Peek returns a retained copy,
// unlike the ancestor's raw pointer. Copy424BB and assignment424D0 identities
// are independently established by their complete owning-handle bodies.
// /O1 emits the 33B return-by-value getter with EBP and the 22B setter without it.
class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {};
template<class T> class RefCountPtr {
public:
    T *p;
    RefCountPtr(const RefCountPtr&);
    ~RefCountPtr() { if(p) p->Release_Ref(); }
    const RefCountPtr &operator=(const RefCountPtr&);
};
class MaterialInfoClass {
    char prefix[0x24];
    RefCountPtr<TextureClass> *Textures;
public:
    RefCountPtr<TextureClass> Peek_Texture(int);
    void Replace_Texture(int,const RefCountPtr<TextureClass>&);
};
RefCountPtr<TextureClass> MaterialInfoClass::Peek_Texture(int index) {
    return Textures[index];
}
inline void MaterialInfoClass::Replace_Texture(int index,const RefCountPtr<TextureClass>& texture) {
    Textures[index]=texture;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
void (MaterialInfoClass::*_bfmeInlineAnchor_MaterialInfoTextureHandles_0)(int index,const RefCountPtr<TextureClass>& texture) = &MaterialInfoClass::Replace_Texture;
