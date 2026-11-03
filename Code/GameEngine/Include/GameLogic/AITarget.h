// Target facts: ctor RVA 0x002C5C1F (rowed as Rva002C589B) and dtor 0x002C589B contain no vptr stores or base calls; AITarget has no virtual functions. The ctor stores its owner argument at +0; the dtor deletes the +0x24 pointee.
// sizeof 0x3C: allocations at 0x0050556D, 0x00505807 and 0x0050587A call that ctor. Its stores at 0x002C5C35..0x002C5C7A prove dwords +0/+4/+8, Coord3D +0x0C, bytes +0x18/+0x19, dwords +0x1C/+0x20/+0x24, float +0x28 and dwords +0x2C/+0x30/+0x34/+0x38; 0x002C5B46 transfers those fields.
// Rowed out-of-line methods: markApproachHazard 0x002C590F, checkThreatInArea 0x002C59CE, rva002C5CF7 0x002C5CF7 and setTarget 0x002C5D8B. Calls at 0x002C597B and 0x002C5D75 identify the +0x24 pointee as ThreatFinder; the +0x0C copy at 0x002C5D0F..0x002C5D14 proves the 12-byte position, and 0x002C5D1B..0x002C5D24 copies GameLogic's frame into +8.
#ifndef BFME2_AITARGET_H
#define BFME2_AITARGET_H

#include "../../../Libraries/Include/Lib/Coord3D.h"

class Object;
class ThreatFinder;

class AITarget
{
public:
    AITarget(int kind, int limit, void *owner);
    ~AITarget();

    void markApproachHazard(const Coord3D *trialPosition);
    float checkThreatInArea(const Coord3D *trialPosition);
    void rva002C5CF7(const Coord3D *position, float radius, int objectId);
    void setTarget(Object *targetObject, float radius);

    void *m_00;
    unsigned int m_04;
    unsigned int m_frame;
    Coord3D m_position;
    bool m_18;
    bool m_19;
    int m_1C;
    int m_20;
    ThreatFinder *m_24;
    float m_28;
    unsigned int m_2C;
    int m_30;
    int m_34;
    unsigned int m_38;
};

#endif
