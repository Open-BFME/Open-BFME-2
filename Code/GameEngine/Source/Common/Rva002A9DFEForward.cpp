// cl: /MD
//
// ?rva002A9DFE@Rva002A9DFE@@QAEXPAXM0@Z @0x002A9DFE 39B
// Evidence: caller 0x003BF9FA passes (esi=float-Coord*) with ecx=[esi+8]; vtable slot 0x28; holder at +0x2DC shared with neighbour 0x002A9DB8.
class Rva002A9DFETarget
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
	virtual void v9();
	virtual void v10(void *a1, float a2, void *a3);
};

class Rva002A9DFE
{
public:
	void rva002A9DFE(void *a1, float a2, void *a3);
private:
	unsigned char m_pad[0x2DC];
	Rva002A9DFETarget *m_target;
};

void Rva002A9DFE::rva002A9DFE(void *a1, float a2, void *a3)
{
	if (m_target != 0)
		m_target->v10(a1, a2, a3);
}
