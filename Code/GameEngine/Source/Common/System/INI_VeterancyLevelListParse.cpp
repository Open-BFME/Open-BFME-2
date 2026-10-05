// cl: /O1 /EHsc /MD
//
// ?rva0033B84E@Rva0033AFBB@@QAEXPAVINI@@PAVRva0033B84ETok@@@Z
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
// 0x00629188 over two string temporaries. The join-append reads as a worker
// member (rva0033B84EAppend): both call sites set ecx=edi immediately before
// push/call, and only the member reading (this gains the append uses)
// reproduces retail's edi=this homing -- a free-function reading homes the
// accumulator instead. The callee body ignores its receiver either way, so
// its YG row still verifies; the member spelling is pinned alongside it.
//
// The string locals reuse the 4-byte StringDataBase* layout; their ctor,
// teardown, reset and nextToken ride TU-local-spelling pins, so no
// canonical string header is redeclared here.
class INI
{
public:
	const char *rva0002DFE2(const char *seps, bool *substituted);
};

class Rva0033B84ETok
{
public:
	Rva0033B84ETok(const char *s);
	~Rva0033B84ETok();
	Rva0033B84ETok() : m_data(0) {}
	const char *str() const { return m_data ? (const char *)m_data + 8 : ""; }
	bool nextToken(Rva0033B84ETok *out, const char *seps);
	void reset();

private:
	void *m_data;
};

class Rva0033AFBB
{
public:
	bool rva0033AFBB(const char *token, bool *foundNormal, bool *foundAddOrSub);
	void rva0033B84E(INI *ini, Rva0033B84ETok *accum);
	void rva0033B84EAppend(const char *s, Rva0033B84ETok *b);
};

// All five callees are byte-verified elsewhere: the StringBase const-char
// ctor (0x00037BA0), the AsciiString teardown (0x00036410, also the folded
// releaseBuffer spelling used for the accumulator reset), narrow nextToken
// (0x00036D90, matched row), and the join-append helper (0x0049B6AE).
// Each TU-local spelling above carries a reverse/symbols.csv pin to it.

void Rva0033AFBB::rva0033B84E(INI *ini, Rva0033B84ETok *accum)
{
	if (accum != 0)
		accum->reset();

	bool foundNormal = false;
	bool foundAddOrSub = false;
	bool wasQuoted = false;

	const char *token;
	while ((token = ini->rva0002DFE2(0, &wasQuoted)) != 0) {
		if (wasQuoted) {
			Rva0033B84ETok tmp(token);
			Rva0033B84ETok part;
			while (tmp.nextToken(&part, 0)) {
				const char *s = part.str();
				rva0033B84EAppend(s, accum);
				if (!rva0033AFBB(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			rva0033B84EAppend(token, accum);
			if (!rva0033AFBB(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
