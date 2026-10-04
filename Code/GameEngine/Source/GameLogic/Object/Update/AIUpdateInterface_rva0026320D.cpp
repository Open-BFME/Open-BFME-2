// cl: /O1 /DNDEBUG /MD
//
// ?rva0026320D@AIUpdateInterface@@MAEXHPAVObject@@@Z, retail 0x0026320D, 139 bytes.
// AIUpdateInterface switch on int 0/2/3/4/5 to state ids 0x30/0x2A/0x14/0x3B/0x3A
// with extra -1/-2; skips when StateMachine+0x50 id already equals desired;
// then Object+0x08 via rowed Object::rva0029439D plus slot 0x13C virtual,
// rowed Rva0033FCC8 copy, slot 0x38 virtual with second arg, pinned
// BfmeSubVfn1A6::notify. Evidence: neighbours rva002631A6/rva002632B3 share
// +0x30 machine and +0x08 object; caller 0x004DCC84 passes int 2-5 plus Object;
// INVALID_STATE_ID 0xF423F matches predicates sibling.

class Object
{
public:
	void *rva0029439D();
};

class Rva0033FCC8
{
public:
	void rva0033FCC8();
};

class BfmeSubVfn1A6
{
public:
	void notify(int a, void *b);
};

class RetState
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	int m_id;
};

class RetObj
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
	virtual void v76(); virtual void v77(); virtual void v78();
	virtual void v79();
};

class StateMachine
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13();
	virtual void slot14(void *a);
	char m_pad04[0x50 - 4];
	RetState *m_state50;
};

class AIUpdateInterface
{
	char m_pad04[4];
	Object *m_obj;
	char m_pad0C[0x30 - 0x0C];
	StateMachine *m_machine;
protected:
	virtual void rva0026320D(int which, Object *arg);
};

void AIUpdateInterface::rva0026320D(int which, Object *arg)
{
	int extra = -1;
	int desired;
	switch (which)
	{
	case 0:
		desired = 0x30;
		break;
	case 2:
		desired = 0x2A;
		break;
	case 3:
		desired = 0x14;
		break;
	case 4:
		desired = 0x3B;
		extra = -2;
		break;
	case 5:
		desired = 0x3A;
		extra = -2;
		break;
	default:
		return;
	}
	RetState *cur = m_machine->m_state50;
	int curId = cur ? cur->m_id : 0xF423F;
	if (curId == desired)
		return;
	Object *o = m_obj;
	if (!o)
		return;
	void *ret = o->rva0029439D();
	if (ret)
		((RetObj *)ret)->v79();
	((Rva0033FCC8 *)m_machine)->rva0033FCC8();
	m_machine->slot14(arg);
	((BfmeSubVfn1A6 *)m_machine)->notify(desired, (void *)extra);
}
