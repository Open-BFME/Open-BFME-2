// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva0033C8B5@ModuleInfo@@QAE_NXZ @0x0033C8B5 51B: vector<Nugget> filter via ModuleData virtual slot 7 erases matching entries returns bool.
// Evidence: calls rowed vector erase at 0x0033C3BC; vcall [eax+0x1c] on [esi+8]; stride 0x14 finish at +4; sibling clearAiModuleInfo 51B same shape.
class ModuleData
{
public:
	virtual ~ModuleData();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual bool isMatching();
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
		if (it->second->isMatching())
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
