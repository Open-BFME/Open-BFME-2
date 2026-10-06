// cl: /MD
// ?rva005796B3@Rva005796B3@@QAEXPAX@Z @0x005796B3 73B
// Thiscall setter for +0x18 pointer with +0x1C flag: if new==old return; if
// old!=0 and flag!=0 and old virtual int getter == flag then old slot1
// forwarder; store new; if new!=0 and flag!=0 then new virtual with &flag.
// Callers pass 0 (e.g. 0x0042DBFC). Callees 0x005CB265 no-arg int pinned
// 0x005CB260 rowed slot1 0x001FF3A9 one-arg int* pinned. Evidence: retail
// bytes unlock lane and 4 callers.
class Rva005CB260
{
public:
	void rva005CB260();
};

class Rva005CB265
{
public:
	virtual int rva005CB265();
};

class Rva001FF3A9
{
public:
	virtual void rva001FF3A9();
	virtual void rva001FF3A9(int *flag);
};

class Rva005796B3
{
public:
	void rva005796B3(void *newObj);
private:
	char m_00[0x18];
	void *m_18;
	int m_1C;
};

void Rva005796B3::rva005796B3(void *newObj)
{
	if (newObj == m_18)
		return;
	if (m_18 != 0)
	{
		int flag = m_1C;
		if (flag != 0)
		{
			if (((Rva005CB265 *)m_18)->Rva005CB265::rva005CB265() == flag)
				((Rva005CB260 *)m_18)->rva005CB260();
		}
	}
	m_18 = newObj;
	if (newObj == 0)
		return;
	int *pFlag = &m_1C;
	if (*pFlag == 0)
		return;
	((Rva001FF3A9 *)newObj)->Rva001FF3A9::rva001FF3A9(pFlag);
}
