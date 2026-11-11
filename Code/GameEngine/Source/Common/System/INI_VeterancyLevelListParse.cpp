// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// ?rva0033B84E@Rva0033AFBB@@QAEXPAVINI@@PAVAsciiString@@@Z
// @0x0033B84E 234B.
//
// Multi-token INI bitstring-list driver for the single-token worker in
// INI_VeterancyLevelToken.cpp (0x0033AFBB): pulls tokens from INI with the
// null-tolerant quoted-token reader at 0x0002DFE2, and per token either
// re-splits a quoted token through StringBase::nextToken (0x00036D90) or
// feeds it straight to the worker, joining every piece into the accumulator
// through the join-append at 0x0049B6AE and setting the worker bitflags.
// A worker false ("NONE") ends the inner split but continues the outer
// stream in the quoted arm, and ends the whole parse in the plain arm --
// that asymmetry is what the two je targets (cleanup/continue vs exit)
// encode. The quoted arm re-clears wasQuoted before looping (dead but
// byte-real: the 0x0002DFE2 null path leaves the flag untouched).
//
// Evidence: thiscall with this=worker; INI* arg1 (flows as this into
// 0x0002DFE2, whose body delegates to INI's getNextTokenOrNull 0x0002DEED
// plus preprocessMacro 0x0002D0A9); accumulator arg2 (flows as the string
// arg of the join-append, whose null-guard makes the 0x0033BEE5 wrapper's
// NULL pass legal); str()'s m_data+8-or-"" shape; __EH_prolog frame
// 0x00629188 over two string temporaries. The join-append is a
// worker-side member (Rva0049B6AE::append, its row's name): both call sites
// set ecx=edi immediately before push/call, and only the member reading
// reproduces retail's edi=this homing -- a free-function reading homes the
// accumulator instead. The callee body ignores its receiver.
//
// The string locals and the accumulator are the canonical AsciiString
// (reference/shims/bfme2_ascii): its inline const-char ctor calls the
// StringBase ctor 0x00037BA0, nextToken forwards to 0x00036D90, and its
// teardown and clear() are the releaseBuffer worker 0x00036410.
#include "ascii_string.h"

#include "../../../Include/Common/INI/INI.h"

class Rva0049B6AE
{
public:
	void append(const char *s, StringBase<char> *b);
};

#include "../../../Include/Common/Rva0033AFBB.h"

void Rva0033AFBB::rva0033B84E(INI *ini, AsciiString *accum)
{
	if (accum != 0)
		accum->clear();

	bool foundNormal = false;
	bool foundAddOrSub = false;
	bool wasQuoted = false;

	const char *token;
	while ((token = ini->rva0002DFE2(0, &wasQuoted)) != 0) {
		if (wasQuoted) {
			AsciiString tmp(token);
			AsciiString part;
			while (tmp.nextToken(&part, 0)) {
				const char *s = part.str();
				((Rva0049B6AE *)this)->append(s, (StringBase<char> *)accum);
				if (!rva0033AFBB(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			((Rva0049B6AE *)this)->append(token, (StringBase<char> *)accum);
			if (!rva0033AFBB(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
