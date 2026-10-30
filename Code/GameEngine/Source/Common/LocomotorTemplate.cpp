// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /O1 /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// ??0LocomotorTemplate@@QAE@ABV0@@Z, retail 0x001E4DEB, 961 bytes.
// Copy constructor of the LocomotorTemplate holder (vtable 0x007DE8B4, rowed dtor
// 0x001E4DB0): base copy constructor (0x007664DD, base Overridable), the AsciiString at
// +0x10 copy-constructed, then the same member-wise int/byte copies up to +0x151 as
// the sibling copy assignment LocomotorTemplate::operator= (Rva001E3955Assign.cpp).
// Target evidence: retail body and the shared member offsets/widths read byte for byte.
#include "ascii_string.h"
class Overridable
{
public:
	Overridable(const Overridable &rhs);
	virtual ~Overridable();
	char m_pad[0x0C];
};
class LocomotorTemplate : public Overridable
{
public:
	LocomotorTemplate(const LocomotorTemplate &rhs);
	virtual ~LocomotorTemplate();
private:
	AsciiString m_10;
	int m_surfaces;
	int m_lookAheadMult;
	unsigned char m_nonDirtyTransform;
	int m_speed;
	int m_speedDamaged;
	int m_minSpeed;
	int m_turnTime;
	int m_turnTimeDamaged;
	int m_slowTurnRadius;
	int m_fastTurnRadius;
	int m_turnThreshold;
	int m_turnThresholdHS;
	int m_acceleration;
	int m_lift;
	int m_liftDamaged;
	int m_braking;
	int m_minTurnSpeed;
	int m_preferredHeight;
	int m_preferredAttackHeight;
	int m_preferredHeightDamping;
	int m_circlingRadius;
	int m_speedLimitZ;
	int m_maxThrustAngle;
	int m_zAxisBehavior;
	int m_appearance;
	int m_formationPriority;
	int m_accDecTrigger;
	int m_walkDistance;
	int m_maxTurnWithoutReform;
	int m_accelerationPitchLimit;
	int m_bounceAmount;
	int m_pitchStiffness;
	int m_rollStiffness;
	int m_pitchDamping;
	int m_rollDamping;
	int m_pitchInDirectionOfZVelFactor;
	int m_maxOverlappedHeight;
	int m_forwardVelocityPitchFactor;
	int m_AC;
	int m_forwardAccelerationPitchFactor;
	int m_lateralAccelerationRollFactor;
	int m_uniformAxialDamping;
	int m_BC;
	int m_airborneTargetingHeight;
	int m_closeEnoughDist;
	unsigned char m_closeEnoughDist3D;
	int m_CC;
	unsigned char m_locomotorWorksWhenDead;
	unsigned char m_allowAirborneMotiveForce;
	unsigned char m_apply2DFrictionWhenAirborne;
	unsigned char m_downhillOnly;
	unsigned char m_stickToGround;
	int m_canMoveBackwards;
	unsigned char m_DC;
	int m_maximumWheelExtension;
	int m_maximumWheelCompression;
	int m_frontWheelTurnAngle;
	unsigned char m_EC;
	unsigned char m_ED;
	int m_wanderWidthFactor;
	int m_wanderLengthFactor;
	int m_wanderAboutPointRadius;
	int m_FC;
	unsigned char m_burningDeathIsCavalry;
	int m_chargeSpeed;
	unsigned char m_chargeAvailable;
	unsigned char m_chargeIgnoresCondition;
	unsigned char m_enableHighSpeedTurnModelconditions;
	unsigned char m_waitForFormation;
	int m_rudderCorrectionDegree;
	int m_rudderCorrectionRate;
	int m_elevatorCorrectionDegree;
	int m_elevatorCorrectionRate;
	int m_aeleronCorrectionDegree;
	int m_aeleronCorrectionRate;
	int m_swoopStandoffRadius;
	int m_swoopStandoffHeight;
	int m_swoopTerminalVelocity;
	int m_swoopAccelerationRate;
	int m_swoopSpeedTuningFactor;
	int m_backingUpSpeed;
	unsigned char m_backingUpStopWhenTurning;
	int m_backingUpDistanceMin;
	int m_backingUpDistanceMax;
	int m_backingUpAngle;
	int m_riverModifier;
	unsigned char m_scalesWalls;
	unsigned char m_turnWhileMoving;
};

