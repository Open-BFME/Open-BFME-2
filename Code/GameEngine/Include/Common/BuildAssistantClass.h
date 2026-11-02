// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x003921FA calls SubsystemInterface's 0x001B4E63 at +0 and installs 0x00C1A088 at 0x00392221. Destructor 0x0039225E installs the same table at 0x00392270, destroys the +0x10 member twice through 0x0039205C, destroys the +0x0C list through 0x004EC395 and calls the base destructor 0x001B4E74. The base constructor/destructor install 0x00BD77A0; that fourteen-slot table belongs to SubsystemInterface, not BuildAssistant.
// Allocation 0x0022ED0D pushes 0x28 before operator new 0x0002FDA0 and the constructor call at 0x0022ED22. Constructor stores prove dwords +0x10/+0x14/+0x18/+0x20/+0x24 and bytes +0x1C/+0x1D; the base owns byte +4 and AsciiString +8. Constructor 0x004EC36C initializes the four-byte list at +0x0C; reset 0x00391F90 traverses its sentinel and pointer-valued nodes. Member storage below is opaque where its complete shared type is unavailable.
// Table 0x00C1A088 contains 27 entries followed at 0x00C1A0F4 by non-code data. Slots 0/1/9/10 are 0x00392DA4 (deleting destructor calling 0x0039225E), 0x003922B7 (this += 0x10; jump 0x00392092), reset 0x00391F90 and update 0x003922BF. The registered base supplies slots 2-8 and 11-13: 2=0x001B5384, 3/8/12=0x000B3FD0, 4/11=0x005CB9FF, 5=0x0047A699, 6=0x000D43D0, 7/13=0x0047A69C. These match the base table's inherited entries.
// Slots 14-21 are 0x003952D8, 0x00392DC0, 0x00394352, 0x00394879, 0x0039361E, 0x00393741, 0x0039380F and 0x0039321C. Slots 22-26 are 0x000D43D0 (zero return), 0x00391A70, 0x00391B08, 0x00392AD7 and 0x003941FD. Ledger rows prove the named declarations and their parameter types; slot 15 points to a nonvirtual QAE row, so its virtual surface remains vslot15 and the rowed rva00392DC0 is declared separately.
// Nonvirtual ledger declarations: iterateFootprint 0x003916AB, rva00391AA1 0x00391AA1, isRemovableForConstruction 0x00391CE3, xferTheSellList 0x003924FE, getPortTransform 0x00392802, clearRemovableForConstruction 0x003940B8 and moveObjectsForConstruction 0x00394FA7. Rowed bodies, including the constructor and virtual destructor, are declared out of line.
// DozerAIUpdate::makePhantomStructureReal (0x0048A15A) pushes option mask 0x15 at 0x0048A1DC and calls slot 16 at 0x0048A1E7. Zero Hour supplies the component names TERRAIN_RESTRICTIONS=1, NO_OBJECT_OVERLAP=4 and SHROUD_REVEALED=0x10.
// Donor facts: Zero Hour Common/BuildAssistant.h supplies the init/reset/update names and the names shared with the ledger. Its buildObjectLineNow, buildTiledLocations and getBuildLocations declarations do not establish BFME2 slot identities. Unknown slots retain neutral names; parameter forward declarations assert no layout.
#pragma once

#ifndef BFME2_COMMON_BUILDASSISTANTCLASS_H
#define BFME2_COMMON_BUILDASSISTANTCLASS_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Object;
class Player;
class Rva0039205C;
class Rva004D9A3C;
class ThingTemplate;
class Xfer;
struct Coord3D;
enum CanMakeType;
enum LegalBuildCode;

class BuildAssistant : public SubsystemInterface
{
public:
    enum LocalLegalToBuildOptions
    {
        TERRAIN_RESTRICTIONS = 0x01,
        NO_OBJECT_OVERLAP = 0x04,
        SHROUD_REVEALED = 0x10
    };

    BuildAssistant();
    virtual ~BuildAssistant();

    virtual void init();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
#endif
    virtual void reset();
    virtual void update();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);
#endif
    virtual Object *buildObjectNow(Object *builder, const ThingTemplate *what, const Coord3D *pos, float angle, Player *player);
    virtual bool vslot15(Object *builder, const ThingTemplate *what, const Coord3D *pos, Player *player, unsigned int kind, Object **result);
    virtual LegalBuildCode isLocationLegalToBuild(const Coord3D *pos, const ThingTemplate *what, float angle, unsigned int options, Object *builder, Player *player);
    virtual bool isLocationClearOfObjects(const Coord3D *pos, const ThingTemplate *what, float angle, Object *builder, unsigned int options, Player *player, bool flag);
    virtual bool rva0039361E(const Coord3D *pos, const ThingTemplate *what, float angle, Object *builder, Player *player);
    virtual void addBibs(const Coord3D *pos, const ThingTemplate *what);
    virtual bool rva0039380F(Rva0039205C *out, Object *builder, const Coord3D *start, const Coord3D *end, unsigned int key);
    virtual bool rva0039321C(Rva0039205C *out, Object *first, Object *second, unsigned int key, bool flag);
    virtual void *vslot22();
    virtual bool rva00391A70(const ThingTemplate *what, const Object *builder);
    virtual CanMakeType canMakeUnit(Object *builder, const ThingTemplate *what, int revivalIndex) const;
    virtual bool isPossibleToMakeUnit(Object *builder, const ThingTemplate *what, int revivalIndex) const;
    virtual void sellObject(Object *obj);

    void iterateFootprint(const ThingTemplate *what, float angle, const Coord3D *pos, float resolution, void (*callback)(const Coord3D *, void *), void *userData);
    bool rva00391AA1(const ThingTemplate *builder, const ThingTemplate *what);
    bool isRemovableForConstruction(Object *obj);
    void xferTheSellList(Xfer *xfer);
    bool getPortTransform(const Coord3D *pos, const ThingTemplate *what, float angle, float *outAngle, Coord3D *outPos);
    bool rva00392DC0(Object *builder, const ThingTemplate *what, const Coord3D *pos, Player *player, unsigned int kind, Object **result);
    void clearRemovableForConstruction(const ThingTemplate *what, const Coord3D *pos, float angle);
    bool moveObjectsForConstruction(const ThingTemplate *what, const Coord3D *pos, float angle, Player *player);

    void *m_field0C;
    unsigned int m_field10;
    unsigned int m_field14;
    Rva004D9A3C *m_field18;
    bool m_field1C;
    bool m_field1D;
    unsigned char m_pad1E[2];
    int m_field20;
    unsigned int m_field24;
};

typedef char BuildAssistantSizeCheck[sizeof(BuildAssistant) == 0x28 ? 1 : -1];
extern BuildAssistant *TheBuildAssistant;

#endif
