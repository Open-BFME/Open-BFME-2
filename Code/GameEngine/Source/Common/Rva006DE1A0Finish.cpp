// cl: /EHsc /MD
// ??0Rva006DE1A0@@QAE@XZ @ 0x006DE1A0 107B Apt ctor with hash member.
// Evidence: neighbours AptValuePtrStackTop plus Rva006DE2B0Slot7 share /O2 /MD;
// EH prolog with scopetable so plus /EHsc; rowed AptNativeHash ctor 0x0070A740
// with 8; two vptr stores at 0x00CEA228 then 0x00CEB150 to the same slot, so the
// base chain is flag-only base -> vptr class holding the hash member -> the
// constructed class; flags and 0xFFFFFFDF plus m_1C zero; unblocks 5.
class AptNativeHash
{
public:
	AptNativeHash(int n);
};
extern "C" {
void __identifier("??_GRva006D71E0@@UAEPAXI@Z")();
void __identifier("??_GRva006DE2B0@@UAEPAXI@Z")();
void __identifier("?AddRef@AptValue@@UAEXXZ")();
void __identifier("?DestroyGCPointers@AptValueWithHash@@UAEXXZ")();
void __identifier("?Enum@IdList@ProfileFuncLevel@@QBE_NIAAVId@2@PAI@Z")();
void __identifier("?ForceDelete@AptValue@@UAEXXZ")();
void __identifier("?GetData@AptValueVector@@QAEPAPAPAVAptValue@@XZ")();
void __identifier("?Read@DebugIOOds@@UAEHPADH@Z")();
void __identifier("?RegisterReferences@AptValueWithHash@@UBEXXZ")();
void __identifier("?Release@AptValue@@UAEXXZ")();
void __identifier("?Rva0065CE90@MemoryPool@@YAPAVGeneralAllocator@Allocator@EA@@I@Z")();
void __identifier("?Rva006DE210@Rva006DE2B0@@UAEPAXHABVEAStringC@@@Z")();
void __identifier("?Rva006DE240@Rva006DE2B0@@UAE_NHABVEAStringC@@PAVAptRef@@@Z")();
void __identifier("?Rva0070DF60@Rva006DE2B0@@UAEXXZ")();
void __identifier("?_AptValidate@@YA_NXZ")();
void __identifier("?debugIgnoreLeaks@?$StringBase@D@@QAEXXZ")();
void __identifier("?m009EC960@Q1Receiver0134FAAC@@QAEXPAX@Z")();
void __identifier("?rva006CBCF0@Rva006CBCF0@@QAEXXZ")();
void __identifier("?rva0070DF80@Rva006DE2B0@@UAEXXZ")();
}

// Retail table at VA 0x00CEA228.
extern "C" const void *const g_aptValueBaseTable[15] = {
	(const void *)&__identifier("?AddRef@AptValue@@UAEXXZ"), // slot 0, RVA 0x006DCAC0
	(const void *)&__identifier("?Release@AptValue@@UAEXXZ"), // slot 1, RVA 0x006DCB20
	(const void *)&__identifier("?ForceDelete@AptValue@@UAEXXZ"), // slot 2, RVA 0x006CBCD0
	(const void *)&__identifier("?GetData@AptValueVector@@QAEPAPAPAVAptValue@@XZ"), // slot 3, RVA 0x006CBFD0
	(const void *)&__identifier("?_AptValidate@@YA_NXZ"), // slot 4, RVA 0x001826C0
	(const void *)&__identifier("?Rva0065CE90@MemoryPool@@YAPAVGeneralAllocator@Allocator@EA@@I@Z"), // slot 5, RVA 0x0065CE90
	(const void *)&__identifier("?m009EC960@Q1Receiver0134FAAC@@QAEXPAX@Z"), // slot 6, RVA 0x00180FD0
	(const void *)&__identifier("?Read@DebugIOOds@@UAEHPADH@Z"), // slot 7, RVA 0x0003FD80
	(const void *)&__identifier("?Enum@IdList@ProfileFuncLevel@@QBE_NIAAVId@2@PAI@Z"), // slot 8, RVA 0x006C8770
	(const void *)&__identifier("?rva006CBCF0@Rva006CBCF0@@QAEXXZ"), // slot 9, RVA 0x006CBCF0
	(const void *)&__identifier("?debugIgnoreLeaks@?$StringBase@D@@QAEXXZ"), // slot 10, RVA 0x0069E440
	(const void *)&__identifier("?DestroyGCPointers@AptValueWithHash@@UAEXXZ"), // slot 11, RVA 0x006DE150
	(const void *)&__identifier("?_AptValidate@@YA_NXZ"), // slot 12, RVA 0x001826C0
	(const void *)&__identifier("?RegisterReferences@AptValueWithHash@@UBEXXZ"), // slot 13, RVA 0x006DCC00
	(const void *)&__identifier("??_GRva006D71E0@@UAEPAXI@Z"), // slot 14, RVA 0x006D71E0
};

