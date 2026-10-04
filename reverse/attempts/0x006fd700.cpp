// ?rva006FD700@@YGPBDPBDPAVEAStringC@@1@Z
// partial score=0.94 date=2026-10-04
// ?rva006FD700@@YGPBDPBDPAVEAStringC@@1@Z
// cl: /O2 /DNDEBUG /MD
//
// ?rva006FD700@@YGPBDPBDPAVEAStringC@@1@Z @0x006FD700 (133B). Splits an
// ampersand-separated name=value pair: releases both output strings, assigns
// the name and value through the bounded append (bfmeAppendVKG 0x006D52A0),
// URL-decodes both through rva006FD630, and returns the cursor past the pair
// (or null when there is no '=').
//
// Two levers close most of the gap from the 0.85 bank, both established from
// the retail bytes rather than guessed:
//
//  1. The scan is a do/while with the null and '&' tests as the first two
//     statements of the body, not a for-condition. That is what stops MSVC's
//     loop rotation: the banked for() rotated the whole test chain to the loop
//     bottom and re-read the first character through ebx, adding the tell-tale
//     `lea ebx,[ebx+0x0]` padding and 12 bytes. With the tests in the body the
//     load stays at the loop top (`mov al,[esi]` / `test al,al` / `cmp al,0x26`
//     / `cmp al,0x3d` / `mov edi,esi` / `inc esi` / `jne`) and matches retail
//     byte for byte.
//  2. The null check guards the whole body rather than returning early, so
//     `test ebx,ebx / je` targets the shared epilogue at the end instead of a
//     private early-out. Both the null exit and the no-'=' exit then land on
//     the same pop/xor eax/ret 0xc tail, exactly as retail does.
//
// Evidence: retail 0x006FD700 boundary is 133B to `ret 0xc`; callees
// rva006D3470 (both release calls), bfmeAppendVKG 0x006D52A0 and the matched
// rva006FD630 URL-decoder in Code/Libraries/Source/WWVegas/WWLib/
// Rva006FD340Cluster.cpp. Register roles match retail: p in ebx, cursor in
// esi, last '=' in edi, outName in ebp.
//
// RESIDUE (133B, 13 differing bytes, first diff +0x3A): retail folds the
// `eq + 1` into edi itself (`inc edi`) before the value append, and re-reads
// `*q` into al for the trailing '&' test; we compute both separately. Naming
// the value pointer, incrementing eq in place, and hoisting the '&' character
// were each tried and each changes the register pairing (see re_attempts.log);
// this spelling is the closest measured.

class EAStringC
{
	void *m_pData;

public:
	EAStringC();
	~EAStringC();
	EAStringC &clear();
	unsigned int rva006D3750() const;
	const char *rva00620090() const;
	EAStringC &Rva006D50A0Append(const char *text);
	EAStringC &operator=(const EAStringC &other);
	void rva006D3470();
};

class BfmeBufVKG
{
public:
	BfmeBufVKG *bfmeAppendVKG(const char *source, unsigned int limit);
};

void __cdecl rva006FD630(EAStringC *pString);

// ?rva006FD700@@YGPBDPBDPAVEAStringC@@1@Z present-unmatched
const char *__stdcall rva006FD700(const char *p, EAStringC *outName, EAStringC *outValue)
{
	const char *q = p;
	const char *eq = 0;
	outName->rva006D3470();
	outValue->rva006D3470();
	if (p != 0) {
		do {
			if (*q == 0)
				break;
			if (*q == '&')
				break;
			if (*q == '=')
				eq = q;
			++q;
		} while (q);
		if (eq != 0) {
			((BfmeBufVKG *)outName)->bfmeAppendVKG(p, (unsigned int)(eq - p));
			rva006FD630(outName);
			((BfmeBufVKG *)outValue)->bfmeAppendVKG(eq + 1, (unsigned int)(q - (eq + 1)));
			rva006FD630(outValue);
		}
		if (*q == '&')
			++q;
		return q;
	}
	return 0;
}