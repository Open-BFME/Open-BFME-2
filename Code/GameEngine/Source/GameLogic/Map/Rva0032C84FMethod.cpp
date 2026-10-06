// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0032C84F@Rva0032C84F@@QAEXXZ @0x0032C84F 64B
// evidence: unlock caller 0x0032D554; rowed NameKeyGenerator::nameToKey UNASSIGNED plus rowed vector erase 0x0032BEE8
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *s);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva0032A3A9Element
{
public:
	char m_pad[4];
};

namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T, class A> class vector
{
public:
	T *erase(T *first, T *last);
	T *begin() { return _First; }
	T *end() { return _Last; }
private:
	T *_First;
	T *_Last;
	T *_End;
};
}

struct Entry0032C84F
{
	NameKeyType key;
	_STL::vector<Rva0032A3A9Element, _STL::allocator<Rva0032A3A9Element> > vec1;
	_STL::vector<Rva0032A3A9Element, _STL::allocator<Rva0032A3A9Element> > vec2;
};

class Rva0032C84F
{
public:
	void rva0032C84F();
private:
	char m_pad00[0xf80];
	Entry0032C84F m_entries[20];
};

void Rva0032C84F::rva0032C84F()
{
	char *p = (char *)this + 0xf94;
	int n = 0x14;
	do
	{
		*(NameKeyType *)(p - 0x14) = TheNameKeyGenerator->nameToKey("UNASSIGNED");
		typedef _STL::vector<Rva0032A3A9Element, _STL::allocator<Rva0032A3A9Element> > Vec;
		Vec *v1 = (Vec *)(p - 0x10);
		v1->erase(v1->begin(), v1->end());
		Vec *v2 = (Vec *)(p - 4);
		v2->erase(v2->begin(), v2->end());
		p += 0x1c;
	} while (--n != 0);
}
