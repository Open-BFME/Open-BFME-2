// cl: /DNDEBUG /MD /EHsc /Ob2

// Open-BFME5: RenderObjectDrawModuleTemplate copy constructor. Retail copies
// the two-vtable category base, then the RenderObjectDrawModuleInfo subobject
// at +8 with the usual null-preserving source adjustment.

class __declspec(novtable) RenderObjectDrawCategoryBaseA
{
public:
	virtual ~RenderObjectDrawCategoryBaseA() {}
};

class __declspec(novtable) RenderObjectDrawCategoryBaseB
{
public:
	virtual ~RenderObjectDrawCategoryBaseB() {}
};

namespace FXParticleSystem
{
template <int Category>
class CategoryModuleTemplate
{
public:
	virtual ~CategoryModuleTemplate();
};
}

// Retail's state-0 funclet 0x00781D3D unwinds this base through 0x00001F18,
// the two-vtable category destructor rowed as
// ??1?$CategoryModuleTemplate@$05@FXParticleSystem@@UAE@XZ (draw category,
// FXParticleSystemFactories.cpp): forward to it.
class __declspec(novtable) RenderObjectDrawCategoryBase
	: public RenderObjectDrawCategoryBaseA,
	  public RenderObjectDrawCategoryBaseB
{
public:
  RenderObjectDrawCategoryBase(const RenderObjectDrawCategoryBase &);
	virtual ~RenderObjectDrawCategoryBase()
	{
		((FXParticleSystem::CategoryModuleTemplate<6> *)this)->FXParticleSystem::CategoryModuleTemplate<6>::~CategoryModuleTemplate();
	}
};

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../Include/GameClient/RenderObjectDrawModuleInfo.h"
namespace FXParticleSystem
{


class RenderObjectDrawModuleTemplate
	: public RenderObjectDrawCategoryBase,
	  public RenderObjectDrawModuleInfo
{
public:
	RenderObjectDrawModuleTemplate(const RenderObjectDrawModuleTemplate &that);
	virtual ~RenderObjectDrawModuleTemplate();
};

// ??0RenderObjectDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
RenderObjectDrawModuleTemplate::RenderObjectDrawModuleTemplate(
	const RenderObjectDrawModuleTemplate &that)
	: RenderObjectDrawCategoryBase(that),
	  RenderObjectDrawModuleInfo(that)
{
}

}
