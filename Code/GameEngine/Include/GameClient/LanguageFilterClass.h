// LanguageFilter: canonical declarations for the members 14 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_LANGUAGEFILTER_H
#define CANONICAL_LANGUAGEFILTER_H

class File;
class UnicodeString;

class LanguageFilter
{
public:
	void filterLine(UnicodeString &line);
protected:
	bool readWord(File *file1, unsigned short *buf);
	void unHaxor(UnicodeString &word);
};

#endif // CANONICAL_LANGUAGEFILTER_H
