// cl: /MD
// ?rva005CC9CB@Rva005CC9CB@@QAEPAV1@PAV1@@Z @0x005CC9CB 45B: refcounted assign via inc 0x005D1A79 plus Release_Ref 0x005D1A7D; caller 0x005CCA18 unblocks 0x005CCA0B.
class Rva005D1A79DwordCounter
{
public:
	void inc();
};
class RefCountClass
{
public:
	void Release_Ref();
};
class Rva005CC9CB
{
public:
	Rva005CC9CB *rva005CC9CB(Rva005CC9CB *other);
private:
	void *m_0;
};

Rva005CC9CB *Rva005CC9CB::rva005CC9CB(Rva005CC9CB *other)
{
	if (this == other)
		return this;
	if (other->m_0 != 0)
		((Rva005D1A79DwordCounter *)other->m_0)->inc();
	if (m_0 != 0)
		((RefCountClass *)m_0)->Release_Ref();
	m_0 = other->m_0;
	return this;
}
