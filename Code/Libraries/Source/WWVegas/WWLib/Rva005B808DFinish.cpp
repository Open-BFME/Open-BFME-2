// cl: /O1 /Oy-
// ?rva005B808D@@YAHEPAVRva005B8053@@@Z @0x005B808D 34B: byte-key lookup.
// Evidence: calls rowed lower_bound 0x005B8053; compares result to [esi] header and reads word at +0x12 else 0; same family as 0x005B80AF 0x005B80D0 0x005B80F2; callers in 0x005B8116 0x005B8A40.
class Rva005B8053
{
	void *m_header;
public:
	void *rva005B8053(unsigned char const *key);
};

static int rva005B808D(unsigned char key, Rva005B8053 *self)
{
	((unsigned char *)&key)[3] = key;
	void *node = self->rva005B8053((unsigned char const *)((char *)&key + 3));
	if (node == *(void **)self)
		return 0;
	return *(unsigned short *)((char *)node + 0x12);
}

// ?rva005B808DCaller@@YAHEPAVRva005B8053@@@Z absent-from-retail
int rva005B808DCaller(unsigned char key, Rva005B8053 *self)
{
	return rva005B808D(key, self) + rva005B808D(key, self);
}
