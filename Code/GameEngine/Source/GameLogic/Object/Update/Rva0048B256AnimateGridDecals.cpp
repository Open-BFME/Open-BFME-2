// cl: /DNDEBUG /MD /GX
// ?rva0048B256@DynamicShroudClearingRangeUpdate@@QAEXXZ @0x0048B256 233B: animateGridDecals.
// Donor Generals/Code/.../DynamicShroudClearingRangeUpdate.cpp animateGridDecals:
//  radius = m_current + ((total-countdown)*2), angle 0, opacity = 1-fade,
//  pos.x = ctr->x + sin(angle)*radius, pos.y = ctr->y + cos(angle)*radius,
//  pos.x -= (Int)pos.x%23, pos.y -= (Int)pos.y%23, setPosition/setOpacity,
//  angle += 2PI/30, do-while pointer loop like CreateGridDecals neighbour.
// Retail uses sin first (x) cos second (y), double sin/cos via ji 0x629216/0x62920A,
// ftol2, g_Va00BBB8D8 for 1.0f, step 0.20943951f Float-ref. Direct m_object+0x38,
// no getPosition call. Same class/flags as neighbours.
// The span doubling is retail `add eax,eax` (03 c0 after mov [ecx+0x28]/sub
// [ecx+0x24]), not `shl eax,1`. Measured on this toolchain: every direct form
// (`x*2`, `2*x`, `x+x`, `x<<1`, `x*=2`, unsigned, sizeof(short)) strength-reduces
// to `d1 e0`; only a copy into a second local followed by `d += v` keeps `03 c0`.
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);

typedef int Int;
struct Coord3D { float x; float y; float z; };
class RadiusDecal {
public:
	void setPosition(const Coord3D &pos);
	void setOpacity(float opacity);
private:
	const void *m_template;
	void *m_decal;
	unsigned char m_empty;
	unsigned char m_pad_09[3];
	float m_unknown0C;
};
class Thing;
class ModuleData;
class Object;
class UpdateModule {
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();
};
class DynamicShroudClearingRangeUpdate : public UpdateModule {
public:
	void rva0048B256();
private:
	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
	int m_state;
	int m_stateCountDown;
	int m_totalFrames;
	unsigned int m_growStartDeadline;
	unsigned int m_sustainDeadline;
	unsigned int m_shrinkStartDeadline;
	unsigned int m_doneForeverFrame;
	unsigned int m_changeIntervalCountdown;
	bool m_decalsCreated;
	unsigned char m_pad_41[3];
	float m_visionChangePerInterval;
	float m_nativeClearingRange;
	float m_currentClearingRange;
	RadiusDecal m_gridDecal[30];
};
void DynamicShroudClearingRangeUpdate::rva0048B256()
{
	const Coord3D *ctr = (const Coord3D *)((char *)m_object + 0x38);
	Coord3D pos;
	pos.z = 0.0f;
	int span = m_totalFrames - m_stateCountDown;
	int doubled = span;
	doubled += span;
	float radius = m_currentClearingRange + doubled;
	float angle = 0.0f;
	float opacity = 1.0f - (m_currentClearingRange / m_nativeClearingRange);
	RadiusDecal *decal = m_gridDecal;
	int left = 30;
	do {
		pos.x = ctr->x + sin(angle) * radius;
		pos.y = ctr->y + cos(angle) * radius;
		pos.x -= ((Int)pos.x) % 23;
		pos.y -= ((Int)pos.y) % 23;
		decal->setPosition(pos);
		decal->setOpacity(opacity);
		angle += 0.20943951f;
		++decal;
	} while (--left != 0);
}
