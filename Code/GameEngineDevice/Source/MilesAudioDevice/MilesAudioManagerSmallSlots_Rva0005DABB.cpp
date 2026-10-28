// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX-
// platformsdk
// Split from MilesAudioManagerSmallSlots.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// Small MilesAudioManager vtable slots (vtable VA 0x00BC55B0, which also holds
// stopAudio and the rows of MilesAudioManagerRva0005168C.cpp) that had no
// ledger owner. Byte fields +0x69E..+0x6A2 are the ones that sibling's setter
// stores under the same flag bits; the getter here reads them back.
//
// The two AIL preference updates and the AIL_serve slot are the BFME2 copies
// of Open-BFME-1's Rva006962A0PreferenceProduct.cpp bodies (donor source,
// same shape; BFME2 reads +0x84/+0x88 of the +0x10 settings object where BFME1
// read +0x48/+0x4C). The object at +0xBE8 is the one whose destructor is the
// opaque pin 0x00260A3C and whose scalar deleting dtor is 0x000453F5; its
// 0x00045837 query is called here for a bool result. Method names stay
// address derived: the bytes prove the hops, offsets and argument counts only.

#include <windows.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

extern "C" __declspec(dllimport) int __stdcall AIL_get_preference(
	unsigned int preference);
extern "C" __declspec(dllimport) void __stdcall AIL_set_preference(
	unsigned int preference, int value);
extern "C" __declspec(dllimport) void __stdcall AIL_serve(void);

// The subtitle window (destructor row 0x00260A3C, nonvirtual) and its state
// query 0x00045837, both rowed under these names.
class SubTitleWindow
{
public:
	~SubTitleWindow();
	Bool rva00045837() const;
};

struct Rva000517F1Settings
{
	char m_pad00[0x84];
	UnsignedInt m_84;
	UnsignedInt m_88;
};

struct Rva0005185EBlock
{
	char m_pad00[0x38];
	Int m_38;
	Int m_3c;
	Int m_40;
};

struct Rva00053281Lock
{
	char m_pad00[0x40];
	CRITICAL_SECTION m_section;	// +0x40, handed to Enter/LeaveCriticalSection
	Bool m_58;
};

struct Rva000527E2Event
{
	char m_pad00[8];
	Int m_8;
};

class AudioEventRTS;

class MilesAudioManager
{
public:
	unsigned int addOrResumeAudioEvent(AudioEventRTS *a, Int b, Int c, Int d, Int e);

	virtual void rva000514BB();
	virtual void rva000517F1();
	virtual void rva0005181B();
	virtual void rva00051840();
	virtual void rva0005185E(Int *a, Int *b, Int *c);
	virtual unsigned char rva0005164F(unsigned char flags);
	virtual Bool rva000527E2(const Rva000527E2Event *event);
	virtual Bool rva000531F6();
	virtual void rva00053281();
	virtual void rva0005329C();
	virtual void rva0005DABB(Int a);
	virtual void slot23(const Int &a);
	virtual void rva0005DACF(const Int &a);
	virtual void rva0005DAE6(Int a, Int resumeHandle);
private:
	char m_pad00[0x0C];
	Rva000517F1Settings *m_10;
	char m_pad14[0x69e - 0x14];
	unsigned char m_69E;
	unsigned char m_69F;
	unsigned char m_6A0;
	unsigned char m_6A1;
	unsigned char m_6A2;
	char m_pad6A3[0xb8c - 0x6a3];
	Rva0005185EBlock *m_b8c;
	Rva00053281Lock *m_b90;
	char m_padB94[0xbe8 - 0xb94];
	SubTitleWindow *m_be8;
};











// Native5D734 returns an audio handle in EAX; WB786F40 identifies addOrResumeAudioEvent.
// These vtable wrappers discard the returned handle.
// vtable 0x00BC55B0#25
void MilesAudioManager::rva0005DABB(Int a)
{
	addOrResumeAudioEvent(reinterpret_cast<AudioEventRTS *>(a), 0, 1, 0, 1);
}

// vtable 0x00BC55B0#29
void MilesAudioManager::rva0005DAE6(Int a, Int resumeHandle)
{
	addOrResumeAudioEvent(reinterpret_cast<AudioEventRTS *>(a), 1, resumeHandle, 0, 1);
}

// vtable 0x00BC55B0#24: the argument is an object whose first dword is the
// event pointer; the equal-arm read keeps retail's load ahead of the constant
// pushes.
void MilesAudioManager::rva0005DACF(const Int &a)
{
	addOrResumeAudioEvent(reinterpret_cast<AudioEventRTS *>((a ? a : a)), 0, 1, 0, 1);
}

// vtable 0x00BC55B0#23: a second virtual with the same body; ICF folds it
// onto 0x0005DACF, so slots 23 and 24 both hold that address.
// ?slot23@MilesAudioManager@@ present-unmatched (ICF-folded at 0x0005DACF; pinned)
void MilesAudioManager::slot23(const Int &a)
{
	addOrResumeAudioEvent(reinterpret_cast<AudioEventRTS *>((a ? a : a)), 0, 1, 0, 1);
}
