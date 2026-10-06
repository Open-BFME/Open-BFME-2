// cl: /MD
//
// ?rva004B6B04@@YGXPAVBfmeObjF9@@PAXD@Z, retail 0x004B6B04, 37 bytes.
// Free __stdcall helper called by the two unclaimed GeometryUpgrade bodies
// 0x004B6B29 and 0x004B6C8A (each calls it twice): iterates a 4-byte-element
// vector (begin at [vec], end at [vec+4], element is BfmeStrF9 which is 4
// bytes) and calls the rowed BfmeObjF9::setFlag at 0x006BF3C0 for each
// element with the char flag. Prev is the rowed GeometryUpgrade pool key
// 0x004B6ABF and next is the rowed GeometryUpgrade xfer 0x004B6C02.
// Identity stays honest address name; BfmeObjF9/BfmeStrF9 spellings are the
// rowed Rva0087F9C0Flag TU names so the callee mangled matches.

class BfmeStrF9
{
private:
	void *m_data;
};

class BfmeObjF9
{
public:
	void setFlag(const BfmeStrF9 &name, char flag);
};

struct BfmeStrVec
{
	BfmeStrF9 *m_begin;
	BfmeStrF9 *m_end;
};

void __stdcall rva004B6B04(BfmeObjF9 *obj, void *vecVoid, char flag)
{
	BfmeStrVec *vec = (BfmeStrVec *)vecVoid;
	for (BfmeStrF9 *p = vec->m_begin; p != vec->m_end; ++p)
		obj->setFlag(*p, flag);
}
