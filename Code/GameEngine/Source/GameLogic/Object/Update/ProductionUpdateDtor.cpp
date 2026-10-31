// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ??1ProductionUpdate@@UAE@XZ @0x0049E1BF 181B
// ProductionUpdate dtor via BFME1 donor ProductionUpdateDestructor.cpp:113 plus
// ctor TU ProductionUpdateCtor.cpp layout (base 0x20 plus ifaces at 0x20/0x24,
// queue at 0x28, list at 0x124, int at 0x12C, vector at 0x130, size 0x140).
// Evidence: pin ??1ProductionUpdate@@UAE@XZ, retail caller 0x0049E34F
// ??_GProductionUpdate, vtable stores at +0/+0xC/+0x10/+0x20/+0x24.
#include <list>
#include <vector>
#include <string.h>
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<AsciiString>(AsciiString *); }
namespace _STL { template <> _List_base<int, allocator<int> >::~_List_base(); }
namespace _STL { template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base(); }
namespace _STL { template <> vector<AsciiString, allocator<AsciiString> >::~vector(); }
namespace _STL { template <> void _List_base<int, allocator<int> >::clear(); }
namespace _STL { template <> void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *, unsigned int); }
namespace _STL { template <> void _STLP_alloc_proxy<AsciiString *, AsciiString, allocator<AsciiString> >::deallocate(AsciiString *, unsigned int); }
namespace _STL { template <> void allocator<_List_node<int> >::deallocate(_List_node<int> *, unsigned int) const; }
namespace _STL { template <> void allocator<AsciiString>::deallocate(AsciiString *, unsigned int) const; }
// bfme link decl-only end
// BitFlags<11> is DisabledMaskType (BitFlags11DisabilityCtors.cpp); its
// copy is a 4-byte memcpy call in retail.
#pragma function(memcpy)

template <int NUM_BITS>
class BitFlags
{
public:
	__forceinline BitFlags(const BitFlags &src) { memcpy(m_bits, src.m_bits, sizeof(m_bits)); }

private:
	unsigned int m_bits[(NUM_BITS + 31) / 32];
};
typedef BitFlags<11> DisabledMaskType;

// The module data's disabled-type mask at +0x2C, the one field
// getDisabledTypesToProcess reads.
class ProductionUpdateModuleData
{
public:
	char m_pad00[0x2C];
	DisabledMaskType m_disabledTypesToProcess;	// +0x2C
};

class Rva0049B47CFold
{
public:
	virtual ~Rva0049B47CFold();
	int m_pad[2];
};

class MiBase1
{
public:
	virtual void f1();
};

class PrimaryP : public Rva0049B47CFold, public MiBase1
{
public:
	~PrimaryP() {}
};

// ProductionUpdate's UpdateModuleInterface table (0x00C514F4): update and the
// getDisabledTypesToProcess override, then UpdateModule's 0x0044DF8D.
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
class Rva0024A797_B2
{
public:
	virtual UpdateSleepTime update() = 0;
	virtual DisabledMaskType getDisabledTypesToProcess() const;
	virtual void rva0044DF8D(UpdateSleepTime sleep) = 0;
	int m_pad2[3];
};

class UpdateModule : public PrimaryP, public Rva0024A797_B2
{
public:
	virtual ~UpdateModule();
	virtual void rva0044DF8D(UpdateSleepTime sleep);
};

class Iface20
{
public:
	virtual void s20() = 0;
};

class Iface24
{
public:
	virtual void s24() = 0;
};

class ProductionEntry
{
public:
	virtual void *scalarDeleting(unsigned int flags);
};

class Rva0049D526
{
public:
	void rva0049D57F(void *entry);
};

class AudioManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(int x);
};

extern AudioManager *TheAudio;

class ProductionUpdate : public UpdateModule, public Iface20, public Iface24
{
public:
	virtual ~ProductionUpdate();
	virtual UpdateSleepTime update();
	virtual DisabledMaskType getDisabledTypesToProcess() const;
private:
	const ProductionUpdateModuleData *getProductionUpdateModuleData() const
	{
		return (const ProductionUpdateModuleData *)m_pad[0];
	}

	ProductionEntry *m_queue28;
	char m_pad2C[0xF8];
	_STL::list<int> m_list124;
	int m_128;
	int m_12C;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_vec130;
};

// ProductionUpdate's UpdateModuleInterface table 0x00C514F4 (at +0x10)
// holds update in slot 0 and, in slot 1 where UpdateModule's default
// 0x00253376 sits in other modules' tables, this override returning the
// module data's mask. Retail places it just before the destructor.
DisabledMaskType ProductionUpdate::getDisabledTypesToProcess() const
{
	return getProductionUpdateModuleData()->m_disabledTypesToProcess;
}

ProductionUpdate::~ProductionUpdate()
{
	while (m_queue28)
	{
		ProductionEntry *entry = m_queue28;
		((Rva0049D526 *)this)->rva0049D57F(entry);
		void *p = entry ? entry->scalarDeleting(0) : 0;
		::operator delete(p);
	}
	if (TheAudio)
		TheAudio->s27(m_12C);
}
