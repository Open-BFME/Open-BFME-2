// cl: /MD
//
// ?rva004CD4DC@Rva004CD4DC@@QAEXPAVObject@@@Z @0x004CD4DC (63B).
// Update FX dispatcher via rowed Object::rva0029439D 0x29439D and
// rowed FXList::doFXObj 0xB2235 with virtual slot 0x1EC on the
// rva0029439D result. Retail saves this+4 to esi then calls
// rva0029439D on the Object arg and on non-null pair forwards
// [esi+0xD8] through the virtual else through static doFXObj
// with (fx primary 0). Callers at 0x004CD5CB 0x004CD662.
class Object;
class FXList;
class Rva004CD4DCItem;

class Object
{
public:
	void *rva0029439D();
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class Rva004CD4DCItem
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
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
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual void v110();
	virtual void v111();
	virtual void v112();
	virtual void v113();
	virtual void v114();
	virtual void v115();
	virtual void v116();
	virtual void v117();
	virtual void v118();
	virtual void v119();
	virtual void v120();
	virtual void v121();
	virtual void v122();
	virtual void target(const FXList *fx);
};

struct Rva004CD4DCMid
{
	unsigned char m_pad[0xD8];
	const FXList *m_fx;
};

class Rva004CD4DC
{
public:
	unsigned char m_pad0[4];
	Rva004CD4DCMid *m_p04;
	void rva004CD4DC(Object *obj);
};

void Rva004CD4DC::rva004CD4DC(Object *obj)
{
	Rva004CD4DCMid *mid = m_p04;
	void *v = obj->rva0029439D();
	if (v != 0 && mid != 0) {
		((Rva004CD4DCItem *)v)->target(mid->m_fx);
		return;
	}
	FXList::doFXObj(mid->m_fx, obj, 0);
}
