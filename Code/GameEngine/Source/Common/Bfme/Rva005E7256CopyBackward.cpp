// cl: /DNDEBUG /MD /EHsc
// ?Rva005E7256CopyBackward@@YAPAVRva005E7198@@PAV1@00PAXH@Z @0x005E7256 47B
// copy_backward for Rva005E7198 4B entries via rowed assign 0x005E7198 with dummy tag args.
// Same 47B shape as Rva002195B7CopyBackward (backwards --last/--dest loop with sar 2 count)
// plus two dummy trailing args (tag pointer plus zero); caller 0x005E7483 passes 5 args.
class Rva005E7198
{
public:
	Rva005E7198 &operator=(const Rva005E7198 &other);
private:
	void *m_object;
};
Rva005E7198 *__cdecl Rva005E7256CopyBackward(Rva005E7198 *first, Rva005E7198 *last, Rva005E7198 *dest, void *tag, int extra)
{
	int n = last - first;
	if (n <= 0)
		return dest;
	for (int i = n; i != 0; --i) {
		--last;
		--dest;
		*dest = *last;
	}
	return dest;
}
Rva005E7198 *__cdecl Rva005E7470Forward(Rva005E7198 *first, Rva005E7198 *last, Rva005E7198 *dest, void *ignored)
{
	char tag;
	return Rva005E7256CopyBackward(first, last, dest, &tag, 0);
}
