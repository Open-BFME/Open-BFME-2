// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ?Rva0033D331Parse@@YAXPAVINI@@PAVThingTemplate@@@Z @0x0033D331 101B: if flag at +0x5EA clears BfmeObject872 vector at +0x358 via rowed range erase then parses WeaponSet stack temp and pushes it.
// Evidence: calls rowed erase 0x0033C44B push_back 0x0033CFC6 ctor 0x0033A888 parse 0x002C8C7B clear 0x002CF7B5; callers none; neighbours ThingTemplate TUs.
class INI;
class ThingTemplate;
struct BfmeObject872
{
	char m_pad[0x368];
};
namespace _STL
{
template <class T> class allocator
{
};
template <class Type, class Alloc>
class vector
{
public:
	typedef Type *iterator;
	iterator begin() { return m_start; }
	iterator end() { return m_finish; }
	iterator erase(iterator first, iterator last);
	void push_back(const Type &val);
private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};
}
class Rva002C752F
{
public:
	Rva002C752F();
	char m_pad[0x368];
};
class WeaponTemplateSet
{
public:
	void parseWeaponTemplateSet(class INI *ini, const class ThingTemplate *tt);
};
class Rva002CF7B5
{
public:
	void rva002CF7B5();
};
#include "../../../Include/Common/ThingTemplate.h"
void Rva0033D331Parse(INI *ini, ThingTemplate *tt)
{
	if (tt->m5EA == 1)
	{
		_STL::vector<BfmeObject872, _STL::allocator<BfmeObject872> > *pv = reinterpret_cast<_STL::vector<BfmeObject872, _STL::allocator<BfmeObject872> > *>(tt->m_armorTemplateSets);
		tt->m5EA = 0;
		pv->erase(pv->begin(), pv->end());
	}
	Rva002C752F tmp;
	((WeaponTemplateSet *)&tmp)->parseWeaponTemplateSet(ini, tt);
	reinterpret_cast<_STL::vector<BfmeObject872, _STL::allocator<BfmeObject872> > *>(tt->m_armorTemplateSets)->push_back(*(const BfmeObject872 *)&tmp);
	reinterpret_cast<Rva002CF7B5 *>(tt->m_armorTemplateSetFinder)->rva002CF7B5();
}
