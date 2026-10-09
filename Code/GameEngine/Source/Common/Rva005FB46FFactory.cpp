// cl: /O1 /Oy- /MD /EHsc /G7
// Native5FB46F..5FB4A1 cdecl hidden return; twelve-byte wrapper ctor5FB400
// copies the input pointer and has no throwing operations. Its nothrow
// declaration removes an unsupported new-expression EH cleanup, retaining
// the native hidden-return flag and ordinary frame. The subsequent native
// caller5FB4DF uses this wrapper for two panel lists based on empty army+18.
// No application-level holder or factory identity is asserted.
struct RvaF1Handle { void *m_p; __forceinline RvaF1Handle(void *p):m_p(p){if(p)++((int*)p)[1];} ~RvaF1Handle(); };
class Rva005FB400 { char storage[12];public: __declspec(nothrow) Rva005FB400(const void*); };
RvaF1Handle Rva005FB46FCreate(const void *input) { return RvaF1Handle(new Rva005FB400(input)); }
