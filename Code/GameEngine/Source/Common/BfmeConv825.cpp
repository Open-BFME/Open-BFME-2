// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common

class BfmeSubVfn1A6
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void vfn5();
	virtual void v6();
	virtual void v7();
	virtual void vfn8(int code);
	void step1();
	void notify(int code, void *val);
};

struct BfmeThing1A6
{
	unsigned char pad[0x30];
	BfmeSubVfn1A6 *m_sub30;
	unsigned char pad2[0x48 - 0x34];
	void *m_val48;
	void doAction(void *val, void *param2);
};

void BfmeThing1A6::doAction(void *val, void *param2)
{
	if (!val) {
		m_sub30->vfn5();
		m_val48 = param2;
		m_sub30->vfn8(0x2a);
	} else {
		m_sub30->step1();
		m_sub30->notify(0x2a, val);
	}
}
