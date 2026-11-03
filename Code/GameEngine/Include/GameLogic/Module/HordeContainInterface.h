// Target facts (code addresses are RVAs; table addresses are VAs):
// HordeContain's constructor 0x0046F543 calls TransportContain at 0x0046F55B,
// stores the interface table 0x00C448B8 at +0x11C at 0x0046F560, then replaces
// it with 0x00C44C58 at 0x0046F5BD. Its destructor 0x0046F901 restores the
// latter at 0x0046F95A. These are the abstract base and derived implementation
// tables of the same subobject. Both have 155 slots. The base table has 152
// __purecall entries (0x0003B810); slot 76 is 0x0050B238 (ret 8), slot 112
// is 0x005CB9FA (mov al,1; ret 4), and slot 136 is 0x0047A699 (xor al,al;
// ret). Slot 76's two word parameters represent its opaque eight-byte argument
// area. Slot 112's float argument is passed by retail at 0x001E7BE3.
// The last base slot is at 0x00C44B20; 0x00C44B24 is data, and 0x00C44EC4
// is zero. The three default bodies below preserve those base-table entries.
// Slot 0 is 0x00472329, not a deleting destructor. This interface has virtual
// functions, no virtual destructor, and no evidenced parent or data members.
// The constructor's byte stores at +0x120/+0x121 (0x0046F5C7/0x0046F5CD)
// bound sizeof(HordeContainInterface) to four bytes, with its vptr at +0.
// The complete HordeContain allocation is 0x30C
// (0x0024B8FB), not the size of this interface.
// In 0x00C44C58, slots 0/1/4/11/13/14/16/26/77/84/103/147/154 are the
// ledger's 0x00472329/0x00471FFA/0x00472790/0x00470D09/0x004704E4/
// 0x00470717/0x00474BDA/0x00472D43/0x0046A5EF/0x0047306E/0x004756C9/
// 0x00473D55/0x0046A0B2. Other slots retain neutral names.
// Slot 7 (0x00474B51) fills a 12-byte result and angle; slot 9 (0x0046D1AC)
// returns AsciiString. Slots 17/30 (0x0046FE99/0x00473799) take Object lists;
// slots 32/33 (0x00472B54/0x00472C8E) implement the enter/exit orders used by
// 0x00264775/0x0026488B. Slot 66 (0x0046F7FF) forwards the supplied result
// buffer to 0x0046247D and returns it; 0x003C6507 uses that eight-byte result
// through the registered Rva0036AE51ListView. Slot 67 (0x0046D1F7) fills an
// Object-pointer list, not an ObjectID list. Slot 96 (0x0046D3FC) counts members
// through Rva2225E0Filter, and slot 146 (0x00468C7B) fills a rally position.
// At 0x00344FF2/0x0034503A/0x0034504A/0x00345069 the melee-state caller
// uses slots 85/89/90/77. At 0x003461F3/0x00346205 the combine-state caller
// uses slots 68/29. These call sites establish the consumer method spellings;
// beginMelee forwards to the ledger-named startMeleeAttack in the same slot.
// HordeAIUpdate::update (0x0049AB10) calls slots 41/38/146/4/55 at
// 0x0049AB57/0x0049AB9A/0x0049AC01/0x0049AC11/0x0049AC4D;
// 0x0049AFB5 also calls slot 4 with true. These calls define the update API.
// Other typed slots follow their C44C58 target rows, including 0x0046970D
// (27), 0x0046E7E3 (46), 0x00473B36 (106), 0x0046FF81 (135), and
// 0x0046EC7C/0x0046DEA1 (137/138). Unidentified slots retain neutral names.

