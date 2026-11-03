// Target facts: BodyModule constructor 0x004BD7FD calls BehaviorModule constructor 0x00253330, constructs BodyModuleInterface with the 43-pure-slot VA 0x00C5AB68, replaces it with VA 0x00C5AC18, installs primary VA 0x00C5AE68 and behavior-interface VA 0x00C5AD78, and stores float 1 at +0x14. The BodyModule primary table has 13 slots. Its destructor 0x004BD763 restores BodyModuleInterface VA 0x00C5AC18 and BehaviorModule VAs 0x00BEEA7C/0x00BEE9C0 before tail-calling 0x0049B47C. These are base-subobject teardown tables, not competing ActiveBody tables. The behavior-interface slot 0 at 0x002533D3 returns complete-object +0x10; body-interface slot 41 at 0x004BF893 returns complete-object +0.
// Donor names: Zero Hour GeneralsMD BodyModule.h supplies BodyModule and m_damageScalar.

#pragma once

#ifndef BFME2_GAMELOGIC_MODULE_BODYMODULECLASS_H
#define BFME2_GAMELOGIC_MODULE_BODYMODULECLASS_H

#include "BehaviorModule.h"
#include "BodyModule.h"

class BodyModule : public BehaviorModule, public BodyModuleInterface
{
public:
    BodyModule(Thing *thing, const ModuleData *moduleData);
    virtual ~BodyModule();
    virtual BodyModuleInterface *getBody();
    virtual bool vslot12();

protected:
    virtual void xfer(Xfer *xfer);

public:
    float m_damageScalar; // +0x14
};

#endif
