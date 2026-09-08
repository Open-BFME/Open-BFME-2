// cl: /O1 /DNDEBUG /MD
// BFME2 signed-character DJB2 hash; retail RVA0x00148A98 through RET.
__declspec(noinline) unsigned int calcHashForString(const char* p)
{
	unsigned int result = 0;
	const char *pp = p;
	while (*pp)
		result = (result << 5) + result + *pp++;
	return result;
}
