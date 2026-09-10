// cl: /O1 /DNDEBUG /MD
//
// BfmeResetTextureRef::Release_Device_Resources, retail 0x00132CAD, 44 bytes.
// Dedicated TU so dx8wrapper.cpp Reset_Device cannot see this body.
// Releases the default-pool COM texture through IUnknown::Release (slot 8)
// and clears backend+8. /O1 for and-zero of the COM pointer.

struct BfmeResetComTexture
{
	virtual long __stdcall QueryInterface(void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

struct BfmeResetTextureBackend
{
	int unused0;
	int unused4;
	BfmeResetComTexture *com;
	char pad[0x50 - 0x0C];
	int pool;
};

struct BfmeResetTextureResource
{
	char pad[0x14];
	BfmeResetTextureBackend *backend;
};

struct BfmeResetTextureRef
{
	BfmeResetTextureResource *pointer;
	void Release_Device_Resources();
};

void BfmeResetTextureRef::Release_Device_Resources()
{
	BfmeResetTextureResource *res = pointer;
	if (res)
	{
		BfmeResetTextureBackend *backend = res->backend;
		if (backend)
		{
			if (backend->com)
			{
				if (backend->pool == 0)
				{
					backend->com->Release();
					res->backend->com = 0;
				}
			}
		}
	}
}
