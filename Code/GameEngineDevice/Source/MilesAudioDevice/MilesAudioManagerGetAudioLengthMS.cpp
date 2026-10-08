// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /MD /EHsc
//
// ?getAudioLengthMS@MilesAudioManager@@UAEMPBUBfmeAudioEventPrefix136@@@Z,
// retail 0x000549A3..0x00054AA1 (254 bytes, EH, RET 4).
//
// Zero Hour's AudioManager::getAudioLengthMS (GameAudio.cpp) in its BFME 2
// form: the body moved to MilesAudioManager and holds the manager's mutex
// (rowed MilesMutexGuard 0x0004120E/0x0004122F on +0x9D4), and an event with
// no info answers 0 without Zero Hour's getInfoForAudioEvent retry. A copy of
// the event (rowed copy constructor 0x002D99E3) generates its filename (rowed
// 0x002D9ADC) and play info (0x002DA8AF, not yet rowed; called by its existing
// Rva002DAAD5Owner pin), and the
// result is the attack, main and decay files' lengths through the rowed
// getFileLengthMS 0x0005492A. WorldBuilder's twin (0x007A9700) is unnamed.
//
// The three filename getters are rowed under the names their folded bodies
// carry elsewhere: the attack name is the +0x1C string 0x002D9BA6 (rowed as
// CDDrive::getPath), the main one AudioEventRTS::getFilename 0x002DA838 and
// the decay name the +0x20 string 0x002D9BC1; they are called by those names.

#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"

typedef float Real;

class MilesMutexGuard
{
public:
	MilesMutexGuard(void *m, int x);
	~MilesMutexGuard();
private:
	void *m_mutex;
	bool m_flag;
};

class AudioEventRTS
{
public:
	void rva002D9ADC();			// generateFilename
	AsciiString getFilename();
};

class Rva002DAAD5Owner
{
public:
	void rva002DA8AF();			// generatePlayInfo
};

class CDDrive
{
public:
	virtual AsciiString getPath();
};

class Rva002D9BC1AsciiField
{
public:
	AsciiString get() const;
};

struct MilesAudioEventInfoView
{
	unsigned char m_pad00[0x08];
	void *m_info08;
};

class MilesAudioManager
{
private:
	// The compiler supplies the four-byte vptr before this explicit prefix.
	unsigned char m_retailPrefix[0x9D0];
	int m_mutex9D4;

public:
	virtual Real getFileLengthMS(AsciiString strToLoad) const;
	virtual Real getAudioLengthMS(const BfmeAudioEventPrefix136 *event);
};

Real MilesAudioManager::getAudioLengthMS(const BfmeAudioEventPrefix136 *event)
{
	MilesMutexGuard guard(&m_mutex9D4, 0);
	if (!reinterpret_cast<const MilesAudioEventInfoView *>(event)->m_info08)
		return 0.0f;

	BfmeAudioEventPrefix136 tmpEvent(*event);
	reinterpret_cast<AudioEventRTS *>(&tmpEvent)->rva002D9ADC();
	reinterpret_cast<Rva002DAAD5Owner *>(&tmpEvent)->rva002DA8AF();
	return MilesAudioManager::getFileLengthMS(reinterpret_cast<CDDrive *>(&tmpEvent)->CDDrive::getPath()) +
	       MilesAudioManager::getFileLengthMS(reinterpret_cast<AudioEventRTS *>(&tmpEvent)->getFilename()) +
	       MilesAudioManager::getFileLengthMS(reinterpret_cast<Rva002D9BC1AsciiField *>(&tmpEvent)->get());
}