LocomotorTemplate::LocomotorTemplate(const LocomotorTemplate &rhs) : Overridable(rhs), m_10(rhs.m_10)
{
	m_surfaces = rhs.m_surfaces;
	m_lookAheadMult = rhs.m_lookAheadMult;
	m_nonDirtyTransform = rhs.m_nonDirtyTransform;
	m_speed = rhs.m_speed;
	m_speedDamaged = rhs.m_speedDamaged;
	m_minSpeed = rhs.m_minSpeed;
	m_turnTime = rhs.m_turnTime;
	m_turnTimeDamaged = rhs.m_turnTimeDamaged;
	m_slowTurnRadius = rhs.m_slowTurnRadius;
	m_fastTurnRadius = rhs.m_fastTurnRadius;
	m_turnThreshold = rhs.m_turnThreshold;
	m_turnThresholdHS = rhs.m_turnThresholdHS;
	m_acceleration = rhs.m_acceleration;
	m_lift = rhs.m_lift;
	m_liftDamaged = rhs.m_liftDamaged;
	m_braking = rhs.m_braking;
	m_minTurnSpeed = rhs.m_minTurnSpeed;
	m_preferredHeight = rhs.m_preferredHeight;
	m_preferredAttackHeight = rhs.m_preferredAttackHeight;
	m_preferredHeightDamping = rhs.m_preferredHeightDamping;
	m_circlingRadius = rhs.m_circlingRadius;
	m_speedLimitZ = rhs.m_speedLimitZ;
	m_maxThrustAngle = rhs.m_maxThrustAngle;
	m_zAxisBehavior = rhs.m_zAxisBehavior;
	m_appearance = rhs.m_appearance;
	m_formationPriority = rhs.m_formationPriority;
	m_accDecTrigger = rhs.m_accDecTrigger;
	m_walkDistance = rhs.m_walkDistance;
	m_maxTurnWithoutReform = rhs.m_maxTurnWithoutReform;
	m_accelerationPitchLimit = rhs.m_accelerationPitchLimit;
	m_bounceAmount = rhs.m_bounceAmount;
	m_pitchStiffness = rhs.m_pitchStiffness;
	m_rollStiffness = rhs.m_rollStiffness;
	m_pitchDamping = rhs.m_pitchDamping;
	m_rollDamping = rhs.m_rollDamping;
	m_pitchInDirectionOfZVelFactor = rhs.m_pitchInDirectionOfZVelFactor;
	m_maxOverlappedHeight = rhs.m_maxOverlappedHeight;
	m_forwardVelocityPitchFactor = rhs.m_forwardVelocityPitchFactor;
	m_AC = rhs.m_AC;
	m_forwardAccelerationPitchFactor = rhs.m_forwardAccelerationPitchFactor;
	m_lateralAccelerationRollFactor = rhs.m_lateralAccelerationRollFactor;
	m_uniformAxialDamping = rhs.m_uniformAxialDamping;
	m_BC = rhs.m_BC;
	m_airborneTargetingHeight = rhs.m_airborneTargetingHeight;
	m_closeEnoughDist = rhs.m_closeEnoughDist;
	m_closeEnoughDist3D = rhs.m_closeEnoughDist3D;
	m_CC = rhs.m_CC;
	m_locomotorWorksWhenDead = rhs.m_locomotorWorksWhenDead;
	m_allowAirborneMotiveForce = rhs.m_allowAirborneMotiveForce;
	m_apply2DFrictionWhenAirborne = rhs.m_apply2DFrictionWhenAirborne;
	m_downhillOnly = rhs.m_downhillOnly;
	m_stickToGround = rhs.m_stickToGround;
	m_canMoveBackwards = rhs.m_canMoveBackwards;
	m_DC = rhs.m_DC;
	m_maximumWheelExtension = rhs.m_maximumWheelExtension;
	m_maximumWheelCompression = rhs.m_maximumWheelCompression;
	m_frontWheelTurnAngle = rhs.m_frontWheelTurnAngle;
	m_EC = rhs.m_EC;
	m_ED = rhs.m_ED;
	m_wanderWidthFactor = rhs.m_wanderWidthFactor;
	m_wanderLengthFactor = rhs.m_wanderLengthFactor;
	m_wanderAboutPointRadius = rhs.m_wanderAboutPointRadius;
	m_FC = rhs.m_FC;
	m_burningDeathIsCavalry = rhs.m_burningDeathIsCavalry;
	m_chargeSpeed = rhs.m_chargeSpeed;
	m_chargeAvailable = rhs.m_chargeAvailable;
	m_chargeIgnoresCondition = rhs.m_chargeIgnoresCondition;
	m_enableHighSpeedTurnModelconditions = rhs.m_enableHighSpeedTurnModelconditions;
	m_waitForFormation = rhs.m_waitForFormation;
	m_rudderCorrectionDegree = rhs.m_rudderCorrectionDegree;
	m_rudderCorrectionRate = rhs.m_rudderCorrectionRate;
	m_elevatorCorrectionDegree = rhs.m_elevatorCorrectionDegree;
	m_elevatorCorrectionRate = rhs.m_elevatorCorrectionRate;
	m_aeleronCorrectionDegree = rhs.m_aeleronCorrectionDegree;
	m_aeleronCorrectionRate = rhs.m_aeleronCorrectionRate;
	m_swoopStandoffRadius = rhs.m_swoopStandoffRadius;
	m_swoopStandoffHeight = rhs.m_swoopStandoffHeight;
	m_swoopTerminalVelocity = rhs.m_swoopTerminalVelocity;
	m_swoopAccelerationRate = rhs.m_swoopAccelerationRate;
	m_swoopSpeedTuningFactor = rhs.m_swoopSpeedTuningFactor;
	m_backingUpSpeed = rhs.m_backingUpSpeed;
	m_backingUpStopWhenTurning = rhs.m_backingUpStopWhenTurning;
	m_backingUpDistanceMin = rhs.m_backingUpDistanceMin;
	m_backingUpDistanceMax = rhs.m_backingUpDistanceMax;
	m_backingUpAngle = rhs.m_backingUpAngle;
	m_riverModifier = rhs.m_riverModifier;
	m_scalesWalls = rhs.m_scalesWalls;
	m_turnWhileMoving = rhs.m_turnWhileMoving;
}
