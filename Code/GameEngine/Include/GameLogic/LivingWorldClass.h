// Target facts (addresses are RVAs): constructor 0x002C0120 calls the registered 0x10-byte Rva00330757Member constructor 0x00330757 at +4 before installing table 0x007FE508 at +0; destructor 0x002BFB2D restores that table at 0x002BFB3F, then Snapshot's 0x007BB554 at 0x002BFBCF. The latter is base teardown, not a second LivingWorld layout. Snapshot is the primary base; the list is declared first, as the construction and reverse destruction order prove.
// Target facts: table 0x007FE508 has 43 code-pointer entries before the next stored table at 0x007FE5B4. Slots 0/1/2/3 are deleting destructor 0x002BFD53, empty 0x000B3FD0, name getter 0x002BE8CE (literal 0x007FE4D4, "LivingWorld (client)"), and transfer 0x002BE833. Nonpure slots 10/16/19/20/27/33/34/35/36/37/38/39 target 0x002BF391/0x002BFBF0/0x002BE7FA/0x0009AA01/0x002C021A/0x004A18C0/0x0009D6E8/0x0009D6ED/0x0009D6F1/0x002886A2/0x0009D6F5/0x002BEFE5; all other slots 4..42 are __purecall 0x0003B810. LivingWorld has virtual functions; slot names without a LivingWorld ledger identity remain neutral.
// Target facts: 0x002C0120 writes dword +14, bytes +18..1B/+24/+25/+78/+94, floats +1C/+20/+54..74/+7C..84, dword +88 and two dwords +8C/+90; it calls 0x002BF807 at +28 and 0x002C00C1 at +98/+AC. The +28 member reaches +54 through 0x002BF807's relative +28 dword; 0x002C00C1 calls 0x002BFD13, whose +4 three-word bucket header and +10 count prove each 0x14-byte hash header. Derived constructor 0x0009D55B starts its members at +C0, bounding sizeof(LivingWorld) to 0xC0. Retail 0x002BE8F9 calls slots 14(two pointers), 19(two words), 22(one pointer) and 40(one word); 0x002BF391 calls slot20(one Boolean). Ledger methods 0x002BFDAE/0x002BE8F9/0x002BF391 and lifetime bodies remain out of line. Opaque member storage uses dword alignment and makes no claim about unrecovered element types.
#pragma once

#ifndef BFME2_GAMELOGIC_LIVINGWORLDCLASS_H
#define BFME2_GAMELOGIC_LIVINGWORLDCLASS_H

#include "../Common/Rva00330757Member.h"
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class LivingWorld : public Rva00330757Member, public Snapshot
{
public:
    LivingWorld();
    virtual ~LivingWorld();

protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const;
#endif
#else
    virtual void crc(Xfer *);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &);
#else
    virtual void DoXfer(Xfer *);
#endif
#else
    virtual void xfer(Xfer *);
#endif

public:
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void rva002BF391(bool active);
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void v14(void *, void *) = 0;
    virtual void slot15() = 0;
    virtual float vslot16();
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void v19(unsigned int, unsigned int);
    virtual void slot20(bool);
    virtual void slot21() = 0;
    virtual void v22(void *) = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual void slot26() = 0;
    virtual void vslot27();
    virtual void slot28() = 0;
    virtual void slot29() = 0;
    virtual void slot30() = 0;
    virtual void slot31() = 0;
    virtual void slot32() = 0;
    virtual void vslot33();
    virtual void vslot34();
    virtual unsigned char vslot35() const;
    virtual unsigned char vslot36() const;
    virtual void vslot37();
    virtual void vslot38();
    virtual void vslot39(const void *, float, float, unsigned int);
    virtual void v40(int) = 0;
    virtual void slot41() = 0;
    virtual void slot42() = 0;

    void *FindClickableObject(void *key);
    void ZoomInTo(void *arg);

    int field14;
    bool m_18;
    bool m_19;
    bool field1A;
    bool field1B;
    float field1C;
    float field20;
    bool field24;
    bool field25;
    unsigned int field28[0x2C / 4];
    float field54;
    float field58;
    float field5C;
    float field60;
    float field64;
    float field68;
    float field6C;
    float field70;
    float field74;
    bool field78;
    float field7C;
    float field80;
    float field84;
    int field88;
    int field8C;
    int field90;
    bool field94;
    unsigned int field98[0x14 / 4];
    unsigned int fieldAC[0x14 / 4];
};

typedef char LivingWorldSizeCheck[sizeof(LivingWorld) == 0xC0 ? 1 : -1];

#endif
