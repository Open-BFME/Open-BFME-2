// Target facts: Drawable's rowed constructor RVA 0x002797BD calls Thing's constructor at 0x002797D5 (callee 0x0030A188); Snapshot's base table VA 0x00BBB554 is installed at +0x60 by 0x002797DF. Stores at 0x00279841/+0 and 0x00279847/+0x60 install VA 0x00BFB0B4/0x00BFB0A4; destructor RVA 0x002793F0 restores that same pair at 0x00279405/0x0027940B. These are the complete-object and secondary-base tables, not competing class layouts.
// The primary table VA 0x00BFB0B4 has Thing's eight slots (Thing table VA 0x00C086E0), then seven Drawable slots: RVAs 0x0027299A, 0x002729B5, 0x002729CB, 0x002729E9, 0x00272971, 0x00271095, 0x00271C38. Its slot 5 is reactToTransformChange (0x002742E5), slots 3/4 return this (0x0047A6A9), and slot 7 is deleting destructor 0x00279FFC, which calls 0x002793F0. The secondary table has four slots: 0x0027966F (subtracts 0x60, jumps to 0x00279FFC), LoadPostProcess 0x002717BC, GetSnapshotName 0x00279669, DoXfer 0x0027A219. VA 0x00BFB0F0 starts the non-code string "#emb". The introducing virtuals and Snapshot overrides have ledger rows.
// Allocation RVA 0x0004C770 pushes 0x470, calls operator new at 0x0004C775, and passes the result unchanged to the three-argument constructor at 0x0004C791: sizeof 0x470. Retail setID 0x00271058 and removeFromList 0x0027150A prove ID +0x100 and links +0x104/+0x108; friend_bindToObject 0x00274240 proves object +0xFC; constructor 0x002797BD proves status +0x114, module lists +0x14C and matrix +0x1A0. Constructor MOVSS at 0x002797F9 initializes float +0xB0; deselectDrawable 0x0029F34F tests selected byte +0x43C, setDrawableHidden 0x00271601 accesses byte +0x43D, and setFullyObscuredByShroud 0x00278C29 accesses byte +0x440. Unmodeled spans are neutral storage; carved fields cite their constructor stores and rowed accesses, and take neutral m_NN names unless named below. Zero Hour Drawable.h names getObject, testDrawableStatus, getNextDrawable, getDrawModules, getInstanceMatrix, isSelected and setTintStatus, declares the four-float PhysicsXformInfo, and names the members kept in its declaration order whose rowed BFME 2 uses match Zero Hour's (envelopes, tint status pair, m_locoInfo, stealth look, flash count and color, m_instanceScale, caption string, second-pass opacity, m_hiddenByStealth, m_instanceIsIdentity). The current ledger supplies the other method names and signatures. Existing pins prove getID 0x0055A88B (load +0x100), getDrawModules 0x002B224B (load +0x14C), getScale 0x000788D3 (float +0x200), rva00270234 (caller 0x00239F4A), rva0027974B (callers 0x0029576F/0x00295799), and rva002724FD's byte-parameter overload (caller 0x00496CA8). The destructor and rowed nontrivial bodies are declared out of line.

#pragma once
#ifndef __BFME2_DRAWABLE_H_
#define __BFME2_DRAWABLE_H_

#include "../../Source/Common/Thing/thing.h"
#ifndef __SNAPSHOT_H_
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

namespace _STL { template <class T> class allocator; template <class T, class A> class vector; }
class AsciiString;
class ClientUpdateModule;
struct DamageInfo;
class DisplayString;
class DrawableLocoInfo;
class DrawModule;
class Image;
class Locomotor;
class ModelConditionFlags;
class Module;
class Object;
struct OpaqueRefElement4;
struct RGBColor;
struct Rva0010F149Handle;
class Rva00271826;
struct Rva002D752DNode;
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

