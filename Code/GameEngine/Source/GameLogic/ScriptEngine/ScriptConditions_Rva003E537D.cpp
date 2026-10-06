// ?Rva003E537DCheck@@YG_NPAVParameter@@@Z
// retail 0x003E537D, 52 bytes.
// Evidence: leaf free __stdcall bool with 1 Parameter arg frameless; rowed ScriptEngine::getUnitNamed; Object +0x250 Mid with vslot 69 (0x114) taking int returning unsigned; unsigned <=0 gives jbe.
// cl: /O1

class Parameter
{
};

class Object;

class Mid003E537D
{
public:
	virtual unsigned int v00(int);
	virtual unsigned int v01(int);
	virtual unsigned int v02(int);
	virtual unsigned int v03(int);
	virtual unsigned int v04(int);
	virtual unsigned int v05(int);
	virtual unsigned int v06(int);
	virtual unsigned int v07(int);
	virtual unsigned int v08(int);
	virtual unsigned int v09(int);
	virtual unsigned int v10(int);
	virtual unsigned int v11(int);
	virtual unsigned int v12(int);
	virtual unsigned int v13(int);
	virtual unsigned int v14(int);
	virtual unsigned int v15(int);
	virtual unsigned int v16(int);
	virtual unsigned int v17(int);
	virtual unsigned int v18(int);
	virtual unsigned int v19(int);
	virtual unsigned int v20(int);
	virtual unsigned int v21(int);
	virtual unsigned int v22(int);
	virtual unsigned int v23(int);
	virtual unsigned int v24(int);
	virtual unsigned int v25(int);
	virtual unsigned int v26(int);
	virtual unsigned int v27(int);
	virtual unsigned int v28(int);
	virtual unsigned int v29(int);
	virtual unsigned int v30(int);
	virtual unsigned int v31(int);
	virtual unsigned int v32(int);
	virtual unsigned int v33(int);
	virtual unsigned int v34(int);
	virtual unsigned int v35(int);
	virtual unsigned int v36(int);
	virtual unsigned int v37(int);
	virtual unsigned int v38(int);
	virtual unsigned int v39(int);
	virtual unsigned int v40(int);
	virtual unsigned int v41(int);
	virtual unsigned int v42(int);
	virtual unsigned int v43(int);
	virtual unsigned int v44(int);
	virtual unsigned int v45(int);
	virtual unsigned int v46(int);
	virtual unsigned int v47(int);
	virtual unsigned int v48(int);
	virtual unsigned int v49(int);
	virtual unsigned int v50(int);
	virtual unsigned int v51(int);
	virtual unsigned int v52(int);
	virtual unsigned int v53(int);
	virtual unsigned int v54(int);
	virtual unsigned int v55(int);
	virtual unsigned int v56(int);
	virtual unsigned int v57(int);
	virtual unsigned int v58(int);
	virtual unsigned int v59(int);
	virtual unsigned int v60(int);
	virtual unsigned int v61(int);
	virtual unsigned int v62(int);
	virtual unsigned int v63(int);
	virtual unsigned int v64(int);
	virtual unsigned int v65(int);
	virtual unsigned int v66(int);
	virtual unsigned int v67(int);
	virtual unsigned int v68(int);
	virtual unsigned int v69(int);
};

class Object
{
public:
	char m_pad[0x250];
	Mid003E537D *m_mid;
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};

extern class ScriptEngine *TheScriptEngine;

bool __stdcall Rva003E537DCheck(Parameter *param)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (obj)
	{
		Mid003E537D *mid = obj->m_mid;
		if (mid)
		{
			if (mid->v69(0) > 0)
				return true;
		}
	}
	return false;
}
