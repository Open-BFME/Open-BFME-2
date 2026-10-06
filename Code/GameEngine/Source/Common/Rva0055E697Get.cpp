// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0055E697@Rva0055E697@@QAEXHHHHH@Z, retail 0x0055E697, 61 bytes.
// Vslot 7 getter: three GameClientRandomVariables at +0x24/+0x30/+0x3C via
// rowed getValue 0x002341A1 into out Vector3 at first arg plus four ignored
// stack args (ret 0x14). Same 3-float shape as siblings. No callers;
// vslot of 0x0081D0EC/0x0081C81C via ParticleModuleInfoCopyCtors.
class GameClientRandomVariable
{
public:
	float getValue() const;
private:
	int m_type;
	float m_low;
	float m_high;
};

struct Vec0055E697
{
	float m_x;
	float m_y;
	float m_z;
};

class Rva0055E697
{
public:
	void rva0055E697(int out, int a2, int a3, int a4, int a5);
private:
	char m_pad[0x24];
	GameClientRandomVariable m_var24;
	GameClientRandomVariable m_var30;
	GameClientRandomVariable m_var3C;
};

void Rva0055E697::rva0055E697(int out, int a2, int a3, int a4, int a5)
{
	Vec0055E697 *dst = (Vec0055E697 *)out;
	float v[3];
	v[0] = m_var24.getValue();
	v[1] = m_var30.getValue();
	v[2] = m_var3C.getValue();
	dst->m_x = v[0];
	dst->m_y = v[1];
	dst->m_z = v[2];
}
