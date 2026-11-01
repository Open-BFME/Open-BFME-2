// cl: /O1 /DNDEBUG /MD /EHsc
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Native BFME 2 warehouse seed. Target constructor 004A7DEA installs
// its four native class tables and loads boxes from ModuleData+10.
// The six unrowed ZH methods are replaced by their existing native owners.
#include "SupplyWarehouseDockUpdateNative.h"
#include "../../../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../../Common/GameLogicObjectLookupView.h"
#include "../../../../Common/Thing/thing.h"

enum DamageType { DAMAGE_UNRESISTABLE = 8 };
enum DeathType { DEATH_NORMAL = 0 };
enum CommandSourceType { CMD_FROM_AI = 2 };
// The native action donor shares this Object prefix: radius B8 and AI 258.
// The three called methods already have native ledger owners.
class Object : public Thing
{
public:
    bool isUsingAirborneLocomotor() const;
    void kill(DamageType, DeathType);
    float rva00263763(const void *other) const;
    char m_unmodelled60[0xB8 - 0x60];
    float m_radius;
    char m_unmodelledBC[0x258 - 0xBC];
    void *m_iface;
};
extern GameLogic *TheGameLogic;
extern "C" const void *const __identifier("??_7ObjectHelperModuleData@@6B@")[];

SupplyWarehouseDockUpdateModuleData::SupplyWarehouseDockUpdateModuleData()
{
    m_vftable = __identifier("??_7ObjectHelperModuleData@@6B@");
    m_startingBoxesData = 1;
    m_deleteWhenEmpty = false;
}

SupplyWarehouseDockUpdate::SupplyWarehouseDockUpdate(Thing *thing, const ModuleData *moduleData)
    : DockUpdate(thing, moduleData)
{
    m_boxesStored = ((const SupplyWarehouseDockUpdateModuleData *)m_moduleData)->m_startingBoxesData;
}

// Pointer-only readers for the two existing dynamic calls. These classes
// are never constructed and emit no vftable. The AI contract supplies the
// +20 AICommandInterface adjustment for aiIdle.
template <int N>
class BfmeWarehouseSlots : public BfmeWarehouseSlots<N - 1>
{
public:
    virtual void unused(char (*)[N]);
};
template <> class BfmeWarehouseSlots<0> {};
class BfmeWarehouseSupplyTruckSlots : public BfmeWarehouseSlots<11>
{
public:
    virtual void setForceWantingState(bool);
};
class BfmeWarehouseAISlots : public BfmeWarehouseSlots<95>
{
public:
    virtual BfmeWarehouseSupplyTruckSlots *getSupplyTruckAIInterface();
};
struct BfmeWarehouseVictimFields
{
    unsigned char m_unreconstructed_000[0x258];
    AIUpdateInterface *m_ai;
};

void SupplyWarehouseDockUpdate::setDockCrippled(bool setting)
{
    if (setting)
    {
        if (m_activeDocker != 0)
        {
            Object *victim = TheGameLogic->findObjectByID((ObjectID)m_activeDocker);
            if (victim)
            {
                if (m_dockerInside)
                {
                    if (!victim->isUsingAirborneLocomotor())
                        victim->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
                }
                else
                {
                    BfmeWarehouseSupplyTruckSlots *supplyTruckAI =
                        ((BfmeWarehouseAISlots *)((BfmeWarehouseVictimFields *)victim)->m_ai)->getSupplyTruckAIInterface();
                    if (supplyTruckAI)
                    {
                        ((BfmeWarehouseVictimFields *)victim)->m_ai->aiIdle(CMD_FROM_AI);
                        supplyTruckAI->setForceWantingState(true);
                    }
                }
            }
        }
    }
    DockUpdate::setDockCrippled(setting);
}
