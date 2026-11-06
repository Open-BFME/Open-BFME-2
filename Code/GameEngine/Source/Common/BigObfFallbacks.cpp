// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Obfuscated fallback callees of the BigObfHookWrappers.cpp hook wrappers, their two masking
// transforms (retail 0x003EFEB2, 0x00226156) and the operation functors they call.
//
// Every fallback and transform opens and closes with the protection marker blocks below. The
// marker references its own label (`mov eax, offset L1`), and an __asm block that references a label
// turns off optimization for the whole function. That is why these bodies keep every local in the frame,
// test constant conditions (`xor eax,eax; je`) and pop cdecl arguments with `pop ecx`, while
// the functors, which carry no marker, are /O1 leaves. Without optimization, named locals are laid out by
// name hash, not by declaration order, and compiler temporaries follow them. The single-letter names reproduce retail's
// frame. The two unused dwords at the bottom of each fallback frame are the functor's two named
// locals: the caller reserves a slot for an inline callee's locals even though it calls it out of line
// (a functor with one local leaves a 0x24 frame against retail's 0x20).
//
// Retail calls each functor thiscall (`lea ecx,[f]` on a zero-initialized byte) and sign-extends
// the short instantiations' result, so they are template member operators. Retail groups the
// operation code (0xe less, 1 second, 2 add, 0xd first, 0x11 greater-or-equal) with the functor
// it calls, and the type code (3 short, 5 int) with the instantiation type.

struct FallbackCtx
{
	char pad[0x14];
	unsigned int m_mask, m_18, m_1c, m_20, m_24, m_28, m_2c, m_30, m_34;
};

