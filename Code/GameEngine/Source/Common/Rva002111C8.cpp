// cl: /DNDEBUG /MD

// ??0Rva002111C8@@QAE@ABV0@@Z, RVA 0x002111C8, 27B. Unlock lane: copy ctor
// copy-constructing the 12B RvaSmartPtr12 member at +0 through rowed
// ??0RvaSmartPtr12@@QAE@ABV0@@Z at 0x0004CC19 then copying the dword at
// +0x0C; returns this, ret 4, no vtable. Caller at 0x00211E07 in 0x00211DFB.
// Owner unknown so honest address-derived name; member size 12B puts m_0c at
// +0x0C per the retail offsets.
class RvaSmartPtr12
{
public:
	RvaSmartPtr12(const RvaSmartPtr12 &o);
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &o);
private:
	char m_data[12];
};

class Rva002111C8
{
public:
	Rva002111C8(const Rva002111C8 &o);
	Rva002111C8 &operator=(const Rva002111C8 &o);
private:
	RvaSmartPtr12 m_00;
	int m_0c;
};

Rva002111C8::Rva002111C8(const Rva002111C8 &o)
	: m_00(o.m_00), m_0c(o.m_0c)
{
}

// ?Rva00211DFBConstruct@@YAXPAVRva002111C8@@PBV1@@Z, RVA 0x00211DFB, 18B.
// Unlock lane: null-guarded placement copy through the row above; frameless
// cdecl with plain ret. Local nothrow placement new (not <new>'s, whose
// placement delete pulls EH states) so the throwing copy construction emits
// no EH states or handler, as retail has none. Callers at
// 0x00211E1B/0x00211E46/0x00213E8E.
inline void *__cdecl operator new(unsigned int, Rva002111C8 *p) throw() { return (void *)p; }

void Rva00211DFBConstruct(Rva002111C8 *d, const Rva002111C8 *s)
{
	if (d)
		new (d) Rva002111C8(*s);
}

// ??4Rva002111C8@@QAEAAV0@ABV0@@Z, RVA 0x002111E3, 27B. Unlock lane: copy
// assignment through rowed ??4RvaSmartPtr12 at 0x0004CC3D for +0 then the
// +0x0C dword; returns *this, ret 4. Caller at 0x00211EC3 in 0x00211EAA.
Rva002111C8 &Rva002111C8::operator=(const Rva002111C8 &o)
{
	m_00 = o.m_00;
	m_0c = o.m_0c;
	return *this;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??$_Construct@URva002111C8@@U1@@_STL@@YAXPAURva002111C8@@ABU1@@Z=?Rva00211DFBConstruct@@YAXPAVRva002111C8@@PBV1@@Z")
