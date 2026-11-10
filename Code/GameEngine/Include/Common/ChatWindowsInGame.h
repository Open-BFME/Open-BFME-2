// ChatWindowsInGame: canonical declarations for the members 9 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_CHATWINDOWSINGAME_H
#define CANONICAL_CHATWINDOWSINGAME_H

class UnicodeString;

class ChatWindowsInGame
{
public:
	bool rva005AFCB4(bool flag);
	int rva005AFDC5(int, const UnicodeString &, const UnicodeString &, int);
	void rva005B000C();
	bool rva005B00C8(int arg0, unsigned int arg1, unsigned int arg2);
};

#endif // CANONICAL_CHATWINDOWSINGAME_H
