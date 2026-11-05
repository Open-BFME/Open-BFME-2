// cl: /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?Reset@Render2DSentenceClass@@UAEXXZ at 0x00155A20 173B: BFME2 thread-guarded Reset.
// Donor: reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/render2dsentence.cpp Render2DSentenceClass::Reset.
// Evidence: callees Release_Pending_Surfaces 0x00154F70 and Reset_Sentence_Data 0x00154F10 (rowed),
// thread Lock 0x0011F520 / Assert 0x00120F50 (rowed), renderer erase 0x001558D0 (rowed Gen_0093E730::rva001558D0),
// renderer dtor pin 0x00119D00, CurSurface release via ops slot 2, Cursor at +0x60, MonoSpaced +0x80, ParseHotKey +0xAD.

class SurfaceClass;

struct SurfaceOps
{
	void (__stdcall *unused)(SurfaceClass *surface);
	void (__stdcall *add_ref)(SurfaceClass *surface);
	void (__stdcall *release_ref)(SurfaceClass *surface);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
class SurfaceClass
{
public:
	SurfaceOps *ops;
};

// The renderer dtor 0x00119D00 is rowed as Render2DClass::~Render2DClass
// (RendererDataStruct's renderer); the call below is a direct one.
#include "Render2DClass.h"

#include <new>

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();

#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"

// Renderers vector: 8-byte {renderer, surface} records with COM second word,
// same layout as Gen_0093E730 whose erase (rva001558D0) retail reuses here.
struct RendererDataStruct
{
	Render2DClass *Renderer;
	SurfaceClass *Surface;
};

class Gen_0093E730
{
public:
	virtual bool Equal(const Gen_0093E730 &that) const;
	virtual bool Unused();
	virtual bool Resize(int size, const RendererDataStruct *array = 0);

	int Count() const { return active_count; }
	RendererDataStruct &operator[](int index) { return vector[index]; }
	bool rva001558D0(int index);

private:
	RendererDataStruct *vector;
	int vector_max;
	bool is_valid;
	bool is_allocated;
	char pad[2];
	int active_count;
	int growth_step;
};

#include "../../../../../reference/shims/wwmath/Vector2.h"

class Vector2i
{
public:
	int X;
	int Y;
};

#include "../WWMath/RectClass.h"

// upstream layout: reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
#include "Render2DSentenceClass.h"

void Render2DSentenceClass::Reset()
{
	BFMEDX8DeviceLock guard;
	if (CurSurface != 0) {
		CurSurface->ops->release_ref(CurSurface);
		CurSurface = 0;
	}
	while (reinterpret_cast<Gen_0093E730 *>(field34)->Count() > 0) {
		Render2DClass *renderer = (*reinterpret_cast<Gen_0093E730 *>(field34))[0].Renderer;
		if (renderer != 0) {
			renderer->Render2DClass::~Render2DClass();
			::operator delete(renderer);
		}
		reinterpret_cast<Gen_0093E730 *>(field34)->rva001558D0(0);
	}
	reinterpret_cast<Vector2 *>(&Cursor)->Set(0.0f, 0.0f);
	MonoSpaced = false;
	ParseHotKey = false;
	Release_Pending_Surfaces();
	Reset_Sentence_Data();
}
