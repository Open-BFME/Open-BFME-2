// cl: /MD /EHsc /DNDEBUG
//
// ?rva00091DC4@Rva00091DC4@@QAEXPAVRva0055A88BDwordField@@@Z @0x00091DC4
// 31B: conditional forward. When the dword at +0x1C is nonzero, reads the
// rowed dword getter 0x0055A88B off the argument and forwards it to the
// pinned 11B stub 0x00068436 on the +0x14 member. Honest address-derived
// names; boundary verified (push esi at 0x91DC4, pop esi + ret 4 at end).

class Rva0055A88BDwordField
{
public:
	int get() const;
};

class Rva00068436
{
public:
	void rva00068436(int v);
};

class Rva00068415
{
public:
	void rva00068415();
};

class Rva00068420
{
public:
	void rva00068420();
};

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff
};

class Rva0006842B
{
public:
	void rva0006842B(ObjectID id);
};

class Rva00091DE3Arg
{
public:
	char m_pad00[0x74];
	int m_74;
};

class Rva00091DC4
{
public:
	void rva00091DC4(Rva0055A88BDwordField *p);
	void rva00091DE3(Rva00091DE3Arg *p);
	void rva00091DFB();
	void rva00091E0A();

private:
	char m_pad00[0x14];
	Rva00068436 *m_14;
	int m_18;
	int m_1C;
};

// ?rva00091DC4@Rva00091DC4@@QAEXPAVRva0055A88BDwordField@@@Z
void Rva00091DC4::rva00091DC4(Rva0055A88BDwordField *p)
{
	if (m_1C)
		m_14->rva00068436(p->get());
}

// ?rva00091DE3@Rva00091DC4@@QAEXPAVRva00091DE3Arg@@@Z
void Rva00091DC4::rva00091DE3(Rva00091DE3Arg *p)
{
	if (m_1C)
		((Rva0006842B *)m_14)->rva0006842B((ObjectID)p->m_74);
}

// ?rva00091DFB@Rva00091DC4@@QAEXXZ
void Rva00091DC4::rva00091DFB()
{
	if (m_1C)
		((Rva00068420 *)m_14)->rva00068420();
}

// ?rva00091E0A@Rva00091DC4@@QAEXXZ
void Rva00091DC4::rva00091E0A()
{
	if (m_1C)
		((Rva00068415 *)m_14)->rva00068415();
}
