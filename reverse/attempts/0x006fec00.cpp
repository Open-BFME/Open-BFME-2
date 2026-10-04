// ?rva006FEC00@@YAXHHHPAHPAVEAStringC@@HH1@Z
// partial score=0.82 date=2026-10-04
// cl: /O2 /MD
// ?rva006FEC00@@YAXHPAPAXPAEAEAStringC@@AEBHPAX@Z @ 0x006FEC00 (251B).
//
// Address-derived Apt string worker next to the banked
// ?rva006FEB50@AptActionInterpreter@@QAEXXZ (0x006FEB50), in the same Apt
// string-value neighbourhood as the rowed Rva006e9730Cluster.cpp factory.
//
// Retail is an all-digits fast path in front of the general parser:
//
//   const char *p = src->rva00620090();          // rowed EAStringC c_str
//   const char *scan = p;
//   char c = *scan++;
//   while (c) {
//       if (c < '0') break;                      // jl  -> parse
//       if (c == ':') break;                     // je  -> parse
//       c = *scan++;                             // load BEFORE the branch
//   }
//   if (allowEmpty) goto parse;                  // edx non-zero -> parse
//   dst->operator=(src);                        // rowed 0x006D3030
//   *resultSlot = arg3;
//   return false;
//
// parse:
//   rva006FD100(arg2, src, &buf, flagArg, slotArg);   // UNROWED, returns byte
//   bufAsString = EAStringC(buf);                // rowed 0x006D4C80, ret 4
//   *outString = bufAsString;                   // rowed 0x006D3030
//   bufAsString.~EAStringC();                   // rowed 0x006D3010
//   return ok;
//
// So the semantics are: a string made only of digits (no ':' terminator) and
// with the strict flag clear is copied straight through and reported as NOT
// parsed; everything else -- non-digits, ':' or the strict flag -- goes to the
// parser. The loop reads the character before branching, which is why the
// comparison is written on the already-loaded `c` rather than on *scan.
//
// 0x006FD100 is UNROWED: five arguments, returns a byte, and carries the same
// large-stack SEH frame as this body, so it is the general Apt string-to-value
// parser this fast path guards. Declared address-derived; identity unproven.
//
// Identity is address-derived throughout.

class EAStringC
{
public:
	const char *rva00620090() const;
	EAStringC &operator=(const EAStringC &other);
	EAStringC();
	EAStringC(const char *text);
	~EAStringC();
};

// Address-derived Apt string-to-value parser, five arguments, returns byte.
unsigned char __cdecl rva006FD100(int arg2, EAStringC *src, char *buf,
	int flagArg, int arg5);

void rva006FEC00(int arg1, int arg2, int arg3, int *resultSlot,
	EAStringC *src, int allowEmpty, int flagArg, EAStringC *outString)
{
	const char *scan = src->rva00620090();
	char c = *scan++;
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

	if (allDigits && !allowEmpty) {
		*outString = *src;
		*resultSlot = arg3;
		return;
	}

	char buf[0x100];
	buf[0] = 0;
	unsigned char ok = rva006FD100(arg2, src, buf, flagArg, arg1);
	EAStringC tmp(buf);
	outString->operator=(tmp);
}