// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /GS-
//
// Rva00075A23Draw, retail 0x00075A23, 437 bytes. Banked partial (score 0.97,
// instruction scheduling) closed by tools/permute.py: statement order, operand
// order and one local's signedness; the body is otherwise the banked one.
// Fullscreen quad via dynamic VB ring (50x4 verts): guards on VB null and
// TheGlobalData+0xC60==-1, Set_Vertex_Buffer(NULL,0), AppendLock(VB,index*4,4,
// DISCARD-if-index-0-else-NOOVERWRITE), NDC positions (-1/1,0,1) with
// 0.5/w,0.5/h texel UVs (1.0/0.5/-1.0/0.0 literals), unlock, rebind VB,
// device SetVertexShader slot 0x15C with FVF global, Draw strip (index*4,2),
// index=(index+1)%50. Callers 0x00077392/0x0007BDAD/0x000FAC37/0x00111C05 push
// (w,h) __cdecl void; callees rowed Set_Vertex_Buffer/AppendLock/bfme00120700
// plus AppendLock-dtor pin; sibling 0x00075746 drawViewport shares VB/index/
// device/counter globals and /O1/SSE/G7 shape. /GX-/GS- for retail's no-EH
// no-cookie frame; /O1 for EBP frame and or/and -1/0 idioms.

struct GlobalDataCheck
{
	char m_pad[0xC60];
	int m_check;
};

extern class GlobalData *TheWritableGlobalData;

class VertexBufferClass
{
public:
	class AppendLockClass
	{
		VertexBufferClass *m_vb;
		void *m_verts;
		void *m_lock;
	public:
		AppendLockClass(VertexBufferClass *vb, unsigned start, unsigned range, int flags);
		~AppendLockClass();
		void *Get_Vertex_Array() const { return m_verts; }
	};
};

class DX8Wrapper
{
public:
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned stream);
	static void bfmeRva00120700(unsigned start, unsigned count);
};

struct DeviceVtbl
{
	void *m_pad[87];
	long (__stdcall *m_setVertexShader)(void *device, unsigned fvf);
	void *m_slot88;
	// Retail drawViewport calls this entry with the 0x144 FVF value.
	long (__stdcall *m_methodAt164)(void *device, unsigned value);
};

struct DeviceObj
{
	DeviceVtbl *m_vtable;
};

extern DeviceObj *g_deviceObj;
extern VertexBufferClass *g_vb;
extern int g_quadIndex;
extern unsigned g_fvfShader;
extern unsigned int number_of_DX8_calls;
VertexBufferClass *g_vb;
int g_quadIndex;
unsigned g_fvfShader;

struct Vec4
{
	float x, y, z, w;
};

struct QuadVertex
{
	Vec4 pos;
	int diffuse;
	float u, v;
};

