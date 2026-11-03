// Target facts: EmotionSystem is polymorphic, with SubsystemInterface at +0: ctor RVA 0x00426402 calls 0x001B4E63 and stores table VA 0x00C3C350 at 0x00426415; destructor RVA 0x0042643D (rowed as Rva0042643D) restores that same table at 0x00426450 and calls 0x001B4E74. GameEngine::init pushes sizeof 0x30 at 0x0022EF80, allocates at 0x0022EF82 and calls this ctor at 0x0022EF95.
// Target facts: table RVA 0x0083C350 has 14 slots (targets, as RVAs): 0 0x00426556 (deleting dtor calling 0x0042643D), 1/9 0x00426572 (init/reset clear +0x24), 2 0x001B5384 (inherited loadIniFilesFromLegend), 3/8/10/12 0x000B3FD0, 4 0x004263CA, 5 0x00426378, 6 0x000D43D0, 7/13 0x0047A69C, 11 0x005CB9FF. The next word at 0x0083C388 is string data. SubsystemInterface's table RVA 0x007D77A0 supplies the same slot signatures; only 0, 1, 4, 5, 9 and 10 differ here.
// Target facts: ctor calls vector-base ctor 0x00211E58 at +0x0C/+0x18/+0x24 (0x0042641B/27/33). Dtor 0x00426456..A2 walks the first two ranges in 4-byte steps and destroys their pointees via 0x004DC9ED; 0x004264A4..D9 frees the three buffers. findNugget 0x004264F4 reads the +0x0C/+0x10 pointer range and calls the rowed name accessor 0x002E4336; AddEmotionNuggetTemplate 0x00426580 appends its pointer argument there. RegisterScaryObject 0x004265D9 compares ObjectID at Object+0x74 against the +0x24/+0x28 range and appends through 0x002E01C6. createEmotion 0x0042632F allocates a separate 0x34-byte Emotion and calls 0x004DD206. Vector storage is opaque because these bytes do not identify the C++ template arguments; payload and method spellings retain the ledger ABI names.
#ifndef CANONICAL_EMOTIONSYSTEM_H
#define CANONICAL_EMOTIONSYSTEM_H

#ifndef BFME_SUBSYSTEM_SLOTS
#ifdef CANONICAL_SUBSYSTEMINTERFACE_H
#error EmotionSystem requires the fourteen-slot SubsystemInterface.
#endif
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class BfmeEmotionName;
class Emotion;
class EmotionNugget;
class EmotionTrackerUpdateEntry;
class MultiplayerColorDefinition;
class Object;

class EmotionSystem : public SubsystemInterface
{
public:
    EmotionSystem();
    virtual ~EmotionSystem();
    virtual void init();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual void reset();
    virtual void update();

    Emotion *createEmotion(EmotionTrackerUpdateEntry *entry, Object *object);
    EmotionNugget *findNugget(const BfmeEmotionName &name);
    void AddEmotionNuggetTemplate(MultiplayerColorDefinition *def);
    void rva00426572();
    void RegisterScaryObject(Object *object);

    unsigned char m_vector0C[0x0C];
    unsigned char m_vector18[0x0C];
    unsigned char m_vector24[0x0C];
};

#endif
