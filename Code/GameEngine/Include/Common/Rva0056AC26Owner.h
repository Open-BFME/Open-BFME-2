// Rva0056AC26Owner: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0056AC26OWNER_H
#define CANONICAL_RVA0056AC26OWNER_H

class Rva0056AC26;
class UnicodeString;

class Rva0056AC26Owner
{
public:
	void notifyTaskCreated(Rva0056AC26 *);
	UnicodeString rva003F855D();
	void rva003F8814(Rva0056AC26 *);
	void rva003F8829(Rva0056AC26 *);
	void rva003F883E(Rva0056AC26 *);
	void rva003F8853(Rva0056AC26 *);
	void rva003F8868(Rva0056AC26 *);
	void rva003F887D(Rva0056AC26 *);
	void rva003F8892(Rva0056AC26 *);
	void rva003F88A7(Rva0056AC26 *entry);
};

#endif // CANONICAL_RVA0056AC26OWNER_H
