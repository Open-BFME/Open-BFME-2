// cl: /Ireference/shims/bfme2_ascii /MD
// ?createPayload@TransportContain@@QAEXXZ, retail 0x004670D6, 214 bytes.
// Slot 28 (offset 0x70) of TransportContain vtable 0x00844278 and
// HordeTransportContain vtable 0x00845EB8. Iterates the contain list at
// [this+4]+0xA4 via rowed Rva002D06CA lookup through g_009FF000 and drives
// the +0xFC secondary slot-0 with the Object at +8 and its +0x250 payload.
// Donor pattern is TransportContainKillBlockedRiders / ZH TransportContain.
// FINISH from reverse/attempts/0x004670d6.cpp score 0.97: empty-string
// je-vs-jne branch layout only; trying non-null-first ternary.
#include "ascii_string.h"

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

class ThingFactory;
extern ThingFactory *TheThingFactory;

class PClass
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
	virtual void slot14C(int v);
};

class Object
{
public:
	virtual ~Object();
	char m_pad[0x250 - 4];
	PClass *m_250;
};

struct RiderNode
{
	RiderNode *m_next;
	void *m_prev;
	AsciiString m_name;
	int m_count;
};

struct Sentinel
{
	RiderNode *m_first;
};

struct PtrA
{
	char m_pad[0xA4];
	Sentinel *m_sentinel;
};

class Secondary
{
public:
	virtual void slot0(void *a, PClass *b, Object *c, const char *d, int e);
};

class TransportContain
{
public:
	virtual ~TransportContain();
	void createPayload();

private:
	PtrA *m_4;
	Object *m_8;
	char m_padC[0xFC - 0xC];
	Secondary m_fc;
};

void TransportContain::createPayload()
{
	PtrA *a = m_4;
	RiderNode *cur = a->m_sentinel->m_first;
	if (cur == (RiderNode *)a->m_sentinel)
		return;
	do
	{
		AsciiString *aname = &cur->m_name;
		int count = *(int *)((char *)aname + 4);
		if (count <= 0)
			return;
		void *res = reinterpret_cast<Rva002D06CA *>(TheThingFactory)->rva002D06CA(aname);
		if (res == 0)
			return;
		Object *obj = m_8;
		if (obj == 0)
			return;
		PClass *p = obj->m_250;
		if (p != 0)
		{
			p->slot14C(0);
			if (*(volatile int *)&count > 0)
			{
				Secondary *sec = &m_fc;
				int n = count;
				do
				{
					const char *str = cur->m_name.str();
					sec->slot0(res, p, obj, str, 1);
					--n;
				} while (n != 0);
			}
			p->slot14C(1);
		}
		cur = cur->m_next;
	} while (cur != (RiderNode *)a->m_sentinel);
}
