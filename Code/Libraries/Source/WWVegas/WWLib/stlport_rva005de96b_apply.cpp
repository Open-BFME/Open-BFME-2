// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc

// ?rva005DE96B@Rva005DE96B@@QAEXXZ, RVA 0x005DE96B, 26B. Chain lane: method
// applying the rowed range-apply 0x005DD6D5 to the [m_04,m_08) range with the
// per-element function at 0x005DE926; scratch out-slot discarded via add esp.
// 0x005DE926 is UNCLAIMED (44B with unclaimed callees) so its address is a
// raw immediate until it lands; callers at 0x005B8EC4/0x005DD0C6. Owner
// unknown so honest address-derived method name. Flags copy the allocate_copy
// TU (frameless, no EH).
struct Rva005DE5B5 {
	char m_data[0x18];
	void rva005DE926();
};
typedef void (Rva005DE5B5::*Rva005DE5B5Fn)();
void Rva005DD6D5Apply(Rva005DE5B5Fn *out, Rva005DE5B5 *first, Rva005DE5B5 *last, Rva005DE5B5Fn fn);

class Rva005DE96B
{
public:
	void rva005DE96B();
private:
	int m_00;
	Rva005DE5B5 *m_04;
	Rva005DE5B5 *m_08;
};

void Rva005DE96B::rva005DE96B()
{
	Rva005DE5B5Fn tmp;
	Rva005DD6D5Apply(&tmp, m_04, m_08, &Rva005DE5B5::rva005DE926);
}
