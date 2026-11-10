// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/inputs/reference/shims/campaignmanagerascii -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/LivingWorld -Ireference/shims/moduledata

#include "Common/AsciiString.h"

class Xfer;

// The two nop-arm thunk calls retail makes read their targets from the REL32
// displacements: ?rva003FAC3F@Rva003FAC3F@@QAEXXZ at 0x003FAC3F (call 0x003FB019)
// and ?rva003FAB93@Rva003FAB93@@QAEXXZ at 0x003FAB93 (call 0x003FB071), both
// already pinned at those addresses in reverse/symbols.csv. The donor's own
// stubs predate the BFME 2 addresses.
// LINK: the two helpers are rowed under their retail names.
class Rva003FAB93
{
public:
	void rva003FAB93();
};
#include "../../../Include/Common/Rva003FAC3F.h"

class LivingWorldSoundThunkCall
{
};

template <class Function, class Raw>
__forceinline Function livingWorldSoundThunk(Raw raw)
{
	union { Raw raw; Function member; } fn;
	fn.raw = raw;
	return fn.member;
}

#define LIVING_WORLD_SOUND_THUNK_CALL(object, Function, raw) \
	(reinterpret_cast<LivingWorldSoundThunkCall *>(object)->*livingWorldSoundThunk<Function>(raw))

class Rva00087750Counted;

// Retail ILT0x0002C6D8 reaches the verified ref-count assignment at0x00087750.
struct OpaqueRefElement4
{
public:
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);

	Rva00087750Counted *m_ptr;
};

#include "../../../../Libraries/Include/Lib/Coord3DBase.h"

struct Region2DBase
{
	float xMin;
	float yMin;
	float xMax;
	float yMax;
};

// Snapshot is the canonical BFME2 base from
// reference/shims/moduledata/Common/Snapshot.h (retail vtable 0x00BBB554: a
// deleting destructor then crc/xfer/loadPostProcess), which this body's
// LoadPostProcess/GetSnapshotName/DoXfer view overrides slot-for-slot.
#include "Common/Snapshot.h"

class LivingWorldSound : public Snapshot
{
public:
	LivingWorldSound &operator=( const LivingWorldSound &that );
	virtual ~LivingWorldSound();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer( Xfer &xfer );

	void Rva0061C060();

private:
	AsciiString m_name;
	Coord3DBase m_position;
	OpaqueRefElement4 m_sound;
	unsigned int m_flags;
	Region2DBase m_zoomRegion;
	int m_playState;
	bool m_shouldFade;
	bool m_isPlaying;
	bool m_hasPlayed;
};

LivingWorldSound &LivingWorldSound::operator=( const LivingWorldSound &that )
{
	if ( this != &that )
	{
		typedef void (LivingWorldSoundThunkCall::*BfmeTwoNA)(void);
		LIVING_WORLD_SOUND_THUNK_CALL(this, BfmeTwoNA, &Rva003FAC3F::rva003FAC3F)();

		m_name = that.m_name;

		m_position = that.m_position;

		m_sound = that.m_sound;
		m_flags = that.m_flags;

		m_zoomRegion = that.m_zoomRegion;

		m_shouldFade = that.m_shouldFade;
		m_isPlaying = that.m_isPlaying;
		m_hasPlayed = that.m_hasPlayed;

		if ( static_cast<unsigned int>( that.m_playState ) >= 5 && m_sound.m_ptr != 0 )
		{
			typedef void (LivingWorldSoundThunkCall::*BfmeOneNA)(void);
			LIVING_WORLD_SOUND_THUNK_CALL(this, BfmeOneNA, &Rva003FAB93::rva003FAB93)();
		}
	}

	return *this;
}
