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
class ModuleInfo
{
public:
	struct Nugget
	{
		char m_pad0[8];
		ModuleData *second;
		char m_pad1[0x14 - 8 - 4];
	};
	bool clearAiModuleInfo();
	bool rva0033C8B5();
private:
	_STL::vector<Nugget, _STL::allocator<Nugget> > m_info;
};
bool ModuleInfo::rva0033C8B5()
{
	bool ret = false;
	_STL::vector<Nugget, _STL::allocator<Nugget> >::iterator it = m_info.begin();
	while (it != m_info.end())
	{
		if (it->second->slot07())
		{
			it = m_info.erase(it);
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
	bool ret = false;
	_STL::vector<Nugget, _STL::allocator<Nugget> >::iterator it = m_info.begin();
	while (it != m_info.end())
	{
		if (it->second->isAiModuleData())
		{
			it = m_info.erase(it);
			ret = true;
		}
		else
		{
			++it;
		}
	}
	return ret;
}
