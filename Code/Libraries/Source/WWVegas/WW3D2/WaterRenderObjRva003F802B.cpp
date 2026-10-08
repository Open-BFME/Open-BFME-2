// cl: /MD
//
// ?rva003F802B@Rva003F802B@@QAE_NXZ @0x003F802B 39B.
// Predicate on +8/+0xC gated by TheAudio vtable slot 0xD0.
// Evidence: cmp [ecx+8] 0 je false; cmp [ecx+0xC] 5 jb false;
// TheAudio ?TheAudio@@3PAVAudioManager@@A; call [edx+0xD0] push int test al;
// callers at 0x003F847B 0x003F8F97.
class AudioManager
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual bool v52(int v);
};

extern AudioManager *TheAudio;

class Rva003F802B
{
public:
	bool rva003F802B();
private:
	char m_pad00[8];
	void *m_08;
	int m_0C;
};

bool Rva003F802B::rva003F802B()
{
	if (m_08 && (unsigned int)m_0C >= 5 && TheAudio->v52(m_0C))
		return true;
	return false;
}

// Address-derived name: Rva003F8052 (21B, retail 0x003F8052). Null-guarded
// negated call to the 0x003F7D29 grid predicate through the pointer at +0x14.
class Rva003F7D29
{
public:
	unsigned char rva003F7D29();
};

class Rva003F8052
{
public:
	bool rva003F8052();
private:
	char m_pad00[0x14];
	Rva003F7D29 *m_14;
};

bool Rva003F8052::rva003F8052()
{
	Rva003F7D29 *p = m_14;
	if (p)
		return !p->rva003F7D29();
	return false;
}
