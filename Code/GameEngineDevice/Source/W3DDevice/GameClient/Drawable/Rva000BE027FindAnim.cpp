// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva000BE027@Rva000BE027Anim@@QAEPAVHTreeClass@@ABVAsciiString@@0_NH@Z,
// retail 0x000BE027..0x000BE201 (474 bytes, thiscall, ret 0x10). The
// list form of the rowed 0x000BF7E8 lookup in the W3DScriptedModelDraw
// area (callers 0x000BE47B 0x000BE4BC 0x000BF36F 0x000BF505; WorldBuilder
// twin 0x0091EFA0 unnamed). It works on a record holding a vector of
// animation name patterns at +0 and a cached duration at +0x18:
//  - each pattern has its own static "#(MODEL)" token (guard 0x00DEAF1C,
//    object 0x00DEAF18, atexit stub 0x007B6CFF) replaced by the model name
//    (rowed Rva000BDD6CReplace);
//  - that result is joined with the base name by the rowed
//    Rva000B992CBuild and looked up exactly as 0x000BF7E8 does, including
//    the numbered "base.replaced" retry;
//  - the first hit ends the walk, and a negative cached duration becomes
//    the hit's frame count * 1000 / frame rate (its slots 5 and 6).
// The record's owner is not proven; names stay address-derived.
#include "ascii_string.h"

class HTreeClass;

// The empty string at 0x00BBAC1C under the name Rva000B992CBuild.cpp gives it.
extern const char g_Rva0107301CEmptyString[];

AsciiString Rva000BDD6CReplace(const AsciiString &source, const AsciiString &find, const AsciiString &replace);
AsciiString Rva000B992CBuild(const AsciiString &a1, const AsciiString &a2, int dummy, bool flag, int num);
bool Rva0014CE16_AnimExists(const char *name);
HTreeClass *Rva0014CF5F_GetAnimTree(const char *name);

// The loaded animation's frame count (slot 5) and frame rate (slot 6).
class Rva000BE027Clip
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual int getNumFrames();
	virtual float getFrameRate();
};

class Rva000BE027Anim
{
public:
	HTreeClass *rva000BE027(const AsciiString &base, const AsciiString &model, bool numbered, int number);

private:
	AsciiString *m_begin;   // +0x00
	AsciiString *m_end;     // +0x04
	char m_pad08[0x18 - 0x08];
	float m_duration18;     // +0x18
};

HTreeClass *Rva000BE027Anim::rva000BE027(const AsciiString &base, const AsciiString &model, bool numbered, int number)
{
	static AsciiString s_modelToken("#(MODEL)");

	char dot[2];
	AsciiString name(g_Rva0107301CEmptyString);
	HTreeClass *tree = 0;
	unsigned int i = 0;
	do
	{
		if (i >= (unsigned int)(m_end - m_begin))
			break;
		{
			AsciiString replaced = Rva000BDD6CReplace(m_begin[i], s_modelToken, model);
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

			if (tree != 0 && m_duration18 < 0.0f)
			{
				Rva000BE027Clip *clip = reinterpret_cast<Rva000BE027Clip *>(tree);
				m_duration18 = (float)clip->getNumFrames() * 1000.0f / clip->getFrameRate();
			}
		}
		++i;
	} while (tree == 0);
	return tree;
}
