// cl: /DNDEBUG /MD
// ?rva006CC4A0Init@@YIPAVRva006CC4A0@@PAV1@HH@Z @0x006CC4A0 32B evidence:
// fastcall init (this, fwd-dead-in-edx, arg): pinned thiscall-0
// ?rva00ADAFA0@Rva006CC4A0@@QAEXXZ @0x00ADAFA0 on this (ecx ambient);
// if (arg & 1) calls pinned __cdecl-2 ?rva00ACBC50@@YAXHPAVRva006CC4A0@@@Z
// @0x00ACBC50(0x1C, this); returns this; ret 4. TU-local view only.
class Rva006CC4A0
{
public:
	void rva00ADAFA0();
};

void __cdecl rva00ACBC50(Rva006CC4A0 *o, int code);

Rva006CC4A0 *__fastcall rva006CC4A0Init(Rva006CC4A0 *o, int fwd, int arg)
{
	o->rva00ADAFA0();
	if (arg & 1)
		rva00ACBC50(o, 0x1C);
	return o;
}
