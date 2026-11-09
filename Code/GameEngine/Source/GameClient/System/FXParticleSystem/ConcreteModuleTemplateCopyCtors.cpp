// cl: /DNDEBUG /MD /GX- /Ob2

// Concrete module template copy constructors (retail 0x003AEB9C cluster).
// Each 45-byte wrapper delegates to its module's 91-byte template copy
// (rowed through the ledger) and installs its own four vftables. All vftable
// dwords are DIR32 sites the gate takes from the target; the call resolves
// through the ledger.

class Rva003AEBC9
{
public:
	Rva003AEBC9(const Rva003AEBC9 &other);
};

class Rva003AEC8B
{
public:
	Rva003AEC8B(const Rva003AEC8B &other);
};

class Rva003AEF9B
{
public:
	Rva003AEF9B(const Rva003AEF9B &other);
};

class Rva003AED6B
{
public:
	Rva003AED6B(const Rva003AED6B &other);
};

// Rva003AEB9C_v0: matched references place it at VA 0xc1ce64 (retail .rdata value -9).
extern "C" char Rva003AEB9C_v0 = -9;
// Rva003AEB9C_v14 gives way to the compiler table the data ledger binds there.
extern "C" char __identifier("??_7Rva003ABD20@@6BRva003AEEB3Slot14@@@");
// Rva003AEB9C_v18 gives way to the compiler table the data ledger binds there.
extern "C" char __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$02@1@@");
// Rva003AEB9C_v1c gives way to the compiler table the data ledger binds there.
extern "C" char __identifier("??_7Rva003ABD20@@6B@");

// Rva003AEC5E_v0: matched references place it at VA 0xc1ce98 (retail .rdata value -9).
extern "C" char Rva003AEC5E_v0 = -9;
// Rva003AEC5E_v14 gives way to the compiler table the data ledger binds there.
extern "C" char __identifier("??_7Rva003ABD81@@6BRva003AEEB3Slot14@@@");
// Rva003AEC5E_v18 gives way to the compiler table the data ledger binds there.
extern "C" char __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$01@1@@");
// Rva003AEC5E_v1c gives way to the compiler table the data ledger binds there.
extern "C" char __identifier("??_7Rva003ABD81@@6B@");

// Rva003AEF6E_v0: matched references place it at VA 0xc1cf38 (retail .rdata value -9).
extern "C" char Rva003AEF6E_v0 = -9;
// Rva003AEF6E_v14: matched references place it at VA 0xc1c640 (retail .rdata value -109).
extern "C" char Rva003AEF6E_v14 = -109;
extern "C" char __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$01@1@@");
// Rva003AEF6E_v1c: matched references place it at VA 0xc1cf28 (retail .rdata value -64).
extern "C" char Rva003AEF6E_v1c = -64;

// Rva003AED3E_v0 gives way to the compiler table the data ledger binds there.
extern "C" char __identifier("??_7Rva005FEAD0DefaultModule7@FXParticleSystem@@6BRva005FEA50PrimaryBase@1@@");
// Rva003AED3E_v14 gives way to the compiler table the data ledger binds there.
extern "C" char __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot1@@@");
extern "C" char __identifier("?vftable_0112B89C@@3HA");
// Rva003AED3E_v1c gives way to the compiler table the data ledger binds there.
extern "C" char __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot3@@@");

class Rva003AEB9C
{
public:
	__declspec(noinline) Rva003AEB9C(const Rva003AEB9C &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04: smart member + int, owned by the template copy
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1c; // +0x1C
};

// ??0Rva003AEB9C@@QAE@ABV0@@Z
Rva003AEB9C::Rva003AEB9C(const Rva003AEB9C &that)
{
	const void *src = &that;
	((Rva003AEBC9 *)this)->Rva003AEBC9::Rva003AEBC9(*(const Rva003AEBC9 *)src);
	*(void **)this = &Rva003AEB9C_v0;
	*(void **)((char *)this + 0x14) = &__identifier("??_7Rva003ABD20@@6BRva003AEEB3Slot14@@@");
	*(void **)((char *)this + 0x18) = &__identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$02@1@@");
	*(void **)((char *)this + 0x1C) = &__identifier("??_7Rva003ABD20@@6B@");
}

class Rva003AEC5E
{
public:
	__declspec(noinline) Rva003AEC5E(const Rva003AEC5E &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04: smart member + int, owned by the template copy
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1c; // +0x1C
};

// ??0Rva003AEC5E@@QAE@ABV0@@Z
Rva003AEC5E::Rva003AEC5E(const Rva003AEC5E &that)
{
	const void *src = &that;
	((Rva003AEC8B *)this)->Rva003AEC8B::Rva003AEC8B(*(const Rva003AEC8B *)src);
	*(void **)this = &Rva003AEC5E_v0;
	*(void **)((char *)this + 0x14) = &__identifier("??_7Rva003ABD81@@6BRva003AEEB3Slot14@@@");
	*(void **)((char *)this + 0x18) = &__identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$01@1@@");
	*(void **)((char *)this + 0x1C) = &__identifier("??_7Rva003ABD81@@6B@");
}

class Rva003AEF6E
{
public:
	__declspec(noinline) Rva003AEF6E(const Rva003AEF6E &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04: smart member + int, owned by the template copy
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1c; // +0x1C
};

// ??0Rva003AEF6E@@QAE@ABV0@@Z
Rva003AEF6E::Rva003AEF6E(const Rva003AEF6E &that)
{
	const void *src = &that;
	((Rva003AEF9B *)this)->Rva003AEF9B::Rva003AEF9B(*(const Rva003AEF9B *)src);
	*(void **)this = &Rva003AEF6E_v0;
	*(void **)((char *)this + 0x14) = &Rva003AEF6E_v14;
	*(void **)((char *)this + 0x18) = &__identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$01@1@@");
	*(void **)((char *)this + 0x1C) = &Rva003AEF6E_v1c;
}

class Rva003AED3E
{
public:
	__declspec(noinline) Rva003AED3E(const Rva003AED3E &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04: smart member + int, owned by the template copy
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1c; // +0x1C
};

// ??0Rva003AED3E@@QAE@ABV0@@Z
Rva003AED3E::Rva003AED3E(const Rva003AED3E &that)
{
	const void *src = &that;
	((Rva003AED6B *)this)->Rva003AED6B::Rva003AED6B(*(const Rva003AED6B *)src);
	*(void **)this = &__identifier("??_7Rva005FEAD0DefaultModule7@FXParticleSystem@@6BRva005FEA50PrimaryBase@1@@");
	*(void **)((char *)this + 0x14) = &__identifier("??_7Rva003AECE6@@6BRva003AECE6Slot1@@@");
	*(void **)((char *)this + 0x18) = &__identifier("?vftable_0112B89C@@3HA");
	*(void **)((char *)this + 0x1C) = &__identifier("??_7Rva003AECE6@@6BRva003AECE6Slot3@@@");
}
// _Rva003AED3E_v18: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
