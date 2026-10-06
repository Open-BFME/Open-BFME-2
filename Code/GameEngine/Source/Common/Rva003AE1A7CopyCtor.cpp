// cl: /DNDEBUG /MD /EHsc
// ??0Rva003AE1A7@@QAE@ABV0@@Z, retail 0x003AE1A7, 38 bytes.
// Derived V3-inline copy: calls rowed base ??0Rva003AE1CD@@QAE@ABV0@@Z at
// 0x003AE1CD then installs its own three vftables (+0 0x00C1CA40,
// +8 0x00C1CA3C, +0x0C 0x00C1CA2C). Caller is 0x003AE19C. Vtable dwords are
// DIR32 sites the gate takes from the target.

class Rva003AE1CD
{
public:
	Rva003AE1CD(const Rva003AE1CD &other);
};

// Rva003AE1A7_v0: matched references place it at VA 0xc1ca40 (retail .rdata value 112).
extern "C" char Rva003AE1A7_v0 = 112;
extern "C" char Rva003AE1A7_v8;
// Rva003AE1A7_v0C: matched references place it at VA 0xc1ca2c (retail .rdata value 72).
extern "C" char Rva003AE1A7_v0C = 72;

class Rva003AE1A7
{
public:
	__declspec(noinline) Rva003AE1A7(const Rva003AE1A7 &other);

private:
	void *m_v0;
	char m_pad04[4];
	void *m_v8;
	void *m_v0C;
};

Rva003AE1A7::Rva003AE1A7(const Rva003AE1A7 &that)
{
	const void *src = &that;
	((Rva003AE1CD *)this)->Rva003AE1CD::Rva003AE1CD(*(const Rva003AE1CD *)src);
	*(void **)this = &Rva003AE1A7_v0;
	*(void **)((char *)this + 8) = &Rva003AE1A7_v8;
	*(void **)((char *)this + 0x0C) = &Rva003AE1A7_v0C;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:_Rva003AE1A7_v8=??_7?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")
