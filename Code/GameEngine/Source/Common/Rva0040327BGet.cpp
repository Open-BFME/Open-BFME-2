// cl: /DNDEBUG /MD
// ?rva0040327B@Rva0040327B@@QAEPAXPAVObject@@@Z retail 0x0040327B 88B
// Guarded indexed fetch from +0xb4 array: if !m_d0 return m_b4[0]; if !obj
// return m_b4[0]; pool=obj->findAttributeModifierPoolUpdate else return m_b4[0];
// idx=pool->rva004031C9(m_0c)-1; clamped=idx>2?2:idx; if clamped<0 return
// m_b4[0]; return m_b4[clamped]. Evidence: cmp byte d0 je test je call test je
// push call dec push-2-pop mov cmp mov lea jg lea mov test jl mov; unblocks 1.
class AttributeModifierPoolUpdate
{
public:
	int rva004031C9(int index);
};
class Object
{
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
	friend class Rva0040327B;
};
class Rva0040327B
{
public:
	void *rva0040327B(Object *obj);
	void *rva004032D3(Object *obj);
private:
	char _pad0[0x0C];
	int m_0c;
	char _pad1[0xA4];
	void *m_b4[3];
	void *m_c0[3];
	char _pad2[0x04];
	bool m_d0;
};
void *Rva0040327B::rva0040327B(Object *obj)
{
	if (!m_d0)
		return m_b4[0];
	if (obj == 0)
		return m_b4[0];
	AttributeModifierPoolUpdate *pool = obj->findAttributeModifierPoolUpdate();
	if (pool == 0)
		return m_b4[0];
	int idx = pool->rva004031C9(m_0c) - 1;
	int two = 2;
	int *pp = idx > 2 ? &two : &idx;
	int clamped = *pp;
	if (clamped >= 0)
		return m_b4[clamped];
	return m_b4[0];
}
// ?rva004032D3@Rva0040327B@@QAEPAXPAVObject@@@Z retail 0x004032D3 88B sibling of
// rva0040327B differing only by array offset +0xc0 vs +0xb4; same guarded fetch
// via pool and clamp evidence; chain from 0x004031C9.
void *Rva0040327B::rva004032D3(Object *obj)
{
	if (!m_d0)
		return m_c0[0];
	if (obj == 0)
		return m_c0[0];
	AttributeModifierPoolUpdate *pool = obj->findAttributeModifierPoolUpdate();
	if (pool == 0)
		return m_c0[0];
	int idx = pool->rva004031C9(m_0c) - 1;
	int two = 2;
	int *pp = idx > 2 ? &two : &idx;
	int clamped = *pp;
	if (clamped >= 0)
		return m_c0[clamped];
	return m_c0[0];
}
