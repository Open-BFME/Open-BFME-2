// cl: /MD
// ?rva000B3814@Rva000B3814@@QAEXPAVRva000B3814Arg@@M@Z @0x000B3814 113B
// Unlock lane: this+0x1c9 flag, callee slots 0x5c (int,float) and 0x194 (int),
// float global g_Va00BBB8D8 (1.0f). Caller 0x000B38F9. Neighbours DispByteOneSetters/Rva000B3A68.
extern float g_Va00BBB8D8;

class Rva000B3814Arg
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
	virtual void v23(int a, float b);
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
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual void v70();
	virtual void v71();
	virtual void v72();
	virtual void v73();
	virtual void v74();
	virtual void v75();
	virtual void v76();
	virtual void v77();
	virtual void v78();
	virtual void v79();
	virtual void v80();
	virtual void v81();
	virtual void v82();
	virtual void v83();
	virtual void v84();
	virtual void v85();
	virtual void v86();
	virtual void v87();
	virtual void v88();
	virtual void v89();
	virtual void v90();
	virtual void v91();
	virtual void v92();
	virtual void v93();
	virtual void v94();
	virtual void v95();
	virtual void v96();
	virtual void v97();
	virtual void v98();
	virtual void v99();
	virtual void v100();
	virtual void v101(int a);
};

class Rva000B3814
{
public:
	void rva000B3814(Rva000B3814Arg *o, float f);
private:
	char m_pad[0x1C9];
	unsigned char m_flag;
};

void Rva000B3814::rva000B3814(Rva000B3814Arg *o, float f)
{
	if (f <= 0.0f) {
		o->v23(1, 0.0f);
		o->v101(1);
	} else {
		o->v101(0);
		if (f >= g_Va00BBB8D8) {
			o->v23(1, 1.0f);
		} else {
			o->v23(1, f);
			m_flag = 1;
		}
	}
}
