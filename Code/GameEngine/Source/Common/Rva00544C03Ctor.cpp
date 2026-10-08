// cl: /MD
// ??0Rva00544C03@@QAE@PAVStateMachine@@@Z, retail 0x00544C03, 33 bytes.
// Derived State ctor via rowed State hash ctor 0x004D73FC with hash
// 0xA2C0BF2B then zero of +0x20 then vtable 0x00C69C98. Evidence:
// vtable store at [this]; base StateCtor row; prev 0x00544AD2 same dir.
class StateMachine;
class Xfer;

enum StateReturnType
{
	STATE_CONTINUE = 0
};

class __declspec(novtable) State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer(Xfer *xfer);
	virtual StateReturnType onEnter();
	virtual void slot05();
	virtual StateReturnType update();
	virtual void slot07();
	virtual bool isIdle() const;
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	StateMachine *m_machine;
	bool m_tail1C;
	unsigned char m_pad1D[0x20 - 0x1D];
};

extern const void *const g_00C69C98[];

class Object;
class AIUpdateInterface;
class RetObj;

class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	int m_40;
};

extern GameLogic *TheGameLogic;

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	unsigned char m_pad00[0x14];
	Object *m_owner;
};

class Object
{
public:
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai;
};

class AIUpdateInterface
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
	virtual RetObj *v95();
};

class RetObj
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
	virtual int w08();
};

typedef unsigned int UnsignedInt;

class Xfer
{
public:
	void Version1();
	virtual ~Xfer();
	virtual bool isLoading();
	virtual bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(struct XferVersion &version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24(int *value);
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(void *value);
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt &value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36(int *value);
};

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

class AIHarvestPrepareSiteState : public State
{
public:
	AIHarvestPrepareSiteState(StateMachine *machine);
	virtual void xfer(Xfer *xfer);
	virtual StateReturnType onEnter();
private:
	UnsignedInt m_20;
};

AIHarvestPrepareSiteState::AIHarvestPrepareSiteState(StateMachine *machine) : State(machine, 0xA2C0BF2Bu)
{
	m_20 = 0;
	*(const void **)this = g_00C69C98;
}

void AIHarvestPrepareSiteState::xfer(Xfer *xfer)
{
	xfer->Version1();
	xfer->xferUnsignedInt(m_20);
}

StateReturnType AIHarvestPrepareSiteState::onEnter()
{
	Object *owner = m_machine->getOwner();
	AIUpdateInterface *ai = owner->m_ai;
	RetObj *ret = ai->v95();
	if (ret == 0)
		return (StateReturnType)-2;
	int frame = TheGameLogic->m_40;
	int v = ret->w08();
	m_20 = v + frame;
	return STATE_CONTINUE;
}
