// cl: /O1 /DNDEBUG /MD /EHsc
//
// Drawable vtable 0x007FB0B4 slots 13 and 14 (slots 8-12 are the rowed
// first-module forwarders in Drawable_rva00272971.cpp), both walks of the
// null-terminated draw-module array at +0x14C like the rowed broadcaster
// 0x00272A02. Slot and method names are unknown; argument types come from
// the bodies. Written as the neighbours' non-virtual views.

class DrawModuleInterfaceForRva271C38
{
public:
	virtual void s00() = 0;
	virtual void s04() = 0;
	virtual void s08() = 0;
	virtual void s0C() = 0;
	virtual void s10() = 0;
	virtual void s14() = 0;
	virtual void s18() = 0;
	virtual void s1C() = 0;
	virtual void s20() = 0;
	virtual void s24() = 0;
	virtual void s28() = 0;
	virtual void s2C() = 0;
	virtual void s30() = 0;
	virtual void s34() = 0;
	virtual void s38() = 0;
	virtual void s3C() = 0;
	virtual void s40() = 0;
	virtual void s44() = 0;
	virtual void s48() = 0;
	virtual void s4C() = 0;
	virtual void s50() = 0;
	virtual void s54() = 0;
	virtual void s58() = 0;
	virtual void s5C() = 0;
	virtual void s60() = 0;
	virtual void s64() = 0;
	virtual void s68() = 0;
	virtual void s6C() = 0;
	virtual void s70() = 0;
	virtual void s74() = 0;
	virtual void s78() = 0;
	virtual void s7C() = 0;
	virtual void s80() = 0;
	virtual void s84() = 0;
	virtual void s88() = 0;
	virtual void s8C() = 0;
	virtual void s90() = 0;
	virtual void s94() = 0;
	virtual void s98() = 0;
	virtual void s9C() = 0;
	virtual void sA0() = 0;
	virtual void sA4() = 0;
	virtual void sA8() = 0;
	virtual void sAC() = 0;
	virtual void sB0() = 0;
	virtual void sB4() = 0;
	virtual void sB8() = 0;
	virtual void sBC() = 0;
	virtual void sC0(int value) = 0;
};

class DrawModuleForRva271095
{
public:
	virtual void s00() = 0;
	virtual void s04() = 0;
	virtual void s08() = 0;
	virtual void s0C() = 0;
	virtual void s10() = 0;
	virtual void s14() = 0;
	virtual void s18() = 0;
	virtual void s1C() = 0;
};

class DrawModuleForRva271C38
{
public:
	virtual void s00() = 0;
	virtual void s04() = 0;
	virtual void s08() = 0;
	virtual void s0C() = 0;
	virtual void s10() = 0;
	virtual void s14() = 0;
	virtual void s18() = 0;
	virtual void s1C() = 0;
	virtual void s20() = 0;
	virtual void s24() = 0;
	virtual void s28() = 0;
	virtual void s2C() = 0;
	virtual void s30() = 0;
	virtual void s34() = 0;
	virtual void s38() = 0;
	virtual void s3C() = 0;
	virtual void s40() = 0;
	virtual void s44() = 0;
	virtual void s48() = 0;
	virtual void s4C() = 0;
	virtual void s50() = 0;
	virtual void s54() = 0;
	virtual void s58() = 0;
	virtual void s5C() = 0;
	virtual void s60() = 0;
	virtual void s64() = 0;
	virtual void s68() = 0;
	virtual void s6C() = 0;
	virtual void s70() = 0;
	virtual void s74() = 0;
	virtual void s78() = 0;
	virtual void s7C() = 0;
	virtual void s80() = 0;
	virtual void s84() = 0;
	virtual void s88() = 0;
	virtual void s8C() = 0;
	virtual void s90() = 0;
	virtual void s94() = 0;
	virtual void s98() = 0;
	virtual void s9C() = 0;
	virtual void sA0() = 0;
	virtual DrawModuleInterfaceForRva271C38 *sA4() = 0;
};

class Drawable
{
public:
	void rva00271095();
	void rva00271C38(int value);
private:
	unsigned char m_pad[0x14C];
	void **m_drawModules;	// +0x14C
};

// ?rva00271095@Drawable@@QAEXXZ, retail 0x00271095, 25 bytes, slot 13:
// every module's slot 7 (+0x1C).
void Drawable::rva00271095()
{
	for (DrawModuleForRva271095 **p = (DrawModuleForRva271095 **)m_drawModules; *p; ++p)
		(*p)->s1C();
}

// ?rva00271C38@Drawable@@QAEXH@Z, retail 0x00271C38, 48 bytes, slot 14:
// each module's slot 41 (+0xA4) interface, when it has one, gets the
// argument through its slot 48 (+0xC0).
void Drawable::rva00271C38(int value)
{
	for (DrawModuleForRva271C38 **p = (DrawModuleForRva271C38 **)m_drawModules; *p; ++p)
	{
		DrawModuleInterfaceForRva271C38 *di = (*p)->sA4();
		if (di)
			di->sC0(value);
	}
}
