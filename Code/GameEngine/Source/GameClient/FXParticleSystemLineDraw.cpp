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

extern class View *TheTacticalView;

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
	Rva0055CD70Vec start;
	start.x = m_a0 + x;
	start.y = m_a1 + y;
	start.z = m_a2 + z;
	Rva0055CD70Vec end;
	end.x = m_b0 + x;
	end.y = m_b1 + y;
	end.z = m_b2 + z;
	((TacticalView *)TheTacticalView)->slot11(&start, &end, 0xccaaffff);
}
