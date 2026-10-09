// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?Rva000BDD6CReplace@@YA?AVAsciiString@@ABV1@00@Z, retail 0x000BDD6C..0x000BDE85
// (281B), cdecl, AsciiString returned through the hidden pointer.
//
// String substitution through BFME 2's expression-template concatenation:
// strstr(src, find); when find does not occur the source is returned
// unchanged, otherwise the result is Left(src, offset) + repl +
// Right(src, src.getLength() - find.getLength()) converted to an AsciiString.
// (The tail count is taken as retail computes it: the source length minus
// the pattern length, independent of the match offset.)
//
// Evidence (target): the strstr import (0x007BA614) and the "" fallback of
// AsciiString::str (0x007BAC1C); callees read at the retail REL32s are the
// rowed expression nodes Rva000B6AF5Build (Right) / Rva000B6AA9Build (Left)
// / Rva005F17C6Build (node + AsciiString operand; pinned there as an
// operator+ taking const AsciiString &) / Rva000B64C5Build (16-byte + 12-byte
// node) and the rowed node-to-AsciiString conversion Rva000BDC6D, then
// StringBase::set 0x000366F0 / releaseBuffer 0x00036410 / copy ctor
// 0x000365F0. Callers 0x000BE0A7 (in 0x000BE027) and 0x000BF84A (in
// 0x000BF7E8), both in the W3DScriptedModelDraw area; WorldBuilder twin
// 0x91E840 (callgraph lead) starts with the same strstr of the two operands.
// No owner or name is proven; the name stays address-derived.
#include "ascii_string.h"

// The nodes are one family: a text reference (operand pointer start and
// count) optionally followed by an AsciiString operand pointer. Each
// ledger spelling of a node derives from the spelling its consumer takes,
// so a node binds to the consumer's reference parameter without a copy.
struct Rva000B64C5S12
{
	void *p;
	int start;
	int count;
};

struct Rva005F17C6S12
{
	void *p;
	int start;
	int count;
};

struct Rva000B64C5S16
{
	Rva005F17C6S12 text;
	int operand;
};

struct Rva005F17C6S16 : Rva000B64C5S16
{
};

struct Rva000B6AA9Rec : Rva005F17C6S12
{
};

struct Rva000B6AF5Rec : Rva000B64C5S12
{
};

// The 28-byte concatenation node; converts itself to an AsciiString.
class Rva000BDC6D
{
public:
	AsciiString rva000BDC6D();

private:
	char m_nodes[0x18];
	int m_extra18;
};

struct Rva000B64C5S28 : Rva000BDC6D
{
};

Rva000B6AA9Rec *__cdecl Rva000B6AA9Build(Rva000B6AA9Rec *dest, void **srcpp, int val);
Rva000B6AF5Rec *__cdecl Rva000B6AF5Build(Rva000B6AF5Rec *dest, void **srcpp, int val);
Rva005F17C6S16 __cdecl Rva005F17C6Build(const Rva005F17C6S12 &src, int v);
Rva000B64C5S28 __cdecl Rva000B64C5Build(const Rva000B64C5S16 &src1, const Rva000B64C5S12 &src2);

AsciiString Rva000BDD6CReplace(const AsciiString &src, const AsciiString &find, const AsciiString &repl)
{
	AsciiString result;
	const char *pos = strstr(src.str(), find.str());
	if (pos != 0)
	{
		int offset = pos - src.str();
		Rva000B6AF5Rec right;
		Rva000B6AA9Rec left;
		{
			const AsciiString &joined = Rva000B64C5Build(
				Rva005F17C6Build(*Rva000B6AA9Build(&left, (void **)&src, offset), (int)&repl),
				*Rva000B6AF5Build(&right, (void **)&src, src.getLength() - find.getLength())).rva000BDC6D();
			result = joined;
		}
		return result;
	}
	return src;
}
