// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0033C84A@ModuleInfo@@QAE_NH@Z @0x0033C84A 56B: vector<Nugget> filter by interfaceMask and flags erases matches returns bool.
// Evidence: calls rowed vector erase at 0x0033C3BC; mask at +0xC flags at +0x10/+0x11; stride 0x14 finish at +4; callers at 0x0033D963/71/7F/8D.
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
	iterator erase(iterator position);
private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};
}
#include "../../../Include/Common/ModuleInfoClass.h"
typedef _STL::vector<ModuleInfo::Nugget, _STL::allocator<ModuleInfo::Nugget> > ModuleInfoNuggetVector;
bool ModuleInfo::rva0033C84A(int mask)
{
	ModuleInfoNuggetVector &info = *reinterpret_cast<ModuleInfoNuggetVector *>(this);
	bool ret = false;
	ModuleInfoNuggetVector::iterator it = info.begin();
	while (it != info.end())
	{
		if ((it->interfaceMask & mask) != 0 && it->copiedFromDefault != 0 && it->inheritable == 0)
		{
			it = info.erase(it);
			ret = true;
		}
		else
		{
			++it;
		}
	}
	return ret;
}
