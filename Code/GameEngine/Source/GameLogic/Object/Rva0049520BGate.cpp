// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva0049520B@Rva0049520B@@QAEHXZ @0x0049520B 148B.
// Player field +0x5c gates a counter at +0x10. Otherwise compare two
// view floats and, when the actor slot 110 accepts, issue command 2.

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class Player
{
public:
	char m_pad[0x5c];
	int m_field5c;
};

class View
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual float s4();
	virtual void s5();
	virtual float s6();
};

class Actor
{
public:
	virtual void a0();
	virtual void a1();
	virtual void a2();
	virtual void a3();
	virtual void a4();
	virtual void a5();
	virtual void a6();
	virtual void a7();
	virtual void a8();
	virtual void a9();
	virtual void a10();
	virtual void a11();
	virtual void a12();
	virtual void a13();
	virtual void a14();
	virtual void a15();
	virtual void a16();
	virtual void a17();
	virtual void a18();
	virtual void a19();
	virtual void a20();
	virtual void a21();
	virtual void a22();
	virtual void a23();
	virtual void a24();
	virtual void a25();
	virtual void a26();
	virtual void a27();
	virtual void a28();
	virtual void a29();
	virtual void a30();
	virtual void a31();
	virtual void a32();
	virtual void a33();
	virtual void a34();
	virtual void a35();
	virtual void a36();
	virtual void a37();
	virtual void a38();
	virtual void a39();
	virtual void a40();
	virtual void a41();
	virtual void a42();
	virtual void a43();
	virtual void a44();
	virtual void a45();
	virtual void a46();
	virtual void a47();
	virtual void a48();
	virtual void a49();
	virtual void a50();
	virtual void a51();
	virtual void a52();
	virtual void a53();
	virtual void a54();
	virtual void a55();
	virtual void a56();
	virtual void a57();
	virtual void a58();
	virtual void a59();
	virtual void a60();
	virtual void a61();
	virtual void a62();
	virtual void a63();
	virtual void a64();
	virtual void a65();
	virtual void a66();
	virtual void a67();
	virtual void a68();
	virtual void a69();
	virtual void a70();
	virtual void a71();
	virtual void a72();
	virtual void a73();
	virtual void a74();
	virtual void a75();
	virtual void a76();
	virtual void a77();
	virtual void a78();
	virtual void a79();
	virtual void a80();
	virtual void a81();
	virtual void a82();
	virtual void a83();
	virtual void a84();
	virtual void a85();
	virtual void a86();
	virtual void a87();
	virtual void a88();
	virtual void a89();
	virtual void a90();
	virtual void a91();
	virtual void a92();
	virtual void a93();
	virtual void a94();
	virtual void a95();
	virtual void a96();
	virtual void a97();
	virtual void a98();
	virtual void a99();
	virtual void a100();
	virtual void a101();
	virtual void a102();
	virtual void a103();
	virtual void a104();
	virtual void a105();
	virtual void a106();
	virtual void a107();
	virtual void a108();
	virtual void a109();
	virtual bool a110();
};

class Object
{
public:
	Player *getControllingPlayer() const;

	char m_pad[0x254];
	View *m_view;
	Actor *m_actor;
};

class Other
{
public:
	char m_pad[8];
	int m_reset;
	int m_unused;
	float m_scale;
};

class AICommandInterface
{
public:
	void rva0036F265(Object *target, CommandSourceType source);
};

class Rva00495183
{
public:
	Object *rva00495183();
};

class Rva0049520B
{
public:
	int rva0049520B();

private:
	char m_pad[0x10];
	int m_counter;
};

int Rva0049520B::rva0049520B()
{
	Object *obj = *(Object **)((char *)this - 8);
	Player *player = obj->getControllingPlayer();
	if (player->m_field5c == 0)
		return 1;
	Other *other = *(Other **)((char *)this - 0xc);
	int counter = m_counter;
	if (counter > 0) {
		m_counter = counter - 1;
		return 1;
	}
	m_counter = other->m_reset;
	Actor *actor = obj->m_actor;
	if (actor == 0)
		return 1;
	View *view = obj->m_view;
	if (view == 0)
		return 1;
	float a = view->s4();
	float scaled = view->s6() * other->m_scale;
	if (a > scaled)
		return 1;
	if (actor->a110()) {
		Object *created = ((Rva00495183 *)((char *)this - 0x10))->rva00495183();
		if (created != 0) {
			AICommandInterface *ai = (AICommandInterface *)((char *)actor + 0x20);
			ai->rva0036F265(created, CMD_FROM_AI);
		}
	}
	return 1;
}
