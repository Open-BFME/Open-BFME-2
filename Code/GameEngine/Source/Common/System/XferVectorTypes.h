// Operand declarations for the canonical Xfer interface in vector transfers.
// An include preserves declaration order when the TU composer hoists headers.
#ifndef XFER_VECTOR_TYPES_H
#define XFER_VECTOR_TYPES_H

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

// Slot 0x2C receives a reference to a temporary string pointer. Keep that
// lifetime: a named local pointer changes retail's stack-slot reuse.
static __forceinline XferUnknown11 &XferVectorTypeName(const char *const &name)
{
	return reinterpret_cast<XferUnknown11 &>(const_cast<const char *&>(name));
}

#endif // XFER_VECTOR_TYPES_H
