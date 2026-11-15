// cl: /DNDEBUG /MD /EHsc /Ob2

// <new> declares operator delete[]: the array path of the vector deleting destructor frees
// through it as retail does.
#include <new>

#include "../../../../Include/GameClient/TerrainCollisionModuleInfo.h"
namespace FXParticleSystem
{


class TerrainCollisionCategoryBaseA
{
public:
    virtual ~TerrainCollisionCategoryBaseA();
};

// Retail's CategoryModuleInfo<8> (table 0x00C1C780): one __purecall slot, no destructor.
class TerrainCollisionCategoryBaseB
{
public:
    virtual void slot00() = 0;
};

class TerrainCollisionCategoryBase
    : public TerrainCollisionCategoryBaseA,
      public TerrainCollisionCategoryBaseB
{
public:
    TerrainCollisionCategoryBase(const TerrainCollisionCategoryBase &) {}
    virtual ~TerrainCollisionCategoryBase();
};

// The category base is retail's CategoryModuleTemplate<8>: its copy
// constructor at 0x00001F30 is rowed in FXParticleSystem.cpp, so it is
// declared, never defined here.
template <int N>
class CategoryModuleTemplate : public TerrainCollisionCategoryBase
{
public:
    CategoryModuleTemplate(const CategoryModuleTemplate &that);
    virtual ~CategoryModuleTemplate();

private:
    volatile unsigned short m_word;
};

class TerrainCollisionModuleTemplate : public CategoryModuleTemplate<8>,
                                       public TerrainCollisionModuleInfo
{
public:
    TerrainCollisionModuleTemplate(const TerrainCollisionModuleTemplate &that);
    virtual ~TerrainCollisionModuleTemplate();
};

// ??0TerrainCollisionModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
TerrainCollisionModuleTemplate::TerrainCollisionModuleTemplate(const TerrainCollisionModuleTemplate &that)
    : CategoryModuleTemplate<8>(that),
      TerrainCollisionModuleInfo(that)
{
}

}

// The anchor (no retail counterpart) only makes this TU emit the vector deleting
// destructor of FXParticleSystem::TerrainCollisionModuleTemplate, which retail holds in the table's destructor slot.
// ?<bfmeVectorDeleteAnchor_FXParticleSystem_TerrainCollisionModuleTemplate> absent-from-retail
void bfmeVectorDeleteAnchor_FXParticleSystem_TerrainCollisionModuleTemplate(FXParticleSystem::TerrainCollisionModuleTemplate *p)
{
	p->FXParticleSystem::TerrainCollisionModuleTemplate::__vecDelDtor(3);
}
