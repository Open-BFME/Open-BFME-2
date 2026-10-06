// cl: /MD
// ??0Rva005D57D3@@QAE@PAX@Z retail 0x005D57D3 24B
// Derived ctor: calls rowed base ??0Rva005AFE86@@QAE@PAX@Z 0x005AFE86
// with same arg, then overwrites base m_vtable slot at +0 with own
// vtable 0x00875B2C via plain store (non-polymorphic derived, no shift,
// no lea). Evidence: callers 0x005D5807 0x005D582D do new plus this ctor.
extern "C" const void *const vtbl_00C75B2C[];  // ??_7Rva005D583C@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C75B2C=??_7Rva005D583C@@6B@")

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
	*(unsigned *)this = ((unsigned int)vtbl_00C75B2C);
}

class Rva005D5802 : public Rva005D57D3
{
public:
	Rva005D5802();
};

Rva005D5802::Rva005D5802() : Rva005D57D3((void *)1)
{
	*(unsigned *)this = 0x00C75B44;
}

class Rva005D5828 : public Rva005D57D3
{
public:
	Rva005D5828();
};

Rva005D5828::Rva005D5828() : Rva005D57D3((void *)0)
{
	*(unsigned *)this = 0x00C75B5C;
}
