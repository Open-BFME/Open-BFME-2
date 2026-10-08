// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003F74CFCopy@@YAPAVRva004F6093Holder@@PAV1@00@Z @0x003F74CF 38B.
// Honest __uninitialized_copy for the 4-byte Rva004F6093Holder through the
// rowed 0x002B2FE2 null-checked placement copy.
// Evidence: retail push esi; mov esi,[esp+0x10]; push edi; mov edi,[esp+0xC];
// jmp check; push edi; push esi; call 0x002B2FE2; pop ecx; add edi,4; pop ecx;
// add esi,4; cmp edi,[esp+0x10]; jne loop; pop edi; mov eax,esi; pop esi; ret.
// Callers at 0x002B55DF 0x002B7237 0x003F79DE 0x003F7A29 0x0040CAF1.
// Sibling of the 37B fill_n at 0x003F74F5 with same Holder copy.
struct Rva004F6093Ref
{
	char m_pad[0xB0];
	int m_refCount;
};
class Rva004F6093Holder
{
public:
	Rva004F6093Holder(const Rva004F6093Holder &other) throw();
private:
	Rva004F6093Ref *m_ptr;
};
void __cdecl Rva002B2FE2Copy(Rva004F6093Holder *dst, const Rva004F6093Holder &src);

Rva004F6093Holder *__cdecl Rva003F74CFCopy(Rva004F6093Holder *first, Rva004F6093Holder *last, Rva004F6093Holder *result)
{
	Rva004F6093Holder *cur = result;
	for (; first != last; ++first, ++cur)
		Rva002B2FE2Copy(cur, *first);
	return cur;
}
