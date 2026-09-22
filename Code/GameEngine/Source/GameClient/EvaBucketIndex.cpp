// cl: /O1 /DNDEBUG /MD /EHsc
// ?bucketIndex@Rva000427195@@QAEHPBVAsciiString@@@Z, retail 0x00223149 (29B).
// Shard TU: hash-mod-count leaf over the Eva bucket vector. The hash comes
// from the rowed EvaAsciiHash helper (chars-or-empty into the STLport
// string hash); the count is the plain end-minus-begin byte span quartered.
// Separate from that helper's TU so neither captures the other's call site
// (same-TU visibility law).

class AsciiString
{
	char *m_text;
};

class Rva000427195
{
public:
	void *first(void *iter);
	int bucketIndex(const AsciiString *name);
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
};

unsigned int __stdcall Rva00055041AsciiHash(const AsciiString *name);

// ?bucketIndex@Rva000427195@@QAEHPBVAsciiString@@@Z
int Rva000427195::bucketIndex(const AsciiString *name)
{
	unsigned hash = Rva00055041AsciiHash(name);
	unsigned count = (unsigned)(((char *)m_endBuckets - (char *)m_beginBuckets) >> 2);
	return hash % count;
}
