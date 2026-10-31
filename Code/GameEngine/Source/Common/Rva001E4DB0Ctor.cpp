// ??0LocomotorTemplate@@QAE@XZ @0x001E4ABE 754B
// LocomotorTemplate default constructor: the class of the rowed dtor
// 0x001E4DB0, copy ctor 0x001E4DEB, copy assignment 0x001E3955 and validate
// 0x001E38B9 (vtable 0x007DE8B4, 0x154 bytes, as LocomotorStore's
// parseLocomotorTemplateDefinition 0x001E8A94 allocates it). WB 0xADBAE0 plus
// the BFME1 a7c38d3b donor Locomotor.cpp constructor give the semantic lead,
// retail/WB establish every field. The native Locomotor ctor 0x1E449A
// consumes template +58/+60/+C4/+C8; m_turnTime/m_acceleration/m_braking are integer frame counts
// from 0x00DBA4E4, not floats. Field names past the ZH set are not recovered;
// +0x150 is the byte flag LocomotorSet::addLocomotor tests into the set's
// +0x15 and the rowed clone 0x001E67BF clears (default 0; +0x151 defaults
// to 1).
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// BFME1 donor a7c38d3b2597121f178ab5190b3062478823257d:
// game/GameEngine/Source/GameLogic/Object/Locomotor.cpp supplies the semantic
// LocomotorTemplate constructor lead; retail/WB establish every field below.
// The canonical Locomotor.cpp still declares the ZH layout of this class; its
// matched getLegalSurfaces reads template+10 rather than native+14.
#include "ascii_string.h"
extern int BfmeLogicFramesPerSecond;
#include "../../Include/Common/Overridable.h"
class LocomotorTemplate : public Overridable {
public:
    LocomotorTemplate();
    virtual ~LocomotorTemplate();
private:
	AsciiString m_10;
	int m_surfaces;
	float m_lookAheadMult;
	unsigned char m_nonDirtyTransform;
	float m_speed;
	float m_speedDamaged;
	float m_minSpeed;
	int m_turnTime;
	int m_turnTimeDamaged;
	float m_slowTurnRadius;
	float m_fastTurnRadius;
	float m_turnThreshold;
	float m_turnThresholdHS;
	int m_acceleration;
	float m_lift;
	float m_liftDamaged;
	int m_braking;
	float m_minTurnSpeed;
	float m_preferredHeight;
	float m_preferredAttackHeight;
	float m_preferredHeightDamping;
	float m_circlingRadius;
	float m_speedLimitZ;
	float m_maxThrustAngle;
	int m_zAxisBehavior;
	int m_appearance;
	int m_formationPriority;
	float m_accDecTrigger;
	float m_walkDistance;
	float m_maxTurnWithoutReform;
	float m_accelerationPitchLimit;
	float m_bounceAmount;
	float m_pitchStiffness;
	float m_rollStiffness;
	float m_pitchDamping;
	float m_rollDamping;
	float m_pitchInDirectionOfZVelFactor;
	float m_maxOverlappedHeight;
	float m_forwardVelocityPitchFactor;
	float m_AC;
	float m_forwardAccelerationPitchFactor;
	float m_lateralAccelerationRollFactor;
	float m_uniformAxialDamping;
	float m_BC;
	int m_airborneTargetingHeight;
	float m_closeEnoughDist;
	unsigned char m_closeEnoughDist3D;
	float m_CC;
	unsigned char m_locomotorWorksWhenDead;
	unsigned char m_allowAirborneMotiveForce;
	unsigned char m_apply2DFrictionWhenAirborne;
	unsigned char m_downhillOnly;
	unsigned char m_stickToGround;
	int m_canMoveBackwards;
	unsigned char m_DC;
	float m_maximumWheelExtension;
	float m_maximumWheelCompression;
	float m_frontWheelTurnAngle;
	unsigned char m_EC;
	unsigned char m_ED;
	float m_wanderWidthFactor;
	float m_wanderLengthFactor;
	float m_wanderAboutPointRadius;
	float m_FC;
	unsigned char m_burningDeathIsCavalry;
	float m_chargeSpeed;
	unsigned char m_chargeAvailable;
	unsigned char m_chargeIgnoresCondition;
	unsigned char m_enableHighSpeedTurnModelconditions;
	unsigned char m_waitForFormation;
	float m_rudderCorrectionDegree;
	float m_rudderCorrectionRate;
	float m_elevatorCorrectionDegree;
	float m_elevatorCorrectionRate;
	float m_aeleronCorrectionDegree;
	float m_aeleronCorrectionRate;
	float m_swoopStandoffRadius;
	float m_swoopStandoffHeight;
	float m_swoopTerminalVelocity;
	float m_swoopAccelerationRate;
	float m_swoopSpeedTuningFactor;
	float m_backingUpSpeed;
	unsigned char m_backingUpStopWhenTurning;
	float m_backingUpDistanceMin;
	float m_backingUpDistanceMax;
	float m_backingUpAngle;
	float m_riverModifier;
	unsigned char m_scalesWalls;
	unsigned char m_turnWhileMoving;
};

