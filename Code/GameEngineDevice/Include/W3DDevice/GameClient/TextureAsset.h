// FILE: TextureAsset.h ///////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 TextureAsset: the 4-byte texture handle's static loaders and setters.
//
// Target facts (code addresses are RVAs):
//  - No constructor, destructor or vftable of TextureAsset is rowed or found in retail, and the
//    class has no virtual functions: SetQualityLevel 0x00132C9D reads [this+0], null-tests it and
//    stores its int argument at that pointer's +0x38, so +0 is a data pointer, not a vptr.
//  - The object is the handle Get 0x00132D89 returns through its hidden pointer: Get writes only
//    the dword at +0 (0x00132DA5 null name, 0x00132E4B) and raises the 16-bit count at pointee+4
//    (0x00132E4F). Callers pass that same local as this to SetQualityLevel (0x000AB301, then
//    0x000AB312) and to rva00132FE9 (0x0004F615, then 0x0004F628). RenderableRiverArea::
//    createTexture 0x0007EEBE keeps such handles at stride 4 ([esi+edi*4+0x44] at 0x0007EF07):
//    sizeof 4.
//  - The pointee is a TextureAsset::Factory. Register 0x00132BD2 allocates 0x3C and calls
//    0x001320D0, which stores table 0x007D25D8 (slot 1 Factory::PreLoad 0x00131C63) and zeroes
//    +0x30/+0x34/+0x38. Get's fallback allocates 0x3C and calls 0x00132D43 (0x001320D0, then table
//    0x007D2690, slot 1 MissingFactory::PreLoad 0x00131CA5). RegisterRecolorForHouseColorDecal
//    0x00132C28 allocates 0x54 and calls 0x0013213B (0x001320D0, then table 0x007D2630, slot 1
//    RecolorFactoryDecal::PreLoad 0x00131D54). Get stores its int options at pointee+0x30 and
//    +0x34 (0x00132E37, 0x00132E40); Factory::PreLoad reads +0x30/+0x34/+0x38.
//  - Get, Register and RegisterRecolorForHouseColorDecal are static (SA rows): they take every
//    argument from the stack and never use an incoming ECX. rva00132FE9 0x00132FE9 turns its bool
//    into 0/1 and calls SetQualityLevel with ECX unchanged.
//  - Nested classes named by rows: Impl::PreLoad 0x00131259, Factory::PreLoad 0x00131C63,
//    MissingFactory::PreLoad 0x00131CA5, RecolorFactoryDecal::PreLoad 0x00131D54. Their layouts
//    are not declared here.
//  - No ledger row mangles TextureAsset as a type, so bytes do not fix its class-key.
// Names: the verified ledger spellings. The +0 member keeps a neutral name.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_TEXTUREASSET_H_
#define __BFME2_TEXTUREASSET_H_

class BFME2ParticleTextureHandle;

class TextureAsset
{
public:
	class Impl;
	class Factory;
	class MissingFactory;
	class RecolorFactoryDecal;

	static BFME2ParticleTextureHandle Get(const char *name, int a, int b);	// 0x00132D89
	static void Register(const char *name);	// 0x00132BD2
	static void RegisterRecolorForHouseColorDecal(void *a, void *b, void *c);	// 0x00132C28
	void SetQualityLevel(int value);	// 0x00132C9D
	void rva00132FE9(bool flag);	// 0x00132FE9

	Factory *m_00;	// +0x00
};

#endif // __BFME2_TEXTUREASSET_H_
