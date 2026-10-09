// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
// Native0011018B..001101D7 RET0, 76B. The existing QAE destructor pin
// was harvested from a byte-placed BF1 Rva00785FD0Renderer caller. Its
// donor-address spelling is retained; historical class identity is unknown.
// Target proves TextureBase reference4 and material referenceD0, with the
// rest of the 0xD4-byte view unnamed. Body explicitly clears material before
// the texture member is destroyed; native EH state0 preserves that lifetime.
// Release_Ref caches its this pointee across the decrement, reproducing
// DEC[ECX+4]/JNE; open-coding --member->refs rereads the member and grows10B.
// The material counter is32-bit at+4 and Delete_This slot0; texture releases
// through the existing TextureBaseClass provider61ED10. No new pins.
class TextureBaseClass {public: void Release_Ref();};
class RefCountClass {public: virtual void Delete_This(); int refs; __forceinline void Release_Ref(){if(--refs==0)Delete_This();}};
class RendererTextureHandle {public: TextureBaseClass *p; ~RendererTextureHandle(){if(p)p->Release_Ref();}};
class RendererMaterialHandle {public: RefCountClass *p; __forceinline void clear(){if(p){ p->Release_Ref(); p=0; }}};
class Rva00785FD0Renderer {
public: ~Rva00785FD0Renderer();
private: void *unknown0; RendererTextureHandle texture; unsigned char gap[0xC8]; RendererMaterialHandle material;
};
Rva00785FD0Renderer::~Rva00785FD0Renderer() { material.clear(); }
