// cl: /O1  /arch:SSE /DNDEBUG /MD
// ZH Line2D.cpp reference body already has a retail owner25F653.
// Canonical Coord2D is class-key class; the old TU uses struct. This is
// the same semantic function and complete274B body with no relocations;
// reconcile its class-key spelling for canonical camera consumers.
// Donor reference is pinned BF1 f98983a7 / inputs/reference ZH.
// Zero new retail bytes; no opaque pin or inferred second function.
#include "../../../Libraries/Include/Lib/Coord2D.h"
bool IntersectLine2D( const Coord2D *a, const Coord2D *b, 
										   const Coord2D *c, const Coord2D *d, 
											 Coord2D *intersection)
{
	if (!a || !b || !c || !d) {
		// sanity. Lines that do not have endpoints do not intersect.
		return false;
	}

	float r, s, denom;

	denom = ((b->x - a->x) * (d->y - c->y) - (b->y - a->y) * (d->x - c->x));
	if (denom == 0) {
		// the lines are parallel.
		return false;
	}

	r = ((a->y - c->y) * (d->x - c->x) - (a->x - c->x) * (d->y - c->y) ) / denom;
	s = ((a->y - c->y) * (b->x - a->x) - (a->x - c->x) * (b->y - a->y) ) / denom;

	if (0 <= r && r <= 1 && 0 <= s && s <= 1) {
		// The lines intersect.
		if (intersection) {
			intersection->x = a->x + r * (b->x - a->x);
			intersection->y = a->y + r * (b->y - a->y);
		}

		return true;
	}

	return false;
}

