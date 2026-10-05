// cl: /O1 /G7 /DNDEBUG /MD
//
// ?rva0048AEC6@Rva0048AEC6@@QAEXH@Z @0x0048AEC6 69B ret 4.
// Slot 0x40 takes the index. Two dwords at index*8+4/+8 clear, then
// three flag bytes at stride 0x10 from index*0x30+0x2c. Object at
// this-0x3DC idles through AI+0x258+0x20. /G7 selects imul by 0x30.

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmd);
};

struct AIUpdateInterface
{
	char m_pad[0x20];
	AICommandInterface m_cmd;
};

class Object
{
public:
	char m_pad[0x258];
	AIUpdateInterface *m_ai;
};

struct Rva0048AEC6Pair
{
	int m_a;
	int m_b;
};

class Rva0048AEC6
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16(int index);
	void rva0048AEC6(int index);

private:
	Rva0048AEC6Pair m_pairs[5];
};

void Rva0048AEC6::rva0048AEC6(int index)
{
	s16(index);
	m_pairs[index].m_a = 0;
	m_pairs[index].m_b = 0;
	unsigned char *flag = (unsigned char *)this + index * 0x30 + 0x2c;
	for (int n = 0; n < 3; ++n)
	{
		*flag = 0;
		flag += 0x10;
	}
	Object *obj = *(Object **)((char *)this - 0x3DC);
	obj->m_ai->m_cmd.aiIdle(CMD_FROM_AI);
}
