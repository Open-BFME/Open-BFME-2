// cl: /DNDEBUG /MD
// ?rva005F8E37Init@@YIPAVRva005F8E37@@PAV1@HHHH@Z @0x005F8E37 35B evidence:
// fastcall init chaining to pinned ?rva005FE7A7@@YIXPAVRva005FE7A7Obj@@HHH@Z
// @0x005FE7A7 with (this, fwd-passthrough-in-edx, c, b); stores a at +0x3C;
// installs vtable 0x00C79CF8 (opaque owner Rva005F8F5A, symbol reused, no
// new emission); returns this. TU-local layout view only.
extern "C" const void *const vtbl_00C79CF8[];	// ??_7Rva005F8F5A@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C79CF8=??_7Rva005F8F5A@@6B@")

class Rva005F8E37
{
public:
	char m_pad[0x3C];
	int m_3C;
};

class Rva005FE7A7Obj;
void __fastcall rva005FE7A7(Rva005FE7A7Obj *o, int fwd, int x, int y);

Rva005F8E37 *__fastcall rva005F8E37Init(Rva005F8E37 *o, int fwd, int a, int b, int c)
{
	rva005FE7A7((Rva005FE7A7Obj *)o, fwd, b, c);
	o->m_3C = a;
	((void **)o)[0] = (void *)vtbl_00C79CF8;
	return o;
}
