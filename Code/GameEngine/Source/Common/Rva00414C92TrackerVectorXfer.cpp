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
// (0x0041484C rowed under its folded BfmeAssignRecord44 instantiation) and
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

struct BfmeAssignRecord44;

namespace _STL
{
template <> void vector<ScoredKillTracker>::push_back(const ScoredKillTracker &value);
template <> void vector<BfmeAssignRecord44>::reserve(size_type n);
}

struct Rva00414EA1Vector
{
	ScoredKillTracker *begin;
	ScoredKillTracker *end;
	ScoredKillTracker *capacity;
	// back() as an in-place step of -1: retail adds -0x2C rather than
	// subtracting 0x2C.
	ScoredKillTracker &back() { ScoredKillTracker *tmp = end; return *(tmp += -1); }
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03(); virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version); // +0x28
	virtual Xfer &xferTypeName(const char *const &name); // +0x2C
	virtual Xfer &xferSnapshot(Snapshot *snapshot); // +0x30
	virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt *value); // +0x78
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};

Xfer *Rva00414C92(Xfer *xfer, Rva00414EA1Vector *trackers)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);
	UnsignedInt count = trackers->end - trackers->begin;
	xfer->xferTypeName("std::vector").xferUnsignedInt(&count);
	if (xfer->isSaving())
	{
		ScoredKillTracker *end = trackers->end;
		for (ScoredKillTracker *it = trackers->begin; it != end; ++it)
			xfer->xferSnapshot(it);
	}
	else
	{
		if (trackers->begin != trackers->end)
			throw XferException(4, "Vector must be empty on load");
		reinterpret_cast<_STL::vector<BfmeAssignRecord44> *>(trackers)->reserve(count);
		ScoredKillTracker value(1, Rva00360D26Member(), 0xFFFFF);
		while (count--)
		{
			reinterpret_cast<_STL::vector<ScoredKillTracker> *>(trackers)->push_back(value);
			ScoredKillTracker *last = &trackers->back();
			xfer->xferSnapshot(last);
		}
	}
	return xfer;
}
