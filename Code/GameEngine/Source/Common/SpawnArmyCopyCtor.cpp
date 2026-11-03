// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??0SpawnArmy@@QAE@ABV0@@Z @ 0x004E2F9F (295B).
// Copy ctor of the ModuleData class with vtable 0x00861F28 whose dtor is
// rowed at 0x004E3184. Same temp is built here and torn down by that dtor
// in caller 0x004FB924. _Construct wrapper at 0x004E3706 treats it as
// 88-byte BfmePod88. Members call StringBase<char> copy at 0x000365F0 and
// vector<AsciiString> copy at 0x000BC07E. Layout from the dtor TU plus
// retail offsets. Snapshot base dtor arms EH state 0 before the first member
// like retail.
#include <memory>
#include <vector>

#include "ascii_string.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> vector<AsciiString, allocator<AsciiString> >::vector(const vector<AsciiString, allocator<AsciiString> >&);
template <> AsciiString *__uninitialized_copy(const AsciiString*, const AsciiString*, AsciiString*, const __false_type&);
}

#include "../../Include/Common/SpawnArmy.h"

SpawnArmy::SpawnArmy(const SpawnArmy &spawnArmy)
    : m_04(spawnArmy.m_04), m_08(spawnArmy.m_08), m_0c(spawnArmy.m_0c), m_10(spawnArmy.m_10),
      m_14(spawnArmy.m_14), m_18(spawnArmy.m_18), m_1c(spawnArmy.m_1c),
      m_20(spawnArmy.m_20), m_24(spawnArmy.m_24),
      m_28(spawnArmy.m_28), m_2c(spawnArmy.m_2c), m_30(spawnArmy.m_30), m_34(spawnArmy.m_34),
      m_vec38(spawnArmy.m_vec38),
      m_44(spawnArmy.m_44), m_48(spawnArmy.m_48), m_4c(spawnArmy.m_4c),
      m_50(spawnArmy.m_50), m_54(spawnArmy.m_54), m_55(spawnArmy.m_55)
{
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0BfmePod88@@QAE@ABU0@@Z=??0SpawnArmy@@QAE@ABV0@@Z")
