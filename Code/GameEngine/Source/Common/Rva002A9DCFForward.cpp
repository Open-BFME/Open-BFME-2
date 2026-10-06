// cl: /MD
//
// ?rva002A9DCF@Rva002A9DCF@@QAEXPAX@Z @0x002A9DCF 29B
// Evidence: slot 0x24 (v9) with (ptr 1) forwarding like sibling Rva002A9DB8Forward slot 15; holder at +0x2DC shared with neighbours; caller 0x003BF9C8 pushes ptr.
class Rva002A9DCFTarget
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9(void *a1, int a2);
};

class Rva002A9DCF
{
public:
	void rva002A9DCF(void *a1);
private:
	unsigned char m_pad[0x2DC];
	Rva002A9DCFTarget *m_target;
};

void Rva002A9DCF::rva002A9DCF(void *a1)
{
	if (m_target != 0)
		m_target->v9(a1, 1);
}
