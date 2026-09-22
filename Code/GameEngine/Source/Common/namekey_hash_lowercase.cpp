// cl: /O2 /DNDEBUG /MD
// BFME2 lowercase DJB2 hash; retail RVA0x0061FCA0 through RET. Twin of the
// plain calcHashForString in namekey_hash.cpp (which is /O1 with shift+add);
// this twin folds every byte through the CRT tolower import and retail
// multiplies by 0x21 with imul, so it lives in its own /O2 TU.
// nameToLowercaseKey calls it for every lookup (pinned Rva0061FCA0Hash).
extern "C" __declspec(dllimport) int tolower(int c);

__declspec(noinline) unsigned int calcHashForLowercaseString(const char *p)
{
	unsigned int result = 0;
	const unsigned char *pp = (const unsigned char *)p;
	while (*pp)
		result = (result << 5) + result + tolower(*pp++);
	return result;
}
