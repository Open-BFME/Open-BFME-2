// cl: /EHsc /MD
// ?rva00256499@Rva00256499@@QAEXPAVINI@@PAX@Z @0x00256499 234B: KindOf bitstring-list driver for worker 0x00255D58 via StringBase split plus join-append 0x0049B6AE.
// Target evidence: LINK BONUS 20B plus pin plus callers 0x002567F4 0x002C8C41 0x002C8C75, this=worker edi homing with mov ecx edi before both Append plus worker calls, INI rva0002DFE2 0x0002DFE2 null-tolerant quoted reader, StringBase ctor 0x00037BA0 plus nextToken 0x00036D90 plus releaseBuffer 0x00036410, worker 0x00255D58, Append 0x0049B6AE, empty fallback g_Rva0107301CEmptyString, __EH_prolog frame; donor is INI_VeterancyLevelListParse.cpp 0x0033B84E 234B same shape with Tok reuse plus member Append homing plus quoted-arm wasQuoted reclear.
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


__forceinline const char *GetStr00256499(const Rva0033B84ETok &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

class Rva00255D58
{
public:
	bool rva00255D58(const char *token, bool *foundNormal, bool *foundAddOrSub);
};

class Rva00256499 : public Rva00255D58
{
public:
	void rva00256499(INI *ini, void *extra);
	void rva00256499Append(const char *s, Rva0033B84ETok *b);
};

void Rva00256499::rva00256499(INI *ini, void *extra)
{
	Rva0033B84ETok *accum = (Rva0033B84ETok *)extra;
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
				const char *s = GetStr00256499(part);
				rva00256499Append(s, accum);
				if (!rva00255D58(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			rva00256499Append(token, accum);
			if (!rva00255D58(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
