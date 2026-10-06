// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0030CA65Copy@@YAPAVRva004733E0@@PBV1@0PAV1@@Z, retail 0x0030CA65, 38 bytes.
// Copy loop returning dst: Rva0030CA53Set copies one 8-byte record. Retail is
// frameless (no ebp) with src in edi, dst in esi and end held at [esp+0x10];
// the local aliases in/out are what make MSVC 7.1 allocate that pair instead
// of spilling dst to an ebp frame. Callers at 0x002828AE/0x002828F9.
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
void Rva0030CA53Set(Rva004733E0 *dst, const Rva004733E0 *src);
Rva004733E0 *Rva0030CA65Copy(const Rva004733E0 *src, const Rva004733E0 *end, Rva004733E0 *dst)
{
	Rva004733E0 *out = dst;
	const Rva004733E0 *in = src;
	while (in != end) {
		Rva0030CA53Set(out, in);
		++in;
		++out;
	}
	return out;
}
