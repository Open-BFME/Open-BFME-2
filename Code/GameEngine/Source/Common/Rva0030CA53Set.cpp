// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0030CA53Set@@YAXPAVRva004733E0@@PBV1@@Z, retail 0x0030CA53, 18 bytes.
// Null-guarded free wrapper over Rva004733E0::set (retail 0x0030BF66):
// mov ecx,[esp+4]; test ecx,ecx; je; push [esp+8]; call set; ret.
// Callees all rowed. Callers at 0x002828C3/0x00308676/0x00308E3E/0x0030CA73/
// 0x005C673C push two pointers and clean 8 (cdecl void). Identity stays
// honest Rva address plus Set verb per fleet free-function convention.
struct Rva004733E0Obj
{
	int m_00;
	int m_04;
};

class Rva004733E0
{
	int m_00;
	Rva004733E0Obj *m_04;

public:
	Rva004733E0 *set(const Rva004733E0 *src);
};

void Rva0030CA53Set(Rva004733E0 *dst, const Rva004733E0 *src)
{
	if (dst)
		dst->set(src);
}
