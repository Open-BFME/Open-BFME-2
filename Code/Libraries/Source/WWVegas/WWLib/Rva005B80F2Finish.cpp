// cl: /O1 /Oy- /arch:SSE
// ?rva005B80F2@@YAMEMPAVRva005B8053@@@Z @0x005B80F2 36B: byte-key float lookup
// with caller default. Follows the rowed 0x005B808D/0x005B80D0 twins (same
// prologue, same lower_bound call, same header compare) but returns the
// caller-passed float on miss instead of 0.0f. Targets from retail REL32.
class Rva005B8053
{
	void *m_header;
public:
	void *rva005B8053(unsigned char const *key);
};

static float rva005B80F2(unsigned char key, float def, Rva005B8053 *self)
{
	((unsigned char *)&key)[3] = key;
	void *node = self->rva005B8053((unsigned char const *)((char *)&key + 3));
	if (node == *(void **)self)
		return def;
	return *(float *)((char *)node + 0x14);
}

// ?rva005B80F2Caller@@YAMEMPAVRva005B8053@@@Z absent-from-retail
float rva005B80F2Caller(unsigned char key, float def, Rva005B8053 *self)
{
	return rva005B80F2(key, def, self) + rva005B80F2(key, def, self);
}
