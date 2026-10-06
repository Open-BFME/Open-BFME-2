// cl: /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0Rva00502C80@@QAE@XZ @ 0x00502C80 (121B).
// EH ctor: 4 header dwords zeroed, two vectors of BfmeE16 at +0x10/+0x24,
// int+float at +0x1C/+0x20, float+int at +0x30/+0x34, two
// map<NameKeyType,ModuleFactory::ModuleTemplate> at +0x38/+0x44.
// Calls rowed Vector_base 0x00211E58 twice and rowed map ctor 0x00413727
// twice. Recipe: TransportAIUpdateModuleDataCtor precedent (explicit-spec
// decls keep the calls out-of-line). The last byte is the second allocator
// temporary's stack slot: declaring the _Vector_base specialization throw()
// lets the compiler reuse [ebp-0xd] for both vectors instead of allocating a
// second [ebp-0xe] slot; the map specialization stays without throw() so the
// 0/1/2 EH states still arm.
#include <map>
#include <vector>

enum NameKeyType
{
	kNameKeyInvalid = 0
};

class ModuleFactory
{
public:
	class ModuleTemplate
	{
	public:
		ModuleTemplate();
		~ModuleTemplate();
	};
};

struct BfmeE16
{
	unsigned char m_pad[16];
};

namespace _STL
{

template <>
_Vector_base<BfmeE16, allocator<BfmeE16> >::_Vector_base(
	const allocator<BfmeE16> &storage) throw();

template <>
map<NameKeyType, ModuleFactory::ModuleTemplate, less<NameKeyType>,
	allocator<pair<const NameKeyType, ModuleFactory::ModuleTemplate> > >::map();

}

class Rva00502C80
{
public:
	Rva00502C80();

private:
	unsigned m_00;
	unsigned m_04;
	unsigned m_08;
	unsigned m_0c;
	_STL::vector<BfmeE16> m_vec10;
	unsigned m_1c;
	float m_20;
	_STL::vector<BfmeE16> m_vec24;
	float m_30;
	int m_34;
	_STL::map<NameKeyType, ModuleFactory::ModuleTemplate> m_map38;
	_STL::map<NameKeyType, ModuleFactory::ModuleTemplate> m_map44;
};

Rva00502C80::Rva00502C80()
	: m_00(0)
	, m_04(0)
	, m_08(0)
	, m_0c(0)
	, m_vec10()
	, m_1c(0)
	, m_20(0.0f)
	, m_vec24()
	, m_30(0.0f)
	, m_34(0)
	, m_map38()
	, m_map44()
{
}