// Retail table at VA 0x00CEB150.
extern "C" const void *const g_aptValueHashTable[15] = {
	(const void *)&__identifier("?AddRef@AptValue@@UAEXXZ"), // slot 0, RVA 0x006DCAC0
	(const void *)&__identifier("?Release@AptValue@@UAEXXZ"), // slot 1, RVA 0x006DCB20
	(const void *)&__identifier("?ForceDelete@AptValue@@UAEXXZ"), // slot 2, RVA 0x006CBCD0
	(const void *)&__identifier("?GetData@AptValueVector@@QAEPAPAPAVAptValue@@XZ"), // slot 3, RVA 0x006CBFD0
	(const void *)&__identifier("?_AptValidate@@YA_NXZ"), // slot 4, RVA 0x001826C0
	(const void *)&__identifier("?Rva0065CE90@MemoryPool@@YAPAVGeneralAllocator@Allocator@EA@@I@Z"), // slot 5, RVA 0x0065CE90
	(const void *)&__identifier("?m009EC960@Q1Receiver0134FAAC@@QAEXPAX@Z"), // slot 6, RVA 0x00180FD0
	(const void *)&__identifier("?Rva006DE210@Rva006DE2B0@@UAEPAXHABVEAStringC@@@Z"), // slot 7, RVA 0x006DE210
	(const void *)&__identifier("?Rva006DE240@Rva006DE2B0@@UAE_NHABVEAStringC@@PAVAptRef@@@Z"), // slot 8, RVA 0x006DE240
	(const void *)&__identifier("?rva006CBCF0@Rva006CBCF0@@QAEXXZ"), // slot 9, RVA 0x006CBCF0
	(const void *)&__identifier("?debugIgnoreLeaks@?$StringBase@D@@QAEXXZ"), // slot 10, RVA 0x0069E440
	(const void *)&__identifier("?Rva0070DF60@Rva006DE2B0@@UAEXXZ"), // slot 11, RVA 0x0070DF60
	(const void *)&__identifier("?_AptValidate@@YA_NXZ"), // slot 12, RVA 0x001826C0
	(const void *)&__identifier("?rva0070DF80@Rva006DE2B0@@UAEXXZ"), // slot 13, RVA 0x0070DF80
	(const void *)&__identifier("??_GRva006DE2B0@@UAEPAXI@Z"), // slot 14, RVA 0x006DE280
};

// Retail's unwind at 0x007A8DA0 jumps to the destructor rowed under this name at 0x006D6340.
class __declspec(novtable) AptValueGC
{
public:
	AptValueGC() : m_04((m_04 & 1) | 0x38000030) {}
protected:
	virtual ~AptValueGC();
protected:
	int m_04;
};
class __declspec(novtable) Rva006DE1A0Mid : public AptValueGC
{
public:
	__forceinline Rva006DE1A0Mid() : m_08((*(const void *const **)this = g_aptValueBaseTable, 8)) { m_04 &= ~0x20; }
protected:
	AptNativeHash m_08;
	char m_pad[0x1C - 0x08 - 4];
	int m_1C;
};
class __declspec(novtable) Rva006DE1A0 : public Rva006DE1A0Mid
{
public:
	Rva006DE1A0();
};
Rva006DE1A0::Rva006DE1A0() { *(const void *const **)this = g_aptValueHashTable; m_1C = 0; }
