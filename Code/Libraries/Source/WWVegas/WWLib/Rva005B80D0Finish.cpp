// cl: /O1 /Oy- /arch:SSE
// ?rva005B80D0@@YAMEPAVRva005B8053@@@Z @0x005B80D0 34B: byte-key float lookup.
// Evidence: calls rowed lower_bound 0x005B8053; compares result to [esi] header and reads float at +0x14 else 0.0f via movss xorps; same family as 0x005B808D 0x005B80AF 0x005B80F2.
class Rva005B8053
{
	void *m_header;
public:
	void *rva005B8053(unsigned char const *key);
};

static float rva005B80D0(unsigned char key, Rva005B8053 *self)
{
	((unsigned char *)&key)[3] = key;
	void *node = self->rva005B8053((unsigned char const *)((char *)&key + 3));
	if (node == *(void **)self)
		return 0.0f;
	return *(float *)((char *)node + 0x14);
}

// ?rva005B80D0Caller@@YAMEPAVRva005B8053@@@Z absent-from-retail
float rva005B80D0Caller(unsigned char key, Rva005B8053 *self)
{
	return rva005B80D0(key, self) + rva005B80D0(key, self);
}
