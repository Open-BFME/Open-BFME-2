/* Target facts: FXParticleSystem::QuadDrawModuleTemplate's constructors install its own table at +0 (deleting
destructor, two pure calls, writeINI), the folded CategoryModuleInfo table VA 0x00C1C780 at +4 and its
QuadDrawModuleInfo table at +8 (the -8 deleting-destructor thunk, then QuadDrawModuleInfo's three Snapshot slots), as
the real link's slot evidence for its copy constructor records. The copy constructor calls
CategoryModuleTemplate's copy 0x0004CB7B and the QuadDrawModuleInfo copy out of line. */
#pragma once

#ifndef __BFME2_QUADDRAWMODULETEMPLATE_H_
#define __BFME2_QUADDRAWMODULETEMPLATE_H_

#include "QuadDrawModuleInfo.h"
#include "FXModuleTemplateBase.h"

namespace FXParticleSystem
{

class QuadDrawModuleTemplate : public CategoryModuleTemplate<6>,
    public QuadDrawModuleInfo
{
public:
    QuadDrawModuleTemplate();
    QuadDrawModuleTemplate(const QuadDrawModuleTemplate &that);
    virtual ~QuadDrawModuleTemplate();

    virtual void writeINI(File &file, unsigned int indent) const;
};

}

#endif
