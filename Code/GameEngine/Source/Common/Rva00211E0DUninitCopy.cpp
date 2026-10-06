// cl: /DNDEBUG /MD
// ?Rva00211E0DGet@@YAPAVRva002111C8@@PAV1@00@Z, RVA 0x00211E0D, 38B. Chain lane:
// uninitialized copy over 0x10-stride Rva002111C8 via rowed 0x00211DFB
// placement copy; push-esi/edi loop with late cmp, returns final dest.
// Dedicated TU so the Construct definition cannot inline. Callers at
// 0x00213E79/0x00213EC4. Owner unknown so honest address-derived names.
class RvaSmartPtr12
{
	char m_data[12];
};
class Rva002111C8
{
	RvaSmartPtr12 m_00;
	int m_0c;
public:
	Rva002111C8 &operator=(const Rva002111C8 &o);
};
void __cdecl Rva00211DFBConstruct(Rva002111C8 *d, const Rva002111C8 *s);

Rva002111C8 *__cdecl Rva00211E0DGet(Rva002111C8 *first, Rva002111C8 *last, Rva002111C8 *result)
{
	Rva002111C8 *cur = result;
	for (; first != last; ++first, ++cur)
		Rva00211DFBConstruct(cur, first);
	return cur;
}

// ?Rva00211E33Fill@@YAPAVRva002111C8@@PAV1@IPBV1@@Z, RVA 0x00211E33, 37B.
// Chain lane: uninitialized fill_n over 0x10-stride Rva002111C8 via rowed
// 0x00211DFB; count in edi with jbe guard, value stays fixed, returns final
// dest. Same dedicated TU so Construct stays a call. Caller at 0x00213EA6.
// Owner unknown so honest address-derived names.

Rva002111C8 *__cdecl Rva00211E33Fill(Rva002111C8 *dest, unsigned int count, const Rva002111C8 *value)
{
	Rva002111C8 *cur = dest;
	for (; count > 0; --count, ++cur)
		Rva00211DFBConstruct(cur, value);
	return cur;
}

// ?Rva00211EAACopy@@YAPAVRva002111C8@@PAV1@00@Z, RVA 0x00211EAA, 47B. Chain
// lane: copy via rowed operator= 0x002111E3; byte-diff sar 4 count with jle
// guard, EBP frame, updates first/dest slots, returns final dest. Caller at
// 0x00211F63. Owner unknown so honest address-derived names.

Rva002111C8 *__cdecl Rva00211EAACopy(Rva002111C8 *first, Rva002111C8 *last, Rva002111C8 *dest)
{
	for (int n = ((int)last - (int)first) >> 4; n > 0; --n) {
		*dest = *first;
		++first;
		++dest;
	}
	return dest;
}
