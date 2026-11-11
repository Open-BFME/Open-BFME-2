// Rva0054D2DDTarget: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0054D2DDTARGET_H
#define CANONICAL_RVA0054D2DDTARGET_H

struct TreeHintRef00217D4C;
class UnicodeString;

class Rva0054D2DDTarget
{
public:
	void method(int type, const UnicodeString &title, const UnicodeString &text);
	void method(int, const UnicodeString &, const UnicodeString &, TreeHintRef00217D4C, TreeHintRef00217D4C);
};

#endif // CANONICAL_RVA0054D2DDTARGET_H
