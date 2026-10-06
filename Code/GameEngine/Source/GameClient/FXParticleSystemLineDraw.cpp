// cl: /MD
// ?rva0055CD70@Rva0055CD70@@QAEXMMM@Z at 0x0055CD70 size 124
// Evidence: vslot lane slot 4 of 0x0081D02C and 0x0081C750 LineEmissionVolumeInfo copies; two points from +0x24 six floats plus x y z then TacticalView slot 0x2c color 0xccaaffff; pattern from stash 0x0055CAEF.

struct Rva0055CD70Vec
{
	float x;
	float y;
	float z;
};

class TacticalView
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
	virtual void slot11(const Rva0055CD70Vec *a, const Rva0055CD70Vec *b, unsigned int color);
};

extern TacticalView *TheTacticalView;

class Rva0055CD70
{
public:
	void rva0055CD70(float x, float y, float z);
private:
	float m_pad[9];
	float m_a0;
	float m_a1;
	float m_a2;
	float m_b0;
	float m_b1;
	float m_b2;
};

void Rva0055CD70::rva0055CD70(float x, float y, float z)
{
	Rva0055CD70Vec a;
	a.x = m_a0 + x;
	a.y = m_a1 + y;
	a.z = m_a2 + z;
	Rva0055CD70Vec b;
	b.x = m_b0 + x;
	b.y = m_b1 + y;
	b.z = m_b2 + z;
	TheTacticalView->slot11(&a, &b, 0xccaaffff);
}
