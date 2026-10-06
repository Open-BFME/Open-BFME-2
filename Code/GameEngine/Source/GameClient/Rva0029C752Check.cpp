// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva0029C752Check@@YA_NXZ @0x0029C752 39B.
// Free helper over TheInGameUI slot 0x124 selection list: empty list returns
// false, else tail-jmps to rowed Object::isLocallyControlled on [nodeData+0xfc].
// Evidence: TheInGameUI global plus virtual 0x124 same as caller 0x0030EFD5;
// list nodes with data at +8 (STL list layout); +0xfc plus rowed 0x0028B07A;
/// caller 0x0030EFDE tests al al for bool.
struct ListNode
{
	ListNode *m_next;
	void *m_prev;
	void *m_data8;
};

struct Sel
{
	ListNode *m_head;
};

class Object
{
public:
	bool isLocallyControlled() const;
};

struct DataWithObject
{
	char m_pad[0xFC];
	Object *m_obj;
};

class InGameUI
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
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
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual Sel *slot73();
};

extern InGameUI *TheInGameUI;

bool __cdecl Rva0029C752Check()
{
	Sel *sel = TheInGameUI->slot73();
	ListNode *head = sel->m_head;
	ListNode *first = head->m_next;
	if (first != head)
		return ((DataWithObject *)first->m_data8)->m_obj->isLocallyControlled();
	return false;
}
