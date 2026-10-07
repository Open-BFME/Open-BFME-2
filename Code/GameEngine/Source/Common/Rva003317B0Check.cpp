// cl: /MD /O1 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003317B0@Rva003317B0@@QAE_NPBVWeaponTemplateSetHead@@@Z retail 0x003317B0 73B
// Subset check over 76-byte sets: if overlap at +0x50 return false; copy arg
// to temp ebp-0x4c via rowed copy ctor 0x00045455; temp intersect member at
// +4 via rowed 0x000B3ED3; return Equal(member temp) via rowed 0x00045473.
// Evidence: sub esp-0x4c push esi lea ecx esi+0x50 call overlap 0x00263546
// then copy-intersect-equal chain; unblocks 0x00335FE1; chain from 0xB3ED3.
typedef bool Bool;
class WeaponTemplateSetHead
{
	char _m[0x4C];
public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &that);
	void rva000B3ED3(const WeaponTemplateSetHead &other);
};
class Rva00263546
{
public:
	bool rva00263546(const Rva00263546 *other) const;
private:
	int m_mask[19];
};
Bool Rva00045473Equal(const void *a, const void *b);
class Rva003317B0
{
public:
	bool rva003317B0(const WeaponTemplateSetHead *arg);
private:
	int m_00;
	WeaponTemplateSetHead m_04;
	Rva00263546 m_50;
};
bool Rva003317B0::rva003317B0(const WeaponTemplateSetHead *arg)
{
	if (m_50.rva00263546((const Rva00263546 *)arg))
		return false;
	WeaponTemplateSetHead tmp(*arg);
	tmp.rva000B3ED3(m_04);
	unsigned char eq = Rva00045473Equal(&m_04, &tmp);
	return eq;
}

// The 73B predicate at 0x003317F9 uses the same copy/intersect/equality
// chain with 16B sets, +0x04 required bits and +0x14 forbidden bits.
// Its caller 0x0033605B walks 0x24-byte records. Application identities and
// the logical flag count are unknown; this is a fixed-storage view only.
#include <bitset>
namespace _STL {
template <> void _Base_bitset<4>::_M_do_and(const _Base_bitset<4> &);
}

// Exact declaration of the existing copy provider at 0x002CF108, whose
// Object872.h view proves 16-byte fixed storage and nonthrowing copy.
class BfmeObject872Header
{
    char bytes[16];
public:
    __declspec(nothrow) BfmeObject872Header(const BfmeObject872Header &);
};
class Rva00331682Holder
{
public:
    bool test(const void *other) const;
};
bool Rva002634E0Equal(const void *a, const void *b);

class Rva003317F9
{
public:
    bool rva003317F9(const BfmeObject872Header *arg);
private:
    int m_00;
    BfmeObject872Header m_required;
    BfmeObject872Header m_forbidden;
};

bool Rva003317F9::rva003317F9(const BfmeObject872Header *arg)
{
    if (((const Rva00331682Holder *)&m_forbidden)->test(arg))
        return false;
    BfmeObject872Header tmp(*arg);
    ((_STL::_Base_bitset<4> *)&tmp)->_M_do_and(
        *(const _STL::_Base_bitset<4> *)&m_required);
    unsigned char eq = Rva002634E0Equal(&m_required, &tmp);
    return eq;
}
