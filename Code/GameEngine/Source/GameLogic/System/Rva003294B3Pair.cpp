// cl: /MD /DNDEBUG /EHsc
// ?rva003294B3@@YAXPAURva003294B3Obj@@HH@Z @0x003294B3 35B: pick one of two cdecl helpers by the
// byte at +0x0C; the first helper takes the third argument, the second the second.
struct Rva003294B3Obj
{
	char m_pad00[0xC];
	unsigned char m_0C;
};

void __cdecl rva00329339(Rva003294B3Obj *o, int value);
void __cdecl rva0032927A(Rva003294B3Obj *o, int value);

// ?rva003294B3@@YAXPAURva003294B3Obj@@HH@Z @0x003294B3
void __cdecl rva003294B3(Rva003294B3Obj *o, int a2, int a3)
{
	if (o->m_0C != 0)
		rva00329339(o, a3);
	else
		rva0032927A(o, a2);
}
