// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DefaultModuleTemplate (N=3) copy constructor.

namespace FXParticleSystem
{

class ModuleTemplate
{
public:
	virtual ~ModuleTemplate();
};

template <int Category>
class CategoryModuleInfo
{
public:
	virtual void unusedVirtual() = 0;
};

template <int Category>
class CategoryModuleTemplateBase : public ModuleTemplate, public CategoryModuleInfo<Category>
{
};

template <int Category>
class CategoryModuleTemplate : public CategoryModuleTemplateBase<Category>
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that) throw();
	virtual ~CategoryModuleTemplate();
};

#include "../../../../Include/GameClient/GameClientRandomVariable.h"

class DefaultPhysicsModuleInfo
{
public:
	DefaultPhysicsModuleInfo(const DefaultPhysicsModuleInfo &that) throw();
	virtual ~DefaultPhysicsModuleInfo();

private:
	float m_field0;
	float m_field1;
	float m_field2;
	int m_field3;
	GameClientRandomVariable m_var1;
};

template <int Category>
class DefaultModuleTemplate : public CategoryModuleTemplate<Category>, public DefaultPhysicsModuleInfo
{
public:
	DefaultModuleTemplate(const DefaultModuleTemplate &that);
	virtual ~DefaultModuleTemplate();
};

template <int Category>
DefaultModuleTemplate<Category>::DefaultModuleTemplate(const DefaultModuleTemplate &that)
	: CategoryModuleTemplate<Category>(that), DefaultPhysicsModuleInfo(that)
{
}

template DefaultModuleTemplate<3>::DefaultModuleTemplate(const DefaultModuleTemplate &);

}
