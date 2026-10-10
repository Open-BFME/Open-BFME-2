// cl: /DNDEBUG /MD /EHsc
// ?reactToTurretChange@Object@@QAEXW4WhichTurretType@@MM@Z @0x0028B141 82B
// (was ?rva0028B141@Object@@QAEXW4WhichTurretType@@MH@Z). Zero Hour
// Object::reactToTurretChange(turret old rotation old pitch): TurretAI
// turn-towards (0x004D8B14) calls it when the angle changed. The pitch
// argument is unused here so its Real type follows Zero Hour. Object
// turret query over AI at +0x258 and face at +0x250. Zeroes two floats,
// fills them via rowed AIUpdateInterface::getTurretRotAndPitch, compares the
// first to the float arg, and when different calls slot3 (+0x0C) on +0x250.
// Evidence: retail call 0x002626FA plus movss/xorps/ucomiss/lahf shape plus
// iface +0x250 AI +0x258 per Object_isAbleToAttack; rowed callee signature.
enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_PRIMARY = 0
};

class AIUpdateInterface
{
public:
	bool getTurretRotAndPitch(WhichTurretType tur, float *turretAngle, float *turretPitch) const;
};

class Rva0028B141Face
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
};

class Object
{
	char m_pad250[0x250];
	Rva0028B141Face *m_face250;
	char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai258;

public:
	void reactToTurretChange(WhichTurretType turret, float oldRotation, float oldPitch);
};

void Object::reactToTurretChange(WhichTurretType turret, float oldRotation, float oldPitch)
{
	(void)oldPitch;
	float angle = 0.0f;
	float pitch = 0.0f;
	AIUpdateInterface *ai = m_ai258;
	if (ai != 0)
		ai->getTurretRotAndPitch(turret, &angle, &pitch);
	if (angle != oldRotation)
	{
		Rva0028B141Face *face = m_face250;
		if (face != 0)
			face->s03();
	}
}
