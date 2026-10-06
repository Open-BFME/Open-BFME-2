// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva005F8FA2Copy@@YAPAURva005F8FA2Dst@@PAU1@PAURva005F8FA2Src@@H@Z @0x005F8FA2 42B.
// Evidence: finish lane; 8-dword src plus dword tail via temp to 9-dword dest;
// callers 0x005F9DCB x3; prev Rva005F8F96Dtor next Rva005F8FCCDeleting;
// returns dest in eax at ret so YAPA not YAX.

struct Rva005F8FA2Src
{
	int m_data[8];
};

struct Rva005F8FA2Dst
{
	int m_data[9];
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

Rva005F8FA2Dst *__cdecl Rva005F8FA2Copy(Rva005F8FA2Dst *dest, Rva005F8FA2Src *src, int value)
{
	Rva005F8FA2Dst tmp;
	*(Rva005F8FA2Src *)&tmp = *src;
	tmp.m_data[8] = value;
	_ReadWriteBarrier();
	*dest = tmp;
	return dest;
}
