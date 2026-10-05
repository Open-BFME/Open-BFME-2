// cl: /O1 /MD /EHsc /DNDEBUG
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

class Rva00091DC4
{
public:
	void rva00091DC4(Rva0055A88BDwordField *p);

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
