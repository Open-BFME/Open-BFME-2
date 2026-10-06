// ?rva005E5CC7@@YAPAPAXPAPAXPBX@Z
// partial score=0.85 date=2026-10-06
// cl: /O1 /MD /Oy-
// ?rva005E5CC7@@YAPAPAXPAPAXPBX@Z retail 0x005E5CC7 50 bytes.
// Two-phase creator: allocates 0x14 via rowed operator new, placement-builds
// the rowed 0x005E59DF payload ctor from the arg, publishes to *pOut with a
// conditional refcount inc at +4, returns pOut. The volatile slot replicates
// retail's alignment zeroing. Address-derived names.
void *operator new(unsigned int size);
inline void *operator new(unsigned int, void *p) { return p; }

class Rva005E59DF
{
public:
	struct Payload { int v[3]; };
	Rva005E59DF(const Payload *src);
	virtual ~Rva005E59DF() {}
private:
	int m_vtbl;
	int m_ref;
	Payload m_data;
};

void **rva005E5CC7(void **pOut, const void *arg)
{
	int align;
	align &= 0;
	void *mem = operator new(0x14);
	Rva005E59DF *p;
	if (mem)
		p = new (mem) Rva005E59DF((const Rva005E59DF::Payload *)arg);
	else
		p = 0;
	*pOut = p;
	if (p)
		++((int *)p)[1];
	return pOut;
}
