// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva00414476Destroy@@YAXPAURva00414476Element@@0H@Z, retail 0x00414476, 26 bytes.
// Range destroy stepping 0x30 calling virtual dtor with 0; called by pinned _Destroy 0x00414508 for 48B Rva00414BDBElement.
// Same shape as sibling 0x0041445C stride 0x2C; element is virtual to reproduce call [eax] shape.
// Owner unproven so honest free-function name.
struct Rva00414476Element {
	virtual ~Rva00414476Element();
	char m_pad[0x30 - 4];
};
void __cdecl Rva00414476Destroy(Rva00414476Element *first, Rva00414476Element *last, int unused)
{
	for (; first != last; ++first)
		first->~Rva00414476Element();
}
