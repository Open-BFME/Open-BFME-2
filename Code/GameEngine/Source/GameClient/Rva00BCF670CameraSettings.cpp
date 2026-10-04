// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// The unnamed 22-slot vftable at VA 0x00BCF670 (installed by the 14-byte
// constructor at 0x00101C92, which then calls reset 0x00101A20). Its slots
// 0..11 are folded getters/setters owned by other rows (the float setters at
// +0x04..+0x14 are Rva00101CB0FloatField and neighbours); slot 20 is the
// folded dword clearer 0x002FD7D7. This unit holds the rest:
//
//   slots 12..16  0x00101A64.. map-dictionary real through a static NameKey
//                 cache, falling back to a TheWritableGlobalData real:
//                   "cameraMinHeight"         -> +0x04, GlobalData +0x9C
//                   "cameraMaxHeight"         -> +0x08, GlobalData +0xA0
//                   "cameraPitchAngle"        -> +0x0C, GlobalData +0xA4
//                   "cameraYawAngle"          -> +0x10, GlobalData +0xA8
//                   "cameraScrollSpeedScalar" -> +0x14, GlobalData +0xAC
//   slot 17       0x0010185A reload all five, flag +0x18 when any of
//                 pitch/yaw/min/max differs from 37.5 / 0 / 120 / 300
//   slot 18       0x001018CD camera offset vector and yaw angle
//   slot 19       0x00101B86 look up a trigger area by name into +0x1C
//   slot 21       0x00101CF6 keep a position inside the trigger area
//   non-virtual   0x00101A20 reset, 0x001019DA position test,
//                 0x00101BFB neighbour search
//
// Target evidence: the cache records at VA 0x00DBDED4..0x00DBDEF4 (retail
// bytes: key 0, then the pointer to the string above), the rowed
// Rva00148F5ECache::get 0x00148F5E, Dict::getReal 0x003131FC on
// g_Va00E00944, TheWritableGlobalData 0x00DFE758, TheTerrainLogic slot 39
// (getTriggerAreaByName), PolygonTrigger 0x002E3A13 / 0x002E38F3 and the
// PartitionManager::getShroudStatusForPlayer thunk 0x007397F0 on
// TheShroudManager with ThePlayerList's local player index (+0x10, +0x54).
// Inference: the owner is a camera-settings record bound to a polygon
// trigger; the class and member names are ours and only the addresses are
// evidence.

#define PI 3.14159265359f

extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl tan(double);

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED
};

struct Coord3D
{
	float x, y, z;
	Coord3D() {}
	Coord3D(const Coord3D &that) { x = that.x; y = that.y; z = that.z; }
	Coord3D &operator-=(const Coord3D &that) { x -= that.x; y -= that.y; z -= that.z; return *this; }
	float Normalize();
	void set(float ax, float ay, float az) { x = ax; y = ay; z = az; }
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

class ICoord3D
{
public:
	int x;
	int y;
	int z;
};

class AsciiString;

class Rva00148F5ECache
{
public:
	NameKeyType get();
	NameKeyType m_key;
	const char *m_name;
};

class Dict
{
public:
	float getReal(int key, bool *exists) const;

private:
	struct DictPairData;
	DictPairData *m_data;
};

extern Dict g_Va00E00944;	// VA 0x00E00944

class GlobalData
{
public:
	char m_pad00[0x9C];
	float m_cameraMinHeight9C;
	float m_cameraMaxHeightA0;
	float m_cameraPitchAngleA4;
	float m_cameraYawAngleA8;
	float m_cameraScrollSpeedScalarAC;
};

extern GlobalData *TheWritableGlobalData;	// VA 0x00DFE758

class PolygonTrigger
{
public:
	bool pointInTrigger(const ICoord3D &point);
	void getCenterPoint(Coord3D *pOutCoord) const;
	bool rva002E3A39(const Coord3D &point);
	bool rva002E3AA8(const Coord3D *from, const Coord3D *to, Coord3D *hit, bool flag);
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual PolygonTrigger *getTriggerAreaByName(const AsciiString &name); // +0x9C
};
extern TerrainLogic *TheTerrainLogic;

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const;
};
extern PartitionManager *TheShroudManager;	// VA 0x00DFE74C

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
	char m_pad00[0x54];
	int m_playerIndex;	// +0x54
};

