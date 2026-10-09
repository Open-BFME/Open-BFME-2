// cl: /EHsc /MD
// ?rva003FB508@Rva003FB508@@QAEXPAVINI@@PAX@Z @0x003FB508 234B: VeterancyLevel-style bitstring-list INI driver for the rowed single-token worker 0x003FB3B8, same shape as the KindOf driver Rva00256499 (System/Rva00256499Parse.cpp) and the ModelCondition driver 0x000B937E: StringBase split plus join-append plus the worker per token.
// Target evidence: retail body matches the 234B driver family by masked n-gram (1.0); worker callee 0x003FB3B8 read at the REL32; the join-append 0x0049B6AE is called through its existing TU-local member pin on Rva000B937E (no new pin). Class names are address-derived.
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


__forceinline const char *GetStr003FB508(const Rva0033B84ETok &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

class Rva003FB3B8
{
public:
	bool rva003FB3B8(const char *token, bool *foundNormal, bool *foundAddOrSub);
};

class Rva000B937E
{
public:
	void rva000B937EAppend(const char *s, Rva0033B84ETok *b);
};

class Rva003FB508 : public Rva003FB3B8
{
public:
	void rva003FB508(INI *ini, void *extra);
};

void Rva003FB508::rva003FB508(INI *ini, void *extra)
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
				const char *s = GetStr003FB508(part);
				((Rva000B937E *)this)->rva000B937EAppend(s, accum);
				if (!rva003FB3B8(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			((Rva000B937E *)this)->rva000B937EAppend(token, accum);
			if (!rva003FB3B8(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
