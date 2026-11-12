// BfmeOwnZC: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
// rva00204EBB is the rowed 0x00204EBB body (?rva00204EBB@BfmeOwnZC@@QAEPAXVBfmeRoomZC@@PAX@Z) and
// rva00204E64 the symbols.csv pin at 0x00204E64 (retail 0x00204F3B calls it with ecx=this and one
// AsciiString argument); ScriptEngine's enable/disable and callSubroutine bodies call both.
#ifndef CANONICAL_BFMEOWNZC_H
#define CANONICAL_BFMEOWNZC_H

class AsciiString;
class BfmeRoomZC;
class ScriptList;

class BfmeOwnZC
{
public:
	void *bfmeCallZC(const BfmeRoomZC &name, void *extra);
	void *rva00204EBB(BfmeRoomZC name, void *extra);	// 0x00204EBB
	void *bfmeRunZC(BfmeRoomZC name, void *extra);
	ScriptList *rva00204E64(const AsciiString &name);	// 0x00204E64
};

#endif // CANONICAL_BFMEOWNZC_H