// DRAWABLE_FRAMES_PER_FLASH (BfmeClientFramesPerSecond / 2): every unit that includes this
// header builds it at startup (one 16-byte .CRT$XCU copy per unit; target facts in the
// included header, which units that cannot take this whole header include on their own).
#include "DrawableFramesPerFlash.h"

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

	Drawable(const ThingTemplate *thingTemplate, DrawableStatus statusBits, int arg);
	virtual ~Drawable();

	virtual void rva0027299A(int);
	virtual void setDeathDecalPosition(int);
	virtual void rva002729CB(float);
	virtual void rva002729E9(int);
	virtual void createDeathDecal(int, float, int);
	virtual void rva00271095();
	virtual void rva00271C38(int);

	DrawableID getID() const;
	const float getScale() const;

	Object *getObject() { return m_object; }
	const Object *getObject() const { return m_object; }
	bool testDrawableStatus(DrawableStatus bit) const { return (m_status & bit) != 0; }
	Drawable *getNextDrawable() const { return m_nextDrawable; }
	bool isSelected() const { return m_selected != 0; }
	void setTintStatus(unsigned int statusBits) { m_tintStatus |= statusBits; }	// inlined: PoisonedBehavior and ObjectScriptStatus OR bits into +0x118
	DrawModule **getDrawModules() { return (DrawModule **)m_modules[0]; }
	const Matrix3D *getInstanceMatrix() const { return &m_instance; }

	void rva000B3FD0();
	void rva0023998E(int);
	void saturateRGB(RGBColor &, float);
	bool calcPitchRoll(void *, void *, void *, void *, int, int);
	void rva00270234();
	void fadeOut(unsigned int);
	void fadeIn(unsigned int);
	void rva00270FAC(bool);
	void setID(void *);
	void setPosition(const Coord3D *);
	bool handleWeaponFireFX(int, int, int, float, float, float, int);
	void setInstanceMatrix(const Matrix3D *, bool);
	void removeFromList(Drawable **);
	void setDrawableHidden(bool);
	void setSelectable(bool);
	int rva00271745() const;
	static void friend_lockDirtyStuffForIteration();
	static void friend_unlockDirtyStuffForIteration();
	void setAnimationLoopDuration(unsigned int);
	void rva002723C0(int);
	void updateSubObjects();
	void rva00272414(const _STL::vector<AsciiString, _STL::allocator<AsciiString> > *);
	void rva0027248A(int, int);
	void rva002724C4(int);
	void rva002724FD(const AsciiString &, int, int, float, float);
	void rva002724FD(const AsciiString &, unsigned char, int, float, float);
	int rva00272545(int);
	int rva0027257B(int);
	int rva002725B1(int);
	int rva002725E7(int);
	int rva0027261D();
	int rva0027264D();
	bool rva0027267D(int, int, int, int);
	bool rva002726C3(int, int, int, int);
	int rva00272709();
	int rva0027272B();
	int getPristineBonePositions(const char *, int, Coord3D *, Matrix3D *, int, int) const;
	int getCurrentClientBonePositions(const char *, int, Coord3D *, Matrix3D *, int) const;
	bool rva00272835(int, int);
	void rva00272870(int);
	int rva00272895(void *);
	void rva002728C5(float, float);
	void rva0027290C(int);
	void rva0027292F(const Coord3D *, const Coord3D *);
	void rva00272945(int);
	void rva0027295B(void *);
	void rva00272A02(bool);
	void rva00272A38();
	void rva00272A51();
	Object *rva00272AD5();
	void rva00272BAB(int, int);
	void rva00272BE7();
	bool rva00272C1E();
	float rva00272C9E(int);
	void rva00272D03(unsigned int);
	void rva00272D3D(unsigned int);
	void rva00272D77(unsigned int, unsigned int);
	void rva00272DBB(Object *);
	void rva00272DEE();
	void rva00273648(void *);
	void rva0027366A();
	void rva00273686(bool);
	void rva002736A8();
	void setEmoticon(const StringBase<char> &, int);
	void rva00273755();
	void drawAmmo();
	void rva002739D1();
	void rva00273DCF();
	void rva00273F74();
	void rva0027411F(void *, float);
	void rva00274176(bool);
	void setIndicatorColor(int);
	void friend_bindToObject(Object *);
	void changedTeam();
	int rva0027434D(int);
	void stopAmbientSound();
	void setInaudible();
	void rva00274445(float);
	ClientUpdateModule *findClientUpdateModule(NameKeyType);
	bool rva00274C62(AsciiString *);
	void rva00274C88(AsciiString *);
	bool rva00274CB2(AsciiString *);
	Rva002390CB rva00274CD8(const AsciiString &);
	int rva00274D6F();
	bool getProjectileLaunchOffset(WeaponSlotType, int, Matrix3D *, WhichTurretType, Coord3D *, Coord3D *) const;
	void colorFlash(const RGBColor *, unsigned int, unsigned int, unsigned int);
	void colorTint(const RGBColor *);
	void rva002754E3();
	void rva00275545();
	void rva00275598();
	void updateDrawable();
	void rva00275DCE(int, float, float, float);
	void rva002761F3(const int *, const int *);
	const Matrix3D *getTransformMatrix() const;
	const Coord3D *getPosition() const;
	void rva0027656F(int, AsciiString);
	bool rva002765D4(UnicodeString *);
	bool rva00276641(UnicodeString *);
	bool rva002766AE(const int *);
	void rva002766F8(const OpaqueRefElement4 &);
	Rva002390CB rva0027675F(int);
	bool rva00276805(int);
	Rva002390CB rva0027682F();
	Rva002390CB rva00276848();
	Rva002390CB rva00276861();
	Rva002390CB rva0027687A();
	Rva002390CB rva00276893();
	void rva00276B95();
	void rva00276BA9(bool);
	Rva002390CB rva0027756D(int);
	void rva002775C9(Coord3D *);
	void rva00277669();
	void rva002778E1();
	void drawVeterancy(bool, int);
	void setCaptionText(const UnicodeString &);
	Rva0036CA00Str rva00278190();
	void rva002781DA(Rva0010F149Handle);
	Rva0036CA00Str rva0027824D(int);
	void rva002784EB();
	void enableAmbientSound(bool);
	void rva002785FB(bool);
	void rva0027862C(bool);
	void setAudible();
	bool rva00278689(const AsciiString &, bool, bool);
	void xferDrawableModules(Xfer *);
	bool rva002788C7(int, int);
	void setFullyObscuredByShroud(bool);
	void rva00278C6B();
	void rva00278C7C(int);
	void drawIconUI();
	void rva002791E7(const ModelConditionFlags &, unsigned int, unsigned int);
	void rva002796B8();
	void rva0027974B();
	void createEmbeddedPortals();
	void rva0027B18C(DamageInfo *);
	void calcPhysicsXformHugeFourLegs(const Locomotor *, PhysicsXformInfo &);
	bool calcPhysicsXform(PhysicsXformInfo &);
	void applyPhysicsXform(Matrix3D *);
	void draw(View *);
	void markTransformChanged(unsigned int);
	Rva002390CB rva0028F8E0();
	Rva002390CB rva0028F8F9();
	Rva002390CB rva0028F912();
	void setInstanceScale(float);
	const TWheelInfo *getWheelInfo() const;
	Rva002390CB rva00346C79();
	Rva002390CB rva00346C92();
	Rva002390CB rva00346CAB();
	Rva002390CB rva00346CC4();
	Rva002390CB rva00374389();
	Rva002390CB rva003743A2();
	Rva002390CB rva00462D95();
	Rva002390CB rva00462DAE();
	Rva002390CB rva00462DC7();
	Rva002390CB rva0049D114();
	Rva002390CB rva004BE120();
	Rva002390CB rva004BE139();
	Rva002390CB rva004BE152();
	Rva002390CB rva004BE16B();
	Rva002390CB rva004BE184();

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
	virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
	virtual void DoXfer(Xfer &xfer);
