#pragma once
// Drawable: canonical BFME2 header (hand-written; header_adopt_lane's generator
// emits no virtuals, and this class is polymorphic).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
// Named DrawableBFME2.h, like TeamBFME2.h: a GameClient/Drawable.h here would
// shadow the Zero Hour header the remaining Zero Hour-shaped units include.
//
// Target facts, read off game.dat:
//  - The only constructor caller, 0x0004C75F, pushes 0x470 before calling the
//    ctor 0x002797BD: sizeof 0x470 (checked below).
//  - The ctor calls Thing::Thing (0x0030A188), stores Snapshot's table
//    0x00BBB554 at +0x60, then Drawable's tables 0x00BFB0B4 at +0 and
//    0x00BFB0A4 at +0x60. The dtor 0x002793F0 stores the same pair. So
//    Drawable : Thing, Snapshot, with Snapshot at +0x60 and its own data from
//    +0x64.
//  - 0x00BFB0A4 (the Snapshot subobject) has four slots and no RTTI: the -0x60
//    thunk 0x0027966F, LoadPostProcess 0x002717BC, GetSnapshotName() const
//    0x00279669, DoXfer(Xfer *) 0x0027A219.
//  - 0x00BFB0B4 has exactly fifteen slots (the string "#emb" follows slot 14):
//      0-7 are Thing's (thing.h): slots 3 and 4 hold 0x0047A6A9
//        (`mov eax,ecx; ret`), so both asDrawableMeth overloads return this;
//        5 is reactToTransformChange 0x002742E5; 6 keeps Thing's 0x000B3FD0;
//        7 is the scalar deleting destructor 0x00279FFC;
//      8-14 are Drawable's own virtuals, in this order: 0x0027299A,
//        0x002729B5 setDeathDecalPosition, 0x002729CB, 0x002729E9,
//        0x00272971 createDeathDecal, 0x00271095, 0x00271C38. No direct call
//        reaches any of them; the table is their only reference.
//
// Members: every Drawable row of reverse/functions.csv with the access,
// constness and parameter types its decorated name states (Q = public,
// I = protected, A = private, U = public virtual, M = protected virtual),
// minus rva00272414, whose _STL::vector<AsciiString> parameter units spell
// differently, plus the Zero Hour inline accessors the views inline
// (getObject, testDrawableStatus, getNextDrawable, getDrawModules,
// getInstanceMatrix) and the pinned getID.
// Data: m_object (+0xFC), m_id and the drawable-list links (+0x100..+0x108),
// m_status (+0x114), m_locoInfo (+0x13C), the module lists (+0x14C) and the
// instance matrix (+0x1A0) are named where retail bodies or matched units
// read them; the rest stays opaque
// until its member types have shared headers. DrawableConstructor.cpp
// carries the full 0x470 layout. Data access is not modeled (all public); it
// has no codegen effect.
#ifndef CANONICAL_DRAWABLE_BFME2_H
#define CANONICAL_DRAWABLE_BFME2_H

#include "../../Source/Common/Thing/thing.h"
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class AsciiString;
class ClientUpdateModule;
struct DamageInfo;
class DrawModule;
class DrawableLocoInfo;
class Locomotor;
class ModelConditionFlags;
class Module;
class Object;
struct OpaqueRefElement4;
struct RGBColor;
struct Rva0010F149Handle;
class Rva002390CB;
class Rva0036CA00Str;
class ThingTemplate;
struct TWheelInfo;
class UnicodeString;
class View;
class Xfer;
template <typename T> class StringBase;
enum DrawableID;
enum DrawableStatus;
enum NameKeyType;
enum WeaponSlotType;
enum WhichTurretType;

class Drawable : public Thing, public Snapshot
{
public:
	struct PhysicsXformInfo
	{
		float m_totalPitch;
		float m_totalRoll;
		float m_totalYaw;
		float m_totalZ;
	};

	Drawable(const ThingTemplate *thingTemplate, DrawableStatus statusBits, int arg);	// 0x002797BD
	virtual ~Drawable();							// 0x002793F0 (??_G 0x00279FFC, ??_E 0x0027966F)

	// Primary-table slots 8-14, in retail order.
	virtual void rva0027299A(int);					// slot 8, 0x0027299A
	virtual void setDeathDecalPosition(int);		// slot 9, 0x002729B5
	virtual void rva002729CB(float);				// slot 10, 0x002729CB
	virtual void rva002729E9(int);					// slot 11, 0x002729E9
	virtual void createDeathDecal(int, float, int);	// slot 12, 0x00272971
	virtual void rva00271095();						// slot 13, 0x00271095
	virtual void rva00271C38(int);					// slot 14, 0x00271C38

