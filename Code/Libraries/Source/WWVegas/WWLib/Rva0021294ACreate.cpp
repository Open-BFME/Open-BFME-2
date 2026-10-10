// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva0021294A@Rva0021294A@@QAEPAVRva003FD789@@ABV?$StringBase@D@@@Z, retail 0x0021294A, 87 bytes.
// Chain: calls 0x003FD716 which just became ready. Creates a 0x2C-byte
// Rva003FD789 from the StringBase arg via rowed new 0x0002FDA0 plus rowed
// ctor 0x003FD716, then appends it to the vector<ModuleData const *> at
// this+0x24C through the rowed push_back 0x004DFCB0, returning the new
// pointer. Same ModuleData EH recipe as Rva003FD789Ctor plus the
// Rva002129A1 push_back shape at +0x258. Caller at 0x003FD7FF.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &other);
	~StringBase();
private:
	T *m_data;
};

class ModuleData
{
public:
	virtual ~ModuleData();
};

class Rva003FD789 : public ModuleData
{
public:
	Rva003FD789(const StringBase<char> &src);
	virtual ~Rva003FD789();
private:
	int volatile m_04;
	float volatile m_08;
	StringBase<char> m_0c;
	bool m_10;
	bool m_11;
	float m_14;
	short m_18;
	StringBase<char> m_1c;
	float volatile m_20;
	float volatile m_24;
	float volatile m_28;
};

class Rva0021294A
{
public:
	Rva003FD789 *rva0021294A(const StringBase<char> &str);

private:
	unsigned char m_pad[0x24C];
	_STL::vector<const ModuleData *> m_vec;
};

Rva003FD789 *Rva0021294A::rva0021294A(const StringBase<char> &str)
{
	Rva003FD789 *item = new Rva003FD789(str);
	m_vec.push_back(item);
	return item;
}
