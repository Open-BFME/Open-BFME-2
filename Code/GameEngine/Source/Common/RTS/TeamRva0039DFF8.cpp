// cl: /DNDEBUG /MD
//
// ?rva0039DFF8@Team@@QAE_NXZ @0x0039DFF8 (74B).
// Team member scan returning false on first live AI member whose slot 0x1b8
// virtual returns false else true. Retail reads AI at Object+0x258 and dead
// bit at Object+0x438 bit0 then virtual call [eax+0x1b8] with no args.
// Walk uses rowed iterate_TeamMemberList 0x263864 and DLINK advance via pin
// at 0x263526. Same flags and iterator model as TeamHasAnyObjects neighbour.
// Caller at 0x004F3041. Virtual slot is positional with no donor identity.

class Object;

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class AIVirtual110
{
public:
	virtual bool _v0();
	virtual bool _v1();
	virtual bool _v2();
	virtual bool _v3();
	virtual bool _v4();
	virtual bool _v5();
	virtual bool _v6();
	virtual bool _v7();
	virtual bool _v8();
	virtual bool _v9();
	virtual bool _v10();
	virtual bool _v11();
	virtual bool _v12();
	virtual bool _v13();
	virtual bool _v14();
	virtual bool _v15();
	virtual bool _v16();
	virtual bool _v17();
	virtual bool _v18();
	virtual bool _v19();
	virtual bool _v20();
	virtual bool _v21();
	virtual bool _v22();
	virtual bool _v23();
	virtual bool _v24();
	virtual bool _v25();
	virtual bool _v26();
	virtual bool _v27();
	virtual bool _v28();
	virtual bool _v29();
	virtual bool _v30();
	virtual bool _v31();
	virtual bool _v32();
	virtual bool _v33();
	virtual bool _v34();
	virtual bool _v35();
	virtual bool _v36();
	virtual bool _v37();
	virtual bool _v38();
	virtual bool _v39();
	virtual bool _v40();
	virtual bool _v41();
	virtual bool _v42();
	virtual bool _v43();
	virtual bool _v44();
	virtual bool _v45();
	virtual bool _v46();
	virtual bool _v47();
	virtual bool _v48();
	virtual bool _v49();
	virtual bool _v50();
	virtual bool _v51();
	virtual bool _v52();
	virtual bool _v53();
	virtual bool _v54();
	virtual bool _v55();
	virtual bool _v56();
	virtual bool _v57();
	virtual bool _v58();
	virtual bool _v59();
	virtual bool _v60();
	virtual bool _v61();
	virtual bool _v62();
	virtual bool _v63();
	virtual bool _v64();
	virtual bool _v65();
	virtual bool _v66();
	virtual bool _v67();
	virtual bool _v68();
	virtual bool _v69();
	virtual bool _v70();
	virtual bool _v71();
	virtual bool _v72();
	virtual bool _v73();
	virtual bool _v74();
	virtual bool _v75();
	virtual bool _v76();
	virtual bool _v77();
	virtual bool _v78();
	virtual bool _v79();
	virtual bool _v80();
	virtual bool _v81();
	virtual bool _v82();
	virtual bool _v83();
	virtual bool _v84();
	virtual bool _v85();
	virtual bool _v86();
	virtual bool _v87();
	virtual bool _v88();
	virtual bool _v89();
	virtual bool _v90();
	virtual bool _v91();
	virtual bool _v92();
	virtual bool _v93();
	virtual bool _v94();
	virtual bool _v95();
	virtual bool _v96();
	virtual bool _v97();
	virtual bool _v98();
	virtual bool _v99();
	virtual bool _v100();
	virtual bool _v101();
	virtual bool _v102();
	virtual bool _v103();
	virtual bool _v104();
	virtual bool _v105();
	virtual bool _v106();
	virtual bool _v107();
	virtual bool _v108();
	virtual bool _v109();
	virtual bool isReady();
};

class Object
{
public:
	unsigned char m_pad0[0x258];
	AIVirtual110 *m_ai;
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_dead;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	bool rva0039DFF8();
};

bool Team::rva0039DFF8()
{
	bool ok = true;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		AIVirtual110 *ai = cur->m_ai;
		if (ai == 0)
			continue;
		if ((cur->m_dead & 1) != 0)
			continue;
		if (!ai->isReady()) {
			ok = false;
			break;
		}
	}
	return ok;
}
