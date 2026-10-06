// cl: /DNDEBUG /MD
//
// ?rva003427A9@Rva003427A9@@QAEXPAVXfer@@@Z @0x003427A9 42B.
//
// Xfer-driven member transfer: Version1 (rowed 0x000053EE) on the stream,
// then the stream's virtual slots 30 and 24 over the +0x4C/+0x50 members
// in that order (the second call reuses edi via add, the vptr reloads).
// No direct caller exists, so this is a virtual (xfer-family) body;
// the member types are unestablished, hence plain ints carried only for
// their addresses. Slot contents are deliberately unnamed pure virtuals:
// indirect calls encode only the slot, and the two slot identities are
// not yet proven (the BFME2 Xfer operator== view would put Region3D and
// RealRange here, but those overlap, so the count is not trusted).

class Xfer
{
public:
	void Version1();
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual void v19() = 0;
	virtual void v20() = 0;
	virtual void v21() = 0;
	virtual void v22() = 0;
	virtual void v23() = 0;
	virtual void v24(void *p) = 0;
	virtual void v25() = 0;
	virtual void v26() = 0;
	virtual void v27() = 0;
	virtual void v28() = 0;
	virtual void v29() = 0;
	virtual void v30(void *p) = 0;
};

class Rva003427A9
{
public:
	void rva003427A9(Xfer *x);
private:
	char m_pad00[0x4c];
	int m_4c; // +0x4C
	int m_50; // +0x50
};

void Rva003427A9::rva003427A9(Xfer *x)
{
	x->Version1();
	x->v30(&m_4c);
	x->v24(&m_50);
}
