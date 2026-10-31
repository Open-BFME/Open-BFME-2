// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva0014F480@@QAE@ABV0@@Z retail 0x0014F480 33B, ??0Rva0014F4A1@@QAE@ABV0@@Z retail 0x0014F4A1 33B, ??0Rva0014F4C2@@QAE@ABV0@@Z retail 0x0014F4C2 33B: derived copy ctors calling base ??0Rva0014F401@@QAE@ABV0@@Z (rowed 0x0014F401) then storing derived vtables 0x007D3854 0x007D385C 0x007D3864 and copying dword at +4. Callers include 0x0014F5AB 0x0014F8E4 0x00150282 families. Same /O1 empty-copy with member recipe.

class Rva0014F401
{
public:
	virtual void dummy();
	Rva0014F401(const Rva0014F401 &other);
};

class Rva0014F480 : public Rva0014F401
{
public:
	Rva0014F480(const Rva0014F480 &other);
	virtual void dummy();
	int m_04;
};

Rva0014F480::Rva0014F480(const Rva0014F480 &other)
	: Rva0014F401(other)
	, m_04(other.m_04)
{
}

extern "C" const void* const __identifier("??_7SourceNamespace_DirectionalLight@FXShaderParameterSourceNamespaceSAS@@6B@")[ ];

class __declspec(novtable) Rva0014F4A1 : public Rva0014F401
{
public:
	Rva0014F4A1(const Rva0014F4A1 &other);
	virtual void dummy();
	int m_04;
};

Rva0014F4A1::Rva0014F4A1(const Rva0014F4A1 &other)
	: Rva0014F401(other)
{
	*(const void **)this = __identifier("??_7SourceNamespace_DirectionalLight@FXShaderParameterSourceNamespaceSAS@@6B@");
	m_04 = other.m_04;
}

class Rva0014F4C2 : public Rva0014F401
{
public:
	Rva0014F4C2(const Rva0014F4C2 &other);
	virtual void dummy();
	int m_04;
};

Rva0014F4C2::Rva0014F4C2(const Rva0014F4C2 &other)
	: Rva0014F401(other)
	, m_04(other.m_04)
{
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?dummy@Rva0014F480@@UAEXXZ=??_GRva000E14BD@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?dummy@Rva0014F4C2@@UAEXXZ=??_GRva000E14BD@@UAEPAXI@Z")
