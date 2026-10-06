// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME-1 donor at cd32c8ef06dfb0d995b2f47e93e41622e4447092:
// Rva007F1DE0DerivedCtors.cpp. The mapped BFME2 targets below each install
// vptrs at +0/+4 and copy the constructor argument to +8; class names and
// shared payload interpretation remain donor-derived.

class __declspec(novtable) Rva007F1DE0BaseA
{
public:
	virtual void primary();
};

class Rva007F1DE0BaseB
{
public:
	virtual void secondary();
	void *m_payload;
	Rva007F1DE0BaseB(void *payload) : m_payload(payload) {}
};

#define BFME_DERIVED_CTOR(RVA) \
class Rva##RVA##Object : public Rva007F1DE0BaseA, public Rva007F1DE0BaseB \
{ \
public: \
	Rva##RVA##Object(void *payload); \
	virtual void primary(); \
	virtual void secondary(); \
}; \
Rva##RVA##Object::Rva##RVA##Object(void *payload) : Rva007F1DE0BaseB(payload) {}

BFME_DERIVED_CTOR(007F1DE0)
BFME_DERIVED_CTOR(007F2680)
BFME_DERIVED_CTOR(007F2F80)
BFME_DERIVED_CTOR(007FAE20)
BFME_DERIVED_CTOR(007FC150)

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?secondary@Rva007F1DE0BaseB@@UAEXXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")
#pragma comment(linker, "/alternatename:?secondary@Rva007F2680Object@@UAEXXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")
#pragma comment(linker, "/alternatename:?primary@Rva007F2680Object@@UAEXXZ=??_GGen007F2E30@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?secondary@Rva007F2F80Object@@UAEXXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")
#pragma comment(linker, "/alternatename:?primary@Rva007F2F80Object@@UAEXXZ=??_GGen007F33E0@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?secondary@Rva007FAE20Object@@UAEXXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")
#pragma comment(linker, "/alternatename:?primary@Rva007FAE20Object@@UAEXXZ=??_GGen007FBAF0@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?secondary@Rva007FC150Object@@UAEXXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")
#pragma comment(linker, "/alternatename:?primary@Rva007FC150Object@@UAEXXZ=??_GGen007F1BF0@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?secondary@Rva007F1DE0Object@@UAEXXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")
#pragma comment(linker, "/alternatename:?primary@Rva007F1DE0Object@@UAEXXZ=??_GGen007F2120@@UAEPAXI@Z")
