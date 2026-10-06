// cl: /DNDEBUG /MD /EHsc
// ?rva00211494@Rva00211494@@QAEXXZ, RVA 0x00211494, 113 bytes.
// Two back-to-back vectors of object pointers at +0x234/+0x240; each element
// virtual slot 3 (+0x0C) called in index order. Evidence: caller 0x002123BE
// calls this first with same this (its +0x218 hashtable pins WindowVideoManager).
struct Rva00211494_Item
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
};

struct Rva00211494
{
	unsigned char m_pad[0x234];
	Rva00211494_Item **m_vec1Begin; // +0x234
	Rva00211494_Item **m_vec1End; // +0x238
	void *m_vec1Cap; // +0x23C
	Rva00211494_Item **m_vec2Begin; // +0x240
	Rva00211494_Item **m_vec2End; // +0x244
	void *m_vec2Cap; // +0x248
	void rva00211494();
};

void Rva00211494::rva00211494()
{
	unsigned int i;
	for (i = 0; i < (unsigned int)(m_vec2End - m_vec2Begin); ++i)
		m_vec2Begin[i]->v3();
	for (i = 0; i < (unsigned int)(m_vec1End - m_vec1Begin); ++i)
		m_vec1Begin[i]->v3();
}
