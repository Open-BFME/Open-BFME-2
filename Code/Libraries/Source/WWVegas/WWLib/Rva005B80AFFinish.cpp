// cl: /O1 /Oy- /arch:SSE
// ?rva005B80AF@@YAHEPAVRva005B8053@@@Z @0x005B80AF 33B: byte-key int lookup.
// Follows the rowed 0x005B808D/0x005B80D0 twins exactly (same prologue,
// same lower_bound call, same header compare): compares the result to the
// header and reads the int at +0x14 else 0. Targets from retail REL32.
class Rva005B8053
{
	void *m_header;
public:
	void *rva005B8053(unsigned char const *key);
};

static int rva005B80AF(unsigned char key, Rva005B8053 *self)
{
	((unsigned char *)&key)[3] = key;
	void *node = self->rva005B8053((unsigned char const *)((char *)&key + 3));
	if (node == *(void **)self)
		return 0;
	return *(int *)((char *)node + 0x14);
}

// ?rva005B80AFCaller@@YAHEPAVRva005B8053@@@Z absent-from-retail
int rva005B80AFCaller(unsigned char key, Rva005B8053 *self)
{
	return rva005B80AF(key, self) + rva005B80AF(key, self);
}
