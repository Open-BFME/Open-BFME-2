// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva0004E704@@YA_NPAVObject@@PAH@Z  Native 0x0004E704..0x0004E7D2 (206 bytes)
// Radar stealth blink for one object: unless the object passes the rowed
// Object query 0x002943B2 (null player) or is disguised (0x0028F4BC record with
// a template at +0x3C) a foreign object that fails rva002933CD and status 0x11
// is hidden (returns false); otherwise the colour alpha pulses between 64 and
// 255 over 2 * g_009BA4E8 client frames (TheGameClient slot 0x7C).
// Same shape as the BFME1 W3DRadar cold path rva006C42B0 (donor f98983a7d).
// Static helper with a private convention: its retail caller 0x00050125 (W3DRadar
// object-list render) passes the object in EDI and the colour pointer in EBX.
// The caller tests only AL of rva002933CD so the int row is read as a byte.

typedef int Int;
typedef int Color;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

class ThingTemplate;
class Player;
class PlayerList { public: Player *getLocalPlayer() { return m_local; } char m_pad00[0x10]; Player *m_local; };
extern PlayerList *ThePlayerList;
class Rva00373EC6 { public: char m_pad00[0x3c]; const ThingTemplate *m_template; };
enum ObjectStatusTypes { OBJECT_STATUS_BFME_17 = 0x11 };

class Object {
public:
	Player *getControllingPlayer() const;
	Rva00373EC6 *rva0028F4BC();
	bool rva002943B2(const Player *player);
	Int rva002933CD();
	bool testStatus(ObjectStatusTypes status) const;
};

class RadarObject {
public:
	Object *friend_getObject() const { return m_object; }
	char m_pad00[4];
	Object *m_object;
};

class GameClient {
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
	virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
	virtual void v70(); virtual void v74(); virtual void v78();
	virtual UnsignedInt getFrame();
};
extern GameClient *TheGameClient;
extern int g_009BA4E8;

void GameGetColorComponents(Color color, UnsignedByte *red, UnsignedByte *green, UnsignedByte *blue, UnsignedByte *alpha);
inline Color GameMakeColor(UnsignedByte r, UnsignedByte g, UnsignedByte b, UnsignedByte a)
{
	return (a << 24) | (r << 16) | (g << 8) | (b);
}

static Bool rva0004E704(Object *object, Color *color)
{
	if (object->rva002943B2(0))
	{
		Rva00373EC6 *disguise = object->rva0028F4BC();
		if (disguise == 0 || disguise->m_template == 0)
		{
			if (object->getControllingPlayer() != ThePlayerList->getLocalPlayer() &&
				!(UnsignedByte)object->rva002933CD() && !object->testStatus(OBJECT_STATUS_BFME_17))
				return false;

			UnsignedByte red, green, blue, alpha;
			GameGetColorComponents(*color, &red, &green, &blue, &alpha);
			const UnsignedInt halfTransition = g_009BA4E8;
			UnsignedInt frame = TheGameClient->getFrame() % (halfTransition * 2);
			if (frame >= halfTransition)
				alpha = (UnsignedByte)(255 - ((frame - halfTransition) * 191) / halfTransition);
			else
				alpha = (UnsignedByte)(64 + (frame * 191) / halfTransition);
			*color = GameMakeColor(red, green, blue, alpha);
		}
	}
	return true;
}

// ?rva0004E704Caller absent-from-retail
Int rva0004E704Caller(RadarObject *const *objects, Int count, Color *colors)
{
	Int drawn = 0;
	for (Int i = 0; i < count; ++i)
	{
		Object *obj = objects[i]->friend_getObject();
		Color c = colors[i];
		if (rva0004E704(obj, &c))
			drawn += c;
	}
	return drawn;
}
