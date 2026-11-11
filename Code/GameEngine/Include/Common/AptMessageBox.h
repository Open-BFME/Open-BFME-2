// AptMessageBox: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTMESSAGEBOX_H
#define CANONICAL_APTMESSAGEBOX_H

struct TreeHintRef00217D4C;
class UnicodeString;

class AptMessageBox
{
public:
	static bool Change(int kind, const UnicodeString &title, const UnicodeString &message, TreeHintRef00217D4C callback);
	static void Change(void *, void *, void *);
	static void Show(int type, const UnicodeString &text, const UnicodeString &title, TreeHintRef00217D4C callback, TreeHintRef00217D4C callback2);
	static void Show(void *, void *, void *);
};

#endif // CANONICAL_APTMESSAGEBOX_H
