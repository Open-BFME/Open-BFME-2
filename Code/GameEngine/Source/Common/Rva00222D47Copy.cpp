// cl: /O1 /DNDEBUG /EHsc /MD /Oy- /Oi-
// ?rva00222D47@Rva00222D47Target@@QAEXHHH@Z @0x00222D47 83B
// Target evidence: when the requested range starts before offset 1, copy the
// first byte from this, then copy the remaining bytes from the pointer at
// this+4 via the rowed memcpy import thunk. The existing address-derived pin
// supplies the member/three-int call shape; higher-level identity is unknown.

extern "C" void *__cdecl memcpy(void *destination, const void *source, unsigned int count);

class Rva00222D47Target
{
	char m_first;
	const char *m_bytes;

public:
	void rva00222D47(int destination, int offset, int count);
};

void Rva00222D47Target::rva00222D47(int destination, int offset, int count)
{
	if (offset < 1)
	{
		int first_count = count;
		if (offset + count > 1)
			first_count = 1 - offset;
		if (first_count > 0)
			*reinterpret_cast<char *>(destination) = m_first;
		count -= first_count;
		if (count <= 0)
			return;
		destination += first_count;
		offset += first_count;
	}
	memcpy(reinterpret_cast<void *>(destination), m_bytes + offset - 1, count);
}
