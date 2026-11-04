// cl: /DNDEBUG /MD /EHsc
// stlport
//
// ??0ReplaceObjectUpdateModuleData@@QAE@XZ, retail 0x004B2AC4, 61 bytes.
// Frameless ctor: canonical SpecialAbilityUpdateModuleData base at 0x44EB54
// called first, compiler installs vtable 0x00C56C78 second, vector
// member at +0xC8 implicitly built through the folded Vector_base<int> row
// (normal STL materializes the temp allocator; NO_EXCEPTIONS inlines it,
// which V1 proved wrong), 0.0f at +0xD4, 0 at +0xD8, 0 at +0xDC. Factory
// 0x24FCEA news 0xE0. Element type is a TU-local stand-in (fold-identical).

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

typedef int Int;

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"

class ReplaceObjectUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	ReplaceObjectUpdateModuleData();
	virtual ~ReplaceObjectUpdateModuleData(); // Defined by the rowed destructor TU.

private:
	_STL::vector<Int> m_members;
	float m_radius;
	int m_count;
	unsigned char m_flag;
};

// ??0ReplaceObjectUpdateModuleData@@QAE@XZ
ReplaceObjectUpdateModuleData::ReplaceObjectUpdateModuleData()
	: SpecialAbilityUpdateModuleData()
{
	m_radius = 0.0f;
	m_count = 0;
	m_flag = 0;
}
