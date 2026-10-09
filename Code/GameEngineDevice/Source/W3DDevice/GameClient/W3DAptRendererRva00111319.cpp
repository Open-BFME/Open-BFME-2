// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ?bfmeBegin982C@BfmeHub982@@QAEXXZ retail 0x00111319..0x001116E2 (969 bytes).
// A W3DAptRenderer state restore (placeholder pin name kept): it flushes the
// pending batch through the pinned W3DAptRenderer 0x00110CFE (as
// BeginTriangleList 0x00111224 does) then inlines DX8Wrapper::Set_Transform
// twice: D3DTS_VIEW from the matrix at +0x50 (transposed into the view half
// of the render-state block at 0x00DEE804 and render_state_changed gains
// VIEW_CHANGED and loses VIEW_IDENTITY) and D3DTS_PROJECTION from the matrix
// at +0x90 (transposed into ProjectionMatrix and copied to
// DeviceProjectionMatrix with ZFar and ZNear cleared then uploaded through
// device slot +0xB0 counted by number_of_DX8_calls). With a mode at +0x8 and
// a stencil buffer it clears D3DRS_STENCILENABLE through the rowed
// Set_DX8_Render_State 0x0006615F. Mode 0/2/1 then select the rowed state
// setters 0x00118B50/0x00118BA0/0x00118C20; every mode but 0 also publishes
// the +0xC stencil reference into the rowed global 0x00DB5FB0. The WB twin
// 0x009799F0 (callsite evidence) has the same flush and the two inlined
// Set_Transform switches (2 and 3). Unrowed thunk 0x001116E2 jumps here.
#include "matrix4.h"
#include "d3d8.h"

extern Matrix4 BFME2World;
extern unsigned number_of_DX8_calls;
extern int g_00DB5FB0;
void Rva00118B50();
void Rva00118BA0();
void Rva00118C20();

class BfmeHub982;

class DX8Wrapper
{
	friend class BfmeHub982;

public:
	static bool Has_Stencil();
	static void Set_DX8_Render_State(unsigned long state, unsigned value);

protected:
	static unsigned render_state_changed;
	static Matrix4 ProjectionMatrix;
	static Matrix4 DeviceProjectionMatrix;
	static float ZFar;
	static float ZNear;
	static IDirect3DDevice8 *D3DDevice;

	enum
	{
		VIEW_CHANGED = 2,
		VIEW_IDENTITY = 0x80000
	};

	static Matrix4 &RenderStateView() { return (&BFME2World)[1]; }

	static __forceinline void Set_Transform(D3DTRANSFORMSTATETYPE transform, const Matrix4 &m)
	{
		switch ((int)transform)
		{
		case D3DTS_VIEW:
			RenderStateView() = m.Transpose();
			render_state_changed |= (unsigned)VIEW_CHANGED;
			render_state_changed &= ~(unsigned)VIEW_IDENTITY;
			break;
		case D3DTS_PROJECTION:
			ProjectionMatrix = m.Transpose();
			DeviceProjectionMatrix = ProjectionMatrix;
			ZFar = 0.0f;
			ZNear = 0.0f;
			D3DDevice->SetTransform(D3DTS_PROJECTION, &DeviceProjectionMatrix);
			number_of_DX8_calls++;
			break;
		}
	}
};

class W3DAptRenderer
{
public:
	void rva00110CFE();
};

class BfmeHub982
{
public:
	void bfmeBegin982C();

private:
	bool m_stateDirty;
	bool m_textureDirty;
	char m_pad2[2];
	void *m_texture;
	int m_mode;
	int m_stencilRef;
	Matrix4 m_matrix;
	Matrix4 m_view;
	Matrix4 m_projection;
};

void BfmeHub982::bfmeBegin982C()
{
	reinterpret_cast<W3DAptRenderer *>(this)->rva00110CFE();
	DX8Wrapper::Set_Transform(D3DTS_VIEW, m_view);
	DX8Wrapper::Set_Transform(D3DTS_PROJECTION, m_projection);
	if (m_mode != 0 && DX8Wrapper::Has_Stencil())
		DX8Wrapper::Set_DX8_Render_State(0x34, 0);
	if (m_mode == 0)
	{
		Rva00118B50();
	}
	else
	{
		if (m_mode == 2)
			Rva00118BA0();
		else if (m_mode == 1)
			Rva00118C20();
		g_00DB5FB0 = m_stencilRef;
	}
}
