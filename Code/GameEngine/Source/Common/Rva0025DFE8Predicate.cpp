// cl: /O1 /MD /GX
// ?rva0025DFE8@Rva0025DFE8@@QAE_NH@Z @0x0025DFE8 (44B): bool predicate with
// vcall plus rowed fallback. Retail: esi=ecx; eax=[esi]; call [eax+0xB8]
// (v46); cmp [esp+8],eax; jne else; eax=0; cmp [esi+16],1; sete al; jmp ret;
// else: push arg; ecx=[esi+12]; call BFMEConnectionManager::isPlayerConnected
// (0x4CF083 rowed); pop esi; ret 4. Single int arg, bool return; no EH;
// address-derived outer, real callee view for mangling.
class Rva0025DFE8Base
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
};

class BFMEConnectionManager
{
public:
	bool isPlayerConnected(int arg);
};

class Rva0025DFE8
{
public:
	bool rva0025DFE8(int arg);
private:
	char m_pad00[0x0C];
	BFMEConnectionManager *m_mgr;
	int m_16;
};

// ?rva0025DFE8@Rva0025DFE8@@QAE_NH@Z
bool Rva0025DFE8::rva0025DFE8(int arg)
{
	Rva0025DFE8Base *base = (Rva0025DFE8Base *)this;
	if (arg == base->v46()) {
		return m_16 == 1;
	}
	return m_mgr->isPlayerConnected(arg);
}