void Rva00075A23Draw(int width, int height)
{
	if (g_vb == 0)
		return;
	if (-1 != (*(GlobalDataCheck **)&TheWritableGlobalData)->m_check)
		return;
	DX8Wrapper::Set_Vertex_Buffer(0, 0);
	int index = g_quadIndex;
	unsigned int flags = !index ? 0x2000 : 0x1000;
	{
		float invW = 1.0f / (float)width;
		VertexBufferClass::AppendLockClass lock(g_vb, index * 4, 4, flags);
		QuadVertex *v = (QuadVertex *)lock.Get_Vertex_Array();
		invW *= 0.5f;
		float invH = 1.0f / (float)height;
		invH *= 0.5f;
		Vec4 tmp;
		tmp.x = 1.0f;
		tmp.y = 1.0f;
		tmp.z = 0.0f;
		tmp.w = 1.0f;
		v[0].pos = tmp;
		tmp.x = 1.0f;
		tmp.y = -1.0f;
		tmp.z = 0.0f;
		tmp.w = 1.0f;
		v[0].diffuse |= -1;
		v[1].pos = tmp;
		v[1].diffuse |= -1;
		v[2].diffuse |= -1;
		tmp.x = -1.0f;
		tmp.y = 1.0f;
		tmp.z = 0.0f;
		tmp.w = 1.0f;
		v[0].u = 1.0f + invW;
		v[2].pos = tmp;
		v[0].v = invH;
		v[1].u = 1.0f + invW;
		v[1].v = 1.0f + invH;
		v[2].u = invW;
		v[2].v = invH;
		tmp.x = -1.0f;
		tmp.y = -1.0f;
		tmp.z = 0.0f;
		tmp.w = 1.0f;
		v[3].pos = tmp;
		v[3].diffuse |= -1;
		v[3].u = invW;
		v[3].v = 1.0f + invH;
	}
	DX8Wrapper::Set_Vertex_Buffer(g_vb, 0);
	g_deviceObj->m_vtable->m_setVertexShader(g_deviceObj, g_fvfShader);
	++number_of_DX8_calls;
	DX8Wrapper::bfmeRva00120700(g_quadIndex * 4, 2);
	if (++g_quadIndex >= 50)
		g_quadIndex = 0;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_deviceObj@@3PAUDeviceObj@@A=?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A")

// The target drawViewport takes an optional pair of floating extents.
struct Vector2
{
	float x;
	float y;
};

// Narrow virtual views from drawViewport's retail call sites: origin at +0x4c,
// width at +0x3c and height at +0x44.
class View
{
public:
	virtual void f00() = 0; virtual void f01() = 0; virtual void f02() = 0;
	virtual void f03() = 0; virtual void f04() = 0; virtual void f05() = 0;
	virtual void f06() = 0; virtual void f07() = 0; virtual void f08() = 0;
	virtual void f09() = 0; virtual void f10() = 0; virtual void f11() = 0;
	virtual void f12() = 0; virtual void f13() = 0; virtual void f14() = 0;
	virtual int getWidth() = 0;
	virtual void f16() = 0;
	virtual int getHeight() = 0;
	virtual void f18() = 0;
	virtual void getOrigin(int *x, int *y) = 0;
};

// The alternate UV extent comes from Display's width and height virtuals at
// +0x40 and +0x44. Retail converts these as unsigned extents.
class Display
{
public:
	virtual void f00() = 0; virtual void f01() = 0; virtual void f02() = 0;
	virtual void f03() = 0; virtual void f04() = 0; virtual void f05() = 0;
	virtual void f06() = 0; virtual void f07() = 0; virtual void f08() = 0;
	virtual void f09() = 0; virtual void f10() = 0; virtual void f11() = 0;
	virtual void f12() = 0; virtual void f13() = 0; virtual void f14() = 0;
	virtual void f15() = 0;
	virtual unsigned int getWidth() = 0;
	virtual unsigned int getHeight() = 0;
};

extern View *TheTacticalView;
extern Display *TheDisplay;

class W3DShaderManager
{
public:
	static void drawViewport(int color, bool useExplicitDimensions, const Vector2 *dimensions);
};

// The clean BFME1 donor draws the same colored TacticalView quad from a stack
// vertex array. Retail keeps the method and ABI, adds an optional UV extent,
// and uses the adjacent 50-quad AppendLock ring represented above.
void W3DShaderManager::drawViewport(int color, bool useExplicitDimensions, const Vector2 *dimensions)
{
	if (g_vb == 0)
		return;
	if (-1 != (*(GlobalDataCheck **)&TheWritableGlobalData)->m_check)
		return;

	DX8Wrapper::Set_Vertex_Buffer(0, 0);

	int xpos;
	int ypos;
	TheTacticalView->getOrigin(&xpos, &ypos);
	int width = TheTacticalView->getWidth();
	int height = TheTacticalView->getHeight();

	float uvWidth;
	float uvHeight;
	if (useExplicitDimensions) {
		uvWidth = dimensions->x;
		uvHeight = dimensions->y;
	} else if (TheDisplay != 0) {
		uvWidth = (float)TheDisplay->getWidth();
		uvHeight = (float)TheDisplay->getHeight();
	} else {
		uvWidth = 1.0f;
		uvHeight = 1.0f;
	}

	unsigned flags = !g_quadIndex ? 0x2000 : 0x1000;
	{
		VertexBufferClass::AppendLockClass lock(g_vb, g_quadIndex * 4, 4, flags);
		QuadVertex *v = (QuadVertex *)lock.Get_Vertex_Array();
		Vec4 tmp;
		tmp.x = (float)(xpos + width) - 0.5f;
		tmp.y = (float)(ypos + height) - 0.5f;
		tmp.z = 0.0f;
		tmp.w = 1.0f;
		v[0].pos = tmp;
		v[0].diffuse = color;
		v[0].u = (float)(xpos + width) / uvWidth;
		v[0].v = (float)(ypos + height) / uvHeight;

		tmp.x = (float)(xpos + width) - 0.5f;
		tmp.y = (float)ypos - 0.5f;
		tmp.z = 0.0f;
		tmp.w = 1.0f;
		v[1].pos = tmp;
		v[1].diffuse = color;
		v[1].u = (float)(xpos + width) / uvWidth;
		v[1].v = (float)ypos / uvHeight;

		tmp.x = (float)xpos - 0.5f;
		tmp.y = (float)(ypos + height) - 0.5f;
		tmp.z = 0.0f;
		tmp.w = 1.0f;
		v[2].pos = tmp;
		v[2].diffuse = color;
		v[2].u = (float)xpos / uvWidth;
		v[2].v = (float)(ypos + height) / uvHeight;

		tmp.x = (float)xpos - 0.5f;
		tmp.y = (float)ypos - 0.5f;
		tmp.z = 0.0f;
		tmp.w = 1.0f;
		v[3].pos = tmp;
		v[3].diffuse = color;
		v[3].u = (float)xpos / uvWidth;
		v[3].v = (float)ypos / uvHeight;
	}

	g_deviceObj->m_vtable->m_methodAt164(g_deviceObj, 0x144);
	++number_of_DX8_calls;
	DX8Wrapper::Set_Vertex_Buffer(g_vb, 0);
	DX8Wrapper::bfmeRva00120700(g_quadIndex * 4, 2);
	if (++g_quadIndex >= 50)
		g_quadIndex = 0;
}
