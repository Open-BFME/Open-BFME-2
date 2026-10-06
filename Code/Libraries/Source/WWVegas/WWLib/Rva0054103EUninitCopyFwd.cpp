// cl: /DNDEBUG /MD
// ?Rva005410B1Copy@@YAPAVRva0054103E@@PAV1@00@Z @0x005410B1 50B.
// Forward copy of 0x14-byte Rva0054103E via its rowed copy ctor at 0x0054103E.
// Count is (last-first)/0x14 via idiv; loop advances first/result in place.
// Same shape as rowed backward ?Rva0054115FCopy@@ at 0x0054115F but forward.
// Evidence: callee row Rva0054103ECopy.cpp; caller 0x00541244; neighbours share flags.
class Rva0054103E
{
	char _m[0x14];

public:
	Rva0054103E(const Rva0054103E &that);
};

Rva0054103E *Rva005410B1Copy(Rva0054103E *first, Rva0054103E *last, Rva0054103E *result)
{
	int n = ((char *)last - (char *)first) / 0x14;
	if (n <= 0)
		return result;
	int k = n;
	do {
		result->Rva0054103E::Rva0054103E(*first);
		++first;
		++result;
		--k;
	} while (k != 0);
	return result;
}
