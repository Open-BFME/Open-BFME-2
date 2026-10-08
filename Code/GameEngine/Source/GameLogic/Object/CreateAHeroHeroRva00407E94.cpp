// cl: /O1 /DNDEBUG /MD
//
// ?rva00407E94@Rva0021937DTarget@@QAEXXZ, retail 0x00407E94, 113B: a
// CreateAHeroHero member (this goes to the rowed HasEarnedAward), rowed
// under the host name its 4 matched callers use. Target evidence: takes the
// award count (0x00406E7D), clears and resizes the bit vector at +0x5C
// (rowed vector<bool> clear/resize), then for each index looks the award up
// in the 0x00E02F74 store by the hero's key for it (0x00406E8F, 0x0040AAD5)
// and sets the bit when the hero has earned it. The vector<bool> view
// declares only the rowed members; _Bit_reference::operator= is STLport's.
namespace _STL
{
struct _Bit_reference
{
	unsigned int *_M_p;
	unsigned int _M_mask;
	_Bit_reference &operator=(bool x)
	{
		if (x)
			*_M_p |= _M_mask;
		else
			*_M_p &= ~_M_mask;
		return *this;
	}
};
template <class T> class allocator {};
template <class T, class A = allocator<T> > class vector;
template <> class vector<bool, allocator<bool> >
{
public:
	void clear();					// 0x0006D52A
	void resize(unsigned int n, bool x);		// 0x0006DB1C
	_Bit_reference operator[](unsigned int n);	// 0x0006BE1F
private:
	unsigned int m_storage[5];
};
}

struct BfmePod40;
class CreateAHeroAward;
class Rva0040AAD5 { public: BfmePod40 *rva0040AAD5(int key); };	// 0x0040AAD5
extern Rva0040AAD5 *g_00E02F74;
class Rva00406E7D { public: int rva00406E7D(); };		// 0x00406E7D
class Rva00406E8F { public: int rva00406E8F(unsigned int i); };	// 0x00406E8F
class CreateAHeroHero { public: bool HasEarnedAward(const CreateAHeroAward *award) const; };	// 0x00406EA7

class Rva0021937DTarget
{
public:
	void rva00407E94();
private:
	unsigned char m_pad0[0x5C];
	_STL::vector<bool> m_earned;		// +0x5C
};

void Rva0021937DTarget::rva00407E94()
{
	unsigned int count = ((Rva00406E7D *)this)->rva00406E7D();
	m_earned.clear();
	m_earned.resize(count, false);
	for (unsigned int i = 0; i < count; ++i)
	{
		BfmePod40 *award = g_00E02F74->rva0040AAD5(((Rva00406E8F *)this)->rva00406E8F(i));
		if (award && ((CreateAHeroHero *)this)->HasEarnedAward((const CreateAHeroAward *)award))
			m_earned[i] = true;
	}
}
