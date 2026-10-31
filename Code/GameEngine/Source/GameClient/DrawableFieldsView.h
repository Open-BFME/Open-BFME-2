#pragma once
// Shared views for the Drawable TU: DrawModule's table as Drawable's module walkers
// call it, and the fields DrawableBFME2.h still keeps opaque, at retail's offsets.
#include "../../Include/GameClient/DrawableBFME2.h"

struct ModuleData;

// The object returned by DrawModule slot 0xA8; slots are named by table offset.
class ObjectDrawInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void setSelectable(bool selectable);	// +0x60
	virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90();
	virtual int slot94(int a);
	virtual int slot98(int a);
	virtual int slot9C(int a);
	virtual int slotA0();
	virtual int slotA4();
	virtual bool slotA8(int a, int b, int c, int d);
	virtual bool slotAC(int a, int b, int c, int d);
};

// Table of the draw modules in Drawable's +0x14C list, slots named by table offset. Retail
// dispatches doDrawModule through +0x2C; the donor DrawModule header's table is shorter.
class DrawModule
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10();
	virtual bool slot14(int a, int b);
	virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28();
	virtual void doDrawModule(const Matrix3D *matrix);	// +0x2C
	virtual void slot30(bool flag);
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40(bool b);
	virtual void slot44();
	virtual void slot48(bool b);
	virtual void slot4C();
	virtual void slot50(int x);
	virtual void slot54(float a, float b);
	virtual void slot58();
	virtual void slot5C(int x);
	virtual void slot60(int a);
	virtual void rva0027292F(const Coord3D *position, const Coord3D *normal);	// +0x64
	virtual void slot68(void *arg);
	virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88();
	virtual void setFullyObscuredByShroud(bool fullyObscured);	// +0x8C
	virtual void slot90(); virtual void slot94();
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, float oldAngle);	// +0x98
	virtual void slot9C();
	virtual void slotA0();
	virtual void *slotA4();
	virtual ObjectDrawInterface *getObjectDrawInterface();	// +0xA8
	virtual void slotAC();
	virtual void slotB0(); virtual void slotB4(); virtual void slotB8(); virtual void slotBC();
	virtual void slotC0();
	virtual int slotC4();
	virtual void slotC8();
	virtual int slotCC();
	virtual int slotD0();
	virtual void slotD4(); virtual void slotD8();
	virtual bool slotDC();
	virtual void slotE0(); virtual void slotE4();
	virtual void slotE8(bool arg);
	virtual void slotEC(void *arg);
	virtual bool slotF0();
	virtual void slotF4();
	ModuleData *m_moduleData;
};

class OpaqueRefCounted;
class BuffManager;
class Rva00270025;
struct BfmeDrawableDrawObject;

class Rva00271C8A
{
public:
	void rva00271C8A(const int *a, const int *b);
	int m_bits[19]; // +0x00
};

class Rva000A8C9B
{
public:
	void rva000A8CE5(OpaqueRefCounted*);
	void clear();
	void *m_ptr; // +0x00
};

struct DrawableKeyStamp
{
	int m_key;
	unsigned int m_stamp;
};

// Drawable's members past what DrawableBFME2.h names, read through a cast of this.
struct BfmeDrawableDrawFields
{
	unsigned char pad000[0xA8];
	int m_terrainDecalType;					// +0xA8
	float m_ac;								// +0xAC
	float m_explicitOpacity;				// +0xB0
	float m_opacityB4;						// +0xB4
	unsigned char padB8[0xFC - 0xB8];
	BfmeDrawableDrawObject *object;			// +0xFC
	unsigned char pad100[0x110 - 0x100];
	Rva000A8C9B m_holder110;				// +0x110
	unsigned int m_status;					// +0x114
	unsigned char tintStatus;				// +0x118
	unsigned char pad119[0x128 - 0x119];
	int m_fadeMode;							// +0x128
	int m_timeElapsedFade;					// +0x12C
	int m_timeToFade;						// +0x130
	int m_134;								// +0x134
	unsigned char pad138[0x144 - 0x138];
	unsigned int m_ambientSound144;			// +0x144
	unsigned char pad148[0x14C - 0x148];
	DrawModule **drawModules;				// +0x14C
	unsigned char pad150[0x2A4 - 0x150];
	Rva00271C8A m_pendingClear;				// +0x2A4
	Rva00271C8A m_pendingSet;				// +0x2F0
	unsigned char pad33C[0x354 - 0x33C];
	Rva00270025 *m_iconInfo;				// +0x354
	float secondMaterialPassOpacity;		// +0x358
	unsigned char pad35C[0x37C - 0x35C];
	int m_fadeStartFrame;					// +0x37C
	unsigned char pad380[0x38C - 0x380];
	DrawableKeyStamp m_records[3];			// +0x38C
	unsigned char pad3A4[0x43C - 0x3A4];
	bool m_selected;						// +0x43C
	bool hidden;							// +0x43D
	bool hiddenByStealth;					// +0x43E
	bool m_instanceIsIdentity;				// +0x43F
	bool fullyObscuredByShroud;				// +0x440
	unsigned char pad441[0x448 - 0x441];
	bool m_448;								// +0x448
	bool m_449;								// +0x449
	bool m_44A;								// +0x44A
	bool m_44B;								// +0x44B
	int m_44C;								// +0x44C
	BuffManager *m_buffManager;				// +0x450
};
typedef char BfmeDrawableDrawFieldsChecks[(sizeof(BfmeDrawableDrawFields) == 0x454 && sizeof(Rva00271C8A) == 19 * 4) ? 1 : -1];
