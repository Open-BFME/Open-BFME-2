// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva0041445CDestroy@@YAXPAURva0041445CElement@@0H@Z, retail 0x0041445C, 26 bytes.
// Range destroy stepping 0x2C calling virtual dtor with 0; called by pinned _Destroy 0x004144F0.
// Same stride as BfmePod44 neighbours; element is virtual to reproduce call [eax] shape.
// Owner unproven so honest free-function name.
struct Rva0041445CElement {
	virtual ~Rva0041445CElement();
	char m_pad[0x2C - 4];
};
void __cdecl Rva0041445CDestroy(Rva0041445CElement *first, Rva0041445CElement *last, int unused)
{
	for (; first != last; ++first)
		first->~Rva0041445CElement();
}