LocomotorTemplate::LocomotorTemplate()
{
    m_riverModifier = 1.0f;
    m_speedDamaged = 1.0f;
    m_turnTimeDamaged = 0;
    m_liftDamaged = -1.0f;
    m_surfaces = 0;
    m_speed = 0.0f;
    m_lookAheadMult = 1.0f;
    m_nonDirtyTransform = 0;
    m_turnTime = BfmeLogicFramesPerSecond;
    m_slowTurnRadius = 0.0f;
    m_fastTurnRadius = 20.0f;
    m_turnThreshold = 0.2617993950843811f;
    m_turnThresholdHS = 3.1415927410125732f;
    m_acceleration = BfmeLogicFramesPerSecond;
    m_lift = 0.0f;
    m_braking = BfmeLogicFramesPerSecond;
    m_minSpeed = 0.0f;
    m_minTurnSpeed = 99999.0f;
    m_zAxisBehavior = 0;
    m_appearance = 1;
    m_formationPriority = 7;
    m_preferredHeight = 0.0f;
    m_preferredAttackHeight = 0.0f;
    m_preferredHeightDamping = 1.0f;
    m_circlingRadius = 0.0f;
    m_accDecTrigger = 0.5f;
    m_walkDistance = 0.0f;
    m_maxThrustAngle = 0.0f;
    m_speedLimitZ = 999999.0f;
    m_maxTurnWithoutReform = 6.2831854820251465f;
    m_accelerationPitchLimit = 0.0f;
    m_bounceAmount = 0.0f;
    m_pitchStiffness = 0.10000000149011612f;
    m_rollStiffness = 0.10000000149011612f;
    m_pitchDamping = 0.8999999761581421f;
    m_rollDamping = 0.8999999761581421f;
    m_forwardVelocityPitchFactor = 0.0f;
    m_pitchInDirectionOfZVelFactor = 0.0f;
    m_maxOverlappedHeight = 3.4028234663852886e+38f;
    m_AC = 0.0f;
    m_forwardAccelerationPitchFactor = 0.0f;
    m_lateralAccelerationRollFactor = 0.0f;
    m_uniformAxialDamping = 1.0f;
    m_BC = 0.0f;
    m_apply2DFrictionWhenAirborne = 0;
    m_downhillOnly = 0;
    m_turnWhileMoving = 1;
    m_allowAirborneMotiveForce = 0;
    m_locomotorWorksWhenDead = 0;
    m_airborneTargetingHeight = 0x7fffffff;
    m_stickToGround = 0;
    m_canMoveBackwards = 0;
    m_DC = 0;
    m_frontWheelTurnAngle = 0.0f;
    m_maximumWheelExtension = 0.0f;
    m_maximumWheelCompression = 0.0f;
    m_closeEnoughDist = 1.0f;
    m_closeEnoughDist3D = 0;
    m_scalesWalls = 0;
    m_CC = 0.0f;
    m_EC = 0;
    m_ED = 0;
    m_wanderWidthFactor = 0.0f;
    m_wanderLengthFactor = 1.0f;
    m_wanderAboutPointRadius = 0.0f;
    m_FC = 0.0f;
    m_burningDeathIsCavalry = 0;
    m_chargeSpeed = 0.0f;
    m_chargeAvailable = 0;
    m_chargeIgnoresCondition = 0;
    m_enableHighSpeedTurnModelconditions = 1;
    m_waitForFormation = 0;
    m_rudderCorrectionDegree = 0.0f;
    m_rudderCorrectionRate = 0.0f;
    m_elevatorCorrectionDegree = 0.0f;
    m_elevatorCorrectionRate = 0.0f;
    m_aeleronCorrectionDegree = 0.0f;
    m_aeleronCorrectionRate = 0.0f;
    m_swoopStandoffRadius = 200.0f;
    m_swoopStandoffHeight = 200.0f;
    m_swoopTerminalVelocity = 0.07000000029802322f;
    m_swoopAccelerationRate = 0.003000000026077032f;
    m_swoopSpeedTuningFactor = 1.0f;
    m_backingUpSpeed = 0.75f;
    m_backingUpStopWhenTurning = 0;
    m_backingUpDistanceMin = 0.0f;
    m_backingUpDistanceMax = 0.0f;
    m_backingUpAngle = 0.5f;
}

