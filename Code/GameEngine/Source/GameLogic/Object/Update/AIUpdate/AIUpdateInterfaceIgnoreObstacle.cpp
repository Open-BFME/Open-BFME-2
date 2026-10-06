// cl: /DNDEBUG /MD
//
// AIUpdateInterface::ignoreObstacle (BFME2 build)
// retail 0x00268D88, 304 bytes. BFME2 AIUpdateInterface::ignoreObstacle with
// CritterDesync fprintf logging (game _fprintf at 0x2CEC42, flag byte
// VA 0x00E03745, sink VA 0x00DFEFF0, TheGameLogic 0x009FE78C). Donor is BFME1
// AIUpdateInterfaceIgnoreObstacle (name at ThingTemplate+0x64, id at
// Object+0x74, m_object at +8, m_ignoreObstacleID at +0x164).
// The desync flag byte and the log sink are real extern globals here; the
// banked attempt read TheGameLogic and the flag through literal-address
// macros, which reordered the loads. Callers 0x00269CEA 0x0026A2DE 0x0026BB26.

extern unsigned char g_00E03745;
// g_00E03745: matched references place it at VA 0xe03745 (zero-filled .bss).
unsigned char g_00E03745;
extern void *g_00DFEFF0;
extern "C" void __cdecl fprintf(void *sink, const char *format, ...);

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T> class StringBase
{
public:
	const T *str() const { return m_data ? m_data->text : ""; }

private:
	BfmeStringData<T> *m_data;
};

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	unsigned char m_isOverride;
};

class ThingTemplate : public Overridable
{
public:
	const StringBase<char> &getName() const { return m_name; }

private:
	char m_pad0c[0x64 - 0x0c];
	StringBase<char> m_name;
};

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }

private:
	void *m_vtable;
	const ThingTemplate *m_template;
	char m_pad08[0x74 - 0x08];
	ObjectID m_id;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class AIUpdateInterface
{
public:
	void ignoreObstacle(const Object *obj);

private:
	char m_pad00[0x08];
	Object *m_object;
	char m_pad0c[0x164 - 0x0c];
	ObjectID m_ignoreObstacleID;
};

void AIUpdateInterface::ignoreObstacle(const Object *obj)
{
	if (g_00E03745)
	{
		if (obj)
		{
			if (g_00DFEFF0)
				fprintf(g_00DFEFF0,
					"  CritterDesync - Critter %s(%d) set to ignore %s(%d)",
					m_object->getTemplate()->getName().str(), m_object->getID(),
					obj->getTemplate()->getName().str(), obj->getID());
		}
		else
		{
			Object *old = TheGameLogic->findObjectByID(m_ignoreObstacleID);
			if (old)
			{
				if (g_00DFEFF0)
					fprintf(g_00DFEFF0,
						"  CritterDesync - Critter %s(%d) set to ignore NOTHING. Was previously ignoring %s(%d)",
						m_object->getTemplate()->getName().str(), m_object->getID(),
						old->getTemplate()->getName().str(), old->getID());
			}
			else
			{
				if (g_00DFEFF0)
					fprintf(g_00DFEFF0,
						"  CritterDesync - Critter %s(%d) set to ignore NOTHING. Was previously ignoring NOTHING",
						m_object->getTemplate()->getName().str(), m_object->getID());
			}
		}
	}
	m_ignoreObstacleID = obj ? obj->getID() : INVALID_ID;
}

// ?g_00DFEFF0@@3PAXA: matched references place it at VA 0xdfeff0; also referenced as _theLogicRandomLogFile.
void * g_00DFEFF0 = 0;
#pragma comment(linker, "/alternatename:_theLogicRandomLogFile=?g_00DFEFF0@@3PAXA")