	DrawableID getID() const;						// 0x0055A88B (reverse/symbols.csv pin)

	// Zero Hour inline accessors.
	Object *getObject() const { return m_object; }
	bool testDrawableStatus(DrawableStatus bit) const { return (m_status & bit) != 0; }
	Drawable *getNextDrawable() const { return m_nextDrawable; }
	DrawModule **getDrawModules() { return (DrawModule **)m_modules[0]; }
	const Matrix3D *getInstanceMatrix() const { return &m_instance; }

	void rva000B3FD0();								// 0x000B3FD0
	void rva0023998E(int);							// 0x0023998E
	void saturateRGB(RGBColor &, float);			// 0x002701A8
	bool calcPitchRoll(void *, void *, void *, void *, int, int);	// 0x00270276
	void fadeOut(unsigned int);						// 0x00270756
	void fadeIn(unsigned int);						// 0x002707A8
	void rva00270FAC(bool);							// 0x00270FAC
	void setID(void *);								// 0x00271058
	void setPosition(const Coord3D *);				// 0x002710E7
	bool handleWeaponFireFX(int, int, int, float, float, float, int);	// 0x00271108
	void setInstanceMatrix(const Matrix3D *, bool);	// 0x002711C6
	void removeFromList(Drawable **);				// 0x0027150A
	void setDrawableHidden(bool);					// 0x00271601
	void setSelectable(bool);						// 0x00271700
	int rva00271745() const;						// 0x00271745
	static void friend_lockDirtyStuffForIteration();	// 0x002717EB
	static void friend_unlockDirtyStuffForIteration();	// 0x00271816
	void setAnimationLoopDuration(unsigned int);	// 0x00272393
	void rva002723C0(int);							// 0x002723C0
	void updateSubObjects();						// 0x002723ED
	void rva0027248A(int, int);						// 0x0027248A
	void rva002724C4(int);							// 0x002724C4
	void rva002724FD(const AsciiString &, int, int, float, float);	// 0x002724FD
	int rva00272545(int);							// 0x00272545
	int rva0027257B(int);							// 0x0027257B
	int rva002725B1(int);							// 0x002725B1
	int rva002725E7(int);							// 0x002725E7
	int rva0027261D();								// 0x0027261D
	int rva0027264D();								// 0x0027264D
	bool rva0027267D(int, int, int, int);			// 0x0027267D
	bool rva002726C3(int, int, int, int);			// 0x002726C3
	int rva00272709();								// 0x00272709
	int rva0027272B();								// 0x0027272B
	int getPristineBonePositions(const char *, int, Coord3D *, Matrix3D *, int, int) const;	// 0x0027274D
	int getCurrentClientBonePositions(const char *, int, Coord3D *, Matrix3D *, int) const;	// 0x002727C8
	bool rva00272835(int, int);						// 0x00272835
	void rva00272870(int);							// 0x00272870
	int rva00272895(void *);						// 0x00272895
	void rva002728C5(float, float);					// 0x002728C5
	void rva0027290C(int);							// 0x0027290C
	void rva0027292F(const Coord3D *, const Coord3D *);	// 0x0027292F
	void rva00272945(int);							// 0x00272945
	void rva0027295B(void *);						// 0x0027295B
	void rva00272A02(bool);							// 0x00272A02
	void rva00272A38();								// 0x00272A38
	void rva00272A51();								// 0x00272A51
	Object *rva00272AD5();							// 0x00272AD5
	void rva00272BAB(int, int);						// 0x00272BAB
	void rva00272BE7();								// 0x00272BE7
	bool rva00272C1E();								// 0x00272C1E
	float rva00272C9E(int);							// 0x00272C9E
	void rva00272D03(unsigned int);					// 0x00272D03
	void rva00272D3D(unsigned int);					// 0x00272D3D
	void rva00272D77(unsigned int, unsigned int);	// 0x00272D77
	void rva00272DBB(Object *);						// 0x00272DBB
	void rva00272DEE();								// 0x00272DEE
	void rva00273648(void *);						// 0x00273648
	void rva0027366A();								// 0x0027366A
	void rva00273686(bool);							// 0x00273686
	void rva002736A8();								// 0x002736A8
	void setEmoticon(const StringBase<char> &, int);	// 0x002736BA
	void rva00273755();								// 0x00273755
	void drawAmmo();								// 0x00273808
	void rva002739D1();								// 0x002739D1
	void rva00273DCF();								// 0x00273DCF
	void rva00273F74();								// 0x00273F74
	void rva0027411F(void *, float);				// 0x0027411F
	void rva00274176(bool);							// 0x00274176
	void setIndicatorColor(int);					// 0x002741DE
	void friend_bindToObject(Object *);				// 0x00274240
	void changedTeam();								// 0x002742AC
	int rva0027434D(int);							// 0x0027434D
	void stopAmbientSound();						// 0x002743D7
	void setInaudible();							// 0x00274401
	void rva00274445(float);						// 0x00274445
	ClientUpdateModule *findClientUpdateModule(NameKeyType);	// 0x0027449C
	bool rva00274C62(AsciiString *);				// 0x00274C62
	void rva00274C88(AsciiString *);				// 0x00274C88
	bool rva00274CB2(AsciiString *);				// 0x00274CB2
	Rva002390CB rva00274CD8(const AsciiString &);	// 0x00274CD8
	int rva00274D6F();								// 0x00274D6F
	bool getProjectileLaunchOffset(WeaponSlotType, int, Matrix3D *, WhichTurretType, Coord3D *, Coord3D *) const;	// 0x00275376
	void colorFlash(const RGBColor *, unsigned int, unsigned int, unsigned int);	// 0x0027541E
	void colorTint(const RGBColor *);				// 0x00275490
	void rva002754E3();								// 0x002754E3
	void rva00275545();								// 0x00275545
	void rva00275598();								// 0x00275598
	void updateDrawable();							// 0x0027566B
	void rva00275DCE(int, float, float, float);		// 0x00275DCE
	void rva002761F3(const int *, const int *);		// 0x002761F3
	const Matrix3D *getTransformMatrix() const;		// 0x0027628E
	const Coord3D *getPosition() const;				// 0x002763E6
	void rva0027656F(int, AsciiString);				// 0x0027656F
	bool rva002765D4(UnicodeString *);				// 0x002765D4
	bool rva00276641(UnicodeString *);				// 0x00276641
	bool rva002766AE(const int *);					// 0x002766AE
	void rva002766F8(const OpaqueRefElement4 &);	// 0x002766F8
	Rva002390CB rva0027675F(int);					// 0x0027675F
	bool rva00276805(int);							// 0x00276805
	Rva002390CB rva0027682F();						// 0x0027682F
	Rva002390CB rva00276848();						// 0x00276848
	Rva002390CB rva00276861();						// 0x00276861
	Rva002390CB rva0027687A();						// 0x0027687A
	Rva002390CB rva00276893();						// 0x00276893
	void rva00276B95();								// 0x00276B95
	void rva00276BA9(bool);							// 0x00276BA9
	Rva002390CB rva0027756D(int);					// 0x0027756D
	void rva002775C9(Coord3D *);					// 0x002775C9
	void rva00277669();								// 0x00277669
	void rva002778E1();								// 0x002778E1
	void drawVeterancy(bool, int);					// 0x00277DB4
	void setCaptionText(const UnicodeString &);		// 0x00278064
	Rva0036CA00Str rva00278190();					// 0x00278190
	void rva002781DA(Rva0010F149Handle);			// 0x002781DA
	Rva0036CA00Str rva0027824D(int);				// 0x0027824D
	void rva002784EB();								// 0x002784EB
	void enableAmbientSound(bool);					// 0x002785D6
	void rva002785FB(bool);							// 0x002785FB
	void rva0027862C(bool);							// 0x0027862C
	void setAudible();								// 0x00278644
	bool rva00278689(const AsciiString &, bool, bool);	// 0x00278689
	void xferDrawableModules(Xfer *);				// 0x002786D9
	bool rva002788C7(int, int);						// 0x002788C7
	void setFullyObscuredByShroud(bool);			// 0x00278C29
	void rva00278C6B();								// 0x00278C6B
	void rva00278C7C(int);							// 0x00278C7C
	void drawIconUI();								// 0x00278DFE
	void rva002791E7(const ModelConditionFlags &, unsigned int, unsigned int);	// 0x002791E7
	void rva002796B8();								// 0x002796B8
	void createEmbeddedPortals();					// 0x0027A018
	void rva0027B18C(DamageInfo *);					// 0x0027B18C
	void calcPhysicsXformHugeFourLegs(const Locomotor *, PhysicsXformInfo &);	// 0x0027B47F
	bool calcPhysicsXform(PhysicsXformInfo &);		// 0x0027BA95
	void applyPhysicsXform(Matrix3D *);				// 0x0027BB65
	void draw(View *);								// 0x0027C157
	void markTransformChanged(unsigned int);		// 0x0028A7EC
	Rva002390CB rva0028F8E0();						// 0x0028F8E0
	Rva002390CB rva0028F8F9();						// 0x0028F8F9
	Rva002390CB rva0028F912();						// 0x0028F912
	void setInstanceScale(float);					// 0x002C8F2E
	const TWheelInfo *getWheelInfo() const;			// 0x00318B83
	Rva002390CB rva00346C79();						// 0x00346C79
	Rva002390CB rva00346C92();						// 0x00346C92
	Rva002390CB rva00346CAB();						// 0x00346CAB
	Rva002390CB rva00346CC4();						// 0x00346CC4
	Rva002390CB rva00374389();						// 0x00374389
	Rva002390CB rva003743A2();						// 0x003743A2
	Rva002390CB rva00462D95();						// 0x00462D95
	Rva002390CB rva00462DAE();						// 0x00462DAE
	Rva002390CB rva00462DC7();						// 0x00462DC7
	Rva002390CB rva0049D114();						// 0x0049D114
	Rva002390CB rva004BE120();						// 0x004BE120
	Rva002390CB rva004BE139();						// 0x004BE139
	Rva002390CB rva004BE152();						// 0x004BE152
	Rva002390CB rva004BE16B();						// 0x004BE16B
	Rva002390CB rva004BE184();						// 0x004BE184