// Implementation target RVAs by slot (table VA 0x00C44C58):
// Slots 000..004: 0x00472329/0x00471FFA/0x00472235/0x0046E253/0x00472790.
// Slots 005..009: 0x004726DD/0x0046BB38/0x00474B51/0x0046F7C9/0x0046D1AC.
// Slots 010..014: 0x0046979B/0x00470D09/0x00469F2F/0x004704E4/0x00470717.
// Slots 015..019: 0x000B3FD0/0x00474BDA/0x0046FE99/0x0046C7A4/0x0046CB2C.
// Slots 020..024: 0x0046CC09/0x0046CBCA/0x004696CD/0x0046CDC9/0x004696E5.
// Slots 025..029: 0x0046CCEF/0x00472D43/0x0046970D/0x0046EA94/0x00473212.
// Slots 030..034: 0x00473799/0x00472A24/0x00472B54/0x00472C8E/0x00468D11.
// Slots 035..039: 0x00468D2C/0x0046BB6F/0x0046A2A7/0x0046BEAC/0x0046C65C.
// Slots 040..044: 0x0046C71E/0x0046C6E7/0x0046B925/0x0046B9DC/0x0046B95E.
// Slots 045..049: 0x00468CA3/0x0046E7E3/0x00474142/0x004707DB/0x004739B4.
// Slots 050..054: 0x0046BC30/0x0046BD70/0x0046BE0E/0x0046C3FE/0x0047A69C.
// Slots 055..059: 0x0046C4C0/0x0046C327/0x0046C20B/0x0046C5D7/0x0046F8A5.
// Slots 060..064: 0x0046F8F4/0x0046A5E6/0x0046AAB8/0x004738B6/0x0046F7EB.
// Slots 065..069: 0x0046F7F8/0x0046F7FF/0x0046D1F7/0x0046D27A/0x0046D2C3.
// Slots 070..074: 0x0046D372/0x00381D34/0x0046F815/0x0046F822/0x0046F8B2.
// Slots 075..079: 0x0046F82A/0x0050B238/0x0046A5EF/0x00468FDC/0x00473ADF.
// Slots 080..084: 0x0046A381/0x0046A46F/0x0046A2EC/0x0046A416/0x0047306E.
// Slots 085..089: 0x00468DCD/0x004730B0/0x0046A4C8/0x0046CE9D/0x00468D7D.
// Slots 090..094: 0x003BA648/0x005BF27A/0x0046D384/0x0046F7D7/0x0046F7E4.
// Slots 095..099: 0x004697CD/0x0046D3FC/0x00468F68/0x00468F7E/0x004708BC.
// Slots 100..104: 0x0046D4BD/0x00468F9F/0x0046F831/0x004756C9/0x0046F84C.
// Slots 105..109: 0x0046F859/0x00473B36/0x0046D8AE/0x0046D7AF/0x0046A78F.
// Slots 110..114: 0x0046A712/0x0046ECDE/0x005CB9FA/0x0046D80B/0x0046A6C1.
// Slots 115..119: 0x0046A677/0x003860FA/0x0046DDC5/0x0046DB6D/0x0046DC92.
// Slots 120..124: 0x00475EA2/0x0046981C/0x00469851/0x0046DE2D/0x0046DA6B.
// Slots 125..129: 0x0046992C/0x00475F61/0x004698BC/0x004698D6/0x004698E2.
// Slots 130..134: 0x00469967/0x00469075/0x004690A9/0x004690C8/0x0046F83E.
// Slots 135..139: 0x0046FF81/0x0046F8CD/0x0046EC7C/0x0046DEA1/0x0046DF9A.
// Slots 140..144: 0x0046E113/0x004690D0/0x00468C37/0x00468BDC/0x00468B5B.
// Slots 145..149: 0x00468C60/0x00468C7B/0x00473D55/0x0046E2BC/0x0046F845.
// Slots 150..154: 0x0046F8DA/0x0046F8E7/0x004692BA/0x0046B850/0x0046A0B2.

#pragma once
#ifndef __BFME2_HORDECONTAININTERFACE_H_
#define __BFME2_HORDECONTAININTERFACE_H_

namespace _STL {
    template <class T> class allocator;
    template <class T, class Alloc> class list;
    template <class T, class Alloc> class vector;
}

class AsciiString;
class Object;
class ThingTemplate;
class Rva2225E0Filter;
class Rva0036AE51ListView;
class Player;
class Team;
class Matrix3D;
class UpgradeTemplate;
class FXList;
class Rva002390CB;
class Rva004692BAFactory;
struct QuarrelPacket;
struct Rva00469851Names;
struct Rva00468CA3Arg;
struct Coord3D;
enum CommandSourceType;
enum PathfindLayerEnum;
enum ObjectID;

