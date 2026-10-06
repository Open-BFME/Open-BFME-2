// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0030BD84@Rva0030BDEE@@QAEXHPBUBfmeE16@@@Z @0x0030BD84 106B
// Chain 16-byte setter with 4-float compare then virtual slot 0x28.
// Evidence: callees rowed vector operator[] 0x00567B4D setter 0x005382B6; member vector+Rva at +0x68; SSE ucomiss lahf x4; virtual call [eax+0x28]; ret 8.
// Precedent Rva0030BDEE 83B same class same slot same pattern with 2 floats.
namespace _STL
{
	template <class T> class allocator;
	template <class T, class A> class vector
	{
	public:
		T &operator[](unsigned i);
	};
}
struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};
struct BfmePod16
{
	int a[4];
};
class Rva005382A6
{
public:
	void rva005382B6(int i, const BfmePod16 &src);
};
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
	void rva0030BD84(int i, const BfmeE16 *src);
private:
	char m_pad[0x64];
	Rva005382A6 m_68;
};
void Rva0030BDEE::rva0030BD84(int i, const BfmeE16 *src)
{
	Rva005382A6 &slot = m_68;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > &vec = *(_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > *)&slot;
	BfmeE16 *cur = &vec[i];
	if (src->x != cur->x || src->y != cur->y || src->z != cur->z || src->w != cur->w)
	{
		slot.rva005382B6(i, *(const BfmePod16 *)src);
		v10();
	}
}
