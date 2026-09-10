// ?Release_Device_Resources@BfmeResetShaderRef@@QAEXXZ
// partial score=0.88 date=2026-09-09
// cl: /O2 /DNDEBUG /MD
//
// BfmeResetShaderRef::Release_Device_Resources, retail 0x00151553, 34 bytes.
// Dedicated TU so dx8wrapper.cpp Reset_Device cannot see this body.
// Guards resource, backend at +0x14, and effect at backend+4, then stdcall
// ID3DXEffect::OnLostDevice at vtable +0x114.

struct BfmeResetEffect9
{
	virtual long __stdcall _v00() = 0;
	virtual long __stdcall _v01() = 0;
	virtual long __stdcall _v02() = 0;
	virtual long __stdcall _v03() = 0;
	virtual long __stdcall _v04() = 0;
	virtual long __stdcall _v05() = 0;
	virtual long __stdcall _v06() = 0;
	virtual long __stdcall _v07() = 0;
	virtual long __stdcall _v08() = 0;
	virtual long __stdcall _v09() = 0;
	virtual long __stdcall _v0a() = 0;
	virtual long __stdcall _v0b() = 0;
	virtual long __stdcall _v0c() = 0;
	virtual long __stdcall _v0d() = 0;
	virtual long __stdcall _v0e() = 0;
	virtual long __stdcall _v0f() = 0;
	virtual long __stdcall _v10() = 0;
	virtual long __stdcall _v11() = 0;
	virtual long __stdcall _v12() = 0;
	virtual long __stdcall _v13() = 0;
	virtual long __stdcall _v14() = 0;
	virtual long __stdcall _v15() = 0;
	virtual long __stdcall _v16() = 0;
	virtual long __stdcall _v17() = 0;
	virtual long __stdcall _v18() = 0;
	virtual long __stdcall _v19() = 0;
	virtual long __stdcall _v1a() = 0;
	virtual long __stdcall _v1b() = 0;
	virtual long __stdcall _v1c() = 0;
	virtual long __stdcall _v1d() = 0;
	virtual long __stdcall _v1e() = 0;
	virtual long __stdcall _v1f() = 0;
	virtual long __stdcall _v20() = 0;
	virtual long __stdcall _v21() = 0;
	virtual long __stdcall _v22() = 0;
	virtual long __stdcall _v23() = 0;
	virtual long __stdcall _v24() = 0;
	virtual long __stdcall _v25() = 0;
	virtual long __stdcall _v26() = 0;
	virtual long __stdcall _v27() = 0;
	virtual long __stdcall _v28() = 0;
	virtual long __stdcall _v29() = 0;
	virtual long __stdcall _v2a() = 0;
	virtual long __stdcall _v2b() = 0;
	virtual long __stdcall _v2c() = 0;
	virtual long __stdcall _v2d() = 0;
	virtual long __stdcall _v2e() = 0;
	virtual long __stdcall _v2f() = 0;
	virtual long __stdcall _v30() = 0;
	virtual long __stdcall _v31() = 0;
	virtual long __stdcall _v32() = 0;
	virtual long __stdcall _v33() = 0;
	virtual long __stdcall _v34() = 0;
	virtual long __stdcall _v35() = 0;
	virtual long __stdcall _v36() = 0;
	virtual long __stdcall _v37() = 0;
	virtual long __stdcall _v38() = 0;
	virtual long __stdcall _v39() = 0;
	virtual long __stdcall _v3a() = 0;
	virtual long __stdcall _v3b() = 0;
	virtual long __stdcall _v3c() = 0;
	virtual long __stdcall _v3d() = 0;
	virtual long __stdcall _v3e() = 0;
	virtual long __stdcall _v3f() = 0;
	virtual long __stdcall _v40() = 0;
	virtual long __stdcall _v41() = 0;
	virtual long __stdcall _v42() = 0;
	virtual long __stdcall _v43() = 0;
	virtual long __stdcall _v44() = 0;
	virtual long __stdcall OnLostDevice() = 0;
};

struct BfmeResetShaderBackend
{
	int unused0;
	BfmeResetEffect9 *effect;
};

struct BfmeResetShaderResource
{
	char pad[0x14];
	BfmeResetShaderBackend *backend;
};

static __forceinline void __fastcall shader_on_lost(BfmeResetShaderBackend *backend)
{
	if (backend->effect)
	{
		BfmeResetEffect9 *effect = backend->effect;
		effect->OnLostDevice();
	}
}

struct BfmeResetShaderRef
{
	BfmeResetShaderResource *pointer;
	void Release_Device_Resources();
};

void BfmeResetShaderRef::Release_Device_Resources()
{
	BfmeResetShaderResource *resource = pointer;
	if (resource)
	{
		BfmeResetShaderBackend *backend = resource->backend;
		if (backend)
			shader_on_lost(backend);
	}
}
