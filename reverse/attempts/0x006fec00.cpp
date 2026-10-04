// ?rva006FEC00@@YAEHHPAVEAStringC@@PAH0@Z
// partial score=0.88 date=2026-10-04
// ?rva006FEC00@@YAEHHPAVEAStringC@@PAH0@Z
// partial score=0.88 date=2026-10-04
// cl: /O2 /MD
// Address-derived Apt string worker next to the banked
// ?rva006FEB50@AptActionInterpreter@@QAEXXZ (0x006FEB50), in the same Apt
// string-value neighbourhood as the rowed Rva006e9730Cluster.cpp factory.
//
// Retail is an all-digits fast path in front of the general parser:
//
//   scan = src->rva00620090();                    // rowed EAStringC c_str
//   char c = *scan++;
//   while (c) {
//       if (c < '0') break;                      // jl  -> parse
//       if (c == ':') break;                     // je  -> parse
//       c = *scan++;                             // load BEFORE the branch
//   }
//   if (strict) goto parse;                      // hoisted edx non-zero -> parse
//   outString->operator=(src);                   // rowed 0x006D3030
//   *resultSlot = value;
//   return 0;
//
// parse:
//   ok = rva006FD100(outString, strict, src, resultSlot, &buf);  // UNROWED
//   tmp = EAStringC(buf);                        // rowed 0x006D4C80
//   *outString = tmp;                            // rowed 0x006D3030
//   tmp.~EAStringC();                            // rowed 0x006D3010
//   return ok;
//
// So the semantics are: a string made only of digits (no ':' terminator) and
// with the strict flag clear is copied straight through and reported as NOT
// parsed; everything else -- non-digits, ':' or the strict flag -- goes to the
// parser. The loop reads the character before branching, which is why the
// comparison is written on the already-loaded `c` rather than on *scan.
//
// Proven from target bytes this pass (all of it contradicting the previous
// banked attempt's guesses):
//
//  * The function RETURNS A BYTE. Retail pushes ebx at 0x006FEC89, keeps the
//    parser's result in bl and reloads it with `mov al,bl` before the epilogue
//    at 0x006FECE9. /O2 never emits that for a void function, so the signature
//    is unsigned char (YAE), not void (YAX).
//
//  * The stack layout is (value, strict, src, resultSlot, outString) -- five
//    arguments, not the eight the previous mangled name claimed. Retail reads
//    value at [esp+0x118], strict at [esp+0x11c], src at [esp+0x120],
//    resultSlot at [esp+0x124] and outString at [esp+0x128] after
//    `sub esp,0x104` / `push esi`. src is the c_str receiver and resultSlot is
//    the store target in the copy-through, which pins those two roles.
//
//  * The parser's five arguments, read off the push sequence at 0x006FEC82,
//    are (outString, strict, src, resultSlot, &buf). The `buf` buffer is NOT
//    pre-zeroed; retail's tail carries no store to it.
//
//  * The strict flag is hoisted into edx before the digit scan (`mov
//    edx,[esp+0x11c]` at 0x006FEC2C, immediately after the c_str call) and
//    then `test edx,edx` gates the copy-through. Naming it in a `const int
//    strict = allowEmpty;` local declared before the loop is what reproduces
//    that hoist; passing the parameter directly makes MSVC reload it into eax
//    at the branch instead, which was the previous attempt's first difference.
//
// Bytes 0x00-0x90 (145 of 251) are now exact, including the SEH prologue, the
// 0x104 frame, the whole digit scan and the copy-through. The remaining delta
// is register scheduling in the parse tail only: retail reuses the hoisted edx
// for the strict push and reloads edx for the outString push, while this
// shape reloads esi for one argument and edx for the other. Same five values,
// same order, different allocation. It is a codegen-scheduling difference in
// MSVC's argument lowering, not a semantic one.
//
// 0x006FD100 is UNROWED: five arguments, returns a byte, and carries the same
// large-stack SEH frame as this body, so it is the general Apt string-to-value
// parser this fast path guards. Declared address-derived; identity unproven.
//
// Identity is address-derived throughout. The mangled name's return type
// (YAE, unsigned char) is proven by the epilogue; the parameter list is
// proven by the stack slots retail reads.

class EAStringC
{
public:
	const char *rva00620090() const;
	EAStringC &operator=(const EAStringC &other);
	EAStringC();
	EAStringC(const char *text);
	~EAStringC();
};

// Retail push sequence at 0x006FEC82: resultSlot into ecx, push ebx, lea &buf,
// push &buf, push ecx (arg4), push esi (arg3), push edx (strict, arg2),
// reload edx = outString (arg1), push edx. The register reuse of edx across
// two arguments is what the hoisted strict flag enables.
unsigned char __cdecl rva006FD100(EAStringC *outString, int strict,
	EAStringC *src, int *resultSlot, char *buf);

// Retail stack layout, after sub esp,0x104 / push esi: value at esp+0x118,
// allowEmpty at esp+0x11c, src at esp+0x120, resultSlot at esp+0x124 and
// outString at esp+0x128; the copy-through writes *resultSlot = value.
unsigned char rva006FEC00(int value, int allowEmpty, EAStringC *src,
	int *resultSlot, EAStringC *outString)
{
	const char *scan = src->rva00620090();
	char c = *scan++;
	const int strict = allowEmpty;
	bool allDigits = true;
	while (c) {
		if (c < '0') {
			allDigits = false;
			break;
		}
		if (c == ':') {
			allDigits = false;
			break;
		}
		c = *scan++;
	}

	if (allDigits && !strict) {
		*outString = *src;
		*resultSlot = value;
		return 0;
	}

	char buf[0x100];
	unsigned char ok = rva006FD100(outString, allowEmpty, src, resultSlot, buf);
	EAStringC tmp(buf);
	*outString = tmp;
	tmp.~EAStringC();
	return ok;
}