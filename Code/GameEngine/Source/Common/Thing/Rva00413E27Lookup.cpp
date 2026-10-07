// cl: /MD /EHsc /O1 /arch:SSE /G7 /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?rva00413E27@Rva00413E27@@QAEPAURva00413E27Bucket@@H@Z @0x00413E27 46B.
// Packet evidence: scans bucket records at +0x18 stride and returns the
// record containing the requested key; caller identity is not yet proven.

struct Rva00413E27Bucket
{
	int *m_first;
	int *m_last;
	char m_pad[0x10];
};

struct Rva00413E27
{
	char m_pad[0x0c];
	Rva00413E27Bucket *m_first;
	Rva00413E27Bucket *m_last;
	Rva00413E27Bucket *rva00413E27(int key);
};

Rva00413E27Bucket *Rva00413E27::rva00413E27(int key)
{
	Rva00413E27Bucket *bucket = m_first;
	Rva00413E27Bucket *last = m_last;
	if (bucket != last) {
		do {
			int *entry = bucket->m_first;
			int *end = bucket->m_last;
			while (entry != end) {
				if (*entry == key)
					return bucket;
				++entry;
			}
			++bucket;
		} while (bucket != last);
	}
	return 0;
}
