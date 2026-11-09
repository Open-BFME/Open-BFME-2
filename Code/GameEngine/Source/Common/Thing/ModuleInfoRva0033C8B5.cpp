// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0033C8B5@ModuleInfo@@QAE_NXZ @0x0033C8B5 51B: vector<Nugget> filter via ModuleData virtual slot 7 erases matching entries returns bool.
// ?clearAiModuleInfo@ModuleInfo@@QAE_NXZ @0x0033C882 51B: the same filter on ModuleData slot 4 (Zero Hour isAiModuleData), moved here from ThingTemplate.cpp.
// Evidence: calls rowed vector erase at 0x0033C3BC; vcall [eax+0x1c] on [esi+8]; stride 0x14 finish at +4; sibling clearAiModuleInfo 51B same shape.
#include "../../../Include/Common/ModuleData.h"
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
bool ModuleInfo::rva0033C8B5()
{
	ModuleInfoNuggetVector &info = *reinterpret_cast<ModuleInfoNuggetVector *>(this);
	bool ret = false;
	ModuleInfoNuggetVector::iterator it = info.begin();
	while (it != info.end())
	{
		if (it->second->slot07())
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

bool ModuleInfo::clearAiModuleInfo()
{
	ModuleInfoNuggetVector &info = *reinterpret_cast<ModuleInfoNuggetVector *>(this);
	bool ret = false;
	ModuleInfoNuggetVector::iterator it = info.begin();
	while (it != info.end())
	{
		if (it->second->isAiModuleData())
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
