// cl: /MD
// ??1Rva003AF50D@@UAE@XZ, retail 0x003A983C, 22 bytes.
// Destructor for the Rva003AF50D particle module-info base (copy rowed at
// 0x003AF50D in ParticleModuleInfoCopyCtors.cpp): restores the second-base
// vtable 0x00C1C780 at +0x14 via the null-guarded neg/lea/sbb/and idiom,
// then tail-jmps to the rowed head-base dtor ??1DefaultModuleHeadBase@@UAE@XZ
// at 0x003A57E7. Layout matches the copy (head vptr +0, 12-byte smart at +4,
// int at +0x10, second vptr at +0x14). novtable suppresses the implicit
// derived store so only the manual +0x14 store remains, in retail order.
// Precedent: V3InlineTemplateDtor.cpp uses the same ternary for +8.
// Vtable 0x0081D420 slot 0 is the ??_G at 0x003AE492 which calls here.

extern "C" const void *const vtbl_00C1C780[];  // folded, 35 classes; via ??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C1C780=??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")

class RvaSmartPtr12
{
public:
	RvaSmartPtr12(const RvaSmartPtr12 &other);
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

class DefaultModuleHeadBase
{
public:
	virtual ~DefaultModuleHeadBase();
	RvaSmartPtr12 m_smart;
	int m_int10;
};

class __declspec(novtable) Rva003AF50D : public DefaultModuleHeadBase
{
public:
	virtual ~Rva003AF50D();
private:
	void *m_v14;
};

Rva003AF50D::~Rva003AF50D()
{
	unsigned char *b14 = this ? (unsigned char *)this + 0x14 : 0;
	*(volatile unsigned int *)b14 = ((unsigned int)vtbl_00C1C780);
}

// ??1Rva003A97E0@@UAE@XZ, retail 0x003A97E0, 5 bytes.
// Trivial derived dtor thunk: tail-jmps to the rowed base ??1Rva003AF50D@@UAE@XZ
// at 0x003A983C. novtable suppresses any derived vptr store so only the jmp
// remains. Called by the deleting dtor at 0x003AE73C and by Unwind funclets
// for the particle module-info copy cluster. Honest address name: no donor,
// vtable, or string proves a real class name. Precedent: ??1Rva006166B0List
// 5B tail-jmp to rowed GenericList dtor in WWLib/ini.cpp.

class __declspec(novtable) Rva003A97E0 : public Rva003AF50D
{
public:
	virtual ~Rva003A97E0();
};

Rva003A97E0::~Rva003A97E0()
{
}
