// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// LivingWorldRegionManager::rva0020FB8B, retail 0x0020FB8B (132 B; WB
// 0x00B56900, unnamed; called from LivingWorldLogic::OnBattleComplete
// 0x002BAF7E): finds the pending battle (+0x14 list) with the completed
// battle's id (+0x34), notifies TheLivingWorldManager with its +0x30
// field (0x00212655), moves the battle to the completed list (+0x20) and
// drops it from the pending one. The lists keep the element spellings their
// rowed vector members carry (erase 0x001FF51F, reserve 0x002B712E,
// push_back 0x004DFCB0).
#include <vector>
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
// Keep the pointer-range accessors inline in this consumer; their retail
// standalone /Od bodies are owned by stlport_vector_voidptr.cpp.
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return this->_M_finish; }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t n)
{ return *(begin() + n); }
}

class ModuleData;

struct LivingWorldBattleIDView
{
	char m_pad00[0x30];
	int m_30;		// +0x30
	int m_id;		// +0x34
};
class LivingWorldBattle;

#include "../../../../Include/Common/Rva00DFE1C8Host.h"
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;	// 0x00DFE1C8

#include "../../../../Include/GameLogic/LivingWorldRegionManager.h"

// Keep the rowed vector template identities over the canonical raw storage.

// bfme link decl-only begin
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::_M_clear(); }
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::_M_insert_overflow(ModuleData const * *,ModuleData const * const &,_STL::__true_type const &,unsigned int,bool); }
namespace _STL { template <> void _STLP_alloc_proxy<ModuleData const * *,ModuleData const *,_STL::allocator<ModuleData const *> >::deallocate(ModuleData const * *,unsigned int); }
namespace _STL { template <> void allocator<ModuleData const *>::deallocate(ModuleData const * *,unsigned int) const; }
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::reserve(unsigned int); }
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::push_back(ModuleData const * const &); }
// bfme link decl-only end
void LivingWorldRegionManager::rva0020FB8B(LivingWorldBattle *battle)
{
	for (unsigned int i = 0; i < reinterpret_cast<_STL::vector<void *> *>(&field14)->size(); ++i)
	{
		if (((LivingWorldBattleIDView *)battle)->m_id == ((LivingWorldBattleIDView *)(*reinterpret_cast<_STL::vector<void *> *>(&field14))[i])->m_id)
		{
			((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00212655(((LivingWorldBattleIDView *)battle)->m_30);
			reinterpret_cast<_STL::vector<const ModuleData *> *>(&field20)->reserve(reinterpret_cast<_STL::vector<void *> *>(&field14)->size());
			reinterpret_cast<_STL::vector<const ModuleData *> *>(&field20)->push_back((const ModuleData *)battle);
			reinterpret_cast<_STL::vector<void *> *>(&field14)->erase(reinterpret_cast<_STL::vector<void *> *>(&field14)->begin() + i);
			return;
		}
	}
}
