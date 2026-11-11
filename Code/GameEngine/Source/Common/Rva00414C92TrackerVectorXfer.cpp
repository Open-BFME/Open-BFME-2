// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ?Rva00414C92@@YAPAVXfer@@PAV1@PAURva00414EA1Vector@@@Z retail
// 0x00414C92..0x00414DAA (280 bytes cdecl EH). Xfer of the
// vector<ScoredKillTracker> that ScoredKillEvaAnnouncer::DoXfer 0x00414EA1
// passes (its only caller; the pinned spelling keeps that caller's
// three-pointer Rva00414EA1Vector view). WorldBuilder twin 0x012B5E00 has
// the same shape: version {1 1} (+0x28) then "std::vector" (+0x2C) and the
// element count (+0x78); saving (+0x08) hands each 44-byte tracker to
// xferSnapshot (+0x30); loading throws XferException(4 "Vector must be
// empty on load") (ctor 0x0060C36E) unless empty then reserves the count
// (0x0041484C rowed under its folded ScoredKillTracker instantiation) and
// for each element pushes a ScoredKillTracker(1 filter 0xFFFFF) copy
// (ctor 0x0055A998 with a temporary filter 0x003623E5/0x00360D26 and
// push_back 0x00414BA4) and transfers the new back element. Same pattern as
// the ScoreKeeper per-frame stats vector xfer 0x0039C4F7.
// The filter handle default constructor is declared in
// ScoredKillTrackerView.h (Rva00360D26Member(); row 0x003623E5). Bank by a
// claude-opus-5-5 helper agent; landed by X1 with that header line.
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;
#include <vector>
#include "ScoredKillTrackerView.h"

class ScoredKillTracker;

namespace _STL
{
template <> void vector<ScoredKillTracker>::push_back(const ScoredKillTracker &value);
template <> void vector<ScoredKillTracker>::reserve(size_type n);
}

struct Rva00414EA1Vector
{
	ScoredKillTracker *begin;
	ScoredKillTracker *end;
	ScoredKillTracker *capacity;
	// back() as an in-place step of -1: retail adds -0x2C rather than
	// subtracting 0x2C.
	ScoredKillTracker &back() { ScoredKillTracker *scoredKillTracker = end; return *(scoredKillTracker += -1); }
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

#include "System/XferVectorTypes.h"
#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/XferException.h"

Xfer *Rva00414C92(Xfer *xfer, Rva00414EA1Vector *trackers)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	(*xfer == reinterpret_cast<Xfer::Version &>(version));
	UnsignedInt count = trackers->end - trackers->begin;
	((*xfer == "std::vector") == count);
	if (xfer->IsStoring())
	{
		ScoredKillTracker *end = trackers->end;
		for (ScoredKillTracker *it = trackers->begin; it != end; ++it)
			(*xfer == static_cast<Snapshot &>(*it));
	}
	else
	{
		if (trackers->begin != trackers->end)
			throw XferException(4, "Vector must be empty on load");
		reinterpret_cast<_STL::vector<ScoredKillTracker> *>(trackers)->reserve(count);
		ScoredKillTracker value(1, Rva00360D26Member(), 0xFFFFF);
		while (count--)
		{
			reinterpret_cast<_STL::vector<ScoredKillTracker> *>(trackers)->push_back(value);
			ScoredKillTracker *last = &trackers->back();
			(*xfer == static_cast<Snapshot &>(*last));
		}
	}
	return xfer;
}
