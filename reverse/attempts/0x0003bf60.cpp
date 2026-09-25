// ??6@YAAAVDebug@@AAV0@ABUSignature@DebugStackwalk@@@Z
// partial score=0.95 date=2026-09-25
// ??6@YAAAVDebug@@AAV0@ABUSignature@DebugStackwalk@@@Z
// partial score=0.95 date=2026-09-26 (struct/U rename of the 2026-09-22 V partial;
// rowed callers AssertDone 0x3A8A0 and CrashDone 0x3AED0 declare struct Signature)
// cl: /DNDEBUG /MD /EHsc
//
// operator<<(Debug &, const DebugStackwalk::Signature &), retail 0x0003BF60
// (369 bytes). AssertDone and CrashDone print their stack walks through it.
//
// Zero Hour prints one GetSymbol line per address. BFME2 uses the detailed
// GetSymbol overload (0x0003BC80, full paths) and prints every frame as
// "file(line):+rel module+rel symbol+rel", each "+rel" only when non-zero.
// The stream operators are Debug virtuals here (unsigned at slot 0x30,
// const char * at 0x38), and GetAddress is inlined with its range check.

#pragma optimize("y", off)

class Debug
{
public:
	// MSVC groups the overloads at the first one's slot in reverse
	// declaration order: unsigned 0x30, int 0x34, const char * 0x38.
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual Debug &operator<<(const char *str);
	virtual Debug &operator<<(int val);
	virtual Debug &operator<<(unsigned val);
};

class DebugStackwalk
{
public:
	struct Signature
	{
		enum { MAX_ADDR = 256 };

		unsigned m_numAddr;
		unsigned m_addr[MAX_ADDR];

	public:
		unsigned Size() const { return m_numAddr; }

		unsigned GetAddress(int n) const
		{
			if (n < 0 || n >= MAX_ADDR)
				return 0;
			return m_addr[n];
		}

		static void GetSymbol(unsigned addr,
			char *bufMod, unsigned sizeMod, unsigned *relMod,
			char *bufSym, unsigned sizeSym, unsigned *relSym,
			char *bufFile, unsigned sizeFile, unsigned *linePtr, unsigned *relLine,
			bool fullPath);
	};
};

static inline void PrintOffset(Debug &dbg, unsigned rel)
{
	if (rel)
		dbg << "+" << rel;
}

// ??6@YAAAVDebug@@AAV0@ABUSignature@DebugStackwalk@@@Z
Debug &operator<<(Debug &dbg, const DebugStackwalk::Signature &sig)
{
	dbg << sig.Size() << " addresses:\n";

	for (unsigned k = 0; k < sig.Size(); k++)
	{
		char bufMod[128], bufSym[256], bufFile[256];
		unsigned relMod, relSym, line, relLine;
		DebugStackwalk::Signature::GetSymbol(sig.GetAddress(k),
			bufMod, sizeof(bufMod), &relMod,
			bufSym, sizeof(bufSym), &relSym,
			bufFile, sizeof(bufFile), &line, &relLine,
			true);
		dbg << bufFile << "(" << line << "):";
		PrintOffset(dbg, relLine);
		dbg << " " << bufMod;
		PrintOffset(dbg, relMod);
		dbg << " " << bufSym;
		PrintOffset(dbg, relSym);
		dbg << "\n";
	}

	return dbg;
}

// 2026-09-26 refuted on the U base (all keep the 375B/0.95 wall: global frame,
// loop and homes match; only the 3 rel-test sites use eax+mov edi,eax instead
// of retail mov edi/test edi): helper named-temp, ternary, param-swap,
// __fastcall, plain static, rel>0, pragma-s on helper, by-ref/const-ref/pointer
// params (these three also break global allocation to 380B ebx-based),
// hand-inline (breaks global allocation: 0x28c frame, ebx=sig), outer copies
// (387B, copies not sunk), hand-inline+/O1 (356B, reshaped).
