// cl: /DNDEBUG /MD
//
// ?rva00491EE6@Rva00491DD3@@QAEXXZ retail 0x00491EE6 50 bytes. Thiscall method
// of Rva00491DD3 (UpdateModule base size 0x20 with bool at +0x20). Reads
// Object at +8 then AI at Object+0x258 calls virtual slot 0x1B8 returning
// bool then if set checks AI+0x34 and calls rowed AIUpdateInterface
// rva0026331C at 0x0026331C then clears bool at +0x20. Evidence is the
// neighbour Xfer TU layout plus the rowed callee plus caller 0x00492161.

class Thing;
class ModuleData;
class AIUpdateInterface;
class Object;

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
	virtual bool IsActive();
	void rva0026331C();

public:
	char m_pad00[0x30 - 4];
	void *m_30;
	void *m_34;
};

class Object
{
public:
	char m_pad00[0x258];
	AIUpdateInterface *m_258;
};

class BehaviorModuleBase
{
public:
	virtual void unused();
	Thing *m_thing;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	void xfer(void *xfer);

protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class Rva00491DD3 : public UpdateModule
{
public:
	void rva00491EE6();

private:
	bool m_20;
	unsigned int m_24;
};

void Rva00491DD3::rva00491EE6()
{
	Object *obj = m_object;
	AIUpdateInterface *ai = obj->m_258;
	if (!ai->IsActive())
		return;
	ai = m_object->m_258;
	if (ai->m_34 != 0)
		ai->rva0026331C();
	m_20 = false;
}
