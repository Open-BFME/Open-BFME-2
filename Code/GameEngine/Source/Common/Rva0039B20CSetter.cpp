// cl: /DNDEBUG /MD /EHsc
// ?rva0039B20C@Rva0039B20C@@QAEXPAX@Z @0x0039B20C 27B conditional setter
// caching a pointer at +0x24 and refreshing the BfmeThingEFC at +0x2C via the
// rowed rva0039B1F9 at 0x0039B1F9. Evidence: chain from just-landed 0xB1F9;
// four callers pass [input+0xFC] with no extra args.

class BfmeThingEFC
{
public:
	void rva0039B1F9(void);
	void bfmeUpdate(int val);
};

class Rva0039B20C
{
public:
	void rva0039B20C(void *src);
	void rva0039B227(int val);
	void rva0039B246(void);

private:
	char m_pad00[0x20];
	bool m_flag20;
	char m_pad21[0x3];
	void *m_ptr24;
	char m_pad28[0x4];
	BfmeThingEFC *m_efc2C;
};

void Rva0039B20C::rva0039B20C(void *src)
{
	if (src == 0)
		return;
	if (m_ptr24 == src)
		return;
	m_ptr24 = src;
	m_efc2C->rva0039B1F9();
}

// ?rva0039B227@Rva0039B20C@@QAEXH@Z @ 0x0039B227 (31B):
// int setter updating the BfmeThingEFC at +0x2C via rowed bfmeUpdate at
// 0x0039B1E2 then clearing flag at +0x20 when arg equals +0x24. Class proven
// by immediate adjacency to 0x0039B20C (0x20C+27=0x227) sharing +0x24/+0x2C
// layout and flags; callers 0x39B249 0x39B285 pass +0x24.
void Rva0039B20C::rva0039B227(int val)
{
	m_efc2C->bfmeUpdate(val);
	if (m_ptr24 == (void *)val)
		m_flag20 = false;
}

// ?rva0039B246@Rva0039B20C@@QAEXXZ @ 0x0039B246 (9B):
// forwarder pushing +0x24 into rowed 0x0039B227. Same class as neighbours;
// callers pass this with no stack args; callee cleans its own push.
void Rva0039B20C::rva0039B246(void)
{
	rva0039B227((int)m_ptr24);
}
