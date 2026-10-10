// ?Rva0008103AAdjust@@YAXPAM@Z
// partial score=0.9159846301633046 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ?Rva0008103AAdjust@@YAXPAM@Z
// partial score=0.99 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
// Effect-parameter callbacks bound by the name dispatcher at 0x000806F3. Each
// is a cdecl (effect, handle) function whose address the dispatcher stores
// after a strcmp against a shader parameter name, and each ends in
// ID3DXEffect::SetVector (vtable slot 34, +0x88) with a four-float local, the
// shape of W3DTerrainFXVectorParams.cpp.
//
// Target facts: the dispatcher stores 0x00080858 for "Mean", then 0x000808F3,
// 0x00080988 and 0x00080A1D for "Bases03X", "Bases03Y" and "Bases03Z", the
// next three for "Bases47X/Y/Z" and the last three for "Bases811X/Y/Z". The
// X, Y and Z callbacks call the getters at 0x00308325, 0x00308417 and
// 0x00308509 with the group index 0, 1 or 2 pushed, so each getter serves one
// axis and the index picks the group of four. The object is the pointer at
// +0x260 of the global at VA 0x00DE2000 (W3DGCData00DE2000, the ledger's name
// there); 0x003093F6 is called on it first, and the time argument is
// WW3D::SyncTime (VA 0x00DEC3CC) * 0.001 * the int at VA 0x00DBA4E8.
// Callback names come from those parameter strings; class, method and field
// names are address-derived.
//
// ?Rva00080858Mean@@YAXPAUID3DXEffect@@PBD@Z       @0x00080858 155B
// ?Rva000808F3Bases03X@@YAXPAUID3DXEffect@@PBD@Z   @0x000808F3 149B (and eight siblings)

typedef const char *D3DXHANDLE;

struct Rva000806F3Vector4
{
	float x, y, z, w;
};

struct ID3DXEffect
{
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33();
	virtual long __stdcall SetVector(D3DXHANDLE parameter, const Rva000806F3Vector4 *vector);
};

class WW3D
{
public:
	static unsigned int Get_Sync_Time( void ) { return SyncTime; }

private:
	static unsigned int SyncTime;
};

extern int g_00DBA4E8;

class Rva003093F6Bases
{
public:
	void rva003093F6();
	Rva000806F3Vector4 rva0030822F(float time);
	Rva000806F3Vector4 rva00308325(float time, int group);
	Rva000806F3Vector4 rva00308417(float time, int group);
	Rva000806F3Vector4 rva00308509(float time, int group);
};

struct Rva000806F3Owner
{
	char m_pad000[0x260];
	Rva003093F6Bases *m_260;
};

extern void *W3DGCData00DE2000;


static __forceinline float SumV(const Rva000806F3Vector4&q){return q.x+q.y+q.z+q.w;}
extern float g_00BC7078;
extern float g_Va007C26F0;
void __cdecl Rva0008103AAdjust(float *v)
{
	Rva003093F6Bases *bases = W3DGCData00DE2000 ? ((Rva000806F3Owner *)W3DGCData00DE2000)->m_260 : 0;
	if (!bases)
		return;
	float time = (WW3D::Get_Sync_Time() / 1000.0f) * g_00DBA4E8;
	bases->rva003093F6();
	{
		v[0] -= SumV(bases->rva00308325(time, 0)) * g_Va007C26F0;
	}
	{
		v[0] -= SumV(bases->rva00308325(time, 1)) * g_Va007C26F0;
	}
	{
		v[1] -= SumV(bases->rva00308417(time, 0)) * g_Va007C26F0;
	}
	{
		v[1] -= SumV(bases->rva00308417(time, 1)) * g_Va007C26F0;
	}
	{
		v[2] -= SumV(bases->rva00308509(time, 0)) * g_Va007C26F0;
	}
	{
		Rva000806F3Vector4 q = bases->rva00308509(time, 1);
		float k = g_Va007C26F0;
		float sc = g_00BC7078;
		float v2 = v[2] - (q.x + q.y + q.z + q.w) * k;
		v[2] = v2;
		_ReadWriteBarrier();
		float v0 = (v[0] - k) * sc;
		v[0] = v0;
		v2 = (v2 - k) * sc;
		v[2] = v2;
		float v1 = (v[1] - k) * sc;
		v[1] = v1;
		v[3] = v[3] * sc;
	}
}
