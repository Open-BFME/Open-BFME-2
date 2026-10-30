// ?Init@AnimInfo@W3DAptComponentView3D@@QAE_NABVAsciiString@@PAVRva00740AB4RefTarget@@H@Z
// partial score=1.0 date=2026-10-12
// cl: /O1 /G7 /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME2 retail 0x00740AB4..0x00740BCD, 281 bytes, RET12.
// WB 0x017EEB30 explicitly identifies W3DAptComponentView3D::AnimInfo::Init
// and its source. Native empty-holder checks, path construction, asset-list
// registration, lookup, reference exchange and SetFrame caller independently
// agree with that operation. The field offsets 0/4/8/C and reference prefix
// (delete slot 0, count +4) are target evidence; the full owner type is unknown.
//
// Whole-file semantic donor: Open-BFME-1 2c01a3c4d8d93dfe6ca821ad7f650bfa8a8118c7,
// game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DAptComponentView3D.cpp,
// bindHAnim at BFME1 0x0078A5D0. BFME1 used private strings; BFME2 canonical
// AsciiString cleanup and the existing 20-byte pointer-set AssetList view
// reproduce the native body and all three EH states under /O1. StringBase
// concatenation, registry, animation lookup and SetFrame use existing owners
// or existing pins. AnimationAsset::GetAnim returns HAnimClass; this caller's
// existing HTreeClass field is only a pointer ABI view, made explicit by the
// cast, and its original field type remains to be reconciled. The allocator
// shim preserves the native null-checked free. Int mode and
// Rva00740AB4RefTarget preserve the observed ABI.

#include <set>

#include "ascii_string.h"

class HTreeClass;

#include "../../../../../Libraries/Source/WWVegas/WW3D2/AnimationAssetBFME2.h"

class Rva00740AB4RefTarget
{
public:
	virtual void release(void);
	int m_refCount;
};

struct Rva001408C0Target;
typedef _STL::set<Rva001408C0Target *> ImageAssetTree;
class AssetList {
public:
 AssetList() : m_pad(0), m_changed(true) {}
 AssetList &operator<<(const AsciiString &name);
private:
 ImageAssetTree m_tree;
 unsigned m_pad;
 bool m_changed;
};
typedef char AssetListNativeStride20[(sizeof(AssetList)==20)?1:-1];

extern void bfmeMergeReceiverKeys(int value);

class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;

class NotifyTarget;
class Rva007401A3
{
public:
	void SetFrame(int a, int b);
private:
	NotifyTarget *m_p0; // +0x00 +0x00
	void *m_p1; // +0x04 +0x04
	int m_08; // +0x08 +0x08
	int m_0C; // +0x0C +0x0C
};

class W3DAptComponentView3D { public: class AnimInfo; };

class W3DAptComponentView3D::AnimInfo
{
public:
	bool Init(const AsciiString &name, Rva00740AB4RefTarget *owner, int mode);
	void publish(int first, int second) { ((Rva007401A3 *)this)->SetFrame(first,second); }

	Rva00740AB4RefTarget *m_owner;
	HTreeClass *m_animation;
	int m_second;
	int m_first;
};

// ?Init@AnimInfo@W3DAptComponentView3D@@QAE_NABVAsciiString@@PAVRva00740AB4RefTarget@@H@Z
bool W3DAptComponentView3D::AnimInfo::Init(const AsciiString &name, Rva00740AB4RefTarget *owner, int mode)
{
	if (owner == 0)
		return false;
	if (m_owner != 0)
		return false;
	if (m_animation != 0)
		return false;

	AsciiString path(name);
	((StringBase<char> *)&path)->concat(".");
	((StringBase<char> *)&path)->concat((const StringBase<char> &)name);

	if (Rva0134FAA0)
	{
		AsciiString glob("a*");
		glob += path;
		AssetList assets;
		assets << glob;
		bfmeMergeReceiverKeys((int)&assets);
	}

	HTreeClass *anim = reinterpret_cast<HTreeClass *>(AnimationAsset::GetAnim(path.str()));
	m_animation = anim;
	if (anim == 0)
		return false;

	++owner->m_refCount;
	Rva00740AB4RefTarget *oldOwner = m_owner;
	if (oldOwner != 0)
	{
		if (--oldOwner->m_refCount == 0)
			oldOwner->release();
	}

	m_owner = owner;
	m_first = 0;
	publish(1, mode);
	return true;
}
