#pragma once

#include "Code/Libraries/Include/Lib/Coord3D.h"

class Object;
class Player;
class Xfer;
class Thing;
class ModuleData;
class Module;
class UpgradeTemplate;
class Rva00373EC6;
struct StealthDetectorUpdateModuleData;
enum ObjectID;

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3fffffff };
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum Relationship { ENEMIES, NEUTRAL, ALLIES };
enum CellShroudStatus { SHROUD_CLEAR = 0 };
enum ObjectStatusTypes { STATUS_DUMMY = -1 };
enum KindOfType { KIND_DUMMY = -1 };

class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva004A2BF0Interface
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual bool s4();
	virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
	virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
	virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
	virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
	virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
	virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32();
	virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
	virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40();
	virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
	virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48();
	virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52();
	virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56();
	virtual void s57(); virtual void s58(); virtual void s59(); virtual void s60();
	virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64();
	virtual void s65(); virtual void s66(); virtual void s67(); virtual void s68();
	virtual void s69(); virtual void s70(); virtual void s71(); virtual void s72();
	virtual int s73();
};

class Object
{
public:
    bool rva002943B2(const Player *player);
    bool testStatus(ObjectStatusTypes) const;
    bool isKindOf(KindOfType) const;
    bool hasUpgrade(const UpgradeTemplate *) const;
    float getVisionRange() const;
    int rva0028F4EF();
    int rva002933CD();
    Rva00373EC6 *rva0028F4BC();
protected:
    Module *findModule(NameKeyType) const;
    friend class StealthDetectorUpdate;
public:
    Player *getControllingPlayer() const;
    Relationship getRelationship(const Object *) const;
    CellShroudStatus getShroudStatusForPlayer(int) const;
    char m_pad00[0x38];
    Coord3D m_pos;
    char m_pad44[0x74 - 0x44];
    ObjectID m_id;
    char m_pad78[0x250 - 0x78];
    Rva004A2BF0Interface *m_250;
    char m_pad254[0x274 - 0x254];
    Object *m_container;
    char m_pad278[0x438 - 0x278];
    unsigned char m_privateStatus;
    unsigned char m_pad439[0x43C - 0x439];
    bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
};

class DetectorPrimary
{
public:
	virtual ~DetectorPrimary();
	const StealthDetectorUpdateModuleData *m_data;	// +0x04
	Object *m_object;				// +0x08
};

class DetectorOther { public: virtual void other(); };

class UpdateModuleInterface { public: virtual UpdateSleepTime update() = 0; };

class UpdateModule : public DetectorPrimary, public DetectorOther, public UpdateModuleInterface
{
protected:
	virtual void loadPostProcess();				// slot 1
	virtual const char *GetSnapshotName() const;		// slot 2
public:
	virtual void xfer(Xfer *xfer);				// slot 3
	virtual NameKeyType getModuleNameKey() const = 0;	// slot 4
protected:
	void setWakeFrame(Object *object, UpdateSleepTime wakeTime);	// rowed 0x0044DF71
};

class StealthDetectorUpdate : public UpdateModule
{
public:
	StealthDetectorUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~StealthDetectorUpdate();
	virtual UpdateSleepTime update();
	virtual NameKeyType getModuleNameKey() const;
	Object *getObject() const { return m_object; }
	const char *name() const;
protected:
	virtual void xfer(Xfer *xfer);
};
