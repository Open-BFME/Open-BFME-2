// ?rva0049C6E1@Rva0049C6E1@@QAE_NPAVObject@@@Z
// partial score=0.96 date=2026-10-04
// cl: /O1 /DNDEBUG /MD
//
// ?rva0049C6E1@Rva0049C6E1@@QAE_NPAVObject@@@Z @0x0049C6E1 89B. Upgrade check via
// TheUpgradeCenter plus rowed find 0x0026F0F0 with mask at this+8 plus 0x284
// then provider path via rowed 0x0049C5F4 plus virtual slot 43 plus pin
// bfmeHas985C else path. Evidence: push esi plus TheUpgradeCenter plus
// 0x284 plus find plus provider plus 0xAC plus pin plus al 1/0; callers
// 0x0041CE8B 0x0049C9AE 0x0049CA77; honest address name.
class Rva0026F0F0
{
public:
	void *rva0026F0F0(const void *mask);
};

class UpgradeCenter;
extern "C" UpgradeCenter *TheUpgradeCenter;
#pragma comment(linker, "/alternatename:_TheUpgradeCenter=?TheUpgradeCenter@@3PAVUpgradeCenter@@A")

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	char m_pad00[0x78];
	ObjectID m_id78;
	char m_pad7C[0x250 - 0x7C];
	void *m_prov250;
	char m_pad254[0x274 - 0x254];
	int m_int274;
};

class Rva0049C5F4
{
public:
	void *rva0049C5F4(Object *arg);
};

class Rva0049C6E1Prov
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
	virtual void v40(); virtual void v41(); virtual void v42();
	virtual bool slot43(void *upgrade);
};

class BfmeArg985
{
public:
	char bfmeHas985C(int x);
};

class Rva0049C6E1
{
	char m_pad00[8];
	void *m_ptr08;
public:
	bool rva0049C6E1(Object *arg);
};

// ?rva0049C6E1@Rva0049C6E1@@QAE_NPAVObject@@@Z present-unmatched
bool Rva0049C6E1::rva0049C6E1(Object *arg)
{
	void *upgrade = ((Rva0026F0F0 *)TheUpgradeCenter)->rva0026F0F0((const void *)((char *)m_ptr08 + 0x284));
	if (upgrade == 0)
		goto ret_false;
	unsigned char ok;
	if (arg->m_int274 != 0)
	{
		void *prov = ((Rva0049C5F4 *)this)->rva0049C5F4(arg);
		if (prov == 0)
			goto ret_false;
		ok = ((Rva0049C6E1Prov *)prov)->slot43(upgrade);
	}
	else
	{
		ok = ((BfmeArg985 *)arg)->bfmeHas985C((int)upgrade);
	}
	if (ok == 0)
		goto ret_false;
	goto ret_true;
ret_true:
	return true;
ret_false:
	return false;
}
