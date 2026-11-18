// ??0TRoadPt@@QAE@XZ retail 0x000D4E9C 52B
//
// BFME 2's self-zeroing TRoadPt default constructor (Zero Hour's TRoadPt in
// W3DRoadBuffer.h has none). The out-of-line copy sits in the W3DRoadBuffer.cpp
// run just ahead of ??0TRoadSegInfo 0x000D4ED0; no caller reaches it directly
// because RoadSegment's constructor (0x000D6C35, RoadSegmentCtor.cpp) inlines
// the same stores: loc, top and bottom zeroed, count 0, then the four flags.
// Layout is Zero Hour's (W3DRoadBuffer.h), matching the RoadSegment view.
#include "../../../../GameEngine/Include/Common/ScalarTypes.h"

#include "../../../../../reference/shims/wwmath/Vector2.h"

struct TRoadPt
{
	TRoadPt();
	Vector2 loc;
	Vector2 top;
	Vector2 bottom;
	Int count;
	bool last;
	bool multi;
	bool isAngled;
	bool isJoin;
};

TRoadPt::TRoadPt() : loc(0.0f, 0.0f), top(0.0f, 0.0f), bottom(0.0f, 0.0f)
{
	count = 0;
	last = false; multi = false; isAngled = false; isJoin = false;
}
