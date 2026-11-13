// Category-8 views fixed to the actual KEY/NAME references. The reference-
// deducing form is not selected by VC7.1 here; only class types vary.
// Primary native slots: deletion, clone, createModule, writeINI; getClass is secondary.
#pragma once
#ifndef BFME2_FX_CONCRETE_EVENT_MODULE_TEMPLATE_H
#define BFME2_FX_CONCRETE_EVENT_MODULE_TEMPLATE_H
class File;
template <class T> class TrackingPtr;
namespace FXParticleSystem { class ParticleSystem; }
// Expand at the original event declaration sites to retain tag initializer order.
// The category's common runtime return base remains unrecovered.
#define BFME_FX_EVENT_CONCRETE(KEY, NAME) \
template <class MODULE, class TEMPLATE, class DEFAULT> \
class ConcreteModuleTemplate<ModuleTag<8, KEY, NAME, MODULE, TEMPLATE, DEFAULT> > : public TEMPLATE \
{ \
public: \
 ConcreteModuleTemplate(); \
 __declspec(noinline) ConcreteModuleTemplate(const ConcreteModuleTemplate &that); \
 virtual const ConcreteModuleClass<ModuleTag<8, KEY, NAME, MODULE, TEMPLATE, DEFAULT> > &getClass() const; \
 virtual TEMPLATE *clone() const; \
 virtual MODULE *createModule(TrackingPtr<ParticleSystem> &system); \
}; \
template <class MODULE, class TEMPLATE, class DEFAULT> \
ConcreteModuleTemplate<ModuleTag<8, KEY, NAME, MODULE, TEMPLATE, DEFAULT> >::ConcreteModuleTemplate() {} \
template <class MODULE, class TEMPLATE, class DEFAULT> \
ConcreteModuleTemplate<ModuleTag<8, KEY, NAME, MODULE, TEMPLATE, DEFAULT> >::ConcreteModuleTemplate( \
 const ConcreteModuleTemplate &that) : TEMPLATE(that) {} \
template <class MODULE, class TEMPLATE, class DEFAULT> \
TEMPLATE *ConcreteModuleTemplate<ModuleTag<8, KEY, NAME, MODULE, TEMPLATE, DEFAULT> >::clone() const \
{ return new ConcreteModuleTemplate(*this); }
#endif
