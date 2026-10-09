// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// W3DScriptedModelDraw::getAnimationFrameCount and the two numbering helpers
// it calls, which share this unit: retail keeps the module's state pointer in
// EDX across either helper call, which cl only does for callees it has
// already compiled in the same unit.
//
// ?Rva000B2BA3Get@@YAHPBURva000B2BE5Src@@PA_N@Z, retail 0x000B2BA3..0x000B2BE5
// (66 bytes), cdecl: the animation numbering mode from TheGameLODManager's
// +0x1774 setting. Unless that is 3, a drawable with the 0x20 status bit
// (+0x114) forces mode 0 and reports it through the optional flag. Mode 0
// answers 2, mode 1 answers 1, anything else 0. Sibling of the rowed
// Rva000B2BE5Get (0x000B2BE5), which tests the same bit; WorldBuilder twin
// 0x0091E640 unnamed.
//
// ?getAnimationFrameCount@W3DScriptedModelDraw@@UAE_NABVAsciiString@@PAH@Z,
// retail 0x000BF953..0x000BF9FC (169 bytes, ret 8), named by its
// WorldBuilder twin 0x00930960 (W3DScriptedModelDraw.cpp). It overrides an
// interface virtual whose subobject sits at +0x0C, so this points there:
// module data at -8, drawable at -4, the current state at +8 and an index at
// +0xB0. Without an output it fails. Otherwise it looks the animation up
// through the rowed 0x000BF7E8 with the state's base (+0x58) and model
// (+0x70) names:
//  - numbered by Rva000B2BA3Get when the module data's +0x135 flag is set;
//  - numbered by Rva000B2BE5Get when its +0x134 flag is set;
//  - unnumbered otherwise.
// It stores the clip's frame count, reads its frame rate (unused), releases
// it and succeeds.
#include "ascii_string.h"

class HTreeClass;

HTreeClass *Rva000BF7E8FindAnimTree(const AsciiString &pattern, const AsciiString &base,
	const AsciiString &model, bool numbered, int number);

struct Rva000B2BE5Src
{
	char pad[0x114];
	unsigned char flag;
};


class GameLODManager;
extern GameLODManager *TheGameLODManager;

struct Rva000B2BA3LOD
{
	char m_pad0000[0x1774];
	int m_mode1774; // +0x1774
};

int __cdecl Rva000B2BA3Get(const Rva000B2BE5Src *p, bool *forced)
{
	int mode = reinterpret_cast<Rva000B2BA3LOD *>(TheGameLODManager)->m_mode1774;
	if (mode != 3 && p && (p->flag & 0x20))
	{
		if (forced)
			*forced = true;
		mode = 0;
	}
	switch (mode)
	{
	case 0:
		return 2;
	case 1:
		return 1;
	case 2:
	case 3:
		return 0;
	}
	return 0;
}

// ?Rva000B2BE5Get@@YAHPBURva000B2BE5Src@@H@Z, retail 0x000B2BE5..0x000B2BFF
// (26 bytes), cdecl: 2 for a drawable with the 0x20 status bit, else the
// fallback (callers 0x000BF33F 0x000BF4D2 0x000BF996 0x000C2ECC).
int __cdecl Rva000B2BE5Get(const Rva000B2BE5Src *p, int fallback)
{
	if (p && (p->flag & 0x20))
		return 2;
	return fallback;
}

// The loaded clip: Delete_This (slot 0), frame count (slot 5), frame rate
// (slot 6) and its reference count at +4.
class Rva000BF953Clip
{
public:
	virtual void deleteThis();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual int getNumFrames();
	virtual float getFrameRate();

	void releaseRef()
	{
		if (--m_refs == 0)
			deleteThis();
	}

private:
	int m_refs; // +0x04
};

struct Rva000BF953ModuleData
{
	char m_pad000[0x134];
	bool m_numberByStatus134; // +0x134
	bool m_numberByLOD135;    // +0x135
};

struct Rva000BF953State
{
	char m_pad00[0x58];
	AsciiString m_base58;     // +0x58
	char m_pad5C[0x70 - 0x5C];
	AsciiString m_model70;    // +0x70
};

class Rva000BF953Module
{
public:
	virtual void m00();

	const Rva000B2BE5Src *getDrawable() const { return m_drawable; }

protected:
	Rva000BF953ModuleData *m_moduleData; // +0x04
	Rva000B2BE5Src *m_drawable;          // +0x08
};

class Rva000BF953FrameInterface
{
public:
	virtual bool getAnimationFrameCount(const AsciiString &name, int *frames) = 0;
};

class W3DScriptedModelDraw : public Rva000BF953Module, public Rva000BF953FrameInterface
{
public:
	virtual bool getAnimationFrameCount(const AsciiString &name, int *frames);

private:
	char m_pad10[0x14 - 0x10];
	Rva000BF953State *m_state14; // +0x14
	char m_pad18[0xBC - 0x18];
	int m_index0BC;              // +0xBC
};

bool W3DScriptedModelDraw::getAnimationFrameCount(const AsciiString &name, int *frames)
{
	if (frames == 0)
		return false;

	HTreeClass *found;
	if (m_moduleData->m_numberByLOD135)
		found = Rva000BF7E8FindAnimTree(name, m_state14->m_base58, m_state14->m_model70, true,
			Rva000B2BA3Get(getDrawable(), 0));
	else if (m_moduleData->m_numberByStatus134)
		found = Rva000BF7E8FindAnimTree(name, m_state14->m_base58, m_state14->m_model70, true,
			Rva000B2BE5Get(getDrawable(), m_index0BC));
	else
		found = Rva000BF7E8FindAnimTree(name, m_state14->m_base58, m_state14->m_model70, false, 0);

	if (found == 0)
		return false;
	Rva000BF953Clip *clip = reinterpret_cast<Rva000BF953Clip *>(found);
	*frames = clip->getNumFrames();
	clip->getFrameRate();
	clip->releaseRef();
	return true;
}
