// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Oi
//
// ?parseAudioLODDefinition@INI@@SAXPAV1@@Z, retail 0x00202F8A,
// 153 bytes. Dedicated TU.
//
// BFME1 INI::parseAudioLODDefinition port
// (reference/open-bfme-1 Code/GameEngine/Source/Common/GameLOD.cpp: default
// AsciiString name; token = ini->getNextToken(); name = token; null-checked
// TheGameLODManager->getAudioLODIndex with a fatal INIException(8,
// "Unknown Audio LOD level '%s'") on -1; element at manager + index*8 and
// ini->initFromINI into the audio table). BFME2 adaptations proven by retail:
// - Element stride 8 with base +0x218 (BFME1's comment says +0x170; retail
//   lea says +0x218).
// - name.m_data starts zeroed via the member-init idiom (retail and-zero,
//   not a mov store); name = token goes through the inline operator= into
//   the matched StringBase::set at 0x000055F5; releaseBuffer resolves via
//   its pin.
// - The throw uses the proven AI-kind shape (8-byte INIException filled by
//   the 0x2F681 helper pin, push-imm throwinfo DIR32 at 0x8FE2FC, plain
//   _CxxThrowException call falling through into the store) with a plain
//   `if (index == -1)` (retail checks-then-throws-then-stores); the decl
//   carries __declspec(noreturn) so the index survives in eax for the store
//   without a callee-saved home.
// - getNextToken/initFromINI/getAudioLODIndex resolve via the matched row
//   and committed pins; the FieldParse table is TU-local opaque words (its
//   push is a DIR32 address patch; handler identities never enter .text).
// - Retail carries the __EH_prolog SEH prologue, so no /GX- here (unlike the
//   frameless pref getters): the dtor-temp plus throw earn the scope table.
//   /Oi lets the memset-free zeroing stay inline (without it the zeroing
//   becomes an out-of-line memset call).

#include <string.h>

typedef int Int;
typedef bool Bool;

#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"


#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"

#include "../../Include/Common/GameLODManager.h"

extern GameLODManager *TheGameLODManager;  // defined in GameLOD.cpp

// The AudioLOD fields, retail .rdata 0x007E34B8: three entries and the null entry, read
// from retail's words; the rowed INI::parseInt (0x0002EF56) and INI::parseBool (0x0002E850).
static const FieldParse audioLODFieldParseTable[] =
{
	{ "MaximumAmbientStreams", INI::parseInt, 0, 0x0 },
	{ "AllowDolby", INI::parseBool, 0, 0x4 },
	{ "AllowReverb", INI::parseBool, 0, 0x5 },
	{ 0, 0, 0, 0 }
};




// ?parseAudioLODDefinition@INI@@SAXPAV1@@Z
void INI::parseAudioLODDefinition(INI *ini)
{
	AsciiString name;
	const char *token = ini->getNextToken((const char *)0);
	name = token;

	if (TheGameLODManager)
	{
		Int index = TheGameLODManager->getAudioLODIndex(name);
		if (index == -1)
		{
			throw INIException(8, "Unknown Audio LOD level '%s'", token);
		}
		void *lodInfo = (char *)TheGameLODManager + index * 8 + 0x218;
		ini->initFromINI(lodInfo, audioLODFieldParseTable);
	}
}
