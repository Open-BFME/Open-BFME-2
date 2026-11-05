// Target facts: constructor 0x003B333A..0x003B3371 writes type +0, initialized byte +4, int +8, real +0xC, string +0x10, coordinates +0x14/+0x18/+0x1C, and zero words +0x20/+0x24. It makes no calls and stores no vptr: Parameter has no retail virtual functions or polymorphic base.
// ReadParameter allocates 0x28 bytes at 0x003B5CB0 and calls that constructor at 0x003B5CD3. Destruction at 0x003B6F60..0x003B6F6E releases the string at +0x10 and frees the object directly, without virtual dispatch; no Parameter destructor row exists. getCoord3D 0x003B27BB and setCoord3D 0x003B27E2 compare type 0x10 and copy +0x14..+0x1F. WriteParameter 0x003B3A38 and getUiText 0x003B4B1D confirm the scalar/string offsets and the named type cases below.
// Names: Zero Hour GeneralsMD GameLogic/Scripts.h supplies the common field/accessor names. Retail 0x00357BA0 loads +0x20 for getPlayerFromMask (call 0x00357BB1), and 0x00357BFE caches the resolved mask there. Retail 0x003588EE loads +0x24 for findObjectByID (call 0x003588FF). Rowed getStatus 0x00579696 reads +0x24/+0x28, contradicting this allocation; its declaration preserves the ledger ABI without claiming a status-mask member. Its BitFlags extent follows Common/Thing/thing.h and the rowed provider's int declaration unless the complete BitFlags header is present. AsciiString must be complete before including this header.
#ifndef CANONICAL_SCRIPTPARAMETER_H
#define CANONICAL_SCRIPTPARAMETER_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
struct Coord3D;
class DataChunkInput;
class DataChunkOutput;
#ifndef __BitFlags_H_
template <int NUMBITS> class BitFlags;
#endif

#include "../../../Libraries/Include/Lib/Coord3D.h"

class Parameter
{
public:
    enum ParameterType
    {
        INT = 0,
        REAL = 1,
        SCRIPT = 2,
        TEAM = 3,
        COUNTER = 4,
        FLAG = 5,
        COMPARISON = 6,
        WAYPOINT = 7,
        BOOLEAN = 8,
        TRIGGER_AREA = 9,
        TEXT_STRING = 10,
        SIDE = 11,
        SOUND = 12,
        SCRIPT_SUBROUTINE = 13,
        UNIT = 14,
        OBJECT_TYPE = 15,
        COORD3D = 16,
        ANGLE = 17,
        TEAM_STATE = 18,
        RELATION = 19,
        AI_MOOD = 20,
        DIALOG = 21,
        MUSIC = 22,
        MOVIE = 23,
        WAYPOINT_PATH = 24,
        LOCALIZED_TEXT = 25,
        BRIDGE = 26,
        KIND_OF_PARAM = 27,
        ATTACK_PRIORITY_SET = 28
    };

    enum { LESS_THAN = 0, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER, NOT_EQUAL };

    Parameter(ParameterType type, int value = 0);
    void getCoord3D(Coord3D *position) const;
    AsciiString getUiText() const;
    BitFlags<45> getStatus() const;
    void WriteParameter(DataChunkOutput &output);
    static Parameter *ReadParameter(DataChunkInput &input);

    int getInt() const { return m_int; }
    float getReal() const { return m_real; }
    const AsciiString &getString() const { return m_string; }
    ParameterType getParameterType() const { return m_paramType; }
    int getCachedPlayerMask() const { return m_cachedPlayerMask; }
    void setCachedPlayerMask(int mask) { m_cachedPlayerMask = mask; }
    void friend_setInt(int value) { m_int = value; }
    void friend_setReal(float value) { m_real = value; }
    void friend_setCoord3D(const Coord3D *position) { setCoord3D(position); }

    ParameterType m_paramType;
    bool m_initialized;
    int m_int;
    float m_real;
    AsciiString m_string;
    Coord3D m_coord;
    int m_cachedPlayerMask;
    unsigned int m_objectID;

protected:
    void setInt(int value) { m_int = value; }
    void setReal(float value) { m_real = value; }
    void setCoord3D(const Coord3D *position);
};

#endif
