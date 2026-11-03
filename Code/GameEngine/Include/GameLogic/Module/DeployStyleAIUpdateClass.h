// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x0048E983 calls AIUpdateInterface at 0x0048E98E, then stores
// 0x00C4CA00/+0, 0x00BFA3C0/+0x0C, 0x00C4C9F4/+0x10,
// 0x00C4C9F0/+0x20 and 0x00C52F88/+0x24 at 0x0048E999..0x0048E9B4.
// Destructor 0x0048E852 restores these same five tables at
// 0x0048E863..0x0048E87E, destroys the +0x3E4 member through 0x0026B03D
// at 0x0048E88F, then calls AIUpdateInterface's destructor 0x0026E836
// at 0x0048E89A. Its scalar-deleting wrapper is 0x0048E9F3.
// These are the class tables; the parent's different stores at 0x0026E9BD
// and 0x0026E836 belong to base construction and destruction.
// Factory 0x0024D1E6 pushes 0x4D8 at 0x0024D1F1 and calls the constructor
// at 0x0024D210. AIUpdateInterface occupies +0..+0x3E3; the constructor
// calls initMember 0x0026AFDA on +0x3E4 at 0x0048E9BB. The member ends
// before byte stores +0x4A8/+0x4A9 at 0x0048E9C4/0x0048E9CA: size 0xC4.
// Its init/dtor/xfer rows name Rva0026AFDAMember; reset 0x0048E634 writes
// its first dword and +0x4A9. Unrecovered member storage remains opaque.
// Constructor stores 0x0048E9D0..0x0048E9E2 establish four-byte fields at
// +0x4AC/+0x4B0/+0x4B4/+0x4B8. Reset 0x0048E65B writes dwords
// +0x4BC/+0x4C0, floats +0x4C4/+0x4C8/+0x4CC, and bytes +0x4D0..+0x4D6.
// Xfer 0x0048E6F8 transfers that float triple as 12 bytes and calls the
// member's doXfer 0x003533BF last. Helpers 0x0048E6AB/0x0048E6D2 read
// +0x4B4 and write +0x4D5/+0x4D6. The final alignment byte is +0x4D7.
// Primary table 0x00C4CA00 has 155 slots, ending at the Deploy literal
// 0x00C4CC6C. Its parent has 154 slots. Changed slots are 0 (deleting
// destructor), 1 (0x0049A7EE, inherited loadPostProcess slot), 2
// (0x0048E8F1, returns the DeployStyleAIUpdate name), 3 (xfer), 4
// (getModuleNameKey 0x0048E8AC), and 110 (0x0048E643, isIdle slot).
// Added slot 154 is doCommand 0x0048EA0F; 0x0048E90B dispatches +0x268.
// Secondary tables have 47/3/1/6 slots at +0x0C/+0x10/+0x20/+0x24.
// The +0x10 update slot targets 0x0048EE8C; the +0x20 aiDoCommand slot
// targets 0x0048E8F7, whose body subtracts 0x20 before calling doCommand.
// The other secondary slots equal AIUpdateInterface's. Its registered
// header supplies the inherited slots and subobject layout.
// ToggleDeploy's 0x004AE717 calls primary +0x1BC (slot 111), whose target
// is AIUpdateInterface::rva00262D8F (0x00262D8F); callers use that inherited name.
// Zero Hour DeployStyleAIUpdate.h names the class, constructor, update,
// aiDoCommand, isIdle and DeployStateTypes. Other declarations below use
// the target ledger's method spellings. The virtual slots whose target rows
// use another class's name remain inherited-slot overrides, not new slots.

#pragma once
#ifndef __BFME2_DEPLOYSTYLEAIUPDATECLASS_H_
#define __BFME2_DEPLOYSTYLEAIUPDATECLASS_H_

#include "AIUpdate.h"

enum DeployStateTypes;

class Rva0026AFDAMember
{
public:
    Rva0026AFDAMember *initMember();
    ~Rva0026AFDAMember();
    void doXfer(Xfer *);

    int m_000;
    unsigned char m_storage004[0xC0];
};

class DeployStyleAIUpdate : public AIUpdateInterface
{
public:
    DeployStyleAIUpdate(Thing *, const ModuleData *);
    virtual ~DeployStyleAIUpdate();
    virtual NameKeyType getModuleNameKey() const;
    virtual UpdateSleepTime update();
    virtual void aiDoCommand(const AICommandParms *);
    virtual bool isIdle() const;
    virtual void doCommand(const AICommandParms *, bool);

    static Module *friend_newModuleInstance(Thing *, const ModuleData *);
    void reset();
    void Rva0048E634Reset();
    void rva0048E6AB();
    void rva0048E6D2();
    void rva0048E8F7(const AICommandParms *);
    void doLastOutsideCommand();
    void rva0048EB53(DeployStateTypes);

protected:
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);

public:
    Rva0026AFDAMember m_member3E4;
    bool m_4A8;
    bool m_4A9;
    int m_4AC;
    int m_4B0;
    int m_4B4;
    unsigned int m_4B8;
    ObjectID m_4BC;
    ObjectID m_4C0;
    float m_4C4[3];
    bool m_4D0;
    bool m_4D1;
    bool m_4D2;
    bool m_4D3;
    bool m_4D4;
    bool m_4D5;
    bool m_4D6;
};

#endif
