// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
// stlport
//
// ?createGridDecals@DynamicShroudClearingRangeUpdate@@QAEXABVRadiusDecalTemplate@@MABUCoord3D@@@Z retail 0x0048B20E
// 70 bytes. Behavior-side grid-decal builder completing the
// DynamicShroudClearingRangeUpdate file-unit (all behavior sides rowed).
//
// Transcribed from the Zero Hour donor
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/
// Code/GameEngine/Source/GameLogic/Object/Update/
// DynamicShroudClearingRangeUpdate.cpp): per decal, clear, template-built
// decal via the owning player's controller, set position. All callees
// settled (clear rowed, getControllingPlayer rowed, createRadiusDecal
// pinned, setPosition pinned). The countdown pointer loop mirrors the
// rowed ctor's proven do-while shape; the fld/fstp radius split comes from
// the named radius local after the controller store.

class Thing;
class ModuleData;
class Player;
struct Coord3D;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();
};

class RadiusDecal
{
public:
	void clear();
	void setPosition(const Coord3D &pos);

private:
	const void *m_template;			// +0x00
	void *m_decal;					// +0x04
	unsigned char m_empty;			// +0x08
	unsigned char m_pad_09[3];
	float m_unknown0C;				// +0x0C
};

class RadiusDecalTemplate
{
public:
	void createRadiusDecal(const Coord3D &pos, float radius, const Player *owningPlayer, RadiusDecal &result) const;
};

class DynamicShroudClearingRangeUpdate : public UpdateModule
{
public:
	void createGridDecals(const RadiusDecalTemplate &tmpl, float radius, const Coord3D &pos);

private:
	const void *m_vtable;				// +0x00
	const ModuleData *m_moduleData;		// +0x04
	Object *m_object;					// +0x08
	char m_unreconstructed_0C[0x50 - 0x0C];
	RadiusDecal m_gridDecal[30];		// +0x50
};

// ?createGridDecals@DynamicShroudClearingRangeUpdate@@QAEXABVRadiusDecalTemplate@@MABUCoord3D@@@Z @0x0048B20E
void DynamicShroudClearingRangeUpdate::createGridDecals(
	const RadiusDecalTemplate &tmpl, float radius, const Coord3D &pos)
{
	RadiusDecal *decal = m_gridDecal;
	int decalsLeft = 30;
	do {
		decal->clear();
		tmpl.createRadiusDecal(pos, radius, m_object->getControllingPlayer(), *decal);
		decal->setPosition(pos);
		++decal;
	} while (--decalsLeft != 0);
}
