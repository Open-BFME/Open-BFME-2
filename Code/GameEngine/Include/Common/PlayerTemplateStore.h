// PlayerTemplateStore: canonical declarations for the members 23 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_PLAYERTEMPLATESTORE_H
#define CANONICAL_PLAYERTEMPLATESTORE_H

class PlayerTemplate;
enum NameKeyType;

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(int index) const;
	const PlayerTemplate *findPlayerTemplate(NameKeyType namekey) const;
	bool rva001FD367(int, int *) const;
};

#endif // CANONICAL_PLAYERTEMPLATESTORE_H
