/* Target facts (RVAs): every FX module template's +0 table (for example LightningDrawModuleTemplate's
0x0081BD90 and DefaultModuleTemplate<1>'s 0x0081BA70) holds its deleting destructor, two pure calls and
writeINI, and its +4 table is the folded single-pure CategoryModuleInfo table VA 0x00C1C780.
CategoryModuleTemplate<6>'s own table holds its deleting destructor 0x00001EAE and three pure calls, so
it introduces the three slots; ModuleTemplate's table VA 0x00BBB52C holds only the deleting destructor.
The copy constructors call CategoryModuleTemplate's copy 0x0004CB7B out of line.
Structural inference: slots 1 and 2 are the clone/getClass pair ConcreteModuleTemplate implements;
their spellings here identify storage, not original source. */
#pragma once

#ifndef __BFME2_FXMODULETEMPLATEBASE_H_
#define __BFME2_FXMODULETEMPLATEBASE_H_

class File;

namespace FXParticleSystem
{

class ModuleClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ModuleFactory.h
class ModuleTemplate
{
public:
    ModuleTemplate() {}
    virtual ~ModuleTemplate() {}
};

template <int Category>
class CategoryModuleInfo
{
public:
    CategoryModuleInfo() {}
    virtual void unusedVirtual() = 0;

protected:
    ~CategoryModuleInfo() {}
};

template <int Category>
class CategoryModuleTemplateBase : public ModuleTemplate,
    public CategoryModuleInfo<Category>
{
public:
    __declspec(dllimport) __forceinline CategoryModuleTemplateBase() {}
    __declspec(dllimport) __forceinline virtual ~CategoryModuleTemplateBase() {}
};

template <int Category>
class CategoryModuleTemplate : public CategoryModuleTemplateBase<Category>
{
public:
    __declspec(dllimport) __forceinline CategoryModuleTemplate() {}
    CategoryModuleTemplate(const CategoryModuleTemplate &that);
    virtual ~CategoryModuleTemplate();

    virtual ModuleTemplate *clone() const = 0;
    virtual const ModuleClass &getClass() const = 0;
    virtual void writeINI(File &file, unsigned int indent) const = 0;
};

}

#endif
