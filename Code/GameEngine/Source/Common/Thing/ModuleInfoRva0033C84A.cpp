// cl: /Ireference/shims/bfme2_ascii /O1 /MD
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
class ModuleInfo
{
public:
	struct Nugget
	{
		char m_pad0[0xC];
		int m_interfaceMask;
		unsigned char m_flag10;
		unsigned char m_flag11;
		char m_pad2[0x14 - 0x12];
	};
	bool rva0033C84A(int mask);
private:
	_STL::vector<Nugget, _STL::allocator<Nugget> > m_info;
};
bool ModuleInfo::rva0033C84A(int mask)
{
	bool ret = false;
	_STL::vector<Nugget, _STL::allocator<Nugget> >::iterator it = m_info.begin();
	while (it != m_info.end())
	{
		if ((it->m_interfaceMask & mask) != 0 && it->m_flag10 != 0 && it->m_flag11 == 0)
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
