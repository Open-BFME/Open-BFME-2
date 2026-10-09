// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include <stddef.h>
void *__cdecl operator new(size_t);
void __cdecl operator delete(void *);
struct FieldParse;
class INI {
public:
 void initFromINI(void *, const FieldParse *);
 const char *getNextToken(const char * = 0);
 unsigned char m_beforeLoadType[8];
 int getLoadType() const { return m_loadType; }
 int m_loadType;
};
class Rva004DC9EDEntry {
public:
 ~Rva004DC9EDEntry();
 unsigned char m_record[0x18C];
};
// ABI views retain the existing provider spellings. This prefix models
// cleanup extent only; it does not assert an engine inheritance relation.
// Existing constructor owns the full 190-byte template. Its cleanup provider
// destroys the 18C-byte prefix; the last four bytes contain only flag/padding.
class Rva004DC920 : public Rva004DC9EDEntry {
public:
 Rva004DC920();
 unsigned char m_tail[4];
};
class Rva004DCAD2 {public: void rva004DCAD2(INI *);};
class BfmeEmotionName;
class EmotionNugget;
class MultiplayerColorDefinition;
class CreateAHeroData;
class EmotionSystem {
public:
 EmotionNugget *findNugget(const BfmeEmotionName &);
 void AddEmotionNuggetTemplate(MultiplayerColorDefinition *);
};
class Rva00426612 {public: void rva00426612(CreateAHeroData *);};
extern EmotionSystem *TheEmotionSystem;
class EmotionNuggetTemplate {public: static void friend_parseEmotionNugget(INI *);};
// BFME1 0bef414b52a39a3ab1ec98dca60d8a214de4260e INI_Emotion.cpp guides
// creation and registry insertion. WB 0x010E9920 independently names this
// parser; native 0x004DCAE4..0x004DCC39 adds replacement for load type 5
// and parses duplicate definitions into a temporary 0x190-byte template.
// getLoadType follows the reference INI accessor with retail offset +8.
// Legacy registry payload spellings are ABI views, not template identities.
void EmotionNuggetTemplate::friend_parseEmotionNugget(INI *ini)
{
 if (!TheEmotionSystem) return;
 const char *name = ini->getNextToken();
 Rva004DC920 *nugget = reinterpret_cast<Rva004DC920 *>(TheEmotionSystem->findNugget(reinterpret_cast<const BfmeEmotionName &>(AsciiString(name))));
 if (!nugget) nugget = new Rva004DC920;
 else if (ini->getLoadType() == 5) {
  reinterpret_cast<Rva00426612 *>(TheEmotionSystem)->rva00426612(reinterpret_cast<CreateAHeroData *>(nugget));
  nugget = new Rva004DC920;
 } else {
  Rva004DC920 sink;
  *reinterpret_cast<AsciiString *>(&sink) = AsciiString(name);
  reinterpret_cast<Rva004DCAD2 *>(&sink)->rva004DCAD2(ini);
  return;
 }
 *reinterpret_cast<AsciiString *>(nugget) = AsciiString(name);
 reinterpret_cast<Rva004DCAD2 *>(nugget)->rva004DCAD2(ini);
 TheEmotionSystem->AddEmotionNuggetTemplate(reinterpret_cast<MultiplayerColorDefinition *>(nugget));
}

// Existing template parse wrapper at 0x004DCAD2 (18 bytes).
extern const FieldParse g_00C61310[];
void Rva004DCAD2::rva004DCAD2(INI *ini)
{
	ini->initFromINI(this, g_00C61310);
}
