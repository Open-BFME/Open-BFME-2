// ?rva00466D50@Rva00466D50@@QAE_NI@Z
// partial score=0.9604734945959856 date=2026-10-10
// ?rva00466D50@Rva00466D50@@QAE_NI@Z
// partial score=0.93 date=2026-09-28
// ?rva00466D50@Rva00466D50@@QAE_NI@Z
// partial score=0.93 date=2026-09-28
// cl: /O1 /DNDEBUG /MD
// ?rva00466D50@Rva00466D50@@QAE_NI@Z retail 0x00466D50 67B
// Predicate over member object at +0x20 with 70 virtuals: calls slot 69
// with 0 then slot 51 then slot 28 compares sum versus arg. Evidence:
// three virtual calls at +0x114 +0xCC +0x70 plus neg/sbb style bool return
// via sbb eax inc and early xor al for null arg; caller at 0x00468188;
// neighbours share /O1 /DNDEBUG /MD. Honest Rva name.
class Inner00466D50
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
	virtual int v69(int);
};
class Rva00466D50
{
public:
	bool rva00466D50(unsigned int arg);
private:
	char m_pad[32];
	Inner00466D50 m_20;
};
// ?rva00466D50@Rva00466D50@@QAE_NI@Z present-unmatched
bool Rva00466D50::rva00466D50(unsigned int arg){if(arg==0)return false;unsigned int t=m_20.v69(0);unsigned int b=m_20.v51();unsigned int *pt=&t;*pt+=arg;b+=*pt;unsigned int c=m_20.v28();return c>=b;}
