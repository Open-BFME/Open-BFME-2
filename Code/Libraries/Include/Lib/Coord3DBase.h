// Opt-in companion to Coord3D.h for units that pass Coord3D members as retail's three-float
// base value (Coord3D::equals/set/operator*, Xfer::operator==). Kept out of Coord3D.h because
// a complete Coord3DBase there perturbs register allocation in unrelated dependents.
#ifndef CANONICAL_COORD3DBASE_H
#define CANONICAL_COORD3DBASE_H

#include "Coord3D.h"

struct Coord3DBase {
    float x;
    float y;
    float z;
};

// The canonical Coord3D and Coord3DBase share one 12-byte float triple.
inline Coord3DBase &asBase(Coord3D &c) { return *reinterpret_cast<Coord3DBase *>(&c); }
inline const Coord3DBase &asBase(const Coord3D &c) { return *reinterpret_cast<const Coord3DBase *>(&c); }

#endif // CANONICAL_COORD3DBASE_H
