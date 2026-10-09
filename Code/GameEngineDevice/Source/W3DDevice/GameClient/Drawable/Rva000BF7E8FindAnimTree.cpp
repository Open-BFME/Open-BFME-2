// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?Rva000BF7E8FindAnimTree@@YAPAVHTreeClass@@ABVAsciiString@@00_NH@Z, retail
// 0x000BF7E8..0x000BF953 (363 bytes), cdecl. Resolves an animation
// hierarchy name in the W3DScriptedModelDraw area:
//  - a function-local static AsciiString holds the "#(MODEL)" token
//    (guard 0x00DEAF24, object 0x00DEAF20, atexit stub 0x007B6D09);
//  - the pattern has the token replaced by the model name (rowed
//    Rva000BDD6CReplace) and the rowed Rva000B992CBuild joins the base name
//    and that result (optionally numbered);
//  - when the rowed Rva0014CE16_AnimExists finds it, the rowed
//    Rva0014CF5F_GetAnimTree loads it;
//  - otherwise, for a numbered request with a base name, it retries with
//    "base.replaced".
// The model name is also handed to Build's unused int slot, which the row
// spells as int. Evidence: the sibling caller pattern of 0x000BE027 and the
// shared callee rows; the name stays address-derived.
#include "ascii_string.h"

class HTreeClass;

// The empty string at 0x00BBAC1C under the name Rva000B992CBuild.cpp gives it.
extern const char g_Rva0107301CEmptyString[];

AsciiString Rva000BDD6CReplace(const AsciiString &source, const AsciiString &find, const AsciiString &replace);
AsciiString Rva000B992CBuild(const AsciiString &a1, const AsciiString &a2, int dummy, bool flag, int num);
bool Rva0014CE16_AnimExists(const char *name);
HTreeClass *Rva0014CF5F_GetAnimTree(const char *name);

HTreeClass *Rva000BF7E8FindAnimTree(const AsciiString &pattern, const AsciiString &base,
	const AsciiString &model, bool numbered, int number)
{
	static AsciiString s_modelToken("#(MODEL)");

	char dot[2];
	AsciiString name(g_Rva0107301CEmptyString);
	HTreeClass *tree = 0;
	AsciiString replaced = Rva000BDD6CReplace(pattern, s_modelToken, model);
	name = Rva000B992CBuild(base, replaced, (int)&model, numbered, number);
	if (Rva0014CE16_AnimExists(name.str()))
		tree = Rva0014CF5F_GetAnimTree(name.str());

	if (tree == 0 && numbered && !base.isEmpty())
	{
		name = base;
		dot[0] = '.';
		((StringBase<char> &)name).concat(dot, 1);
		name.concat(replaced);
		if (Rva0014CE16_AnimExists(name.str()))
			tree = Rva0014CF5F_GetAnimTree(name.str());
	}
	return tree;
}
