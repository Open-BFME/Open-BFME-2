// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc

// ?Rva005EC594Clear@@YAXPAURva005EC594@@0@Z, RVA 0x005EC594, 25B. Unlock
// lane: clears the StringBase at +0 of each 0x18-byte element in
// [first,last) through rowed ?clear@?$StringBase@G@@QAEXXZ at 0x005B804E;
// frameless cdecl loop with add/jne. Unblocks 0x005EC9F9/0x005EC9BA.
// Element owner unproven (0x18 stride with string head, a different family
// from Rva005DE5B5) so honest address-derived struct and free-function names.
// Flags copy the prev neighbour uninitialized_copy TU (no EH frame).
template <typename T>
class StringBase
{
public:
	void clear();
private:
	void *m_data;
};

struct Rva005EC594 {
	StringBase<unsigned short> m_00;
	char m_pad[0x14];
};

void Rva005EC594Clear(Rva005EC594 *first, Rva005EC594 *last)
{
	for (; first != last; ++first)
		first->m_00.clear();
}

// ?rva005EC9F9@Rva005EC9F9@@QAEXXZ, RVA 0x005EC9F9, 30B. Chain lane: clears
// the [m_00,m_04) range through the row above, then frees m_00 through rowed
// _free at 0x00030830 when non-null; frameless, ret. Caller at 0x005ECBC1 in
// 0x005ECB28. Owner unknown so honest address-derived names.
extern "C" void free(void *);

class Rva005EC9F9
{
public:
	void rva005EC9F9();
private:
	Rva005EC594 *m_00;
	Rva005EC594 *m_04;
};

void Rva005EC9F9::rva005EC9F9()
{
	Rva005EC594Clear(m_00, m_04);
	Rva005EC594 *p = m_00;
	if (p)
		free(p);
}
