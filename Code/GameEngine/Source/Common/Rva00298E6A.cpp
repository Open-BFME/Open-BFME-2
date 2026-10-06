// cl: /DNDEBUG /MD
// ?rva00298E6A@Rva00298E6A@@QAEXXZ retail 0x00298E6A 63B
// Unlock body: +0x250 slot-31 chain then tail slot-0x1e0 else Object::findAttributeModifierPoolUpdate plus Rva002983DAVector::EraseRange clear.
// Evidence: prev BfmeSubBGB 0x00298893 same +0x250/w31 pattern; findAttributeModifierPoolUpdate row 0x0028BDD7; EraseRange row 0x002983DA; callers 0x00475EA2 0x004BDA67.
class Rva00297360Element
{
};
class Rva002983DAVector
{
public:
	Rva00297360Element *EraseRange(Rva00297360Element *first, Rva00297360Element *last);
	Rva00297360Element *m_first;
	Rva00297360Element *m_last;
};
class AttributeModifierPoolUpdate
{
public:
	char m_pad[0x20];
	Rva002983DAVector m_vec;
};
class Object
{
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
	friend class Rva00298E6A;
};
class Inner250Res
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
};
class Inner250
{
public:
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual void w04();
	virtual void w05();
	virtual void w06();
	virtual void w07();
	virtual void w08();
	virtual void w09();
	virtual void w10();
	virtual void w11();
	virtual void w12();
	virtual void w13();
	virtual void w14();
	virtual void w15();
	virtual void w16();
	virtual void w17();
	virtual void w18();
	virtual void w19();
	virtual void w20();
	virtual void w21();
	virtual void w22();
	virtual void w23();
	virtual void w24();
	virtual void w25();
	virtual void w26();
	virtual void w27();
	virtual void w28();
	virtual void w29();
	virtual void w30();
	virtual Inner250Res *w31();
};
class Rva00298E6A
{
public:
	void rva00298E6A();
	char m_pad[0x250];
	Inner250 *m_250;
};
void Rva00298E6A::rva00298E6A()
{
	Inner250 *p = m_250;
	Inner250Res *r = p ? p->w31() : 0;
	if (r)
		return r->v120();
	AttributeModifierPoolUpdate *pool = ((Object *)this)->findAttributeModifierPoolUpdate();
	if (pool) {
		Rva002983DAVector *vec = &pool->m_vec;
		vec->EraseRange(vec->m_first, vec->m_last);
	}
}
