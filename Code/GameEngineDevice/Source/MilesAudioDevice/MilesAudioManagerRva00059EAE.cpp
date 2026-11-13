// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii
// platformsdk
// ?rva00059EAE@MilesAudioManager@@QAE?AVRva00051ADA@@PBVAsciiString@@@Z @0x00059EAE 206B
//
// Reference-counted audio-event-info lookup: under the manager's mutex guard
// (+0x9D4) the event table at +0xBC is searched for the name (rowed find
// 0x0041534B); a hit whose info can still take a reference (rowed try-add-ref
// 0x00050EFA) is returned as a counted reference (ctor 0x00051914, copy
// 0x00051ADA); no hit, or an info that is going away, returns the empty
// reference. Evidence: target bytes; the guard/table views of the other
// MilesAudioManager units. Method and reference class names are
// address-derived; WorldBuilder has no match for this body.
//
// Codegen: the find (0x0041534B), the reference constructor (0x00051914)
// and the reference copy (0x00051ADA) are defined here (never inlined, the
// rows' own bodies); each is needed. Seeing that the find
// only writes its result lets cl give the iterator copy the result's slot
// (retail's self-copy of [ebp-0x1c], frame 0x14); seeing that the copy only
// reads the reference it is given makes the release test read memory
// (cmp [ebp+0xC], edi) as retail does.
#include "ascii_string.h"
#include <windows.h>

#include "../../Include/MilesAudioDevice/MilesMutexGuard.h"

#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"

struct AudioEventInfo;

class AudioEventInfoRef
{
public:
	__declspec(noinline) AudioEventInfoRef(const AudioEventInfo *info) : m_info(info) { if (m_info) ((OpaqueRefCounted *)m_info)->Add_Ref(); }
	~AudioEventInfoRef()
	{
		if (m_info)
			((OpaqueRefCounted *)m_info)->Release_Ref();
	}
	const AudioEventInfo *m_info;
};

class Rva00051ADA
{
public:
	Rva00051ADA() : m_ptr(0) {}
	Rva00051ADA(const AudioEventInfoRef &ref) { rva00051ADA(*(const Rva00051ADA *)&ref, 0); }
	~Rva00051ADA()
	{
		if (m_ptr)
			((OpaqueRefCounted *)m_ptr)->Release_Ref();
	}
	__declspec(noinline) Rva00051ADA &rva00051ADA(const Rva00051ADA &other, int unused)
	{
		void *p = other.m_ptr;
		m_ptr = p;
		if (p != 0)
			((OpaqueRefCounted *)p)->Add_Ref();
		return *this;
	}
	void *m_ptr;
};

struct Rva0041534BNode
{
	Rva0041534BNode *m_next;
	AsciiString m_name;
	OpaqueRefCounted *m_info;
};
class Rva00056F61;
#include "../../../GameEngine/Include/GameClient/Rva0041534BIter.h"
class Rva00056F61
{
public:
	void *rva00056F61(const AsciiString *key);
	__declspec(nothrow) __declspec(noinline) Rva0041534BIter rva0041534B(const AsciiString *key)
	{
		return Rva0041534BIter((Rva0041534BNode *)rva00056F61(key), this);
	}
};

class MilesAudioManager
{
public:
	virtual Rva00051ADA findAudioEventInfo(const AsciiString &name) const;

private:
	char m_pad0[0xB8];
	mutable Rva00056F61 m_eventTable;	// +0xBC
	char m_padBC[0x9D4 - 0xBC - 4];
	mutable int m_mutex9D4;
};

Rva00051ADA MilesAudioManager::findAudioEventInfo(const AsciiString &name) const
{
	MilesMutexGuard guard(&m_mutex9D4, 0);
	Rva0041534BIter found = m_eventTable.rva0041534B(&name);
	Rva0041534BIter it = found;
	if (it.m_node == 0)
		return Rva00051ADA();
	if (((Rva0041534BNode *)it.m_node)->m_info->rva00050EFA())
	{
		AudioEventInfoRef ref((const AudioEventInfo *)((Rva0041534BNode *)it.m_node)->m_info);
		((OpaqueRefCounted *)ref.m_info)->Release_Ref();
		return Rva00051ADA(ref);
	}
	return Rva00051ADA();
}
