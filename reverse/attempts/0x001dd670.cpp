// ?rva001DD670@Eva@@QBE_NW4EvaEventID@@PAUVec001DCDAF@@@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Oy- /EHsc /DNDEBUG /MD
//
// ?rva001DD670@Eva@@QBE_NW4EvaEventID@@PAUVec001DCDAF@@@Z retail 0x001DD670
// (125 bytes, RET 8): the position sibling of
// Eva::getLastReallyPlayedFrameForEvaEvent (0x001DD604, Eva.cpp). The output
// is cleared first; an invalid or out-of-range event, mismatched info/status
// arrays or an event that has not played return false; otherwise the status
// record's position (+0x24, written by Rva001DCDAF::rva001DD7C1) is copied
// out. Layout as in Eva.cpp: info records of 0x30 bytes at +0x1C, status
// records of 0x34 bytes at +0x5C. Retail keeps a frame pointer here, hence
// /Oy- in a unit of its own.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

enum EvaEventID
{
    EVA_INVALID = -1
};

struct Vec001DCDAF
{
    Real x;
    Real y;
    Real z;
};

template <class T> class EvaVectorView
{
public:
    UnsignedInt size() const { return UnsignedInt(m_finish - m_start); }
    T &operator[](UnsignedInt i) { return m_start[i]; }
    const T &operator[](UnsignedInt i) const { return m_start[i]; }

private:
    T *m_start;
    T *m_finish;
    T *m_endOfStorage;
};

struct Arg001DCDAF
{
    unsigned char m_data[0x30];
};

struct Rva001DCDAF
{
    unsigned char m_pad00[0x22];
    Bool m_hasPlayed;                   // +0x22
    unsigned char m_pad23;
    Vec001DCDAF m_lastReallyPlayedPosition; // +0x24
    unsigned char m_pad30[0x34 - 0x30];
};

class Eva
{
public:
    Bool rva001DD670(EvaEventID eventID, Vec001DCDAF *position) const;

private:
    unsigned char m_pad00[0x1c];
    EvaVectorView<Arg001DCDAF> m_allEventInfos;     // +0x1C
    unsigned char m_pad28[0x5c - 0x28];
    EvaVectorView<Rva001DCDAF> m_eventStatus;       // +0x5C
};

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
    if (!m_eventStatus[eventID].m_hasPlayed)
        return false;
    *position = m_eventStatus[eventID].m_lastReallyPlayedPosition;
    return true;
}
