// cl: /MD
// ??0Rva005D57D3@@QAE@PAX@Z retail 0x005D57D3 24B
// Derived ctor: calls rowed base ??0Rva005AFE86@@QAE@PAX@Z 0x005AFE86
// with same arg, then overwrites base m_vtable slot at +0 with own
// vtable 0x00875B2C via plain store (non-polymorphic derived, no shift,
// no lea). Evidence: callers 0x005D5807 0x005D582D do new plus this ctor.
extern "C" const void *const __identifier("??_7Rva005D583C@@6B@")[];  // vftable 0x00C75B2C
// The retail table at RVA 0x00875B44: 6 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?rva005AFD89@Rva005AFE86@@UAEXHPBURva005AFD89Param@@@Z")();
void __identifier("?rva005AFCEC@Rva005AFCEC@@QAEXH@Z")();
void __identifier("??_GRva005D583C@@UAEPAXI@Z")();
void __identifier("?PopulatePlayerList@ChatWindowsOnlineRoom@@UAE_NXZ")();
void __identifier("?rva005D57EB@Rva005D57EB@@QAE_NABVUnicodeString@@PAVGameWindow@@@Z")();
void __identifier("?showPlayerTooltip@Rva005D5F86@@QAEXABVAsciiString@@@Z")();
}
extern "C" const void *const vtbl_00C75B44[6] = {
	(const void *)&__identifier("?rva005AFD89@Rva005AFE86@@UAEXHPBURva005AFD89Param@@@Z"), // slot 0 0x005AFD89
	(const void *)&__identifier("?rva005AFCEC@Rva005AFCEC@@QAEXH@Z"), // slot 1 0x005AFCEC
	(const void *)&__identifier("??_GRva005D583C@@UAEPAXI@Z"), // slot 2 0x005D58A8
	(const void *)&__identifier("?PopulatePlayerList@ChatWindowsOnlineRoom@@UAE_NXZ"), // slot 3 0x005D6AA4
	(const void *)&__identifier("?rva005D57EB@Rva005D57EB@@QAE_NABVUnicodeString@@PAVGameWindow@@@Z"), // slot 4 0x005D57EB
	(const void *)&__identifier("?showPlayerTooltip@Rva005D5F86@@QAEXABVAsciiString@@@Z"), // slot 5 0x005D5F86
};
// The retail table at RVA 0x00875B5C: 6 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?rva005AFD89@Rva005AFE86@@UAEXHPBURva005AFD89Param@@@Z")();
void __identifier("?rva005AFCEC@Rva005AFCEC@@QAEXH@Z")();
void __identifier("??_GRva005D583C@@UAEPAXI@Z")();
void __identifier("?PopulatePlayerList@ChatWindowsOnlineBuddy@@UAE_NXZ")();
void __identifier("?rva005D57EB@Rva005D57EB@@QAE_NABVUnicodeString@@PAVGameWindow@@@Z")();
void __identifier("?showPlayerTooltip@Rva005D5F86@@QAEXABVAsciiString@@@Z")();
}
extern "C" const void *const vtbl_00C75B5C[6] = {
	(const void *)&__identifier("?rva005AFD89@Rva005AFE86@@UAEXHPBURva005AFD89Param@@@Z"), // slot 0 0x005AFD89
	(const void *)&__identifier("?rva005AFCEC@Rva005AFCEC@@QAEXH@Z"), // slot 1 0x005AFCEC
	(const void *)&__identifier("??_GRva005D583C@@UAEPAXI@Z"), // slot 2 0x005D58A8
	(const void *)&__identifier("?PopulatePlayerList@ChatWindowsOnlineBuddy@@UAE_NXZ"), // slot 3 0x005D6C94
	(const void *)&__identifier("?rva005D57EB@Rva005D57EB@@QAE_NABVUnicodeString@@PAVGameWindow@@@Z"), // slot 4 0x005D57EB
	(const void *)&__identifier("?showPlayerTooltip@Rva005D5F86@@QAEXABVAsciiString@@@Z"), // slot 5 0x005D5F86
};

class EmptyBase005AFE86
{
public:
	EmptyBase005AFE86() {}
	~EmptyBase005AFE86();
};

class Rva005AFE86 : public EmptyBase005AFE86
{
public:
	Rva005AFE86(void *p);
private:
	const void *m_vtable;
	void *m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
};

class Rva005D57D3 : public Rva005AFE86
{
public:
	Rva005D57D3(void *p);
};

Rva005D57D3::Rva005D57D3(void *p) : Rva005AFE86(p)
{
	*(unsigned *)this = ((unsigned int)__identifier("??_7Rva005D583C@@6B@"));
}

class Rva005D5802 : public Rva005D57D3
{
public:
	Rva005D5802();
};

Rva005D5802::Rva005D5802() : Rva005D57D3((void *)1)
{
	*(unsigned *)this = ((unsigned int)vtbl_00C75B44);
}

class Rva005D5828 : public Rva005D57D3
{
public:
	Rva005D5828();
};

Rva005D5828::Rva005D5828() : Rva005D57D3((void *)0)
{
	*(unsigned *)this = ((unsigned int)vtbl_00C75B5C);
}
