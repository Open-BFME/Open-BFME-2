// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// ?rva00334506@Rva003339CE@@QAEXVAsciiString@@@Z @0x00334506 129B: multi-token
// BodyState parser looping nextToken and driving single-token worker 0x003339CE.
// Evidence: calls worker 0x003339CE which muse-05 just landed, nextToken
// 0x00036D90, releaseBuffer 0x00036410 twice, empty fallback
// g_Rva0107301CEmptyString, callers at 0x00336FAA 0x00336FC1 0x0045E335.
// ?rva0033394D@Rva000B664E@@QAEXVAsciiString@@@Z @0x0033394D 129B is the same
// loop over the ModelCondition worker 0x000B664E (callers 0x00336D60,
// 0x00336D77, 0x003A4954, 0x0049724A).
#include "ascii_string.h"


__forceinline const char *GetStr00334506(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

class Rva003339CE
{
public:
	void rva00334506(AsciiString s);
	bool rva003339CE(const char *token, bool *foundNormal, bool *foundAddOrSub);

private:
	unsigned m_words[4];
};
class Rva000B664E
{
public:
	void rva0033394D(AsciiString s);
	bool rva000B664E(const char *token, bool *foundNormal, bool *foundAddOrSub);
private:
	unsigned m_words[19];
};

void Rva003339CE::rva00334506(AsciiString s)
{
	bool foundNormal = false;
	bool foundAddOrSub = false;
	AsciiString token;
	while (s.nextToken(&token, 0)) {
		const char *tokStr = GetStr00334506(token);
		if (!rva003339CE(tokStr, &foundNormal, &foundAddOrSub))
			break;
	}
}
void Rva000B664E::rva0033394D(AsciiString s)
{
	bool foundNormal = false;
	bool foundAddOrSub = false;
	AsciiString token;
	while (s.nextToken(&token, 0)) {
		const char *tokStr = GetStr00334506(token);
		if (!rva000B664E(tokStr, &foundNormal, &foundAddOrSub))
			break;
	}
}
