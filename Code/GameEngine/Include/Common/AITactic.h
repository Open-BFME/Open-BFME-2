// FILE: AITactic.h
// Target facts (addresses are RVAs unless marked VA):
// 0x004ED3D1 stores VA 0x00C629E4 at +0 and initializes through dword +0x54. Its calls at +4/+0x14 construct 12-byte vectors (0x00211E58), and +0x2C copies the name (0x000365F0). It has no base-constructor call or secondary vptr. 0x005AB203 allocates 0x58 bytes for AIStartWoTRBattleTactic; 0x005AB1B4 and 0x005DCC0A add no fields, proving AITactic is 0x58 bytes.
// 0x004EDCE9 restores VA 0x00C629E4, calls end(0,1), releases the string at +0x2C, then frees the vectors at +0x14/+4. Its deleting destructor 0x004EDEE7 occupies slot 0. These destructor rows currently have the owner spelling Rva004EDCE9.
// VA 0x00C629E4 has nine slots: 0x004EDEE7, purecall, purecall, 0x004ECE61, 0x000910FB, 0x004EDA8C, purecall, purecall, 0x004EDDAA. VA 0x00C62A08 starts string data. The intermediate tables VA 0x00C767DC, 0x00C76834 and 0x00C7690C add slot 9; create is not an AITactic slot.
// Slot names and signatures follow initializeTeamTemplate (0x004ECE61), xfer (0x004EDA8C), and derived overrides canRun (0x005AA652), cleanUp (0x005AAD26), run (0x005AA663), update (0x005AA670). Slot 4 returns one (0x000910FB); its original name is unproved. Slot 8 targets the nonvirtual row rva004EDDAA; its virtual spelling is unproved.
// 0x004ED3D1 writes byte flags at +0x10/+0x28/+0x34/+0x50/+0x51; pointers at +0x20/+0x24; the string at +0x2C; dwords at +0x30/+0x54; and floats at +0x38/+0x3C/+0x40/+0x44/+0x48/+0x4C. 0x004ECECD/0x004ECF05 iterate the 20-byte records through +0x14/+0x18. Other member declarations below use their matched ledger spellings; no donor declaration establishes this class.
// 0x004ED257 loads +0x24 as the receiver of Rva002A9BF2::rva002A9BF2 (0x002A9BF2). 0x004EDDAA passes +0x38 to a coordinate query, and 0x004EDA60 passes +0x44 to rva004ED372(const Coord3D *); both coordinate spans have the registered Coord3D layout. 0x004ED6D2 compares the +4 vector's elements with Team's prototype at +0x30.
// Nonvirtual ledger rows: rva004ECE1C 0x004ECE1C; rva004ECECD 0x004ECECD; rva004ECF05 0x004ECF05; anyTeamMembersInCombat 0x004ECF41; updateTeamInfos 0x004ECF9C; cohereTeams 0x004ED08A; isTeamIdle 0x004ED134; rva004ED169 0x004ED169; teamAttackObject 0x004ED1A1; teamAttackMove 0x004ED1FD; teamForceMove 0x004ED257; teamGarrisonObject 0x004ED2ED; rva004ED342 0x004ED342; rva004ED372 0x004ED372.
// Remaining nonvirtual ledger rows: sendTeamToAssistAnotherHorde 0x004ED52E; NotifyTeamCreated 0x004ED6D2; end 0x004ED748; start(request,owner) 0x004ED81D; start(owner) 0x004ED955; rva004EDA60 0x004EDA60; NotifyTeamCancelled 0x004EDD4D; rva004EDDAA 0x004EDDAA; calcLastTeamPos 0x004EDDD3; preUpdate 0x004EDF03; rva005ACDA9 0x005ACDA9.

#pragma once

#ifndef __BFME2_AITACTIC_H_
#define __BFME2_AITACTIC_H_

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

struct Rva004ECECDNode;
struct Rva00506909Request;
class Rva002A9BF2;
class Object;
class Team;
class TeamPrototype;
class Xfer;

class AITactic
{
public:
    AITactic(const AsciiString &name, bool flag);
    virtual ~AITactic();
    virtual bool canRun(void *request) = 0;
    virtual void cleanUp() = 0;
    virtual bool initializeTeamTemplate(void *team, int count);
    virtual unsigned int v4();
    virtual void xfer(Xfer *xfer);
    virtual void run() = 0;
    virtual void update() = 0;
    virtual void vslot08();

    void rva004ECE1C();
    Team *rva004ECECD(int id);
    Rva004ECECDNode *rva004ECF05(int id);
    bool anyTeamMembersInCombat();
    void updateTeamInfos();
    void cohereTeams();
    bool isTeamIdle(int id);
    unsigned char rva004ED169();
    void teamAttackObject(int id, Object *target);
    void teamAttackMove(int id, const Coord3D *point);
    void teamForceMove(int id, const Coord3D *point);
    void teamGarrisonObject(int id, Object *target);
    void rva004ED342(void *point);
    void rva004ED372(const Coord3D *point);
    bool sendTeamToAssistAnotherHorde(Team *team);
    void NotifyTeamCreated(Team *team);
    void NotifyTeamCancelled(Team *team);
    void end(bool first, bool second);
    bool start(Rva00506909Request *request, void *owner);
    bool start(void *owner);
    void rva004EDA60();
    void rva004EDDAA();
    void calcLastTeamPos();
    void preUpdate();
    bool rva005ACDA9();

    TeamPrototype **m_field04;
    TeamPrototype **m_field08;
    TeamPrototype **m_field0C;
    bool m_field10;
    unsigned char m_pad11[3];
    Rva004ECECDNode *m_field14;
    Rva004ECECDNode *m_field18;
    Rva004ECECDNode *m_field1C;
    void *m_field20;
    Rva002A9BF2 *m_field24;
    bool m_field28;
    unsigned char m_pad29[3];
    AsciiString m_field2C;
    unsigned int m_field30;
    bool m_field34;
    unsigned char m_pad35[3];
    Coord3D m_field38;
    Coord3D m_field44;
    bool m_field50;
    bool m_field51;
    unsigned char m_pad52[2];
    unsigned int m_field54;
};

#endif
