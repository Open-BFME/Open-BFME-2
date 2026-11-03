// Target facts (code addresses are RVAs, tables are VAs): constructor 0x00468301 calls OpenContainModuleData's 0x00465124 at 0x00468316, stores its own 0x00C442F8 at 0x00468320 and starts fields at +0x98. Factory 0x0024B89C allocates 0x18C bytes at 0x0024B8A8 and calls that constructor at 0x0024B8C0. HordeTransportContainModuleData's 0x00477D61 calls it at 0x00477D64 before installing the distinct 0x00C45FB0. The live table has 31 slots through 0x00C44370; slot 0 is deleting destructor 0x004684D5, calling destructor 0x004684F1 at 0x004684D8. All other slots equal OpenContainModuleData's 0x00C43658, including true slot 8 (0x0050B5C6) and inherited GetSnapshotName (0x00065212). Destructor 0x004684F1 stores no table; it calls the base destructor at 0x00468547, whose 0x002574F7 store restores Snapshot's four-slot 0x00BBB554 during base teardown. Constructors, virtual destructor, buildFieldParse (0x004689DF) and friend_newModuleData (0x0024B89C) remain out of line.
// Target fields: 0x00468326/0x0046832C/0x00468337 initialize +0x98/+0x9C/+0xA0; 0x0046834B constructs the four-byte list at +0xA4; 0x00468363/0x0046836B initialize +0xA8/+0xAC. Calls 0x00468371/0x0046837D/0x00468389/0x00468395/0x004683A1 copy five 0x1C-byte BfmeFixedStorage0004543D values at +0xB0/+0xCC/+0xE8/+0x104/+0x120. Stores 0x004683A6..0x00468410 prove flags +0x13C..+0x142/+0x148/+0x150, dwords +0x144/+0x14C/+0x154/+0x164 and three floats +0x158/+0x15C/+0x160. Call 0x00468416 constructs the four-byte Rva003623E5Member at +0x168. Stores 0x00468421..0x00468452 prove floats +0x170/+0x174/+0x17C and flags +0x16C/+0x16D/+0x178. Call 0x0046845A constructs 12-byte vector storage at +0x180. Destructor calls 0x0046850F/0x0046851E/0x0046852D/0x0046853C destroy that vector, handle, list and AsciiString respectively; unregistered container types remain opaque.
// Target names and types: buildFieldParse's 0x004689EF registers table 0x00C44648..0x00C44858. It names Slots (+0x98), ExitPitchRate (+0x9C), ExitBone (+0xA0), HealthRegen%PerSec (+0xA8), ExitDelay (+0xAC), the five Type* masks, ForceOrientationContainer (+0x13C), CanGrabStructure (+0x13D), ScatterNearbyOnExit (+0x13E), OrientLikeContainerOnExit (+0x13F), GoAggressiveOnExit (+0x140), ResetMoodCheckTimeOnExit (+0x141), DestroyRidersWhoAreNotFreeToExit (+0x142), GrabWeapon (+0x144), FireGrabWeaponOnVictim (+0x148), ConditionForEntry (+0x14C), ShouldThrowOutPassengers (+0x150), ThrowOutPassengersDelay (+0x154), ThrowOutPassengersVelocity (+0x158), ThrowOutPassengersLandingWarhead (+0x164), FadeFilter (+0x168), FadePassengerOnEnter/Exit (+0x16C/+0x16D), EnterFadeTime/ExitFadeTime (+0x170/+0x174), FadeReverse (+0x178) and ReleaseSnappyness (+0x17C). Its parsers are rowed INI::parseDurationUnsignedInt (0x00338B30), parseWeaponTemplate (0x00339569) and parseCoord3D (0x0002F507). InitialPayload's callback 0x00467DE6 appends at +0xA4. Zero Hour TransportContain.h supplies shared member spellings; its layout is not used.
#pragma once

#ifndef BFME2_TRANSPORTCONTAINMODULEDATA_H
#define BFME2_TRANSPORTCONTAINMODULEDATA_H

#include "OpenContainModuleData.h"
#include "../../Common/BfmeFixedStorage0004543D.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

class INI;
class WeaponTemplate;

class TransportContainModuleData : public OpenContainModuleData
{
public:
    TransportContainModuleData();
    virtual ~TransportContainModuleData();
    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    int m_slotCapacity;
    float m_exitPitchRate;
    AsciiString m_exitBone;
    void *m_initialPayload;
    float m_healthRegen;
    unsigned int m_exitDelay;
    BfmeFixedStorage0004543D m_typeOneForWeaponSet;
    BfmeFixedStorage0004543D m_typeTwoForWeaponSet;
    BfmeFixedStorage0004543D m_typeOneForWeaponState;
    BfmeFixedStorage0004543D m_typeTwoForWeaponState;
    BfmeFixedStorage0004543D m_typeThreeForWeaponState;
    bool m_forceOrientationContainer;
    bool m_canGrabStructure;
    bool m_scatterNearbyOnExit;
    bool m_orientLikeContainerOnExit;
    bool m_goAggressiveOnExit;
    bool m_resetMoodCheckTimeOnExit;
    bool m_destroyRidersWhoAreNotFreeToExit;
    const WeaponTemplate *m_grabWeapon;
    bool m_fireGrabWeaponOnVictim;
    int m_conditionForEntry;
    bool m_shouldThrowOutPassengers;
    unsigned int m_throwOutPassengersDelay;
    Coord3D m_throwOutPassengersVelocity;
    const WeaponTemplate *m_throwOutPassengersLandingWarhead;
    Rva003623E5Member m_fadeFilter;
    bool m_fadePassengerOnEnter;
    bool m_fadePassengerOnExit;
    float m_enterFadeTime;
    float m_exitFadeTime;
    bool m_fadeReverse;
    float m_releaseSnappyness;
    unsigned char m_storage180[0x0C];
};

#endif
