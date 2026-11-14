// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
// ?cacheButtonImage@CommandButton@@QAEXXZ @0x0035B77D 92B: image-name array resolve loop
// over AsciiString slots [+0xB4,+0xB8) pushing found Images into the ModuleData
// vector at +0xEC then clearing each slot. Skips empty names and misses via
// rowed isEmpty 0x00001E2F plus rowed findImageByName 0x002D92F6 plus rowed
// push_back plus rowed releaseBuffer 0x00036410 plus global 0x00DFF078.
// Evidence: ECX=this plus void ret plus same four callees plus global as
// sibling Rva0026F216ImageResolve; caller 0x0031AC39 walks +0x18 list calling this.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

#include "ascii_string.h"


#include "../../../Include/Common/ModuleData.h"

#include "../../../Include/GameClient/Image.h"


extern ImageCollection *TheMappedImageCollection;

#include "../../../Include/GameClient/CommandButton.h"

// bfme link decl-only begin
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::_M_clear(); }
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::_M_insert_overflow(ModuleData const * *,ModuleData const * const &,_STL::__true_type const &,unsigned int,bool); }
namespace _STL { template <> ModuleData const * * allocator<ModuleData const *>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<ModuleData const * *,ModuleData const *,_STL::allocator<ModuleData const *> >::deallocate(ModuleData const * *,unsigned int); }
namespace _STL { template <> void allocator<ModuleData const *>::deallocate(ModuleData const * *,unsigned int) const; }
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::push_back(ModuleData const * const &); }
// bfme link decl-only end
void CommandButton::cacheButtonImage()
{
	if (TheMappedImageCollection != 0)
	{
		for (AsciiString *it = m_imageNamesBegin; it != m_imageNamesEnd; ++it)
		{
			if (!it->isEmpty())
			{
				// Keep the existing non-owning vector provider ABI; Image has no ModuleData base.
				const ModuleData *found = reinterpret_cast<const ModuleData *>(TheMappedImageCollection->findImageByName(*it));
				if (found != 0)
					reinterpret_cast<_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *>(&m_imagesBegin)->push_back(found);
				it->clear();
			}
		}
	}
}
