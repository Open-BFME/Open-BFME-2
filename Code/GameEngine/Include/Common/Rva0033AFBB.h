// Rva0033AFBB: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0033AFBB_H
#define CANONICAL_RVA0033AFBB_H

class AsciiString;
class INI;

class Rva0033AFBB
{
public:
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);
	bool rva0033AFBB(const char *token, bool *foundNormal, bool *foundAddOrSub);
	void rva0033B84E(INI *ini, AsciiString *str);
};

#endif // CANONICAL_RVA0033AFBB_H
