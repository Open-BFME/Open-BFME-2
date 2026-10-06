// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002E00F9@Rva002E00F9@@QAEXPAX0@Z @0x002E00F9 52B iterate ptr range virtual then push_back
// Evidence: callee rowed 0x004DFCB0 vector ModuleData push_back; virtual slot 1 returning ModuleData star; caller 0x004E1230; neighbours STL vector units share /O1
class ModuleData
{
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, typename A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
}

class Rva002E00F9Elem
{
public:
	virtual ~Rva002E00F9Elem();
	virtual const ModuleData *rva002E00F9Get(void *arg);
};

class Rva002E00F9
{
public:
	void rva002E00F9(void *arg1, void *arg2);
private:
	char m_pad[0x30];
	Rva002E00F9Elem **m_30;
	Rva002E00F9Elem **m_34;
};

void Rva002E00F9::rva002E00F9(void *arg1, void *arg2)
{
	_STL::vector<const ModuleData *> *out = (_STL::vector<const ModuleData *> *)arg2;
	Rva002E00F9Elem **p = m_30;
	Rva002E00F9Elem **end = m_34;
	for (; p != end; ++p)
	{
		const ModuleData *res = (*p)->rva002E00F9Get(arg1);
		const ModuleData *tmp = res;
		out->push_back(tmp);
	}
}
