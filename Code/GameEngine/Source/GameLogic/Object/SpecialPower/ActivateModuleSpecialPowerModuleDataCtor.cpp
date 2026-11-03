// cl: /DNDEBUG /MD
// stlport
//
// ??0ActivateModuleSpecialPowerModuleData@@QAE@XZ, retail 0x00256DA1,
// 36 bytes. ModuleData ctor over the pinned SpecialAbilityUpdateModuleData base (0x44EB54,
// 0xC8 bytes per the ToggleHidden row): the implicit _STL::vector<int>
// member at +0xC8 builds through the folded Vector_base at 0x211E58 (int
// spelling reuses the existing pin), and the compiler installs the derived
// vtable 0x00BF3F60 between the vector setup and call (TransitionDamageFX
// precedent; non-dtor virtual so no EH prolog draws). Class size 0xD4 proven
// by the ActivateModuleSpecialPower data factory (news 0xD4, sole caller at
// 0x256DE9). Row supersedes the ctor pin.

#include <vector>

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
// Declaration-only: retail keeps one 14-byte copy of the vector<int> teardown
// (0x0007FAB3); this TU's flags would emit a private 24-byte one.
template <> vector<int, allocator<int> >::~vector();
template <> _Vector_base<int, allocator<int> >::~_Vector_base();
}

class INI;
class Xfer;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

#include "../../../../Include/Common/INI/FieldParse.h"

// Rowed parse proc (retail 0x004CDF2B).
void parseTriggerSpecialPower(INI *ini, void *instance, void *store, const void *userData);


#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"

class ActivateModuleSpecialPowerModuleData : public SpecialAbilityUpdateModuleData
{
public:
	ActivateModuleSpecialPowerModuleData();
	virtual ~ActivateModuleSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0xC8 vector (implicit default init; ends at the rowed 0xD4 size).
	_STL::vector<int> m_vectorC8;
};

// ??0ActivateModuleSpecialPowerModuleData@@QAE@XZ @0x00256DA1
ActivateModuleSpecialPowerModuleData::ActivateModuleSpecialPowerModuleData()
	: SpecialAbilityUpdateModuleData()
{
}

// ?buildFieldParse@ActivateModuleSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004CDFBE
void ActivateModuleSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);

	// Own table (retail .data 0x00C5FD70): one entry and the terminator.
	static const FieldParse dataFieldParse[] =
	{
		{ "TriggerSpecialPower", parseTriggerSpecialPower, 0, 0 },
		{ 0, 0, 0, 0 }
	};
	parse.add(dataFieldParse, 0);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
