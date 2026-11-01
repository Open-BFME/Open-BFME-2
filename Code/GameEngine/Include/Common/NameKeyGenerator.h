// NameKeyGenerator: canonical BFME2 interface and target layout.
// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x001491AC calls SubsystemInterface's 0x001B4E63 at 0x001491BF and stores table 0x00BD3568 at 0x001491CF. Destructor 0x00148BC2 restores that table at 0x00148BD6, then calls the parent destructor 0x001B4E74 at 0x00148C2E. The parent's table 0x00BD77A0 belongs to base construction/destruction.
// GameEngine::init allocates 0x2BF84 bytes at 0x0022E3BC and calls the constructor at 0x0022E3D4, then dispatches slot 1 at 0x0022E3EB. The parent constructor clears byte +4 and the AsciiString pointer +8; the derived socket array starts at +0xC.
// Table 0x00BD3568 has fourteen slots: 0=0x00148DC3 (deleting destructor calling 0x00148BC2), 1/9=0x00148C41 (init/reset), 2=0x001B5384 (rowed SubsystemInterface::loadIniFilesFromLegend), 3/8/10/12=0x000B3FD0 (ret), 4/11=0x005CB9FF (false, ret 4), 5=0x0047A699 (false, ret), 6=0x000D43D0 (zero, ret), 7/13=0x0047A69C (ret 4). The parent table shares slots 2-8/11-13 and has purecall at 1/9/10. Zero Hour proves init/reset/update names; the other unnamed slots stay neutral in the parent.
// Constructor 0x001491F4..0x001491FC clears 45007 pointers at +0xC; nameToKey 0x00148E57 indexes them. Constructor 0x001491EC clears the dword at +0x2BF48, incremented at 0x00148EB1 and set to one at 0x00148C74. Zero Hour supplies m_sockets and m_nextID names.
// Reverse-index storage is +0x2BF4C..+0x2BF60: member construction 0x001491D5 calls 0x0014918D, destruction 0x00148C23 calls 0x00148B84; insert 0x00148ED9 calls 0x004DA240, lookup 0x00148CC5 calls 0x002888D4. The original container type is not proved; storage stays opaque.
// Mutex storage is +0x2BF60..+0x2BF84: construction 0x001491E7 calls 0x000411C1, destruction 0x00148C14 calls 0x00040FE5. The lock/unlock receiver proves the role; the original member name and concrete type are not proved.
// Out-of-line rows: nameToKey(char const*) 0x00148E1A, nameToKey(AsciiString const&) 0x0009FA65, keyToName 0x00148C95 (reference return in EAX, ret 4, no hidden result), freeSockets 0x00148B42, parseStringAsNameKeyType 0x00148FBE, Rva00148F02 0x00148F02, Rva002D91AF 0x002D91AF. Lifetime bodies and reset are declared out of line.
// nameToLowercaseKey(char const*) has a separate row at 0x00620500 whose legacy accesses use sockets +4 and next ID +0x2BF40. That body does not establish this constructor-owned layout. Its declaration preserves the ledger identity.
#ifndef BFME2_NAMEKEYGENERATOR_H
#define BFME2_NAMEKEYGENERATOR_H

#if defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#error Include NameKeyGenerator.h before the short SubsystemInterface definition.
#endif
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

enum NameKeyType;
class INI;
class Bucket;

class NameKeyGenerator : public SubsystemInterface {
public:
    NameKeyGenerator();
    virtual ~NameKeyGenerator();
    virtual void init();
    virtual void reset();
    virtual void update() {}

    NameKeyType nameToKey(const char *name);
    NameKeyType nameToKey(const AsciiString &name);
    NameKeyType nameToLowercaseKey(const char *name);
    const AsciiString &keyToName(NameKeyType key);
    NameKeyType Rva00148F02(const char *name);
    NameKeyType Rva002D91AF(const AsciiString &name);
    static void parseStringAsNameKeyType(INI *ini, void *instance, void *store, const void *userData);

private:
    enum { SOCKET_COUNT = 45007 };
    void freeSockets();
    Bucket *m_sockets[SOCKET_COUNT];
    unsigned int m_nextID;
    unsigned int field2BF4C[5];
    unsigned int field2BF60[9];
};

extern NameKeyGenerator *TheNameKeyGenerator;

#endif
