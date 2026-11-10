// CreateAHeroHero: canonical declarations for the members 22 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_CREATEAHEROHERO_H
#define CANONICAL_CREATEAHEROHERO_H

class AsciiString;
class CommandButton;
class CreateAHeroAward;

class CreateAHeroHero
{
public:
	void ConstructHeroBlingList();
	int GetBlingCount(int blingKey) const;
	int GetBlingId(int blingKey, unsigned int index) const;
	const CommandButton *GetButtonForLevel(int index);
	bool HasEarnedAward(const CreateAHeroAward *award) const;
	bool RegisterExperienceLevels();
	bool SetDefaultColors();
	bool Update(int flags);
	void UpdateAwardEarnedFlags();
	bool UpdateCommandSet(unsigned int commandSet);
	void rva004088F0(const void *victim, int arg1);
	bool rva004098BE(const AsciiString &file, bool system);
	void rva005B0357(int index, char *buffer, int unused);
};

#endif // CANONICAL_CREATEAHEROHERO_H
