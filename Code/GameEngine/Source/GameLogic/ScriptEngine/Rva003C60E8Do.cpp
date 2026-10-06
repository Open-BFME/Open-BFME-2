// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
// ?Rva003C60E8Do@@YGXPAVParameter@@PAURva003C60E8Arg@@@Z @0x003C60E8 169B.
// Script free function getting unit by Parameter name then setting status
// 0x44 from the arg flag, then filling a stack list<int> via Object virtual
// +0x10C and setting status on each listed entry. Evidence: leaf lane,
// ret 8 two-arg stdcall, rowed getUnitNamed 0x3588E7 via TheScriptEngine
// 0x009FE16C, rowed setStatus 0x23DB0E twice, rowed rva0028C197 0x28C197,
// rowed List_base<int> ctor/dtor 0x4EC36C/0x4EC395, EH prolog scopetable
// 0x00782FA1. Layout honest-address only.
#include <list>
void __cdecl operator delete(void *);
class Parameter;
enum ObjectStatusTypes
{
	OBJECT_STATUS_44 = 0x44
};
class Object
{
public:
	void setStatus(ObjectStatusTypes st, bool flag);
	void *rva0028C197() const;
};
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};
struct Rva003C60E8Arg
{
	char m_pad00[8];
	int m_08;
};
class Rva003C60E8ListIface
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
	virtual void fillList(_STL::list<int> *lst);
};
extern ScriptEngine *TheScriptEngine;
void __stdcall Rva003C60E8Do(Parameter *p, Rva003C60E8Arg *a)
{
	Object *obj = TheScriptEngine->getUnitNamed(p);
	if (!obj)
		return;
	obj->setStatus(OBJECT_STATUS_44, a->m_08 != 0);
	unsigned char *flagBase = *(unsigned char **)((char *)obj + 4);
	if ((flagBase[0x115] & 0x20) == 0)
		return;
	void *rva = obj->rva0028C197();
	if (!rva)
		return;
	_STL::list<int> lst;
	((Rva003C60E8ListIface *)rva)->fillList(&lst);
	for (_STL::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
	{
		Object *o = (Object *)(*it);
		o->setStatus(OBJECT_STATUS_44, a->m_08 != 0);
	}
}
