// cl: /O1 /DNDEBUG /MD
// ?update@RadiusDecalUpdate@@UAE?AW4UpdateSleepTime@@XZ retail 0x0039157B, 51
// bytes: Zero Hour's RadiusDecalUpdate::update. It is the first slot of the
// three-slot UpdateModuleInterface vftable (rdata 0x0081A00C) that sits right
// before RadiusDecalUpdate's primary one (??_GRadiusDecalUpdate at 0x0081A018),
// so MSVC compiles it on the interface subobject at +0x10: the object pointer
// is read at -8 (+0x08 in the module), the delivery decal at +0x10 (+0x20) and
// the kill-when-no-longer-attacking flag at +0x20 (+0x30). Callees:
// Object::testStatus (rowed 0x0004E536, OBJECT_STATUS_IS_ATTACKING = 0x16),
// RadiusDecal::clear (rowed 0x00330DBA) and RadiusDecal::update (pinned
// 0x00330F98). It sits between killRadiusDecal (0x0039155F) and xfer
// (0x003915AE) as in the Zero Hour source.

enum ObjectStatusTypes
{
	OBJECT_STATUS_IS_ATTACKING = 0x16
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class Object
{
public:
	bool testStatus( ObjectStatusTypes bit ) const;
};

class RadiusDecal
{
public:
	void clear();
	void update();

private:
	const void *m_template;
	void *m_decal;
};

class RadiusDecalUpdateModuleBase
{
public:
	virtual ~RadiusDecalUpdateModuleBase();

protected:
	Object *getObject() const { return m_object; }

private:
	void *m_moduleData;		///< 0x04
	Object *m_object;		///< 0x08
	unsigned int m_unrecovered0C;
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class RadiusDecalUpdate : public RadiusDecalUpdateModuleBase, public UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();

private:
	unsigned char m_unrecovered14[ 0x20 - 0x14 ];
	RadiusDecal m_deliveryDecal;					///< 0x20
	unsigned char m_unrecovered28[ 0x30 - 0x28 ];
	bool m_killWhenNoLongerAttacking;				///< 0x30
};

//-------------------------------------------------------------------------------------------------
UpdateSleepTime RadiusDecalUpdate::update()
{
	if (m_killWhenNoLongerAttacking && !getObject()->testStatus(OBJECT_STATUS_IS_ATTACKING))
	{
		m_deliveryDecal.clear();
		return UPDATE_SLEEP_FOREVER;
	}

	m_deliveryDecal.update();
	return UPDATE_SLEEP_NONE;
}
