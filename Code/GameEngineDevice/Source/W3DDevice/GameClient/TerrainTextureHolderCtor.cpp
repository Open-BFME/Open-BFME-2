// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native EF902..EF961 RET12,95B creates a counted one-word terrain handle.
// Target allocation3C and constructorEF272 (now named as its sole owner)
// establish resource size and constructor purpose. Existing retaining
// Set_Texture atEF87B establishes adoption and the two-byte resource refs.
// Base cleanup and failed-allocation state match native EH; the inherited
// RefCountPtr is an owning-word ABI view, not an original type-name claim.
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void*);
class TextureClass {public:void Release_Ref();};
template<class T>class RefCountPtr {public:
 RefCountPtr():m_ptr(0){}
 ~RefCountPtr(){if(m_ptr)m_ptr->Release_Ref();}
private:T*m_ptr;
};
class BfmeOwnerZQ { public:BfmeOwnerZQ(void*,void*,void*,void*);void *m_bfmeVfZQ;char unknown04[0x3C-4];};
class BfmeMapPictureTexture {public:void Set_Texture(TextureClass*);};
class Rva000EF902 :public RefCountPtr<TextureClass> {public:Rva000EF902(int width,int height,int format);};
Rva000EF902::Rva000EF902(int width,int height,int format) {
 ((BfmeMapPictureTexture*)this)->Set_Texture((TextureClass*)new BfmeOwnerZQ((void*)height,(void*)width,(void*)format,(void*)3));
}

// Native EF8A1..EF902 RET8,97B has the same counted-word ownership.
// Allocation3C and EF272 establish the constructor ABI; the fixed leading
// 0x800 argument and the two caller-supplied pointers are target evidence.
// Resource and caller argument names remain unknown.
class Rva000EF8A1 :public RefCountPtr<TextureClass> {
public:Rva000EF8A1(void*first,void*second);
};
Rva000EF8A1::Rva000EF8A1(void*first,void*second) {
 ((BfmeMapPictureTexture*)this)->Set_Texture(
  (TextureClass*)new BfmeOwnerZQ((void*)0x800,first,second,(void*)3));
}
