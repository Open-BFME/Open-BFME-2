// cl: /O2
// 0x007EAD30 / 0x007EADC0: after a prepare helper, send either the flag
// string at +0x101/+0x142 or the +0x30/+0x70 pair through this+0xC.

class Rva007EADIface
{
public:
	virtual void v0();
	virtual void sendFlag(char *flag, int n, int tag, void *self);
	virtual void v2();
	virtual void sendPairC(char *a, char *b, int tag, void *self);
	virtual void sendPairD(char *a, char *b, int tag, void *self);
};

class Rva007EA320Owner;
class Rva007EA380Owner;
void __cdecl rva007EAD10BindCallback(Rva007EA320Owner *owner, void *first, void *second);
void __cdecl rva007EADA0BindCallback(Rva007EA380Owner *owner, void *first, void *second);

class Rva007EAD30Owner
{
public:
	void send();
	void prepare();

private:
	char m_pad00[0x0C];
	Rva007EADIface *m_iface;
	char m_pad10[0x20];
	char m_buf30[0x40];
	char m_buf70[0x91];
	char m_flag;
	char m_pad102[0x126];
	int m_n;
};

class Rva007EADC0Owner
{
public:
	void send();
	void prepare();

private:
	char m_pad00[0x0C];
	Rva007EADIface *m_iface;
	char m_pad10[0x20];
	char m_buf30[0x40];
	char m_buf70[0xD2];
	char m_flag;
	char m_pad143[0xE9];
	int m_n;
};

// The D30 and DC0 sends target their matched BFME2 callbacks at 0x00A57CB0
// and 0x00A57D40, respectively; the BFME1 donor uses different addresses.
void Rva007EAD30Owner::send()
{
	prepare();
	char *flag = &m_flag;
	if (m_flag)
	{
		int n = m_n;
		if (n <= 0)
			n = 0x34C1;
		m_iface->sendFlag(flag, n,
			reinterpret_cast<int>(&rva007EAD10BindCallback), this);
	}
	else
	{
		m_iface->sendPairC(m_buf30, m_buf70,
			reinterpret_cast<int>(&rva007EAD10BindCallback), this);
	}
}

void Rva007EADC0Owner::send()
{
	prepare();
	char *flag = &m_flag;
	if (m_flag)
	{
		int n = m_n;
		if (n <= 0)
			n = 0x37DC;
		m_iface->sendFlag(flag, n,
			reinterpret_cast<int>(&rva007EADA0BindCallback), this);
	}
	else
	{
		m_iface->sendPairD(m_buf30, m_buf70,
			reinterpret_cast<int>(&rva007EADA0BindCallback), this);
	}
}

// ?rva00657D30@Rva00657D30@@QAEXXZ @0x00657D30 8B member forwarder to rowed
// ?send@Rva007EAD30Owner@@QAEXXZ (0x00657CD0). No callers. Honest address name.
class Rva00657D30
{
public:
	void rva00657D30();
private:
	char m_pad[4];
	Rva007EAD30Owner *m_member;
};
void Rva00657D30::rva00657D30()
{
	return m_member->send();
}

// ?rva00657DC0@Rva00657DC0@@QAEXXZ @0x00657DC0 8B member forwarder to rowed
// ?send@Rva007EADC0Owner@@QAEXXZ (0x00657D60). No callers. Honest address name.
class Rva00657DC0
{
public:
	void rva00657DC0();
private:
	char m_pad[4];
	Rva007EADC0Owner *m_member;
};
void Rva00657DC0::rva00657DC0()
{
	return m_member->send();
}
