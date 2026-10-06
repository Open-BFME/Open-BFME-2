// cl: /MD /DNDEBUG
//
// Three InGameUI hero-event members, retail 0x002A123F / 0x002A1261 /
// 0x002A1283 (34 bytes each, ret 4): each passes the Object, an event-name
// literal ("HeroInitialSpawn", "HeroRespawn", "HeroDeath"), the address of
// an InGameUI word (+0x9D0 / +0x9D8 / +0x9E0) and the float after it to
// InGameUI helper 0x0029F954 (thiscall: `this` stays in ecx, hence retail's
// lea eax for the address argument). The first and last are pinned under these
// placeholder names from TheInGameUI calls; the middle one is their twin.
// The helper's and the members' real names are unknown.

class Object;

class InGameUI
{
public:
	void rva002A123F(Object *obj);
	void rva002A1261(Object *obj);
	void rva002A1283(Object *obj);
	void rva0029F954(Object *obj, const char *eventName, const int *value, float scale);
private:
	unsigned char m_pad000[0x9D0];
	int m_heroInitialSpawn;
	float m_heroInitialSpawnScale;
	int m_heroRespawn;
	float m_heroRespawnScale;
	int m_heroDeath;
	float m_heroDeathScale;
};

void InGameUI::rva002A123F(Object *obj)
{
	rva0029F954(obj, "HeroInitialSpawn", &m_heroInitialSpawn, m_heroInitialSpawnScale);
}

void InGameUI::rva002A1261(Object *obj)
{
	rva0029F954(obj, "HeroRespawn", &m_heroRespawn, m_heroRespawnScale);
}

void InGameUI::rva002A1283(Object *obj)
{
	rva0029F954(obj, "HeroDeath", &m_heroDeath, m_heroDeathScale);
}