class HordeContainInterface
{
public:
    virtual void rva00472329(const Coord3D *, int) = 0;
    virtual void attackTargetNow(Object *, int) = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void returnToFormation(bool) = 0;
    virtual void slot5(Object *) = 0;
    virtual bool slot06(Object *) = 0;
    virtual Coord3D slot7(Object *, float *) = 0;
    virtual void slot8(Object *) = 0;
    virtual AsciiString slot09() = 0;
    virtual int slot10() = 0;
    virtual void assignSpotToUnit(Object *) = 0;
    virtual void slot12(Object *) = 0;
    virtual void notifyOfMemberDeath(Object *) = 0;
    virtual void removeMemberFromHorde(Object *) = 0;
    virtual void slot15() = 0;
    virtual void performReform() = 0;
    virtual void slot17(_STL::list<Object *, _STL::allocator<Object *> > &) = 0;
    virtual void slot18() = 0;
    virtual Object *slot19() = 0;
    virtual Object *slot20() = 0;
    virtual Object *slot21() = 0;
    virtual void *slot22() = 0;
    virtual bool slot23() = 0;
    virtual void slot24() = 0;
    virtual bool slot25(const ThingTemplate *) = 0;
    virtual void changeToFormation(const ThingTemplate *) = 0;
    virtual bool slot27(Object *, int, const Rva00469851Names *, bool) = 0;
    virtual bool slot28(Object *) = 0;
    virtual Object *slot29(Object *, const Object *, bool) = 0;
    virtual void slot30(const _STL::list<Object *, _STL::allocator<Object *> > &) = 0;
    virtual void slot31(const Coord3D *, CommandSourceType, int) = 0;
    virtual void enterObject(Object *, CommandSourceType) = 0;
    virtual void exitObject(Object *, CommandSourceType) = 0;
    virtual bool slot34() = 0;
    virtual bool slot35() = 0;
    virtual bool slot36(int *, unsigned int) = 0;
    virtual bool slot37() = 0;
    virtual void notifyMember(Object *) = 0;
    virtual bool slot39() = 0;
    virtual bool slot40() = 0;
    virtual bool isReady() = 0;
    virtual void slot42(const Object *) = 0;
    virtual bool slot43(int) = 0;
    virtual bool slot44(int) = 0;
    virtual void slot45(const Rva00468CA3Arg *) = 0;
    virtual void slot46(const UpgradeTemplate *, bool) = 0;
    virtual void slot47() = 0;
    virtual void slot48(Object *, float) = 0;
    virtual void slot49() = 0;
    virtual void slot50() = 0;
    virtual void slot51() = 0;
    virtual void slot52() = 0;
    virtual void slot53(Player *) = 0;
    virtual void slot54() = 0;
    virtual void update() = 0;
    virtual void slot56() = 0;
    virtual void slot57() = 0;
    virtual bool slot58(int) = 0;
    virtual bool slot59() = 0;
    virtual bool slot60() = 0;
    virtual void slot61() = 0;
    virtual bool slot62() = 0;
    virtual void slot63(Object *) = 0;
    virtual void slot64(int) = 0;
    virtual unsigned int slot65() const = 0;
    virtual Rva0036AE51ListView getMemberList() = 0;
    virtual void slot67(_STL::list<const Object *, _STL::allocator<const Object *> > &) = 0;
    virtual Object *getCombineTarget() = 0;
    virtual Object *slot69(int) = 0;
    virtual Object *slot70() = 0;
    virtual int slot71() = 0;
    virtual void slot72(int) = 0;
    virtual void slot73() = 0;
    virtual void slot74() = 0;
    virtual unsigned char slot75() = 0;
    virtual void slot76(unsigned int, unsigned int) {}
    virtual void startMeleeAttack(Object *) = 0;
    virtual void slot78() = 0;
    virtual void slot79() = 0;
    virtual bool slot80(Object *) = 0;
    virtual bool slot81() = 0;
    virtual bool slot82(Object *) = 0;
    virtual bool slot83() = 0;
    virtual bool canEngageInMelee(Object *, int) = 0;
    virtual bool isMeleeTargetReady(Object *) = 0;
    virtual void slot86(Object *) = 0;
    virtual bool slot87() = 0;
    virtual bool slot88(Object *) = 0;
    virtual void prepareMeleeTarget(Object *) = 0;
    virtual void setMeleeFormation(unsigned int) = 0;
    virtual int slot91() = 0;
    virtual void slot92(Team *) = 0;
    virtual void slot93(int) = 0;
    virtual void *slot94() = 0;
    virtual int slot95() = 0;
    virtual int getMemberCount(Rva2225E0Filter *) = 0;
    virtual int slot97() = 0;
    virtual int slot98() = 0;
    virtual Object *slot99(const Matrix3D *) = 0;
    virtual void slot100() = 0;
    virtual int slot101(Object *) = 0;
    virtual void slot102(int) = 0;
    virtual void backAwaySomeMembersFrom(Object *) = 0;
    virtual void slot104(unsigned char) = 0;
    virtual unsigned char slot105() = 0;
    virtual void instigateQuarrel(int, int, QuarrelPacket, QuarrelPacket) = 0;
    virtual void slot107() = 0;
    virtual void slot108(int) = 0;
    virtual void slot109(const Matrix3D *) = 0;
    virtual void slot110(int) = 0;
    virtual void slot111(const Coord3D *, const Coord3D *, int, PathfindLayerEnum) = 0;
    virtual bool slot112(float) { return true; }
    virtual bool slot113() = 0;
    virtual bool slot114() = 0;
    virtual bool slot115() = 0;
    virtual void slot116() = 0;
    virtual void slot117(int, int) = 0;
    virtual void slot118(const AsciiString &, Rva2225E0Filter *, int) = 0;
    virtual void slot119(const AsciiString &, Rva2225E0Filter *) = 0;
    virtual void slot120() = 0;
    virtual void slot121() = 0;
    virtual void slot122() = 0;
    virtual void slot123(const FXList *) = 0;
    virtual void slot124() = 0;
    virtual bool slot125() = 0;
    virtual void slot126() = 0;
    virtual bool slot127() = 0;
    virtual const void *slot128() = 0;
    virtual const void *slot129() = 0;
    virtual void slot130() = 0;
    virtual void slot131(float) = 0;
    virtual void slot132(const Coord3D *) = 0;
    virtual void slot133() = 0;
    virtual void *slot134() = 0;
    virtual void ClassifyBeforeOnAfterInvalidPortal(_STL::vector<ObjectID, _STL::allocator<ObjectID> > &, _STL::vector<ObjectID, _STL::allocator<ObjectID> > &, _STL::vector<ObjectID, _STL::allocator<ObjectID> > &) = 0;
    virtual bool slot136() { return false; }
    virtual Rva002390CB slot137(Object *) = 0;
    virtual ObjectID slot138(ObjectID) = 0;
    virtual bool slot139(Coord3D *) = 0;
    virtual bool slot140(Coord3D *) = 0;
    virtual void slot141(int) = 0;
    virtual bool slot142() = 0;
    virtual void slot143(int) = 0;
    virtual float slot144(float) = 0;
    virtual void slot145(const Coord3D *) = 0;
    virtual bool getRallyPosition(Coord3D *) = 0;
    virtual bool isFlankedBy(Object *) = 0;
    virtual void slot148() = 0;
    virtual unsigned char slot149() = 0;
    virtual float slot150() = 0;
    virtual float slot151() = 0;
    virtual void slot152(Rva004692BAFactory *) = 0;
    virtual float slot153() = 0;
    virtual void endMove() = 0;

    void beginMelee(Object *object) { startMeleeAttack(object); }
    void refreshFormation(bool value) { returnToFormation(value); }
    Object *combine(Object *object, const void *target, bool flag)
    {
        return slot29(object, static_cast<const Object *>(target), flag);
    }
};

#endif
