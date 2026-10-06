// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva002E1E9ACopy@@YAPAVRva002E0D93@@PAV1@00PAD@Z @0x002E1E9A 29B.
// Copy wrapper: forwards first three args plus fresh byte flag and 0 to rowed
// 0x002E17A0 copy; returns its result. Evidence: caller pushes 0x002E204D
// 0x002E2690 pass 4 args (three pointers plus byte address); body pushes 5
// (three forwarded plus local byte address plus 0) and propagates eax.
// Fourth arg is dead (never reads [ebp+0x14]); neighbours share /O1.
class Rva002E0D93
{
public:
	Rva002E0D93 &operator=(const Rva002E0D93 &other);
	char m_pad[0xD8];
};
Rva002E0D93 *Rva002E17A0Copy(Rva002E0D93 *src, Rva002E0D93 *srcEnd, Rva002E0D93 *dst, char *tmp, int zero);
Rva002E0D93 *Rva002E1E9ACopy(Rva002E0D93 *src, Rva002E0D93 *srcEnd, Rva002E0D93 *dst, char *ignored)
{
	char tmp;
	return Rva002E17A0Copy(src, srcEnd, dst, &tmp, 0);
}
