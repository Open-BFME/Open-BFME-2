// cl: /O1 /EHsc /MD
// ?rva002C8754@Rva002C8754@@QAEXPAVINI@@PAX@Z @0x002C8754 234B.
// Multi-token INI bitstring-list driver over BitFlags104 worker 0x002C82C8.
// Direct transfer of the landed 234B sibling ?rva0033B84E@Rva0033AFBB in
// INI_VeterancyLevelListParse.cpp (same shape same callees same EH).
// Evidence: thiscall with this=worker flag set; INI arg flows as this into
// 0x0002DFE2 null-tolerant quoted-token reader; accumulator void star flows
// as the string arg of the join-append at 0x0049B6AE whose null-guard makes
// the 0x002C8C06 wrapper NULL pass legal; str m_data plus 8 or empty shape;
// EH prolog frame 0x00629188 over two string temporaries. The join-append
// reads as a worker member (both call sites set ecx edi before push call)
// so it reuses the landed Rva0033AFBB member spelling whose body ignores
// its receiver; the YG row still verifies. String locals reuse the 4-byte
// Tok layout; their ctor teardown reset and nextToken ride existing pins.
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

class Rva002C82C8
{
public:
	bool rva002C82C8(const char *token, bool *foundNormal, bool *foundAddOrSub);
};

class Rva0033AFBB
{
public:
	void rva0033B84EAppend(const char *s, Rva0033B84ETok *b);
};

class Rva002C8754
{
public:
	void rva002C8754(INI *ini, void *accum);
};

void Rva002C8754::rva002C8754(INI *ini, void *accumVoid)
{
	Rva0033B84ETok *accum = (Rva0033B84ETok *)accumVoid;
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
				((Rva0033AFBB *)this)->rva0033B84EAppend(s, accum);
				if (!((Rva002C82C8 *)this)->rva002C82C8(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			((Rva0033AFBB *)this)->rva0033B84EAppend(token, accum);
			if (!((Rva002C82C8 *)this)->rva002C82C8(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
