// EmotionNuggetTemplate: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_EMOTIONNUGGETTEMPLATE_H
#define CANONICAL_EMOTIONNUGGETTEMPLATE_H

class INI;

class EmotionNuggetTemplate
{
public:
	static void IniParseEmotionType(INI *ini, void *instance, void *store, const void *userData);
	static void friend_parseEmotionNugget(INI *);
};

#endif // CANONICAL_EMOTIONNUGGETTEMPLATE_H
