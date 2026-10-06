// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ?rva0028D86F@Rva0028D86F@@QAEXABU?$_Base_bitset@$03@_STL@@@Z @0x0028D86F 34B: __thiscall void method with bitset OR at +0x370 plus WeaponSet update at +0x330. Evidence: rowed _M_do_or 0x0028C53E plus pin updateWeaponSet 0x002C8C97 plus caller 0x004B577C plus prev ObjectIsSelectable plus next RvaBitTestTwins.
namespace _STL
{
template<unsigned N> struct _Base_bitset;
template<> struct _Base_bitset<4>
{
	void _M_do_or(const _Base_bitset<4> &other);
	unsigned long _M_w[4];
};
}

class Object;
class WeaponSet
{
public:
	void updateWeaponSet(const Object *obj);
};

class Rva0028D86F
{
public:
	void rva0028D86F(const _STL::_Base_bitset<4> &other);
private:
	char m_pad[0x330];
};

void Rva0028D86F::rva0028D86F(const _STL::_Base_bitset<4> &other)
{
	((_STL::_Base_bitset<4> *)((char *)this + 0x370))->_M_do_or(other);
	((WeaponSet *)((char *)this + 0x330))->updateWeaponSet((const Object *)this);
}
