// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003F74F5Fill@@YAPAVRva004F6093Holder@@PAV1@IABV1@@Z @0x003F74F5 37B.
// Honest __uninitialized_fill_n for the 4-byte Rva004F6093Holder through the
// rowed 0x002B2FE2 null-checked placement copy.
// Evidence: retail push esi; mov esi,[esp+8]; push edi; mov edi,[esp+0x10];
// test edi,edi; jbe end; loop push [esp+0x14]; push esi; call 0x002B2FE2;
// pop ecx; add esi,4; dec edi; pop ecx; jne loop; pop edi; mov eax,esi;
// pop esi; ret. Caller at 0x003F7A0B. Mirrors the 37B Pod104 fill_n at 0x003B8B05
// with stride 4 and Holder copy.
struct Rva004F6093Ref
{
	char m_pad[0xB0];
	int m_refCount;
};
#include "../../Include/Common/Rva004F6093Holder.h"
void __cdecl Rva002B2FE2Copy(Rva004F6093Holder *dst, const Rva004F6093Holder &src);

Rva004F6093Holder *__cdecl Rva003F74F5Fill(Rva004F6093Holder *first, unsigned int count, const Rva004F6093Holder &fillValue)
{
	Rva004F6093Holder *cur = first;
	for (; count > 0; --count, ++cur)
		Rva002B2FE2Copy(cur, fillValue);
	return cur;
}
