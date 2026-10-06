// cl: /DNDEBUG /MD
// ?Rva0070B4F0GetString@@YAPAV..., retail 0x0070B4F0 (58B).
// StringPool constant accessor: asserts saConstant[eSC] non-empty via StringPool.inl:42 then returns its address.
// Evidence: own immediates "saConstant[eSC].IsEmpty() == false" + ".\string\StringPool.inl" line 0x2A;
// callers at 0x006DC9E7/0x006DCA07 push one int index and consume the return as EAStringC this;
// 0x0070A740 asserts StringPool::GetString(SC___proto__)->GetLength and UpdateHashValue.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class EAStringC
{
	void *m_pData;
public:
	bool IsEmpty() const;
};

extern EAStringC saConstantAtE18388[]; // 0x00E18388

EAStringC *Rva0070B4F0GetString(int eSC)
{
	EAStringC *entry = &saConstantAtE18388[eSC];
	if (entry->IsEmpty()) {
		g_bfmeAptAssertAtE17734("saConstant[eSC].IsEmpty() == false", ".\\string\\StringPool.inl", 0x2A);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {
			__asm int 3
		}
	}
	return entry;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?saConstantAtE18388@@3PAVEAStringC@@A=_bfmeObjDAE")