class PlayerList
{
public:
	char m_pad00[0x10];
	Player *m_local;	// +0x10
	Player *getLocalPlayer() { return m_local; }
};
extern PlayerList *ThePlayerList;	// VA 0x00DFEEE8

// VA 0x00DBDED4..0x00DBDEF4 (.data): retail bytes 00 00 00 00 then the
// string pointer.
Rva00148F5ECache g_00DBDED4 = { NAMEKEY_INVALID, "cameraMinHeight" };
Rva00148F5ECache g_00DBDEDC = { NAMEKEY_INVALID, "cameraMaxHeight" };
Rva00148F5ECache g_00DBDEE4 = { NAMEKEY_INVALID, "cameraPitchAngle" };
Rva00148F5ECache g_00DBDEEC = { NAMEKEY_INVALID, "cameraYawAngle" };
Rva00148F5ECache g_00DBDEF4 = { NAMEKEY_INVALID, "cameraScrollSpeedScalar" };

class Rva00BCF670CameraSettings
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(); virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void loadMinHeight();					// slot 12
	virtual void loadMaxHeight();					// slot 13
	virtual void loadPitchAngle();					// slot 14
	virtual void loadYawAngle();					// slot 15
	virtual void loadScrollSpeedScalar();			// slot 16
	virtual void reload();							// slot 17
	virtual void getCameraOffset(Coord3D *offset, float *yaw);	// slot 18
	virtual bool setTriggerArea(const AsciiString &name, const Coord3D *pos);	// slot 19
	virtual void vslot20();
	virtual void constrainPosition(Coord3D *pos);	// slot 21

	void reset();
	bool isPositionAllowed(const Coord3D *pos);
	bool findAllowedNeighbour(Coord3D *pos, float step);

private:
	float m_minHeight04;
	float m_maxHeight08;
	float m_pitchAngle0C;
	float m_yawAngle10;
	float m_scrollSpeedScalar14;
	bool m_custom18;
	PolygonTrigger *m_trigger1C;
	Coord3D m_lastPos20;
};

void Rva00BCF670CameraSettings::loadMinHeight()
{
	bool exists;
	m_minHeight04 = g_Va00E00944.getReal(g_00DBDED4.get(), &exists);
	if (!exists)
		m_minHeight04 = TheWritableGlobalData->m_cameraMinHeight9C;
}

void Rva00BCF670CameraSettings::loadMaxHeight()
{
	bool exists;
	m_maxHeight08 = g_Va00E00944.getReal(g_00DBDEDC.get(), &exists);
	if (!exists)
		m_maxHeight08 = TheWritableGlobalData->m_cameraMaxHeightA0;
}

void Rva00BCF670CameraSettings::loadPitchAngle()
{
	bool exists;
	m_pitchAngle0C = g_Va00E00944.getReal(g_00DBDEE4.get(), &exists);
	if (!exists)
		m_pitchAngle0C = TheWritableGlobalData->m_cameraPitchAngleA4;
}

void Rva00BCF670CameraSettings::loadYawAngle()
{
	bool exists;
	m_yawAngle10 = g_Va00E00944.getReal(g_00DBDEEC.get(), &exists);
	if (!exists)
		m_yawAngle10 = TheWritableGlobalData->m_cameraYawAngleA8;
}

void Rva00BCF670CameraSettings::loadScrollSpeedScalar()
{
	bool exists;
	m_scrollSpeedScalar14 = g_Va00E00944.getReal(g_00DBDEF4.get(), &exists);
	if (!exists)
		m_scrollSpeedScalar14 = TheWritableGlobalData->m_cameraScrollSpeedScalarAC;
}

void Rva00BCF670CameraSettings::reload()
{
	loadMinHeight();
	loadMaxHeight();
	loadPitchAngle();
	loadYawAngle();
	loadScrollSpeedScalar();
	if (m_pitchAngle0C != 37.5f || m_yawAngle10 != 0.0 || m_minHeight04 != 120.0f || m_maxHeight08 != 300.0f)
		m_custom18 = true;
	else
		m_custom18 = false;
}

