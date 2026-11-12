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

// Rva003AEB9C_v0: retail table 0x00C1CE64 (9 slots). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRva003ACB6F@@UAEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?clone@Rva003AEB9C@@QBEPAV1@XZ")();
void __identifier("?xfer@Rva0055EF39@@UAEXPAVXfer@@@Z")();
void __identifier("?get@Rva00094A9CFloatField@@QBEMXZ")();
void __identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ")();
void __identifier("?rva003ABD6B@Rva003ABD6B@@QAE?AURva00SlotFloat2@@XZ")();
void __identifier("?get@Rva0045310DByteField@@QBEEXZ")();
void __identifier("?get@Rva003ABD51ByteField@@QBEEXZ")();
extern const void *const Rva003AEB9C_v0[9] = {
	(const void *)&__identifier("??_GRva003ACB6F@@UAEPAXI@Z"), //  0 0x003AD3F7
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?clone@Rva003AEB9C@@QBEPAV1@XZ"), //  2 0x003AEB65
	(const void *)&__identifier("?xfer@Rva0055EF39@@UAEXPAVXfer@@@Z"), //  3 0x0055EF39
	(const void *)&__identifier("?get@Rva00094A9CFloatField@@QBEMXZ"), //  4 0x00094A9C
	(const void *)&__identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ"), //  5 0x004F5FA3
	(const void *)&__identifier("?rva003ABD6B@Rva003ABD6B@@QAE?AURva00SlotFloat2@@XZ"), //  6 0x003ABD6B
	(const void *)&__identifier("?get@Rva0045310DByteField@@QBEEXZ"), //  7 0x0045310D
	(const void *)&__identifier("?get@Rva003ABD51ByteField@@QBEEXZ")  //  8 0x003ABD51
};
}
// The compiler table the data ledger binds at this address:
extern "C" char __identifier("??_7Rva003ABD20@@6BRva003AEEB3Slot14@@@");
// The compiler table the data ledger binds at this address:
extern "C" char __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$02@1@@");
// The compiler table the data ledger binds at this address:
extern "C" char __identifier("??_7Rva003ABD20@@6B@");

// Rva003AEC5E_v0: retail table 0x00C1CE98 (12 slots). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRva003ACB6F@@UAEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?clone@Rva003AEC5E@@QBEPAV1@XZ")();
void __identifier("?DoXfer@Rva003ABD81@@UAEXAAVXfer@@@Z")();
void __identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ")();
void __identifier("?getSolution@PartitionSolver@@QBEABV?$vector@U?$pair@W4ObjectID@@W41@@_STL@@V?$allocator@U?$pair@W4ObjectID@@W41@@_STL@@@2@@_STL@@XZ")();
void __identifier("?getAttackSoundsVector@AudioEventInfo@@QBEABV?$vector@URvaPair001D9F62@@V?$allocator@URvaPair001D9F62@@@_STL@@@_STL@@XZ")();
void __identifier("?get@Rva003F3FE4LeaField@@QBEPAXXZ")();
void __identifier("?get@Rva0008BCC8LeaField@@QBEPAXXZ")();
void __identifier("?get@Rva0053998CLeaField@@QBEPAXXZ")();
void __identifier("?get@Rva003EE704LeaField@@QBEPAXXZ")();
void __identifier("?getSoundsVector@AudioEventInfo@@QBEABV?$vector@URvaPair001D9F62@@V?$allocator@URvaPair001D9F62@@@_STL@@@_STL@@XZ")();
extern const void *const Rva003AEC5E_v0[12] = {
	(const void *)&__identifier("??_GRva003ACB6F@@UAEPAXI@Z"), //  0 0x003AD3F7
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?clone@Rva003AEC5E@@QBEPAV1@XZ"), //  2 0x003AEC24
	(const void *)&__identifier("?DoXfer@Rva003ABD81@@UAEXAAVXfer@@@Z"), //  3 0x0055F710
	(const void *)&__identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ"), //  4 0x004F5FA3
	(const void *)&__identifier("?getSolution@PartitionSolver@@QBEABV?$vector@U?$pair@W4ObjectID@@W41@@_STL@@V?$allocator@U?$pair@W4ObjectID@@W41@@_STL@@@2@@_STL@@XZ"), //  5 0x002A9808
	(const void *)&__identifier("?getAttackSoundsVector@AudioEventInfo@@QBEABV?$vector@URvaPair001D9F62@@V?$allocator@URvaPair001D9F62@@@_STL@@@_STL@@XZ"), //  6 0x001D96F0
	(const void *)&__identifier("?get@Rva003F3FE4LeaField@@QBEPAXXZ"), //  7 0x003F3FE4
	(const void *)&__identifier("?get@Rva0008BCC8LeaField@@QBEPAXXZ"), //  8 0x0008BCC8
	(const void *)&__identifier("?get@Rva0053998CLeaField@@QBEPAXXZ"), //  9 0x0053998C
	(const void *)&__identifier("?get@Rva003EE704LeaField@@QBEPAXXZ"), // 10 0x003EE704
	(const void *)&__identifier("?getSoundsVector@AudioEventInfo@@QBEABV?$vector@URvaPair001D9F62@@V?$allocator@URvaPair001D9F62@@@_STL@@@_STL@@XZ")  // 11 0x001D96EC
};
}
// The compiler table the data ledger binds at this address:
extern "C" char __identifier("??_7Rva003ABD81@@6BRva003AEEB3Slot14@@@");
// The compiler table the data ledger binds at this address:
extern "C" char __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$01@1@@");
// The compiler table the data ledger binds at this address:
extern "C" char __identifier("??_7Rva003ABD81@@6B@");

