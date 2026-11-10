// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native 001E520C..001E525A, 78 bytes, RET4; incoming ECX is unused.
// The rowed LocomotorTemplate assignment 001E3955 and constructor 001E4ABE.
// Constructor 001E4ABE..001E4DB0 only initializes fields and cannot throw.
// Allocation size 0x154, override link +4 and flag +8 are target facts.
// LocomotorStore::newOverride: the rowed LocomotorStore::
// parseLocomotorTemplateDefinition 0x001E8A94 calls it on TheLocomotorStore
// with the final override; donor ZH Locomotor.cpp newOverride (allocate,
// copy, link, mark), plus BFME2's g_00E01EA8 bracket around the copy.
class LocomotorTemplate
{
public:
    LocomotorTemplate() throw();
    LocomotorTemplate &operator=(const LocomotorTemplate &rhs);
    void setNextOverride(LocomotorTemplate *next) { m_next = next; }
    void markAsOverride() { m_override = true; }
private:
    void *m_vptr;
    LocomotorTemplate *m_next;
    bool m_override;
    char m_unknown09[0x154 - 9];
};

#include "../../Include/GameLogic/LocomotorStore.h"
extern unsigned char g_00E01EA8;
LocomotorTemplate *LocomotorStore::newOverride(LocomotorTemplate *original)
{
    if (!original)
        return 0;
    LocomotorTemplate *result = new LocomotorTemplate;
    g_00E01EA8 = 1;
    *result = *original;
    g_00E01EA8 = 0;
    original->setNextOverride(result);
    result->markAsOverride();
    return result;
}
