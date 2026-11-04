// cl: /DNDEBUG /MD
// EA BFME1 matinfo.h texture accessors, adapted to BFME2 owning handles.
// Retail Textures vector data is at +0x24. Peek returns a retained copy,
// unlike the ancestor's raw pointer. Copy424BB and assignment424D0 identities
// are independently established by their complete owning-handle bodies.
// /O1 emits the 33B return-by-value getter with EBP and the 22B setter without it.
// The complete 21-byte copy at 0x424BB is owned as AssetReference.
// RefCountPtr<TextureClass> has the same one-pointer owning representation;
// its separate, rowed constructor at 0x1494F0 is a different emitted body.
// The native copy only loads/stores its pointer and increments a WORD count,
// so it cannot throw. The member owns the pointer until the handle releases it.
class AssetReference {
public:
    void *m_object;
};

class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {};
template<class T> class RefCountPtr {
public:
    AssetReference m_native;
    RefCountPtr(const RefCountPtr&);
    template<class Native> __declspec(noinline) RefCountPtr(const Native &other) {
        m_native.m_object = other.m_object;
        if (m_native.m_object)
            ++*(unsigned short *)((char *)m_native.m_object + 4);
    }
    ~RefCountPtr() {
        T *p = (T *)m_native.m_object;
        if(p) p->Release_Ref();
    }
    const RefCountPtr &operator=(const RefCountPtr&);
};
typedef char TextureHandleWidth[sizeof(RefCountPtr<TextureClass>) == 4 ? 1 : -1];
#include "MaterialInfoClass.h"

RefCountPtr<TextureClass> MaterialInfoClass::Peek_Texture(int index) {
    return RefCountPtr<TextureClass>(field24[index].m_native);
}
inline void MaterialInfoClass::Replace_Texture(int index,const RefCountPtr<TextureClass>& texture) {
    field24[index]=texture;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
void (MaterialInfoClass::*_bfmeInlineAnchor_MaterialInfoTextureHandles_0)(int index,const RefCountPtr<TextureClass>& texture) = &MaterialInfoClass::Replace_Texture;
