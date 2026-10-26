// Operand declarations for the AI consumers of the canonical Xfer interface.
// Keep them in an include so TU composition cannot hoist BfmeXfer.h ahead of them.
#ifndef AI_XFER_TYPES_H
#define AI_XFER_TYPES_H

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;

#endif // AI_XFER_TYPES_H
