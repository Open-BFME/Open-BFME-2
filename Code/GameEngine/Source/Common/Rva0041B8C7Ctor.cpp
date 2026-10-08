// cl: /MD
//
// ??0Rva0041B8C7@@QAE@XZ, retail 0x0041B8B5, 18 bytes.
// Ctor beside the rowed dtor 0x0041B8C7 in GameEngineDeletingBaseDerived.cpp.
// Calls rowed BFME2NativeNetwork::baseConstruct 0x001B4E63 then stores
// vtable 0x00C3AE60 then returns this. No members beyond the 0xC base.
// Evidence: callee rowed baseConstruct; vtable matches dtor row; caller at
// 0x0022FA81; honest address-derived class name.

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

extern const void *const g_00C3AE60[];

class Rva0041B8C7
{
	int m_pad00[3];
public:
	Rva0041B8C7();
};

Rva0041B8C7::Rva0041B8C7()
{
	((BFME2NativeNetwork *)this)->baseConstruct();
	*(const void **)this = g_00C3AE60;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00C3AE60@@3QBQBXB=??_7Rva0041B8C7@@6B@")