	// Snapshot slots, spelled the way the unit selected Snapshot.h's; Drawable's
	// rows are LoadPostProcess, GetSnapshotName() const and DoXfer(Xfer *), all
	// public (U).
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess();					// 0x002717BC
#else
	virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName();
#else
	virtual const char *GetSnapshotName() const;	// 0x00279669
#endif
#else
	virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
	virtual void DoXfer(Xfer &xfer);
#else
	virtual void DoXfer(Xfer *xfer);				// 0x0027A219
#endif
#else
	virtual void xfer(Xfer *xfer);
#endif

protected:
	// Thing slots 3 and 4 (0x0047A6A9) and 5.
	virtual Drawable *asDrawableMeth() { return this; }
	virtual const Drawable *asDrawableMeth() const { return this; }
	virtual void reactToTransformChange(const Matrix3D *, const Coord3D *, float);	// 0x002742E5

	void calcPhysicsXformTreads(const Locomotor *, PhysicsXformInfo &);	// 0x00270817
	void rva00270B0F(const Locomotor *, PhysicsXformInfo &);	// 0x00270B0F
	void rva00272FB6(const Locomotor *, PhysicsXformInfo &);	// 0x00272FB6
	void calcPhysicsXformWheels(const Locomotor *, PhysicsXformInfo &);	// 0x00276CFB

private:
	void onComingOutOfShroud();						// 0x0027893E

public:
	unsigned char m_opaque64[0xFC - 0x64];			// +0x64 (tint color +0x6C)
	Object *m_object;								// +0xFC
	DrawableID m_id;								// +0x100 (getID 0x0055A88B)
	Drawable *m_nextDrawable;						// +0x104 (removeFromList 0x0027150A)
	Drawable *m_prevDrawable;						// +0x108
	unsigned char m_opaque10C[0x114 - 0x10C];		// +0x10C two release handles
	DrawableStatus m_status;						// +0x114 (the ctor's statusBits)
	unsigned char m_opaque118[0x13C - 0x118];		// +0x118
	DrawableLocoInfo *m_locoInfo;					// +0x13C (allocated by the calcPhysicsXform* bodies)
	unsigned char m_opaque140[0x14C - 0x140];		// +0x140
	Module **m_modules[3];							// +0x14C draw, client-update and third module lists
	unsigned char m_opaque158[0x1A0 - 0x158];		// +0x158 (module-interface vector, previous instance +0x170)
	Matrix3D m_instance;							// +0x1A0
	unsigned char m_opaque1D0[0x470 - 0x1D0];		// +0x1D0 (instance scale +0x200 ... indicator color +0x454)
};													// sizeof 0x470
typedef char CanonicalDrawableSizeCheck[sizeof(Drawable) == 0x470 ? 1 : -1];

#endif // CANONICAL_DRAWABLE_BFME2_H
