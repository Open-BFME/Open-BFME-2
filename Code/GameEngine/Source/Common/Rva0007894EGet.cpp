// cl: /DNDEBUG /MD
//
// ?rva0007894E@W3DHordeModelDrawManager@@QAE_NPAVRva0007894EOuter@@@Z @0x0007894E 61B probe v1
// Native call sites79FE7 and7A0F1 pass manager in ECX before this RET4 helper.
// The receiver is unused by the body; original helper name is unknown.
// Rename the former free-stdcall owner to preserve the observed member-call
// ABI. Outer+8 flags440/441 and vslotC4 follow target bytes.

class Rva00270260
{
public:
	bool rva00270260();
private:
	char m_pad00[0x440];
public:
	unsigned char m_440;
	unsigned char m_441;
};

class Rva0007894EOuter
{
public:
	virtual int v00() = 0;
	virtual int v01() = 0;
	virtual int v02() = 0;
	virtual int v03() = 0;
	virtual int v04() = 0;
	virtual int v05() = 0;
	virtual int v06() = 0;
	virtual int v07() = 0;
	virtual int v08() = 0;
	virtual int v09() = 0;
	virtual int v10() = 0;
	virtual int v11() = 0;
	virtual int v12() = 0;
	virtual int v13() = 0;
	virtual int v14() = 0;
	virtual int v15() = 0;
	virtual int v16() = 0;
	virtual int v17() = 0;
	virtual int v18() = 0;
	virtual int v19() = 0;
	virtual int v20() = 0;
	virtual int v21() = 0;
	virtual int v22() = 0;
	virtual int v23() = 0;
	virtual int v24() = 0;
	virtual int v25() = 0;
	virtual int v26() = 0;
	virtual int v27() = 0;
	virtual int v28() = 0;
	virtual int v29() = 0;
	virtual int v30() = 0;
	virtual int v31() = 0;
	virtual int v32() = 0;
	virtual int v33() = 0;
	virtual int v34() = 0;
	virtual int v35() = 0;
	virtual int v36() = 0;
	virtual int v37() = 0;
	virtual int v38() = 0;
	virtual int v39() = 0;
	virtual int v40() = 0;
	virtual int v41() = 0;
	virtual int v42() = 0;
	virtual int v43() = 0;
	virtual int v44() = 0;
	virtual int v45() = 0;
	virtual int v46() = 0;
	virtual int v47() = 0;
	virtual int v48() = 0;
	virtual int v49();
	int m_04;
	Rva00270260 *m_08;
};

class W3DHordeModelDrawManager {public: bool rva0007894E(Rva0007894EOuter *);};

bool W3DHordeModelDrawManager::rva0007894E(Rva0007894EOuter *p)
{
	Rva00270260 *s = p->m_08;
	if (!s->m_441)
		return false;
	else {
		if (s->rva00270260())
			return false;
		if (s->m_440)
			return false;
		return p->v49();
	}
}
