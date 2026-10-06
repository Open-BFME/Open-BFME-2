// cl: /DNDEBUG /MD
//
// ?Rva0054115FCopy@@YAPAVRva0054103E@@PAV1@00@Z @0x0054115F (50B).
// Backward copy of 0x14-byte Rva0054103E via its rowed copy ctor at 0x0054103E.
// Count is (last-first)/0x14 via idiv; loop decrements last/result in place.
// Evidence: callee row Rva0054103ECopy.cpp; caller 0x005412C5 pushes 5 args
// and cleans 0x14; neighbours Rva0054103EFillN/UninitCopy share flags.

class Rva0054103E
{
	char _m[0x14];

public:
	Rva0054103E(const Rva0054103E &that);
};

Rva0054103E *Rva0054115FCopy(Rva0054103E *first, Rva0054103E *last, Rva0054103E *result)
{
	int n = ((char *)last - (char *)first) / 0x14;
	if (n <= 0)
		return result;
	int k = n;
	do {
		--last;
		--result;
		result->Rva0054103E::Rva0054103E(*last);
		--k;
	} while (k != 0);
	return result;
}
