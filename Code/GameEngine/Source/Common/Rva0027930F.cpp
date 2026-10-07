// cl: /O1 /MD
class WeaponTemplateSetHead
{
public:
	__declspec(nothrow) WeaponTemplateSetHead(const WeaponTemplateSetHead &that);
	void rva000B3FA5(int a, int b);
	unsigned int m_bits[19];
};
class ModelConditionFlags
{
public:
	unsigned int m_bits[19];
};
class Drawable
{
public:
	void rva002791E7(const ModelConditionFlags &flags, unsigned int a, unsigned int b);
};
struct Rva0027930FFC
{
	unsigned char m_pad[0x10C];
	WeaponTemplateSetHead m_wtsh;
};
class Rva0027930FHost
{
public:
	void rva0027930F(int v);
private:
	unsigned char m_pad[0xFC];
	Rva0027930FFC *m_FC;
};
// ?rva0027930F@Rva0027930FHost@@QAEXH@Z
void Rva0027930FHost::rva0027930F(int v)
{
	WeaponTemplateSetHead tmp(m_FC->m_wtsh);
	tmp.rva000B3FA5(7, v == 4);
	((Drawable *)this)->rva002791E7((const ModelConditionFlags &)tmp, 0, 0);
}
