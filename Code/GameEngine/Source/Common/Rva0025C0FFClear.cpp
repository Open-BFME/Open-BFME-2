// cl: /MD
// ?rva0025C0FF@Rva0025C0FF@@QAEXXZ, retail 0x0025C0FF, 53 bytes.
// Clears the node list headed at this+0x1c: each node yields its successor via
// vtable slot 152 (0x260), is torn down via vtable slot 0 with flag 0, and its
// memory is freed with the rowed global operator delete (mem_ops.cpp). Head is
// then nulled (and [m],0 idiom). Slots 1-151 are never called; they only pad
// getNext to its retail slot.
// Evidence: callers at 0x0004A0BB (dtor-like, passes this in ecx) and 0x0025D6AB
// (unclaimed dtor storing vtable 0x7F5DA0, same this); prev/next rows live in
// Code/GameEngine/Source/Common and GameClient (default and /O1 /DNDEBUG /MD /EHsc flags).
class ListNode
{
public:
	virtual void *destroy(int flag);
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual void slot004();
	virtual void slot005();
	virtual void slot006();
	virtual void slot007();
	virtual void slot008();
	virtual void slot009();
	virtual void slot010();
	virtual void slot011();
	virtual void slot012();
	virtual void slot013();
	virtual void slot014();
	virtual void slot015();
	virtual void slot016();
	virtual void slot017();
	virtual void slot018();
	virtual void slot019();
	virtual void slot020();
	virtual void slot021();
	virtual void slot022();
	virtual void slot023();
	virtual void slot024();
	virtual void slot025();
	virtual void slot026();
	virtual void slot027();
	virtual void slot028();
	virtual void slot029();
	virtual void slot030();
	virtual void slot031();
	virtual void slot032();
	virtual void slot033();
	virtual void slot034();
	virtual void slot035();
	virtual void slot036();
	virtual void slot037();
	virtual void slot038();
	virtual void slot039();
	virtual void slot040();
	virtual void slot041();
	virtual void slot042();
	virtual void slot043();
	virtual void slot044();
	virtual void slot045();
	virtual void slot046();
	virtual void slot047();
	virtual void slot048();
	virtual void slot049();
	virtual void slot050();
	virtual void slot051();
	virtual void slot052();
	virtual void slot053();
	virtual void slot054();
	virtual void slot055();
	virtual void slot056();
	virtual void slot057();
	virtual void slot058();
	virtual void slot059();
	virtual void slot060();
	virtual void slot061();
	virtual void slot062();
	virtual void slot063();
	virtual void slot064();
	virtual void slot065();
	virtual void slot066();
	virtual void slot067();
	virtual void slot068();
	virtual void slot069();
	virtual void slot070();
	virtual void slot071();
	virtual void slot072();
	virtual void slot073();
	virtual void slot074();
	virtual void slot075();
	virtual void slot076();
	virtual void slot077();
	virtual void slot078();
	virtual void slot079();
	virtual void slot080();
	virtual void slot081();
	virtual void slot082();
	virtual void slot083();
	virtual void slot084();
	virtual void slot085();
	virtual void slot086();
	virtual void slot087();
	virtual void slot088();
	virtual void slot089();
	virtual void slot090();
	virtual void slot091();
	virtual void slot092();
	virtual void slot093();
	virtual void slot094();
	virtual void slot095();
	virtual void slot096();
	virtual void slot097();
	virtual void slot098();
	virtual void slot099();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void slot105();
	virtual void slot106();
	virtual void slot107();
	virtual void slot108();
	virtual void slot109();
	virtual void slot110();
	virtual void slot111();
	virtual void slot112();
	virtual void slot113();
	virtual void slot114();
	virtual void slot115();
	virtual void slot116();
	virtual void slot117();
	virtual void slot118();
	virtual void slot119();
	virtual void slot120();
	virtual void slot121();
	virtual void slot122();
	virtual void slot123();
	virtual void slot124();
	virtual void slot125();
	virtual void slot126();
	virtual void slot127();
	virtual void slot128();
	virtual void slot129();
	virtual void slot130();
	virtual void slot131();
	virtual void slot132();
	virtual void slot133();
	virtual void slot134();
	virtual void slot135();
	virtual void slot136();
	virtual void slot137();
	virtual void slot138();
	virtual void slot139();
	virtual void slot140();
	virtual void slot141();
	virtual void slot142();
	virtual void slot143();
	virtual void slot144();
	virtual void slot145();
	virtual void slot146();
	virtual void slot147();
	virtual void slot148();
	virtual void slot149();
	virtual void slot150();
	virtual void slot151();
	virtual ListNode *getNext();
};

class Rva0025C0FF
{
public:
	void rva0025C0FF();
private:
	char m_pad[0x1c];
	ListNode *m_head;
};

void Rva0025C0FF::rva0025C0FF()
{
	ListNode *cur = m_head;
	if (cur != 0)
	{
		ListNode *next;
		do
		{
			next = cur->getNext();
			::operator delete(cur->destroy(0));
			cur = next;
		} while (next != 0);
	}
	m_head = 0;
}