// The six fallback key contexts (names: reverse/name_agreed.csv), retail's initial bytes.
// Each getter in ConstIntGettersAddr.cpp returns one context's address.
FallbackCtx g_engineLoopIndexKeys = { { '\x41', '\x13', '\x23', '\x67', '\x84', '\x01', '\x00', '\x00', '\x01', '\x00', '\x00', '\x00', '\x01', '\x00', '\x00', '\x00', '\x01', '\x00', '\x00', '\x00' }, 0x5CAC5AC5, 0x29FDDBF3, 0x4BFD7FCD, 0x0742F06E, 0xE1B3EE35, 0x2371E3A6, 0x6ECEF435, 0xCC45E78D, 0x32E6B04C }; // RVA 0x009C2274
FallbackCtx g_loginEmailLengthKeys = { { '\x41', '\x13', '\x23', '\x67', '\x84', '\x01', '\x00', '\x00', '\x01', '\x00', '\x00', '\x00', '\x05', '\x00', '\x00', '\x00', '\x01', '\x00', '\x00', '\x00' }, 0x5CAC5AC5, 0xBBABB917, 0x49E737EF, 0x763A8C61, 0x24A14DC1, 0x71A29F83, 0x9D365BDA, 0x8EE5D6AA, 0x1780FC70 }; // RVA 0x009C2884
FallbackCtx g_nicknameCharIndexKeys = { { '\x41', '\x13', '\x23', '\x67', '\x84', '\x01', '\x00', '\x00', '\x01', '\x00', '\x00', '\x00', '\x08', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00' }, 0x5CAC5AC5, 0x7EE87841, 0x29C2AAC0, 0xCBA0C394, 0x9578B91A, 0xAFAC3592, 0x7BC3106F, 0x0ECF21BB, 0xC2F4139D }; // RVA 0x009C2D10
FallbackCtx g_gameSlotIndexKeys = { { '\x41', '\x13', '\x23', '\x67', '\x84', '\x01', '\x00', '\x00', '\x01', '\x00', '\x00', '\x00', '\x0d', '\x00', '\x00', '\x00', '\x01', '\x00', '\x00', '\x00' }, 0x5CAC5AC5, 0x52D0362D, 0x6F22478D, 0x550F6755, 0x5192767A, 0x7D5B191C, 0xFCB361B3, 0x2C66FCB9, 0x6ED933EB }; // RVA 0x009C34A4
FallbackCtx g_loginFieldLengthKeys = { { '\x41', '\x13', '\x23', '\x67', '\x84', '\x01', '\x00', '\x00', '\x01', '\x00', '\x00', '\x00', '\x1c', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00' }, 0x5CAC5AC5, 0x5B8F1DB7, 0x963DDCB4, 0xAF7ABE43, 0xC9E1121C, 0xC2AD42BA, 0xC3175136, 0xF3D7AEAA, 0x8D8FDF83 }; // RVA 0x009C4B60
FallbackCtx g_externHandlerIndexKeys = { { '\x41', '\x13', '\x23', '\x67', '\x84', '\x01', '\x00', '\x00', '\x01', '\x00', '\x00', '\x00', '\x20', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00' }, 0x5CAC5AC5, 0x5596E8DD, 0x77DC459F, 0x55ED9FE4, 0xD266FAB4, 0x4C067BF0, 0x3CB742FC, 0x02D16A90, 0x95D61099 }; // RVA 0x009C5170

int __cdecl Rva00226140Get(void);
int __cdecl Rva003EFE9AGet(void);
int __cdecl Rva00434091Get(void);
int __cdecl Rva0056DD52Get(void);
int __cdecl Rva0056DD58Get(void);
int __cdecl Rva0056DD5EGet(void);
int __cdecl Rva00225A93Get(int, int, int, int, int);

template<class T> struct ObfLess { T operator()(T a, T b) { T x = a; T y = b; return x < y; } };
template<class T> struct ObfGreaterEqual { T operator()(T a, T b) { T x = a; T y = b; return x >= y; } };
template<class T> struct ObfFirst { T operator()(T a, T b) { T x = a; T y = b; return x; } };
template<class T> struct ObfSecond { T operator()(T a, T b) { T x = a; T y = b; return y; } };
template<class T> struct ObfAdd { T operator()(T a, T b) { T x = a; T y = b; x += y; return x; } };

#define OBF_MARK_BEGIN __asm { __asm push eax __asm mov eax, 0xCFCECDCC __asm L1: __asm mov eax, offset L1 __asm mov eax, 1 __asm mov eax, 0 __asm mov eax, 0xCFCECDCC __asm pop eax }
#define OBF_MARK_END __asm { __asm push eax __asm mov eax, 0xCFCECDCC __asm mov eax, offset L1 __asm mov eax, 0 __asm mov eax, 0 __asm mov eax, 0xCECDCCCB __asm pop eax }

#define OBF_LOAD_KEYS(ctx) \
	unsigned int g = ((FallbackCtx *)(ctx))->m_mask; \
	unsigned int q = ((FallbackCtx *)(ctx))->m_18; \
	unsigned int f = ((FallbackCtx *)(ctx))->m_1c; \
	unsigned int u = ((FallbackCtx *)(ctx))->m_20; \
	unsigned int y = ((FallbackCtx *)(ctx))->m_24; \
	unsigned int w = ((FallbackCtx *)(ctx))->m_28; \
	unsigned int l = ((FallbackCtx *)(ctx))->m_2c; \
	unsigned int z = ((FallbackCtx *)(ctx))->m_30; \
	unsigned int v = ((FallbackCtx *)(ctx))->m_34;

#define OBF_ROUND1(t_) ((((t_) & g) ^ (((t_) & g) + w) * l ^ (((t_) & g) + z) * v) & ~g)
#define OBF_ROUND2(t_) ((((t_) & ~g) ^ (((t_) & ~g) + f) * q ^ (((t_) & ~g) + y) * u) & g)
#define OBF_IROUND2(t_) (((~g & (t_)) ^ ((~g & (t_)) + f) * q ^ ((~g & (t_)) + y) * u) & g)
#define OBF_MIX1(t_) (OBF_ROUND1(t_) ^ (t_))
#define OBF_IMIX2(t_) (OBF_IROUND2(t_) ^ (t_))

unsigned int __cdecl unmaskValue(int ctx, unsigned int obfuscatedValue)
{
	OBF_MARK_BEGIN
	OBF_LOAD_KEYS(ctx)
	unsigned int n = OBF_MIX1(obfuscatedValue) ^ OBF_ROUND2(OBF_MIX1(obfuscatedValue));
	OBF_MARK_END
	return n;
}

unsigned int __cdecl maskValue(int ctx, unsigned int clearValue)
{
	OBF_MARK_BEGIN
	OBF_LOAD_KEYS(ctx)
	unsigned int n = OBF_IMIX2(clearValue) ^ OBF_ROUND1(OBF_IMIX2(clearValue));
	OBF_MARK_END
	return n;
}

// R: the wrapper's result type; GET: the context getter; T and KIND: the operand type and its code;
// OP: the operation code; F: its functor. Operation 1 yields the second operand and 0xd the first.
#define OBF_FALLBACK(R, NAME, GET, T, KIND, OP, F) \
R __cdecl NAME(R pA, R pB) \
{ \
	OBF_MARK_BEGIN \
	unsigned int y = 0; \
	int w = GET(); \
	unsigned int v = unmaskValue(w, pA); \
	unsigned int u = unmaskValue(w, pB); \
	F<T> f = {}; \
	int n = f((T)v, (T)u); \
	n = Rva00225A93Get(KIND, OP, v, u, n); \
	if (0) \
		if (v == 1) \
			((FallbackCtx *)w)->m_18 = 0; \
	if ((OP) == 1) \
		n = (T)pB; \
	if ((OP) == 0xd) \
		y = v; \
	else \
		y = maskValue(w, n); \
	OBF_MARK_END \
	return y; \
}

OBF_FALLBACK(int, Rva002264B3Fallback, Rva00226140Get, int, 5, 0xe, ObfLess)
OBF_FALLBACK(int, Rva00226588Fallback, Rva00226140Get, int, 5, 1, ObfSecond)
OBF_FALLBACK(int, Rva0022665EFallback, Rva00226140Get, int, 5, 2, ObfAdd)
OBF_FALLBACK(int, Rva00226733Fallback, Rva00226140Get, int, 5, 0xd, ObfFirst)
OBF_FALLBACK(unsigned int, Rva003F0906Fallback, Rva003EFE9AGet, short, 3, 0xe, ObfLess)
OBF_FALLBACK(int, Rva003F09DFFallback, Rva003EFE9AGet, short, 3, 2, ObfAdd)
OBF_FALLBACK(int, Rva003F0AB8Fallback, Rva003EFE9AGet, short, 3, 1, ObfSecond)
OBF_FALLBACK(int, Rva003F0B92Fallback, Rva003EFE9AGet, short, 3, 0xd, ObfFirst)
OBF_FALLBACK(unsigned int, Rva00434548Fallback, Rva00434091Get, short, 3, 0xe, ObfLess)
OBF_FALLBACK(int, Rva00434621Fallback, Rva00434091Get, short, 3, 1, ObfSecond)
OBF_FALLBACK(int, Rva004346FBFallback, Rva00434091Get, short, 3, 2, ObfAdd)
OBF_FALLBACK(int, Rva004347D4Fallback, Rva00434091Get, short, 3, 0xd, ObfFirst)
OBF_FALLBACK(unsigned int, Rva0056DE2BFallback, Rva0056DD52Get, short, 3, 0x11, ObfGreaterEqual)
OBF_FALLBACK(unsigned int, Rva0056DF04Fallback, Rva0056DD58Get, int, 5, 0xe, ObfLess)
OBF_FALLBACK(int, Rva0056DFD9Fallback, Rva0056DD5EGet, int, 5, 0x11, ObfGreaterEqual)
OBF_FALLBACK(int, Rva0056E0AEFallback, Rva0056DD5EGet, short, 3, 0x11, ObfGreaterEqual)
OBF_FALLBACK(int, Rva0056E187Fallback, Rva0056DD52Get, short, 3, 1, ObfSecond)
OBF_FALLBACK(int, Rva0056E261Fallback, Rva0056DD58Get, int, 5, 2, ObfAdd)
OBF_FALLBACK(int, Rva0056E336Fallback, Rva0056DD58Get, int, 5, 1, ObfSecond)
OBF_FALLBACK(int, Rva0056E40CFallback, Rva0056DD5EGet, int, 5, 1, ObfSecond)
OBF_FALLBACK(int, Rva0056E4E2Fallback, Rva0056DD5EGet, short, 3, 1, ObfSecond)
OBF_FALLBACK(int, Rva0056E5BCFallback, Rva0056DD58Get, int, 5, 0xd, ObfFirst)
