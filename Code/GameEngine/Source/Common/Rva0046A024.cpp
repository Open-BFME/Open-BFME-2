// cl: /MD
// ?rva0046A024@Rva0046A024@@QAEXXZ @ 0x0046A024 142B unlock with EBP frame.
// Evidence: isKindOf row 0x0006F039 ?isKindOf@Object@@QBE_NW4KindOfType@@@Z; caller 0x00470DC1; subobject at +0x11C with virtuals at +0x108 (slot 66) and +0x23C (slot 143); list nodes with Object* at +8; counter at +0x2F4 with guard at +0x2F0.
enum KindOfType
{
	K_67 = 0x67,
	K_69 = 0x69,
	K_1BB = 0x1BB
};

class Object
{
public:
	bool isKindOf(KindOfType kind) const;
};

struct ListNode
{
	ListNode *m_next;
	ListNode *m_prev;
	Object *m_obj;
};

struct ListHolder
{
	ListNode *m_head;
};

struct Iter
{
	void *m_a;
	ListHolder *m_b;
};

class Sub11C
{
public:
	virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03(); virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07(); virtual void a08(); virtual void a09();
	virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
	virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27(); virtual void a28(); virtual void a29();
	virtual void a30(); virtual void a31(); virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35(); virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39();
	virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43(); virtual void a44(); virtual void a45(); virtual void a46(); virtual void a47(); virtual void a48(); virtual void a49();
	virtual void a50(); virtual void a51(); virtual void a52(); virtual void a53(); virtual void a54(); virtual void a55(); virtual void a56(); virtual void a57(); virtual void a58(); virtual void a59();
	virtual void a60(); virtual void a61(); virtual void a62(); virtual void a63(); virtual void a64(); virtual void a65();
	virtual void getIter(Iter *it);
	virtual void b067(); virtual void b068(); virtual void b069(); virtual void b070(); virtual void b071(); virtual void b072(); virtual void b073(); virtual void b074(); virtual void b075(); virtual void b076();
	virtual void b077(); virtual void b078(); virtual void b079(); virtual void b080(); virtual void b081(); virtual void b082(); virtual void b083(); virtual void b084(); virtual void b085(); virtual void b086();
	virtual void b087(); virtual void b088(); virtual void b089(); virtual void b090(); virtual void b091(); virtual void b092(); virtual void b093(); virtual void b094(); virtual void b095(); virtual void b096();
	virtual void b097(); virtual void b098(); virtual void b099(); virtual void b100(); virtual void b101(); virtual void b102(); virtual void b103(); virtual void b104(); virtual void b105(); virtual void b106();
	virtual void b107(); virtual void b108(); virtual void b109(); virtual void b110(); virtual void b111(); virtual void b112(); virtual void b113(); virtual void b114(); virtual void b115(); virtual void b116();
	virtual void b117(); virtual void b118(); virtual void b119(); virtual void b120(); virtual void b121(); virtual void b122(); virtual void b123(); virtual void b124(); virtual void b125(); virtual void b126();
	virtual void b127(); virtual void b128(); virtual void b129(); virtual void b130(); virtual void b131(); virtual void b132(); virtual void b133(); virtual void b134(); virtual void b135(); virtual void b136();
	virtual void b137(); virtual void b138(); virtual void b139(); virtual void b140(); virtual void b141(); virtual void b142();
	virtual void reset(int v);
};

class Rva0046A024
{
public:
	void rva0046A024();
private:
	char m_pad[0x11C];
	Sub11C m_sub;
	char m_fill[0x2F0 - 0x120];
	int m_flag;
	int m_count;
};

void Rva0046A024::rva0046A024()
{
	if (m_flag == 0)
		return;
	Iter it;
	m_sub.getIter(&it);
	ListNode *head = it.m_b->m_head;
	ListNode *cur = head->m_next;
	for (; cur != head; cur = cur->m_next)
	{
		if (cur->m_obj->isKindOf((KindOfType)0x1BB))
			return;
		if (cur->m_obj->isKindOf((KindOfType)0x67))
			return;
		if (cur->m_obj->isKindOf((KindOfType)0x69))
			return;
	}
	int v = m_count;
	m_count = v + 1;
	if (v < 4)
		return;
	m_sub.reset(0);
	m_count = 0;
}
