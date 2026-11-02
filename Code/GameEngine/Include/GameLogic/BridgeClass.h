// Target facts: Bridge ctors RVA 0x0027F899/0x00280C38 and dtor 0x0027FBBD store VA 0x00BFB1E0 at +0; its sole slot is VA 0x00680C05 (deleting dtor RVA 0x00280C05), followed by non-code 0x7149F2CA. Bridge is polymorphic. Allocations at RVA 0x002802A1/0x00281269 request 0xCC bytes. The ctors place next +4, AsciiString +8, the 0xA8 record +0x0C (calls 0x0027C410/0x0027C36A), bounds +0xB4, layer +0xC4 and outline +0xC8; neither they nor dtor 0x0027FBAC calls a base constructor/destructor or restores a base table.
// Record facts: ctor RVA 0x0027C36A and copy 0x0027C410 access nineteen floats, integers +0x4C/+0x50/+0x54, four IDs +0x58 and byte +0x68; ctor arrays are four 12-byte entries +0x6C and two 6-byte entries +0x9C. Landmark ctor 0x00280C21 writes four corner triples there and six shorts at Bridge+0xA8. Assignment 0x00085420 and copy 0x0027C410 are called out of line. Setters 0x0045653D/0x00456547 store Bridge+0x60/+0x64+4*index; deleteInstance's slot-0 call and free are at 0x0028200C..0x0028201A.
// Method RVAs: createTower 0x0027EDBC, isCellOnEnd 0x0027C79C, isCellOnSide 0x0027C95B, isCellEntryPoint 0x0027CB7F (ret 8), isPointOnBridge 0x0027EEAD, pickBridge 0x0027FBFE (Bool), getBridgeHeight 0x0027FD2A and updateDamageState 0x00281C13. Dtor 0x0027FBAC deletes outline and releases the string. Donor facts: Zero Hour GeneralsMD TerrainLogic.h supplies Bridge's member/accessor names and record names through +0x68; the two added arrays retain neutral names.
#ifndef BFME2_BRIDGECLASS_H
#define BFME2_BRIDGECLASS_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Include/Lib/Region2D.h"

class Dict;
class Object;
class PolygonTrigger;
class ThingTemplate;
class Vector3;
enum ObjectID;
enum BodyDamageType;
enum BridgeTowerType;

class Rva0027C36A
{
public:
    Rva0027C36A();
    Rva0027C36A(const Rva0027C36A &other);
    Rva0027C36A &operator=(const Rva0027C36A &other);

    Coord3D from;
    Coord3D to;
    float bridgeWidth;
    Coord3D fromLeft;
    Coord3D fromRight;
    Coord3D toLeft;
    Coord3D toRight;
    int bridgeIndex;
    BodyDamageType curDamageState;
    ObjectID bridgeObjectID;
    ObjectID towerObjectID[4];
    bool damageStateChanged;
    char m_pad69[3];
    Coord3D m_6c[4];
    short m_9c[6];
};

typedef Rva0027C36A BridgeInfo;

class Bridge
{
public:
    Bridge(Rva0027C36A &info, Dict *properties, const AsciiString &templateName, PolygonTrigger *outline = 0);
    Bridge(Object *object);
    virtual ~Bridge();

    Object *createTower(Coord3D *position, BridgeTowerType tower, const ThingTemplate *towerTemplate, Object *bridge);
    bool isPointOnBridge(const Coord3D *position);
    bool pickBridge(const Vector3 &from, const Vector3 &to, Vector3 *position);
    float getBridgeHeight(const Coord3D *position, Coord3D *normal);
    bool isCellOnEnd(const Region2D *cell);
    bool isCellOnSide(const Region2D *cell);
    bool isCellEntryPoint(const Region2D *cell, float *height);
    void updateDamageState();
    void setBridgeObjectID(ObjectID id);
    void setTowerObjectID(ObjectID id, BridgeTowerType tower);
    __forceinline void deleteInstance() { ::delete this; }

    Bridge *getNext() { return m_next; }
    Bridge *getNext() const { return m_next; }
    void setNext(Bridge *next) { m_next = next; }
    int getLayer() const { return m_layer; }
    void setLayer(int layer) { m_layer = layer; }
    const Region2D *getBounds() const { return &m_bounds; }
    const Rva0027C36A *peekBridgeInfo() const { return &m_bridgeInfo; }
    void getBridgeInfo(Rva0027C36A *info) { *info = m_bridgeInfo; }

    Bridge *m_next;
    AsciiString m_templateName;
    Rva0027C36A m_bridgeInfo;
    Region2D m_bounds;
    int m_layer;
    PolygonTrigger *m_c8;
};

#endif
