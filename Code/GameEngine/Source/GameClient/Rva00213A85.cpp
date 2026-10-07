// cl: /DNDEBUG /MD /EHsc
// Target evidence: 0x00213A85 0x00213B88 and 0x00213C30 each obtain an iterator
// through the table view at receiver+0x204 and read a callback receiver at node+8.
// 0x00213BBE and 0x00213C30 share the same caller receiver across a branch.
// Shared class ownership with 0x00213A85/0x00213B88 is inferred from the offset.
// The exact table specialization key type and mapped payload semantics remain unknown.

class Rva000427195;
class Rva000411084
{
public:
	void *m_node;
	Rva000427195 *m_table;
	void *next();
};

class Rva000427195
{
public:
	void *first(Rva000411084 *iterator);
};

class Rva003FAC83
{
public:
	void rva003FACB4();
	void rva003FACE4();
	void rva003FACE9(void *value);
	void rva003FAD4A(void *value);
	void rva003FAD2B();
	void rva003FAD9A();
	void rva003FADA3();
};

class AudioManager;
extern AudioManager *TheAudio;

class AudioManagerSlotView
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
	virtual void slot14(int value);
};

class InGameUI;
extern InGameUI *TheInGameUI;

class Rva0029B17C
{
public:
	void rva0029B17C();
};

void HideControlBar(bool visible);

class Mouse;
extern Mouse *TheMouse;

class Rva00210C33
{
public:
	void rva00210C33();
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;

class Rva00211589
{
public:
	void rva002110DF(int value);
};

class LivingWorldManager
{
};
extern LivingWorldManager *TheLivingWorldManager;

class Rva00213A85
{
public:
	void rva00213A0E();
	void rva00213A85();
	void rva00213AB6();
	void rva00213AFC(void *value);
	void rva00213B44();
	void rva00213B88(void *value);
	void rva00213BBE();
	void rva00213C30();

private:
	char m_pad[0x204];
	Rva000427195 m_table;
	char m_padToState[0xBB];
	unsigned char m_state_2C0;
};

void Rva00213A85::rva00213A0E()
{
	Rva000411084 iterator;
	m_table.first(&iterator);
	while (iterator.m_node != 0) {
		((Rva003FAC83 *)*(void **)((char *)iterator.m_node + 8))->rva003FACE4();
		iterator.next();
	}
	if (TheAudio != 0) {
		((AudioManagerSlotView *)TheAudio)->slot14(2);
	}
	Rva000411084 second;
	m_table.first(&second);
	iterator = second;
	while (iterator.m_node != 0) {
		((Rva003FAC83 *)*(void **)((char *)iterator.m_node + 8))->rva003FACB4();
		iterator.next();
	}
}

void Rva00213A85::rva00213A85()
{
	Rva000411084 iterator;
	m_table.first(&iterator);
	while (iterator.m_node != 0) {
		((Rva003FAC83 *)*(void **)((char *)iterator.m_node + 8))->rva003FACB4();
		iterator.next();
	}
}

void Rva00213A85::rva00213AB6()
{
	if (TheAudio != 0) {
		((AudioManagerSlotView *)TheAudio)->slot14(2);
	}
	Rva000411084 iterator;
	m_table.first(&iterator);
	while (iterator.m_node != 0) {
		((Rva003FAC83 *)*(void **)((char *)iterator.m_node + 8))->rva003FACE4();
		iterator.next();
	}
}

void Rva00213A85::rva00213AFC(void *value)
{
	m_state_2C0 = 1;
	Rva000411084 iterator;
	m_table.first(&iterator);
	while (iterator.m_node != 0) {
		((Rva003FAC83 *)*(void **)((char *)iterator.m_node + 8))->rva003FACE9(value);
		iterator.next();
	}
	((Rva0029B17C *)TheInGameUI)->rva0029B17C();
}

void Rva00213A85::rva00213B44()
{
	HideControlBar(m_state_2C0 = 1);
	Rva000411084 iterator;
	m_table.first(&iterator);
	while (iterator.m_node != 0) {
		((Rva003FAC83 *)*(void **)((char *)iterator.m_node + 8))->rva003FAD2B();
		iterator.next();
	}
}

void Rva00213A85::rva00213B88(void *value)
{
	Rva000411084 iterator;
	m_table.first(&iterator);
	while (iterator.m_node != 0) {
		((Rva003FAC83 *)*(void **)((char *)iterator.m_node + 8))->rva003FAD4A(value);
		iterator.next();
	}
}

void Rva00213A85::rva00213BBE()
{
	Rva000411084 iterator;
	m_table.first(&iterator);
	while (iterator.m_node != 0) {
		((Rva003FAC83 *)*(void **)((char *)iterator.m_node + 8))->rva003FAD9A();
		iterator.next();
	}
	int state = *(int *)((char *)g_00DFEF18 + 0x14);
	if (state != 0 && state != 1) {
		m_state_2C0 = 1;
	} else {
		((Rva00210C33 *)TheMouse)->rva00210C33();
	}
	if (((unsigned char *)TheWritableGlobalData)[0x60] != 0) {
		((Rva00211589 *)TheLivingWorldManager)->rva002110DF(1);
	}
}

void Rva00213A85::rva00213C30()
{
	Rva000411084 iterator;
	m_table.first(&iterator);
	while (iterator.m_node != 0) {
		((Rva003FAC83 *)*(void **)((char *)iterator.m_node + 8))->rva003FADA3();
		iterator.next();
	}
	((Rva00211589 *)TheLivingWorldManager)->rva002110DF(0);
}
