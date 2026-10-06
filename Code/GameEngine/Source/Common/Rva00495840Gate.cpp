// cl: /O1 /DNDEBUG /MD
//
// ?rva00495840@Rva00495840@@QAEHPAVArg@@@Z @0x00495840 110B.
// The argument's slot 110 gates the command-button path. A null scan
// returns 0x3FFFFFFF. Every other exit returns the int at holder+8.

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;

	char m_pad[0x1c];
	int m_code;
};

class CommandButton
{
public:
	char m_pad[0x44];
	Overridable *m_ov;
};

class Object
{
public:
	void *rva0028BD92(int code);
	void rva00297000(const CommandButton *btn, Object *target, int kind, int zero);
};

class Arg
{
public:
	virtual bool s0();
	virtual bool s1();
	virtual bool s2();
	virtual bool s3();
	virtual bool s4();
	virtual bool s5();
	virtual bool s6();
	virtual bool s7();
	virtual bool s8();
	virtual bool s9();
	virtual bool s10();
	virtual bool s11();
	virtual bool s12();
	virtual bool s13();
	virtual bool s14();
	virtual bool s15();
	virtual bool s16();
	virtual bool s17();
	virtual bool s18();
	virtual bool s19();
	virtual bool s20();
	virtual bool s21();
	virtual bool s22();
	virtual bool s23();
	virtual bool s24();
	virtual bool s25();
	virtual bool s26();
	virtual bool s27();
	virtual bool s28();
	virtual bool s29();
	virtual bool s30();
	virtual bool s31();
	virtual bool s32();
	virtual bool s33();
	virtual bool s34();
	virtual bool s35();
	virtual bool s36();
	virtual bool s37();
	virtual bool s38();
	virtual bool s39();
	virtual bool s40();
	virtual bool s41();
	virtual bool s42();
	virtual bool s43();
	virtual bool s44();
	virtual bool s45();
	virtual bool s46();
	virtual bool s47();
	virtual bool s48();
	virtual bool s49();
	virtual bool s50();
	virtual bool s51();
	virtual bool s52();
	virtual bool s53();
	virtual bool s54();
	virtual bool s55();
	virtual bool s56();
	virtual bool s57();
	virtual bool s58();
	virtual bool s59();
	virtual bool s60();
	virtual bool s61();
	virtual bool s62();
	virtual bool s63();
	virtual bool s64();
	virtual bool s65();
	virtual bool s66();
	virtual bool s67();
	virtual bool s68();
	virtual bool s69();
	virtual bool s70();
	virtual bool s71();
	virtual bool s72();
	virtual bool s73();
	virtual bool s74();
	virtual bool s75();
	virtual bool s76();
	virtual bool s77();
	virtual bool s78();
	virtual bool s79();
	virtual bool s80();
	virtual bool s81();
	virtual bool s82();
	virtual bool s83();
	virtual bool s84();
	virtual bool s85();
	virtual bool s86();
	virtual bool s87();
	virtual bool s88();
	virtual bool s89();
	virtual bool s90();
	virtual bool s91();
	virtual bool s92();
	virtual bool s93();
	virtual bool s94();
	virtual bool s95();
	virtual bool s96();
	virtual bool s97();
	virtual bool s98();
	virtual bool s99();
	virtual bool s100();
	virtual bool s101();
	virtual bool s102();
	virtual bool s103();
	virtual bool s104();
	virtual bool s105();
	virtual bool s106();
	virtual bool s107();
	virtual bool s108();
	virtual bool s109();
	virtual bool s110();
};

class Gate
{
public:
	virtual void s0();
	virtual void s1();
	virtual bool s2();
};

struct RetHolder
{
	char m_pad[8];
	int m_val;
};

class Rva00495840
{
public:
	int rva00495840(Arg *arg);
	Object *rva00495489();

private:
	char m_pad0[4];
	RetHolder *m_holder;
	Object *m_obj;
	char m_padC[0x24 - 0xC];
	CommandButton *m_btn;
};

int Rva00495840::rva00495840(Arg *arg)
{
	RetHolder *holder = m_holder;
	Object *obj = m_obj;
	if (arg->s110() == 0)
		return holder->m_val;
	Overridable *ov = m_btn->m_ov;
	if (ov != 0) {
		void *found = obj->rva0028BD92(ov->friend_getFinalOverride()->m_code);
		if (found == 0)
			return 0x3FFFFFFF;
		if (((Gate *)((char *)found + 0x20))->s2())
			return holder->m_val;
	}
	Object *hit = rva00495489();
	if (hit != 0)
		obj->rva00297000(m_btn, hit, 2, 0);
	return holder->m_val;
}
