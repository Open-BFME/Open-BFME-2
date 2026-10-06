// cl: /DNDEBUG /MD
// ?rva005F8E5AInit@@YIPAVRva005F8E5A@@PAV1@HHHH@Z @0x005F8E5A 35B evidence:
// fastcall init chaining to pinned ?rva005FE640@@YIXPAVRva005FE640Obj@@HHH@Z
// @0x005FE640 with (this, fwd-passthrough-in-edx, c, b); stores a at +0x38;
// installs vtable 0x00C79D0C (opaque owner Rva005F8F7B, symbol reused, no
// new emission); returns this. Sibling of 0x005F8E37 (same shape, base
// ctor called directly). TU-local layout view only.
extern "C" const void *const vtbl_00C79D0C[];	// ??_7Rva005F8F7B@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C79D0C=??_7Rva005F8F7B@@6B@")

class Rva005F8E5A
{
public:
	char m_pad[0x38];
	int m_38;
};

class Rva005FE640Obj;
void __fastcall rva005FE640(Rva005FE640Obj *o, int fwd, int x, int y);

Rva005F8E5A *__fastcall rva005F8E5AInit(Rva005F8E5A *o, int fwd, int a, int b, int c)
{
	rva005FE640((Rva005FE640Obj *)o, fwd, b, c);
	o->m_38 = a;
	((void **)o)[0] = (void *)vtbl_00C79D0C;
	return o;
}
