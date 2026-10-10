// cl: /DNDEBUG /MD
// ?rva005E18B9@Rva005E18B9@@QAEXXZ @0x005E18B9 16B unlock vcall forwarder via member vtables.
// Evidence: retail mov eax ecx mov ecx [eax] mov eax [eax+0x24] push [eax+0x14] vcall [edx+0x14] ret; guard caller 0x005E18D0 tests +0x24 then jumps here; caller 0x005E19CA 189B.
class Rva005E18B9Inner
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14(int value);
	virtual void v18();
};

class Rva005E18B9Other
{
public:
	char m_pad[0x14];
	int m_14;
};

class Rva005E18B9
{
protected:
	Rva005E18B9Inner *m_0;
	char m_pad[0x20];
	Rva005E18B9Other *m_24;
public:
	void rva005E18B9();
};

void Rva005E18B9::rva005E18B9()
{
	m_0->v14(m_24->m_14);
}

class Rva005E18D0Forwarder : public Rva005E18B9
{
public:
	void tail005E18D0();
};

// Exact guarded forwarder owned by Rva005E18D0Forwarders.cpp.

class Rva005E18DCForwarder : public Rva005E18B9
{
public:
	void tail005E18DC();
};

// Exact guarded forwarder owned by Rva005E18D0Forwarders.cpp.

