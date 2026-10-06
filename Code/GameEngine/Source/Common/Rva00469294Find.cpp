// cl: /MD
// ?rva00469294@Rva00469294@@QAEPAXH@Z 0x00469294 38B evidence: ptr-vector search key at [eax] callers 0x46AF67 0x472421 0x472CDC 0x474D57 0x470D4E ret ptr+4 is AsciiString
struct Rva00469294Entry
{
	int m_key;
	char m_pad[4];
};
class Rva00469294
{
public:
	void *rva00469294(int key);
private:
	char m_pad[0x18c];
	Rva00469294Entry **m_begin;
	Rva00469294Entry **m_end;
};
void *Rva00469294::rva00469294(int key)
{
	for (Rva00469294Entry **p = m_begin; p != m_end; ++p) {
		Rva00469294Entry *e = *p;
		if (key == e->m_key)
			return e;
	}
	return 0;
}