#else
	virtual void DoXfer(Xfer *xfer);
#endif
#else
	virtual void xfer(Xfer *xfer);
#endif

protected:

	virtual Drawable *asDrawableMeth() { return this; }
	virtual const Drawable *asDrawableMeth() const { return this; }
	virtual void reactToTransformChange(const Matrix3D *, const Coord3D *, float);

	void calcPhysicsXformTreads(const Locomotor *, PhysicsXformInfo &);
	void rva00270B0F(const Locomotor *, PhysicsXformInfo &);
	void rva00272FB6(const Locomotor *, PhysicsXformInfo &);
	void calcPhysicsXformWheels(const Locomotor *, PhysicsXformInfo &);

private:
	void onComingOutOfShroud();

	// Private statics per their decorated data rows: 0x009FEB70, 0x009FEB74, 0x009FEB78, 0x009FEB80, 0x009FEB84.
	static const Image *s_fullAmmo;
	static const Image *s_emptyAmmo;
	static Rva002D752DNode **s_animationTemplates;
	static const Image *s_pipImage;
	static const Image *s_pipOverlay;

public:
	Rva00271826 *m_selectionFlashEnvelope;	// ctor 0x0027984E zeroes; updateDrawable 0x00275C53 updates it after +0x68
	Rva00271826 *m_colorTintEnvelope;	// colorFlash 0x0027543B news Rva00271826, stores at 0x00275444
	unsigned char m_opaque6C[0x8C - 0x6C];
	Rva00271826 *m_8C;	// rva00275598 0x002755CD news Rva00271826, stores at 0x002755D6
	unsigned char m_opaque90[0xB0 - 0x90];
	float field_0b0;
	unsigned char m_opaqueB4[0xE4 - 0xB4];
	bool m_E4;	// ctor 0x002798B2 byte store; updateDrawable 0x00275899 byte test
	unsigned char m_opaqueE5[0xFC - 0xE5];
	Object *m_object;
	DrawableID m_id;
	Drawable *m_nextDrawable;
	Drawable *m_prevDrawable;
	unsigned char m_opaque10C[0x114 - 0x10C];
	DrawableStatus m_status;
	unsigned int m_tintStatus;	// updateDrawable 0x00275A60 compares with +0x11C, 0x00275C28 copies it there
	unsigned int m_prevTintStatus;	// updateDrawable 0x00275A66 / 0x00275C2E
	unsigned int m_120;	// rva00275598 0x002755A7 / 0x002755EB
	unsigned char m_opaque124[0x13C - 0x124];
	DrawableLocoInfo *m_locoInfo;	// calcPhysicsXformTreads 0x00270843 news DrawableLocoInfo, stores at 0x0027084C
	float m_140;	// ctor 0x00279948 MOVSS; rva00270B0F 0x00270B53 / 0x00270B96 MOVSS
	unsigned char m_opaque144[0x14C - 0x144];
	Module **m_modules[3];
	unsigned char m_opaque158[0x164 - 0x158];
	int m_stealthLook;	// rva00275DCE 0x00275DD8 compares, 0x00275E4D stores, then sets +0x358
	int m_flashCount;	// updateDrawable 0x00275A1B tests, 0x00275A57 decrements
	int m_flashColor;	// updateDrawable 0x00275A3A passes it to RGBColor::setFromInt before colorFlash
	Matrix3D m_170;	// ctor 0x0027997C row construction; setInstanceMatrix 0x002711D2 copies into it
	Matrix3D m_instance;
	unsigned char m_opaque1D0[0x200 - 0x1D0];
	float m_instanceScale;	// ctor 0x00279CB7 MOVSS from the template; getScale 0x000788D3 reads it
	int m_204;	// ctor 0x002799A3 and setInstanceMatrix 0x00271411 store -1
	unsigned char m_opaque208[0x344 - 0x208];
	DisplayString *m_captionDisplayString;	// setCaptionText 0x002780AB / 0x002780C0
	unsigned char m_opaque348[0x358 - 0x348];
	float m_secondMaterialPassOpacity;	// ctor 0x00279A3C MOVSS; rva00275DCE 0x00275F18 MOVSS
	unsigned char m_opaque35C[0x360 - 0x35C];
	int m_360;	// ctor 0x00279A4A
	int m_364;	// ctor 0x00279CBF stores the third constructor argument
	unsigned char m_opaque368[0x378 - 0x368];
	int m_378;	// ctor 0x00279A5E stores -1; setInstanceMatrix 0x00271418
	unsigned char m_opaque37C[0x3A4 - 0x37C];
	unsigned int m_3A4;	// ctor 0x00279ABD; getTransformMatrix 0x002762CE compares
	bool m_3A8;	// ctor 0x00279AC3 byte store
	bool m_3A9;	// ctor 0x00279AC9; reactToTransformChange 0x002742F3 stores 1
	unsigned char m_opaque3AA[0x43C - 0x3AA];
	unsigned char m_selected;
	bool field_43d;
	bool m_hiddenByStealth;	// rva00275DCE 0x00275E79 / 0x00275E84 store it per stealth look
	bool m_instanceIsIdentity;	// ctor 0x00279AF2 stores 1; setInstanceMatrix 0x002712CE / 0x00271342
	bool field_440;
	bool m_441;	// updateDrawable 0x002756F5 byte test
	unsigned char m_opaque442[0x447 - 0x442];
	bool m_447;	// ctor 0x00279B1F stores 1
	bool m_448;	// ctor 0x00279B26 stores 1
	bool m_449;	// ctor 0x00279B2D stores 1
	bool m_44A;	// ctor 0x00279B34 stores 1
	unsigned char m_opaque44B[0x44C - 0x44B];
	int m_44C;	// ctor 0x00279B42; rva0027290C 0x00272914
	unsigned char m_opaque450[0x470 - 0x450];
};
typedef char DrawableSizeCheck[sizeof(Drawable) == 0x470 ? 1 : -1];

#endif