void Rva00BCF670CameraSettings::getCameraOffset(Coord3D *offset, float *yaw)
{
	if (m_custom18)
	{
		if (offset)
		{
			float dist = m_maxHeight08 * 1.642665f;
			float s = sin(m_pitchAngle0C * PI * (1.0 / 180.0));
			float c = cos(m_pitchAngle0C * PI * (1.0 / 180.0));
			offset->z = s * dist;
			offset->y = 0.0f - c * dist;
			offset->x = 0.0f;
		}
		if (yaw)
			*yaw = m_yawAngle10 * PI * (1.0 / 180.0);
	}
	else
	{
		if (offset)
		{
			float height = m_maxHeight08;
			offset->z = height;
			offset->y = -(height / tan(m_pitchAngle0C * (double)(PI / 180.0f)));
			offset->x = -(tan(m_yawAngle10 * (double)(PI / 180.0f)) * offset->y);
		}
		if (yaw)
			*yaw = 0.0f;
	}
}

bool Rva00BCF670CameraSettings::isPositionAllowed(const Coord3D *pos)
{
	if (m_trigger1C == 0)
		return true;
	if (TheShroudManager->getShroudStatusForPlayer(ThePlayerList->getLocalPlayer()->getPlayerIndex(), pos) == CELLSHROUD_SHROUDED)
		return false;
	return m_trigger1C->rva002E3A39(*pos) ? true : false;
}

void Rva00BCF670CameraSettings::reset()
{
	m_minHeight04 = 0.0f;
	m_maxHeight08 = 0.0f;
	m_pitchAngle0C = 37.5f;
	m_yawAngle10 = 0.0f;
	m_scrollSpeedScalar14 = 1.0f;
	m_custom18 = false;
	m_lastPos20.zero();
	m_trigger1C = 0;
}

bool Rva00BCF670CameraSettings::setTriggerArea(const AsciiString &name, const Coord3D *pos)
{
	m_trigger1C = TheTerrainLogic->getTriggerAreaByName(name);
	if (m_trigger1C && pos)
	{
		ICoord3D ipos;
		ipos.x = (int)pos->x;
		ipos.y = (int)pos->y;
		ipos.z = (int)pos->z;
		if (m_trigger1C->pointInTrigger(ipos))
		{
			m_lastPos20 = *pos;
		}
		else
		{
			m_trigger1C->getCenterPoint(&m_lastPos20);
			constrainPosition((Coord3D *)pos);
			return true;
		}
	}
	return false;
}

bool Rva00BCF670CameraSettings::findAllowedNeighbour(Coord3D *pos, float step)
{
	if (!pos)
		return false;
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (i == 0 && j == 0)
				continue;
			Coord3D probe = *pos;
			probe.x = i * step + probe.x;
			probe.y = j * step + probe.y;
			if (isPositionAllowed(&probe))
			{
				*pos = probe;
				m_lastPos20 = probe;
				return true;
			}
		}
	}
	return false;
}

void Rva00BCF670CameraSettings::constrainPosition(Coord3D *pos)
{
	if (m_trigger1C == 0 || pos == 0)
		return;
	Coord3D tmp = *pos;
	tmp -= m_lastPos20;
	if (tmp.Normalize() > 100.0f)
	{
		for (float r = 0.0f; r < 500.0f; r += 30.0f)
		{
			if (findAllowedNeighbour(pos, r))
				return;
		}
	}
	bool lastVisible = TheShroudManager->getShroudStatusForPlayer(ThePlayerList->getLocalPlayer()->getPlayerIndex(), &m_lastPos20) != CELLSHROUD_SHROUDED;
	bool posVisible = TheShroudManager->getShroudStatusForPlayer(ThePlayerList->getLocalPlayer()->getPlayerIndex(), pos) != CELLSHROUD_SHROUDED;
	if (lastVisible && !posVisible)
	{
		*pos = m_lastPos20;
		return;
	}
	if (m_trigger1C->rva002E3A39(*pos))
	{
		m_lastPos20 = *pos;
		return;
	}
	if (m_trigger1C->rva002E3AA8(&m_lastPos20, pos, &tmp, true))
	{
		*pos = tmp;
		m_lastPos20 = tmp;
		return;
	}
	*pos = m_lastPos20;
}
