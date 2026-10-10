// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// Native21A651..21A6C8 RET4 has a hidden AsciiString result and one
// reference input. Retail reads mutable prefix/extension pointers atDB9D10
// andDB9D14, initially pointing to MyHero_ atBE5BEC and .cah atBE5BE4.
// The chosen data identifiers describe these proven contents/purposes;
// their original source names and the function name are unknown.
// Four data rows own the initialized text bytes and pointer relocations.
#include "ascii_string.h"
extern const char BfmeCreateAHeroFilenamePrefixText[8]="MyHero_";
const char *g_CreateAHeroFilenamePrefix=BfmeCreateAHeroFilenamePrefixText;
extern const char BfmeCreateAHeroFilenameExtensionText[5]=".cah";
const char *g_CreateAHeroFilenameExtension=BfmeCreateAHeroFilenameExtensionText;
AsciiString Rva0021A651Filename(const AsciiString &name) {
 AsciiString filename;
 filename.format("%s%s%s",g_CreateAHeroFilenamePrefix,name.str(),g_CreateAHeroFilenameExtension);
 return filename;
}
