// Target facts: constructor RVA 0x00351BD0 writes command/source at +0/+4, zeros position +8..+0x10, object pointers +0x14/+0x18/+0x1C, waypoint/polygon +0x2C/+0x30, integer +0x34, float +0x38 and dwords +0xB8/+0xBC; it constructs the coordinate vector at +0x20 through RVA 0x00211E58 and DamageInfo at +0x3C through RVA 0x00263895. Caller RVA 0x00394191 reserves 0xC0 bytes and passes that block to the constructor. AICommandParms has no base, vptr or virtual functions: +0 is the command, and the VA 0x00BF9200 table is installed inside DamageInfo at +0x3C, not on AICommandParms.
// Target facts: destructor RVA 0x001E7E9F (15 bytes) reads only the vector start at +0x20 and conditionally calls free RVA 0x00030830; it installs no table. DamageInfo constructor RVA 0x00263895 installs VA 0x00BF9200 (one slot, RVA 0x004D6F86), constructs input +4 and output +0x6C, and occupies 0x7C bytes. Store/reconstitute RVAs 0x00351570/0x0035164E copy the vector through RVA 0x0035149F, the +0x3C record through RVA 0x003427DD, and the last two dwords at +0xB8/+0xBC.
// Names: Zero Hour GeneralsMD GameLogic/AI.h supplies m_cmd, m_cmdSource, m_pos, m_obj, m_otherObj, m_team, m_coords, m_waypoint, m_polygon, m_intValue, m_damage, m_commandButton and m_path; the BFME2 float at +0x38 retains an offset name. The ledger declares the constructor and nonvirtual destructor out of line; its AICommandParms argument spellings use struct. The vector's three pointers at +0x20/+0x24/+0x28 are exposed without defining its operations.
#pragma once

#ifndef BFME2_GAMELOGIC_AICOMMANDPARMS_H
#define BFME2_GAMELOGIC_AICOMMANDPARMS_H

#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "Damage.h"

enum AICommandType;
enum CommandSourceType;
class Object;
class Team;
class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;

struct RvaCoords
{
    Coord3D *field00;
    Coord3D *field04;
    Coord3D *field08;
};

struct AICommandParms
{
    AICommandParms(AICommandType cmd, CommandSourceType cmdSource);
    ~AICommandParms();

    AICommandType m_cmd;
    CommandSourceType m_cmdSource;
    Coord3D m_pos;
    Object *m_obj;
    Object *m_otherObj;
    const Team *m_team;
    RvaCoords m_coords;
    const Waypoint *m_waypoint;
    const PolygonTrigger *m_polygon;
    int m_intValue;
    float field38;
    DamageInfo m_damage;
    const CommandButton *m_commandButton;
    Path *m_path;
};

#endif