// Rva003AEF6E_v0: retail table 0x00C1CF38 (12 slots). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRva003ACB6F@@UAEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?clone@Rva003AEF6E@@QBEPAV1@XZ")();
void __identifier("?rva00562233@Rva00562233@@UAEXPAVXfer@@@Z")();
void __identifier("?get@Rva003EE704LeaField@@QBEPAXXZ")();
void __identifier("?get@Rva0030BBA5LeaField@@QBEPAXXZ")();
void __identifier("?get@Rva00308156LeaGetter@@QBEPAXXZ")();
void __identifier("?get@Rva003ABE71LeaGetter@@QBEPAXXZ")();
void __identifier("?get@Rva003ABE78LeaGetter@@QBEPAXXZ")();
extern const void *const Rva003AEF6E_v0[12] = {
	(const void *)&__identifier("??_GRva003ACB6F@@UAEPAXI@Z"), //  0 0x003AD3F7
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?clone@Rva003AEF6E@@QBEPAV1@XZ"), //  2 0x003AEF34
	(const void *)&__identifier("?rva00562233@Rva00562233@@UAEXPAVXfer@@@Z"), //  3 0x00562233
	(const void *)&__identifier("?get@Rva003EE704LeaField@@QBEPAXXZ"), //  4 0x003EE704
	(const void *)&__identifier("?get@Rva0030BBA5LeaField@@QBEPAXXZ"), //  5 0x0030BBA5
	(const void *)&__identifier("?get@Rva00308156LeaGetter@@QBEPAXXZ"), //  6 0x00308156
	(const void *)&__identifier("?get@Rva003ABE71LeaGetter@@QBEPAXXZ"), //  7 0x003ABE71
	(const void *)&__identifier("?get@Rva003ABE78LeaGetter@@QBEPAXXZ"), //  8 0x003ABE78
	(const void *)&__identifier("?get@Rva00308156LeaGetter@@QBEPAXXZ"), //  9 0x00308156
	(const void *)&__identifier("?get@Rva003ABE71LeaGetter@@QBEPAXXZ"), // 10 0x003ABE71
	(const void *)&__identifier("?get@Rva003ABE78LeaGetter@@QBEPAXXZ")  // 11 0x003ABE78
};
}
// Rva003AEF6E_v14: retail table 0x00C1C640 (1 slot). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("?rva003ACA93@Rva003ACA93Host@@UAEPAVRva003ACA93Object@@I@Z")();
extern const void *const Rva003AEF6E_v14[1] = {
	(const void *)&__identifier("?rva003ACA93@Rva003ACA93Host@@UAEPAVRva003ACA93Object@@I@Z")  //  0 0x003ACA93
};
}
extern "C" char __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$01@1@@");
// Rva003AEF6E_v1c: retail table 0x00C1CF28 (4 slots). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_ERva003ABD81@@WBM@AEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?name@Rva003ABE7FNamed@@QBEPBDXZ")();
void __identifier("?rva00562233@Rva00562233@@WBM@AEXPAVXfer@@@Z")();
extern const void *const Rva003AEF6E_v1c[4] = {
	(const void *)&__identifier("??_ERva003ABD81@@WBM@AEPAXI@Z"), //  0 0x003ABDC0
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?name@Rva003ABE7FNamed@@QBEPBDXZ"), //  2 0x003ABE7F
	(const void *)&__identifier("?rva00562233@Rva00562233@@WBM@AEXPAVXfer@@@Z")  //  3 0x003ABE85
};
}

// The compiler table the data ledger binds at this address:
extern "C" char __identifier("??_7Rva005FEAD0DefaultModule7@FXParticleSystem@@6BRva005FEA50PrimaryBase@1@@");
// The compiler table the data ledger binds at this address:
extern "C" char __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot1@@@");
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");
// The compiler table the data ledger binds at this address:
extern "C" const void *const __identifier("??_7Rva005FEAD0DefaultModule7@FXParticleSystem@@6BRva005FEA50WindInfoBase@1@@")[4];

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
	*(void **)this = (void *)Rva003AEB9C_v0;
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
	*(void **)this = (void *)Rva003AEC5E_v0;
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
	*(void **)this = (void *)Rva003AEF6E_v0;
	*(void **)((char *)this + 0x14) = (void *)Rva003AEF6E_v14;
	*(void **)((char *)this + 0x18) = &__identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$01@1@@");
	*(void **)((char *)this + 0x1C) = (void *)Rva003AEF6E_v1c;
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
	*(void **)((char *)this + 0x18) = &__identifier("??_7Rva003F498ACallback@@6B@");
	*(const void **)((char *)this + 0x1C) = __identifier("??_7Rva005FEAD0DefaultModule7@FXParticleSystem@@6BRva005FEA50WindInfoBase@1@@");
}
// _Rva003AED3E_v18: the global at VA 0xc1c780 is ??_7Rva003F498ACallback@@6B@.

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
