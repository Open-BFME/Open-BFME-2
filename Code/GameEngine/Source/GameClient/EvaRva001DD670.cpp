// cl: /O1 /G7 /EHsc /DNDEBUG /MD /arch:SSE /Oy- /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva001DD670@Eva@@QBE_NW4EvaEventID@@PAUVec001DCDAF@@@Z @0x001DD670 125B.
// Twin of the matched getLastReallyPlayedFrameForEvaEvent 0x001DD604 in
// Eva.cpp (same checks, same inline vector size() idivs). This body needs
// the ebp frame (/Oy-) that the shared file omits: with stable ebp-relative
// homes the eventID reloads from [ebp+8] and the output pointer spills to
// edi, giving the SIB flag access and lea copy source. Without /Oy- the
// same source spills eventID to esi and reloads the output pointer.
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

enum EvaEventID
{
	EVA_INVALID = -1
};

template <class T> class EvaVectorView
{
public:
	UnsignedInt size() const { return UnsignedInt(m_finish - m_start); }
	T &operator[](UnsignedInt i) { return m_start[i]; }
	const T &operator[](UnsignedInt i) const { return m_start[i]; }
	T *begin() const { return m_start; }
	T *end() const { return m_finish; }

private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};

#include "../../Include/Common/Vec001DCDAF.h"

struct Arg001DCDAF
{
	unsigned char m_data[0x20];
	int *m_eventIDsStart;
	int *m_eventIDsFinish;
	unsigned char m_pad28[0x2c - 0x28];
	Bool m_2c;
	unsigned char m_pad2d[0x30 - 0x2d];
};

class Rva001DCDAF
{
public:
	Real m_blockedTime;
	Real m_aboutToPlayTime;
	Vec001DCDAF m_position;
	unsigned char m_pad14[0x20 - 0x14];
	Bool m_hasPosition;
	unsigned char m_pad21;
	Bool m_hasPlayed;
	unsigned char m_pad23;
	Vec001DCDAF m_lastPlayedPosition;
	UnsignedInt m_lastReallyPlayedFrame;
};

class Eva
{
public:
	Bool rva001DD670(EvaEventID eventID, Vec001DCDAF *position) const;

private:
	unsigned char m_pad00[0x1c];
	EvaVectorView<Arg001DCDAF> m_allEventInfos;
	unsigned char m_pad28[0x5c - 0x28];
	EvaVectorView<Rva001DCDAF> m_eventStatus;
};

// Eva::rva001DD670, retail 0x001DD670 (125 bytes): the last-played-location
// query. Mirrors getLastReallyPlayedFrameForEvaEvent: clear the output,
// validate the parallel arrays through the inline sizes, require the played
// flag, then copy the +0x24 played position.
Bool Eva::rva001DD670(EvaEventID eventID, Vec001DCDAF *position) const
{
	position->x = 0.0f;
	position->y = 0.0f;
	position->z = 0.0f;
	if (eventID == EVA_INVALID)
		return false;
	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
		return false;
	if (m_eventStatus.size() != m_allEventInfos.size())
		return false;
	if (!(m_eventStatus.begin() + eventID)->m_hasPlayed)
		return false;
	Rva001DCDAF *s = m_eventStatus.begin();
	*position = s[eventID].m_lastPlayedPosition;
	return true;
}
