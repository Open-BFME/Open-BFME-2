// ?rva0047BDED@OpenContain@@QAEX_N@Z
// partial score=0.85 date=2026-10-08
// cl: /MD /DNDEBUG
// ?rva0047BDED@OpenContain@@QAEX_N@Z @0x0047BDED 54B: drain the contained list, calling
// virtual slot 41 on each non-null node value with the flag, then removeAllContained.
class OpenContain;
struct Rva0047BDEDNode
{
	Rva0047BDEDNode *m_next;
	char m_pad04[4];
	void *m_value;
};

class Rva0047BDEDList
{
public:
	Rva0047BDEDNode *m_head;
};

class OpenContain
{
public:
	virtual void rva0047BDEDV00();
	virtual void rva0047BDEDV01();
	virtual void rva0047BDEDV02();
	virtual void rva0047BDEDV03();
	virtual void rva0047BDEDV04();
	virtual void rva0047BDEDV05();
	virtual void rva0047BDEDV06();
	virtual void rva0047BDEDV07();
	virtual void rva0047BDEDV08();
	virtual void rva0047BDEDV09();
	virtual void rva0047BDEDV10();
	virtual void rva0047BDEDV11();
	virtual void rva0047BDEDV12();
	virtual void rva0047BDEDV13();
	virtual void rva0047BDEDV14();
	virtual void rva0047BDEDV15();
	virtual void rva0047BDEDV16();
	virtual void rva0047BDEDV17();
	virtual void rva0047BDEDV18();
	virtual void rva0047BDEDV19();
	virtual void rva0047BDEDV20();
	virtual void rva0047BDEDV21();
	virtual void rva0047BDEDV22();
	virtual void rva0047BDEDV23();
	virtual void rva0047BDEDV24();
	virtual void rva0047BDEDV25();
	virtual void rva0047BDEDV26();
	virtual void rva0047BDEDV27();
	virtual void rva0047BDEDV28();
	virtual void rva0047BDEDV29();
	virtual void rva0047BDEDV30();
	virtual void rva0047BDEDV31();
	virtual void rva0047BDEDV32();
	virtual void rva0047BDEDV33();
	virtual void rva0047BDEDV34();
	virtual void rva0047BDEDV35();
	virtual void rva0047BDEDV36();
	virtual void rva0047BDEDV37();
	virtual void rva0047BDEDV38();
	virtual void rva0047BDEDV39();
	virtual void rva0047BDEDV40();
	virtual void rva0047BDEDVirt41(void *value, bool flag);
	virtual void removeAllContained(bool flag);
	void rva0047BDED(bool flag);

private:
	char m_pad00[0xFC - 4];
	Rva0047BDEDList *m_fc;
};

// ?rva0047BDED@OpenContain@@QAEX_N@Z @0x0047BDED
void OpenContain::rva0047BDED(bool flag)
{
	for (;;)
	{
		Rva0047BDEDList *list = m_fc;
		if ((void *)list->m_head == (void *)list)
			break;
		void *value = list->m_head->m_value;
		if (value != 0)
			rva0047BDEDVirt41(value, flag);
	}
	this->OpenContain::removeAllContained(flag);
}
