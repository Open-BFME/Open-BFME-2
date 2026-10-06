// cl: /MD
// ?rva00318BA5@Rva00318BA5@@QAEXPAVLivingWorldRegion@@@Z @0x00318BA5 33B
// Leaf __thiscall: out = this+0x34 via rowed 0x003F0F13, then this+0x2c = arg+0x12c.
// Evidence: callee 0x003F0F13 rowed; caller 0x002B7AB4; prev/next same // cl: /O1 /MD.
struct Rva003F0F13Elem
{
	float a;
	float b;
};

class LivingWorldRegion
{
public:
	void GetGarrisonArmyPlacementSpot(Rva003F0F13Elem *out);
};

class Rva00318BA5
{
public:
	void rva00318BA5(LivingWorldRegion *x);
private:
	unsigned char m_pre2c[0x2c];
	int m_2c;
	unsigned char m_pad30[0x4];
	Rva003F0F13Elem m_34;
};

void Rva00318BA5::rva00318BA5(LivingWorldRegion *x)
{
	x->GetGarrisonArmyPlacementSpot(&m_34);
	m_2c = *(int *)((char *)x + 0x12c);
}
