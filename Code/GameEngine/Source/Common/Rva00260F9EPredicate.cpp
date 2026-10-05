// cl: /O1 /MD /GX
// ?rva00260F9E@Rva00260F9E@@QAE_NH@Z @0x00260F9E (50B): bool with vcall.
// Retail: esi=ecx; ecx=[esp+8] (arg); call Object::rva0028C197 (0x28C197
// rowed) on arg; test eax,eax; je skip; push [esi+8]; edx=[eax];
// ecx=eax; call [edx+0x180] (v96); test eax,eax; jbe skip2; al=[esi+12];
// jmp ret; skip2: xor eax,eax; cmp [esi+12],al; sete al; pop esi; ret 4.
// Single int arg, bool return; no EH; address-derived outer; real Object
// view for rowed mangling; 97-virtual inner for slot 96.
// NOTE: initial guess; expects add_match verification.
class Object
{
public:
	void *rva0028C197() const;
};

class Rva00260F9EInner
{
public:
	virtual int v00();
	virtual int v01();
	virtual int v02();
	virtual int v03();
	virtual int v04();
	virtual int v05();
	virtual int v06();
	virtual int v07();
	virtual int v08();
	virtual int v09();
	virtual int v10();
	virtual int v11();
	virtual int v12();
	virtual int v13();
	virtual int v14();
	virtual int v15();
	virtual int v16();
	virtual int v17();
	virtual int v18();
	virtual int v19();
	virtual int v20();
	virtual int v21();
	virtual int v22();
	virtual int v23();
	virtual int v24();
	virtual int v25();
	virtual int v26();
	virtual int v27();
	virtual int v28();
	virtual int v29();
	virtual int v30();
	virtual int v31();
	virtual int v32();
	virtual int v33();
	virtual int v34();
	virtual int v35();
	virtual int v36();
	virtual int v37();
	virtual int v38();
	virtual int v39();
	virtual int v40();
	virtual int v41();
	virtual int v42();
	virtual int v43();
	virtual int v44();
	virtual int v45();
	virtual int v46();
	virtual int v47();
	virtual int v48();
	virtual int v49();
	virtual int v50();
	virtual int v51();
	virtual int v52();
	virtual int v53();
	virtual int v54();
	virtual int v55();
	virtual int v56();
	virtual int v57();
	virtual int v58();
	virtual int v59();
	virtual int v60();
	virtual int v61();
	virtual int v62();
	virtual int v63();
	virtual int v64();
	virtual int v65();
	virtual int v66();
	virtual int v67();
	virtual int v68();
	virtual int v69();
	virtual int v70();
	virtual int v71();
	virtual int v72();
	virtual int v73();
	virtual int v74();
	virtual int v75();
	virtual int v76();
	virtual int v77();
	virtual int v78();
	virtual int v79();
	virtual int v80();
	virtual int v81();
	virtual int v82();
	virtual int v83();
	virtual int v84();
	virtual int v85();
	virtual int v86();
	virtual int v87();
	virtual int v88();
	virtual int v89();
	virtual int v90();
	virtual int v91();
	virtual int v92();
	virtual int v93();
	virtual int v94();
	virtual int v95();
	virtual int v96(int arg);
};

class Rva00260F9E
{
public:
	bool rva00260F9E(int arg);
private:
	char m_pad00[0x08];
	int m_08;
	bool m_0C;
};

// ?rva00260F9E@Rva00260F9E@@QAE_NH@Z
bool Rva00260F9E::rva00260F9E(int arg)
{
	Object *o = (Object *)arg;
	void *p = o->rva0028C197();
	if (p == 0) {
		return m_0C == 0;
	}
	Rva00260F9EInner *inner = (Rva00260F9EInner *)p;
	int r = inner->v96(m_08);
	if ((unsigned)r > 0) {
		return *(bool *)((char *)this + 0x0C);
	}
	return m_0C == 0;
}
