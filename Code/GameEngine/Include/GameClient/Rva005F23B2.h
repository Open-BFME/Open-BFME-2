// Rva005F23B2: canonical declarations for the members units call through views of it; each call
// resolves to the unit's ledger row or pin. Target facts: 24 bytes. Destructor 0x005F23B2 frees the
// pointer at +0 and destroys the member at +0x10 through 0x005F21F8 (8 bytes in its own rows), and
// StrategicInGameUI.cpp's matched owner view holds it at +0x1C with the next field at +0x34. No unit that
// includes this header reads a field, so the storage stays unnamed.
#ifndef CANONICAL_RVA005F23B2_H
#define CANONICAL_RVA005F23B2_H

class Rva005F23B2
{
public:
	~Rva005F23B2();
	char storage[24]; // +0x00
};

typedef char Rva005F23B2SizeCheck[sizeof(Rva005F23B2) == 24 ? 1 : -1];

#endif // CANONICAL_RVA005F23B2_H
