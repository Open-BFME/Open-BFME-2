// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?Reset_Polys@Render2DSentenceClass@@QAEXXZ @ 0x00154EC0 (38B).
// Retail iterates DynamicVectorClass<RendererDataStruct> (Vector at +0x38,
// ActiveCount at +0x44) and calls Render2DClass::Reset at 0x00119F00 directly.
// The WW3D2 reference header declares Render2DClass::Reset virtual, which would
// emit a vtable-slot call ([edx+4]); the retail direct call at 0x00154ED6 proves
// Reset is non-virtual in BFME2. This TU therefore declares it non-virtual and
// the REL32 resolves against the pinned 0x00119F00 body.
class Render2DClass
{
public:
	void Reset();
};

class SurfaceClass;

struct RendererDataStruct
{
	Render2DClass *Renderer;
	SurfaceClass *Surface;
};

// DynamicVectorClass<RendererDataStruct> layout: vptr +0, Vector +4,
// VectorMax +8, IsValid +0xC, IsAllocated +0xD, pad to +0x10, ActiveCount
// +0x10, GrowthStep +0x14. Both accessors are in-class inline, matching the
// reference header.
class RendererVector
{
public:
	int Count() const { return ActiveCount; }
	RendererDataStruct &operator[](int index) { return Vector[index]; }

private:
	void *m_vptr;
	RendererDataStruct *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	char m_pad[2];
	int ActiveCount;
	int GrowthStep;
};

// Render2DSentenceClass prefix: vptr at +0; SentenceData and PendingSurfaces
// occupy +4..+0x33, so Renderers begins at +0x34.
class Render2DSentenceClass
{
public:
	void Reset_Polys();

private:
	void *m_vptr;
	char m_prefix[0x30];
	RendererVector Renderers;
};

void Render2DSentenceClass::Reset_Polys()
{
	for (int index = 0; index < Renderers.Count(); index++) {
		Renderers[index].Renderer->Reset();
	}
}
