#pragma once

// Include after the CategoryModuleTemplateBase definition used by the unit.
// The wind default template table at VA 0x00C1BFB8 binds slots 1-3 to
// clone, createModule and writeINI. The category table has pure entries there.
#include "WindModuleInfo.h"

class File;
template <class T> class TrackingPtr;

namespace FXParticleSystem {
template <int Category> class CategoryModuleTemplate;
class ParticleSystem;
template <int Category> class DefaultModule;

template <>
class CategoryModuleTemplate<7> : public CategoryModuleTemplateBase<7>, public WindModuleInfo
{
public:
    CategoryModuleTemplate();
    CategoryModuleTemplate(const CategoryModuleTemplate &that);
    virtual CategoryModuleTemplate *clone() const = 0;
    virtual DefaultModule<7> *createModule(TrackingPtr<ParticleSystem> &owner) = 0;
    virtual void writeINI(File &file, unsigned int indent) const = 0;
};
}
