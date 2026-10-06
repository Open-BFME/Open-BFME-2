// Bare vtable installs: nine-byte __thiscall members with one shape:
//
//     mov eax,ecx / mov dword [eax],<VTABLE> / ret
//
// The vtable pointer at offset zero of `this` is overwritten with a literal
// vtable address and nothing else is touched. The classes are otherwise
// unidentified: each body gets a TU-local class with an explicit vtable
// member (no virtuals, so the compiler emits the immediate store instead
// of a vtable reference) and an address-derived name.
// No // cl: line (defaults match the frameless nine-byte shape).
extern "C" const void *const vtbl_00C7A84C[];  // ??_7Rva00602645@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C7A84C=??_7Rva00602645@@6B@")

extern "C" const void *const vtbl_00C18DFC[];  // ??_7Rva0037F57E@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C18DFC=??_7Rva0037F57E@@6B@")

extern "C" const void *const vtbl_00BBC8D4[];  // ??_7_Messages@_STL@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBC8D4=??_7_Messages@_STL@@6B@")
extern "C" const void *const vtbl_00C7A660[];  // ??_7Rva0060061A@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C7A660=??_7Rva0060061A@@6B@")

// vftable_map target evidence: 0x00BC7F74 has five slots installed at
// 0x00090FE0; 0x00C6573C has two slots installed at 0x005111FA. The map
// identifies every slot as a matched body, so keep the retail tables as
// relocations to those bodies rather than absolute image-address bytes.
extern "C" void bfmeVTableSlot_00BC7F74_0(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00BC7F74_0=?rva000910E1@Rva000910E1@@QAEPAXIH@Z")
extern "C" void bfmeVTableSlot_00BC7F74_1(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00BC7F74_1=?rva000910EE@Rva000910E1@@QAEXPAXH@Z")
extern "C" void bfmeVTableSlot_00BC7F74_2(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00BC7F74_2=?Create@GameFileClass@@UAEHXZ")
extern "C" void bfmeVTableSlot_00BC7F74_4(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00BC7F74_4=??_GRva0090771@@UAEPAXI@Z")
extern "C" void bfmeVTableSlot_00C6573C_0(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00C6573C_0=?rva00511620@Rva005114BD@@UAEXHH@Z")
extern "C" void bfmeVTableSlot_00C6573C_1(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00C6573C_1=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")

extern "C" const void *const vtbl_00BC7F74[] =
{
	reinterpret_cast<const void *>(bfmeVTableSlot_00BC7F74_0),
	reinterpret_cast<const void *>(bfmeVTableSlot_00BC7F74_1),
	reinterpret_cast<const void *>(bfmeVTableSlot_00BC7F74_2),
	reinterpret_cast<const void *>(bfmeVTableSlot_00BC7F74_2),
	reinterpret_cast<const void *>(bfmeVTableSlot_00BC7F74_4)
};

extern "C" const void *const vtbl_00C6573C[] =
{
	reinterpret_cast<const void *>(bfmeVTableSlot_00C6573C_0),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C6573C_1)
};

// vftable_map identifies all 35 slots in 0x00C594E0 as matched bodies.
// Keep the GrantUpgradeCreateModuleData ctor's pointer relocatable by mapping
// each slot to the corresponding linked body rather than the retail VA.
extern "C" void bfmeVTableSlot_00C594E0_0(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00C594E0_0=??_GGrantUpgradeCreateModuleData@@UAEPAXI@Z")
extern "C" void bfmeVTableSlot_00C594E0_1(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00C594E0_1=??1Coord2D@@QAE@XZ")
extern "C" void bfmeVTableSlot_00C594E0_2(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00C594E0_2=?name@Rva00065212Named@@QBEPBDXZ")
extern "C" void bfmeVTableSlot_00C594E0_3(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00C594E0_3=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
extern "C" void bfmeVTableSlot_00C594E0_4(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00C594E0_4=?IsCRC@Xfer@@UBE_NXZ")
extern "C" void bfmeVTableSlot_00C594E0_5(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00C594E0_5=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
extern "C" void bfmeVTableSlot_00C594E0_6(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00C594E0_6=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
extern "C" void bfmeVTableSlot_00C594E0_7(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00C594E0_7=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" void bfmeVTableSlot_00C594E0_8(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00C594E0_8=?onBuildComplete@ExperienceLevelCreate@@UAEXXZ")
extern "C" void bfmeVTableSlot_00C594E0_9(void);
#pragma comment(linker, "/alternatename:_bfmeVTableSlot_00C594E0_9=?Is_Valid@RegistryClass@@QAE_NXZ")

extern "C" const void *const vtbl_00C594E0[] =
{
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_0),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_1),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_2),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_3),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_4),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_4),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_4),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_4),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_4),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_4),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_4),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_4),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_4),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_4),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_5),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_4),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_6),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_6),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_6),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_6),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_6),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_6),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_6),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_6),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_6),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_6),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_6),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_6),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_6),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_6),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_7),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_1),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_8),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_1),
	reinterpret_cast<const void *>(bfmeVTableSlot_00C594E0_9)
};

#define BFME_VTABLE_INSTALL(NAME, VTABLE) \
	class NAME \
	{ \
	public: \
		NAME *init(); \
		void *m_vtable; \
	}; \
	NAME *NAME::init() \
	{ \
		m_vtable = VTABLE; \
		return this; \
	}

BFME_VTABLE_INSTALL(Rva00019EB0VTableInstall, reinterpret_cast<void *>(((unsigned int)vtbl_00BBC8D4)))
BFME_VTABLE_INSTALL(Rva000910D8VTableInstall, reinterpret_cast<void *>(((unsigned int)vtbl_00BC7F74)))
BFME_VTABLE_INSTALL(Rva0037F4C0VTableInstall, reinterpret_cast<void *>(((unsigned int)vtbl_00C18DFC)))
BFME_VTABLE_INSTALL(Rva005114BDVTableInstall, reinterpret_cast<void *>(((unsigned int)vtbl_00C6573C)))
BFME_VTABLE_INSTALL(Rva00600611VTableInstall, reinterpret_cast<void *>(((unsigned int)vtbl_00C7A660)))
BFME_VTABLE_INSTALL(Rva00602635VTableInstall, reinterpret_cast<void *>(((unsigned int)vtbl_00C7A84C)))

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:??0BfmeThingVTD@@QAE@XZ=?init@Rva00600611VTableInstall@@QAEPAV1@XZ")
