// cl: /DNDEBUG /MD /EHsc
// ?Rva005E7285Copy@@YAPAVRva005E7198@@PAV1@00PAXH@Z @0x005E7285 47B
// forward copy for Rva005E7198 4B entries via rowed assign 0x005E7198 with dummy tag args.
// Same 47B shape as Rva005EF4C0Copy (forward *dest=*first ++first ++dest loop with sar 2 count)
// plus two dummy trailing args (tag pointer plus zero) that ride dead above the frame;
// caller 0x005E74A0 passes 5 args. Precedent: Rva0014FA90Copy 50B 5-arg forward copy.
class Rva005E7198
{
public:
	Rva005E7198 &operator=(const Rva005E7198 &other);
private:
	void *m_object;
};
Rva005E7198 *__cdecl Rva005E7285Copy(Rva005E7198 *first, Rva005E7198 *last, Rva005E7198 *dest, void *tag, int extra)
{
	int n = last - first;
	if (n <= 0)
		return dest;
	for (int i = n; i != 0; --i) {
		*dest = *first;
		++first;
		++dest;
	}
	return dest;
}
Rva005E7198 *__cdecl Rva005E748DForward(Rva005E7198 *first, Rva005E7198 *last, Rva005E7198 *dest, void *ignored)
{
	char tag;
	return Rva005E7285Copy(first, last, dest, &tag, 0);
}
