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
extern "C" const void *const __identifier("??_7Rva00602645@@6B@")[];  // vftable 0x00C7A84C

extern "C" const void *const __identifier("??_7Rva0037F57E@@6B@")[];  // vftable 0x00C18DFC

extern "C" const void *const __identifier("??_7_Messages@_STL@@6B@")[];  // vftable 0x00BBC8D4
extern "C" const void *const __identifier("??_7Rva0060061A@@6B@")[];  // vftable 0x00C7A660

// vftable_map target evidence: 0x00BC7F74 has five slots installed at
// 0x00090FE0; 0x00C6573C has two slots installed at 0x005111FA. The map
// identifies every slot as a matched body, so keep the retail tables as
// relocations to those bodies rather than absolute image-address bytes.
extern "C" void __identifier("?allocate@Rva000910E1@@QAEPAXIH@Z")(void);
extern "C" void __identifier("?deallocate@Rva000910E1@@QAEXPAXH@Z")(void);
extern "C" void __identifier("?Create@GameFileClass@@UAEHXZ")(void);
extern "C" void __identifier("??_GRva0090771@@UAEPAXI@Z")(void);
extern "C" void __identifier("?rva00511620@Rva005114BD@@UAEXHH@Z")(void);
extern "C" void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")(void);

extern "C" const void *const vtbl_00BC7F74[] =
{
	reinterpret_cast<const void *>(__identifier("?allocate@Rva000910E1@@QAEPAXIH@Z")),
	reinterpret_cast<const void *>(__identifier("?deallocate@Rva000910E1@@QAEXPAXH@Z")),
	reinterpret_cast<const void *>(__identifier("?Create@GameFileClass@@UAEHXZ")),
	reinterpret_cast<const void *>(__identifier("?Create@GameFileClass@@UAEHXZ")),
	reinterpret_cast<const void *>(__identifier("??_GRva0090771@@UAEPAXI@Z"))
};

extern "C" const void *const vtbl_00C6573C[] =
{
	reinterpret_cast<const void *>(__identifier("?rva00511620@Rva005114BD@@UAEXHH@Z")),
	reinterpret_cast<const void *>(__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"))
};

// vftable_map identifies all 35 slots in 0x00C594E0 as matched bodies.
// Keep the GrantUpgradeCreateModuleData ctor's pointer relocatable by mapping
// each slot to the corresponding linked body rather than the retail VA.
extern "C" void __identifier("??_GGrantUpgradeCreateModuleData@@UAEPAXI@Z")(void);
extern "C" void __identifier("??1Coord2D@@QAE@XZ")(void);
extern "C" void __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")(void);
extern "C" void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")(void);
extern "C" void __identifier("?IsCRC@Xfer@@UBE_NXZ")(void);
extern "C" void __identifier("?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")(void);
extern "C" void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")(void);
extern "C" void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")(void);
extern "C" void __identifier("?onBuildComplete@ExperienceLevelCreate@@UAEXXZ")(void);
extern "C" void __identifier("?Is_Valid@RegistryClass@@QAE_NXZ")(void);

extern "C" const void *const vtbl_00C594E0[] =
{
	reinterpret_cast<const void *>(__identifier("??_GGrantUpgradeCreateModuleData@@UAEPAXI@Z")),
	reinterpret_cast<const void *>(__identifier("??1Coord2D@@QAE@XZ")),
	reinterpret_cast<const void *>(__identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")),
	reinterpret_cast<const void *>(__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")),
	reinterpret_cast<const void *>(__identifier("?IsCRC@Xfer@@UBE_NXZ")),
	reinterpret_cast<const void *>(__identifier("?IsCRC@Xfer@@UBE_NXZ")),
	reinterpret_cast<const void *>(__identifier("?IsCRC@Xfer@@UBE_NXZ")),
	reinterpret_cast<const void *>(__identifier("?IsCRC@Xfer@@UBE_NXZ")),
	reinterpret_cast<const void *>(__identifier("?IsCRC@Xfer@@UBE_NXZ")),
	reinterpret_cast<const void *>(__identifier("?IsCRC@Xfer@@UBE_NXZ")),
	reinterpret_cast<const void *>(__identifier("?IsCRC@Xfer@@UBE_NXZ")),
	reinterpret_cast<const void *>(__identifier("?IsCRC@Xfer@@UBE_NXZ")),
	reinterpret_cast<const void *>(__identifier("?IsCRC@Xfer@@UBE_NXZ")),
	reinterpret_cast<const void *>(__identifier("?IsCRC@Xfer@@UBE_NXZ")),
	reinterpret_cast<const void *>(__identifier("?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")),
	reinterpret_cast<const void *>(__identifier("?IsCRC@Xfer@@UBE_NXZ")),
	reinterpret_cast<const void *>(__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")),
	reinterpret_cast<const void *>(__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")),
	reinterpret_cast<const void *>(__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")),
	reinterpret_cast<const void *>(__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")),
	reinterpret_cast<const void *>(__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")),
	reinterpret_cast<const void *>(__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")),
	reinterpret_cast<const void *>(__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")),
	reinterpret_cast<const void *>(__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")),
	reinterpret_cast<const void *>(__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")),
	reinterpret_cast<const void *>(__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")),
	reinterpret_cast<const void *>(__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")),
	reinterpret_cast<const void *>(__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")),
	reinterpret_cast<const void *>(__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")),
	reinterpret_cast<const void *>(__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")),
	reinterpret_cast<const void *>(__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")),
	reinterpret_cast<const void *>(__identifier("??1Coord2D@@QAE@XZ")),
	reinterpret_cast<const void *>(__identifier("?onBuildComplete@ExperienceLevelCreate@@UAEXXZ")),
	reinterpret_cast<const void *>(__identifier("??1Coord2D@@QAE@XZ")),
	reinterpret_cast<const void *>(__identifier("?Is_Valid@RegistryClass@@QAE_NXZ"))
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

BFME_VTABLE_INSTALL(Rva00019EB0VTableInstall, reinterpret_cast<void *>(((unsigned int)__identifier("??_7_Messages@_STL@@6B@"))))
BFME_VTABLE_INSTALL(Rva000910D8VTableInstall, reinterpret_cast<void *>(((unsigned int)vtbl_00BC7F74)))
BFME_VTABLE_INSTALL(Rva0037F4C0VTableInstall, reinterpret_cast<void *>(((unsigned int)__identifier("??_7Rva0037F57E@@6B@"))))
BFME_VTABLE_INSTALL(Rva005114BDVTableInstall, reinterpret_cast<void *>(((unsigned int)vtbl_00C6573C)))
BFME_VTABLE_INSTALL(Rva00600611VTableInstall, reinterpret_cast<void *>(((unsigned int)__identifier("??_7Rva0060061A@@6B@"))))
BFME_VTABLE_INSTALL(Rva00602635VTableInstall, reinterpret_cast<void *>(((unsigned int)__identifier("??_7Rva00602645@@6B@"))))
