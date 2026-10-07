// cl: /O1 /arch:SSE /G7 /MD
//
// ?rva003F816E@Rva003F81FDProxy@@QAEPAVRva003F8101@@XZ @0x003F816E 39B and
// ?rva003F81B0@Rva003F81FDProxy@@QAEPAVRva003F7D86Inner@@XZ @0x003F81B0 30B.
// ?rva003F819A@Rva003F81FDProxy@@QAEPAXXZ @0x003F819A 17B forwards the
// selected entry's result directly.
// ?rva003F85C6@Rva003F81FDProxy@@QAEEXZ @0x003F85C6 19B tests that result,
// then delegates to Rva003F8090::rva003F8536 when it is non-null.
// 0x003F816E is the +0x14/+0x18 twin of the rowed 0x003F8101 lookup: the
// entry whose +8 id is TheLivingWorldLogic's +0xFC plus one, else null.
// 0x003F81B0 chains it through 0x003F8101 into the rowed 0x003F80C3,
// returning null when a link is missing; the matched callers in
// Rva003F830F.cpp and VslotProxyForwarders.cpp pin it at this address.
// The callees live in other units so neither call is inlined here.

class LivingWorldLogic
{
public:
	char m_pad00[0xFC];
	int m_xFC;
};

extern LivingWorldLogic *TheLivingWorldLogic;	// 0x00DFEF10

class Rva003F7D86Inner;

class Rva003F8090
{
public:
	void rva003F8090();
	unsigned char rva003F8536();
	void *rva003F80C3();						// 0x003F80C3
};

class Rva003F8101
{
public:
	void *rva003F8101();						// 0x003F8101
};

struct Rva003F816EItem
{
	char m_pad00[8];
	int m_id08;
};

class Rva003F81FDProxy
{
public:
	__declspec(noinline) Rva003F8101 *rva003F816E();
	void *rva003F819A();
	unsigned char rva003F85C6();
	Rva003F7D86Inner *rva003F81B0();
private:
	char m_pad00[0x14];
	Rva003F816EItem **m_begin14;
	Rva003F816EItem **m_end18;
};

Rva003F8101 *Rva003F81FDProxy::rva003F816E()
{
	Rva003F816EItem **p = m_begin14;
	Rva003F816EItem **end = m_end18;
	int sought = TheLivingWorldLogic->m_xFC + 1;
	for (; p != end; ++p)
	{
		Rva003F816EItem *it = *p;
		if (it->m_id08 == sought)
			return (Rva003F8101 *)it;
	}
	return 0;
}

class Rva003F80E6
{
public:
	void rva003F80E6();
private:
	char m_pad00[0x0C];
	Rva003F8090 **m_begin0C;
	Rva003F8090 **m_end10;
};

class Rva003F812C
{
public:
	void rva003F812C();
private:
	char m_pad00[0x14];
	Rva003F80E6 **m_begin14;
	Rva003F80E6 **m_end18;
	char m_pad1C[4];
	unsigned char m_flag20;
};

void Rva003F812C::rva003F812C()
{
	Rva003F80E6 **p = m_begin14;
	Rva003F80E6 **end = m_end18;
	m_flag20 = 0;
	for (; p != end; ++p)
		(*p)->rva003F80E6();
}

void Rva003F80E6::rva003F80E6()
{
	Rva003F8090 **p = m_begin0C;
	Rva003F8090 **end = m_end10;
	for (; p != end; ++p)
		(*p)->rva003F8090();
}

void *Rva003F81FDProxy::rva003F819A()
{
	Rva003F8101 *entry = rva003F816E();
	if (entry == 0)
		return 0;
	return entry->rva003F8101();
}

unsigned char Rva003F81FDProxy::rva003F85C6()
{
	Rva003F8090 *inner = (Rva003F8090 *)rva003F819A();
	if (inner != 0)
		return inner->rva003F8536();
	return 1;
}

Rva003F7D86Inner *Rva003F81FDProxy::rva003F81B0()
{
	Rva003F8101 *entry = rva003F816E();
	if (entry == 0)
		return 0;
	Rva003F8090 *inner = (Rva003F8090 *)entry->rva003F8101();
	if (inner == 0)
		return 0;
	return (Rva003F7D86Inner *)inner->rva003F80C3();
}
