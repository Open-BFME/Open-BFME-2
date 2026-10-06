// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0030BD5B@Rva0030BDEE@@QAEXPBURGBColor@@@Z @0x0030BD5B 41B
// Conditional RGBColor copy with virtual slot 0x20.
// Evidence: callee rowed operator!= 0x00004F65; member RGBColor at +0x50; 12B copy via movsd x3; virtual call [eax+0x20]; ret 4.
// Precedent Rva0030BD84/Rva0030BDEE same class same pattern with floats.
struct RGBColor
{
	float red;
	float green;
	float blue;
};
bool __cdecl operator!=(const RGBColor &left, const RGBColor &right);
class Rva0030BDEE
{
public:
	virtual ~Rva0030BDEE();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	void rva0030BD5B(const RGBColor *src);
private:
	char m_pad[0x4C];
	RGBColor m_50;
};
void Rva0030BDEE::rva0030BD5B(const RGBColor *src)
{
	if (*src != m_50)
	{
		m_50 = *src;
		v08();
	}
}
