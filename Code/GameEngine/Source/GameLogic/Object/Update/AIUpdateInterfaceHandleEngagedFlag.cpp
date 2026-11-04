// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /ICode/GameEngine/Source
// Native 0x00265AF9..0x00265C5B, 354 bytes, no EH frame.
// WB 0x00E41540 names AIUpdateInterface::handleEngagedFlag in AIUpdate.cpp.
// The 19-word condition-mask constructor and overlap test are existing
// verified providers. The three-bit static mask is lazily initialized at
// retail VA 0x00DFEAF0; the constructor cannot throw on this native path.
// Kind 37 and template +0x508/+0x55C retain their observed values and roles.

#include "Common/GameLogicObjectLookupView.h"

class Rva00265254 {
public:
    Rva00265254(unsigned, unsigned, unsigned, unsigned) throw();
    unsigned bits[19];
};

class Rva00263546 {
public:
    bool rva00263546(const Rva00263546 *) const;
    __forceinline bool engaged() const { return ((bits[4] >> 29) & 1) != 0; }
    unsigned bits[19];
};

enum KindOfType { KIND_37 = 37 };
class AIUpdateInterface;

struct EngagedTemplate {
    char before[0x508];
    float distance;
    char toDuration[0x55C - 0x50C];
    unsigned duration;
};

class Object {
public:
    void *vtable;
    EngagedTemplate *type;
    char toFlags[0x10C - 8];
    unsigned flags[19];
    char toAI[0x258 - 0x158];
    AIUpdateInterface *ai;

    bool isKindOf(KindOfType) const;
    Object *rva002931F5(bool);
    void rva0028AE6D();
};

extern GameLogic *TheGameLogic;

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

int AIUpdateInterface::handleEngagedFlag()
{
    Object *obj = m_object;
    if (!obj)
        return 1;

    int sleep = 0x3FFFFFFF;
    static Rva00265254 activeMask(0, 123, 124, 125);
    Rva00263546 *mask = reinterpret_cast<Rva00263546 *>(obj->flags);
    const Rva00263546 *active = reinterpret_cast<const Rva00263546 *>(&activeMask);
    if (mask->engaged()) {
        bool disengage = false;
        if (!active->rva00263546(mask)) {
            bool beyondThreshold = false;
            if (obj->isKindOf(KIND_37)) {
                float distance = obj->type->distance;
                if (getLocomotorDistanceToGoal() > distance)
                    beyondThreshold = true;
            }
            if (!beyondThreshold) {
                Object *holder = obj->rva002931F5(false);
                if (holder && holder->isKindOf(KIND_37) && holder->ai) {
                    float distance = holder->type->distance;
                    if (holder->ai->getLocomotorDistanceToGoal() > distance)
                        beyondThreshold = true;
                }
            }
            if (!beyondThreshold)
                disengage = true;
        }
        unsigned duration = obj->type->duration;
        unsigned interval = (duration >> 1) + 1;
        if (disengage) {
            unsigned now = TheGameLogic->getFrame();
            if (m_field234 <= now) {
                if (obj->flags[4] & 0x20000000) {
                    reinterpret_cast<unsigned char *>(mask)[19] &= 0xDF;
                    obj->rva0028AE6D();
                }
            } else {
                unsigned left = m_field234 - now;
                sleep = left > interval ? interval : left;
            }
        } else {
            m_field234 = TheGameLogic->getFrame() + duration;
            sleep = interval;
        }
    } else if (active->rva00263546(mask)) {
        if (!(obj->flags[4] & 0x20000000)) {
            mask->bits[4] |= 0x20000000;
            obj->rva0028AE6D();
        }
    }
    return sleep;
}
