// cl: /DNDEBUG /MD
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

extern int g_009BA4E8;

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

void Rva00080858Mean(ID3DXEffect *effect, D3DXHANDLE handle)
{
	Rva000806F3Vector4 value;
	value.x = 0.0f;
	value.y = 0.0f;
	value.z = 1.0f;
	value.w = 0.0f;
	Rva003093F6Bases *bases = W3DGCData00DE2000 ? ((Rva000806F3Owner *)W3DGCData00DE2000)->m_260 : 0;
	if (bases)
	{
		float time = (WW3D::Get_Sync_Time() / 1000.0f) * g_009BA4E8;
		bases->rva003093F6();
		value = bases->rva0030822F(time);
	}
	effect->SetVector(handle, &value);
}

#define RVA000806F3_BASES_PARAM( NAME, GETTER, GROUP )                    \
	void NAME(ID3DXEffect *effect, D3DXHANDLE handle)                     \
	{                                                                     \
		Rva000806F3Vector4 value;                                         \
		value.x = 0.0f;                                                   \
		value.y = 0.0f;                                                   \
		value.z = 0.0f;                                                   \
		value.w = 0.0f;                                                   \
		Rva003093F6Bases *bases = W3DGCData00DE2000 ? ((Rva000806F3Owner *)W3DGCData00DE2000)->m_260 : 0; \
		if (bases)                                                        \
		{                                                                 \
			float time = (WW3D::Get_Sync_Time() / 1000.0f) * g_009BA4E8;     \
			bases->rva003093F6();                                         \
			value = bases->GETTER(time, GROUP);                           \
		}                                                                 \
		effect->SetVector(handle, &value);                                \
	}

RVA000806F3_BASES_PARAM( Rva000808F3Bases03X, rva00308325, 0 )
RVA000806F3_BASES_PARAM( Rva00080988Bases03Y, rva00308417, 0 )
RVA000806F3_BASES_PARAM( Rva00080A1DBases03Z, rva00308509, 0 )
RVA000806F3_BASES_PARAM( Rva00080AB2Bases47X, rva00308325, 1 )
RVA000806F3_BASES_PARAM( Rva00080B47Bases47Y, rva00308417, 1 )
RVA000806F3_BASES_PARAM( Rva00080BDCBases47Z, rva00308509, 1 )
RVA000806F3_BASES_PARAM( Rva00080C71Bases811X, rva00308325, 2 )
RVA000806F3_BASES_PARAM( Rva00080D06Bases811Y, rva00308417, 2 )
RVA000806F3_BASES_PARAM( Rva00080D9BBases811Z, rva00308509, 2 )

// Second binding, dispatcher 0x00080E30: the same ten parameter names bind
// the callbacks below, each scaled by the 1.6f at VA 0x00BC7078. "Mean"
// passes the vector to 0x0008103A (pinned) and "Bases03X" to the rowed
// Rva000812E1Scale. The other eight (0x00081324..0x00081913, 217B each)
// expand the scale inline. Retail loads each component and then multiplies
// by the held scale. Every spelling tried here folds the local into mulss,
// so those eight are banked, not landed (see reverse/re_attempts.log).
// The out-of-line Scale body sits between 0x00081242 and 0x00081324, so it
// was probably defined in this unit after its first caller.
//
// ?Rva00080F95Mean2@@YAXPAUID3DXEffect@@PBD@Z      @0x00080F95 165B
// ?Rva00081242Bases03X2@@YAXPAUID3DXEffect@@PBD@Z  @0x00081242 159B

extern float g_00BC7078;
void __cdecl Rva000812E1Scale(float *v);
void __cdecl Rva0008103AAdjust(float *v);

void Rva00080F95Mean2(ID3DXEffect *effect, D3DXHANDLE handle)
{
	Rva000806F3Vector4 value;
	value.x = 0.0f;
	value.y = 0.0f;
	value.z = 1.0f;
	value.w = 0.0f;
	Rva003093F6Bases *bases = W3DGCData00DE2000 ? ((Rva000806F3Owner *)W3DGCData00DE2000)->m_260 : 0;
	if (bases)
	{
		float time = (WW3D::Get_Sync_Time() / 1000.0f) * g_009BA4E8;
		bases->rva003093F6();
		value = bases->rva0030822F(time);
		Rva0008103AAdjust(&value.x);
	}
	effect->SetVector(handle, &value);
}

void Rva00081242Bases03X2(ID3DXEffect *effect, D3DXHANDLE handle)
{
	Rva000806F3Vector4 value;
	value.x = 0.0f;
	value.y = 0.0f;
	value.z = 0.0f;
	value.w = 0.0f;
	Rva003093F6Bases *bases = W3DGCData00DE2000 ? ((Rva000806F3Owner *)W3DGCData00DE2000)->m_260 : 0;
	if (bases)
	{
		float time = (WW3D::Get_Sync_Time() / 1000.0f) * g_009BA4E8;
		bases->rva003093F6();
		value = bases->rva00308325(time, 0);
		Rva000812E1Scale(&value.x);
	}
	effect->SetVector(handle, &value);
}
