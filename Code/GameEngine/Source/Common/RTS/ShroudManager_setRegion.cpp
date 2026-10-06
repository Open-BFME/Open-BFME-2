// cl: /O2 /DNDEBUG /MD /EHsc
//
// ?setRegion@ShroudManager@@QAEXPBURegion3D@@M@Z,
// retail 0x0073DF50, 123 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/Common/RTS/ShroudManagerImpl.cpp,
// ShroudManagerImpl::setRegion): clamp a non-positive cell size to the
// default, then reconfigure only when the new region has non-negative width
// and height. The retail body matches the reference shape exactly, including
// the 123-byte size: the NaN-aware cell-size compare, the default cell size
// at +0x1C, and the by-value Region3D hand-off to _ReallocCells (0x73DBF0 pin).

typedef float Real;
typedef int Int;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Region3D
{
	__forceinline Region3D() {}

	__forceinline Region3D(const Region3D &other)
	{
		lo.x = other.lo.x;
		lo.y = other.lo.y;
		lo.z = other.lo.z;
		hi.x = other.hi.x;
		hi.y = other.hi.y;
		hi.z = other.hi.z;
	}

	__forceinline ~Region3D() {}

	Real width() const { return hi.x - lo.x; }
	Real height() const { return hi.y - lo.y; }

	Coord3D lo;
	Coord3D hi;
};

class ShroudManager
{
public:
	void setRegion(const Region3D *newRegion, Real cellSize);

private:
	int m_mode; // +0x00
	Region3D m_region; // +0x04
	Real m_defaultCellSize; // +0x1C
};

class ShroudManagerImpl
{
public:
	void _ReallocCells(Region3D newRegion, Real cellSize);
};

// ?setRegion@ShroudManager@@QAEXPBURegion3D@@M@Z
void ShroudManager::setRegion(const Region3D *newRegion, Real cellSize)
{
	if (cellSize <= 0.0f)
		cellSize = m_defaultCellSize;

	if (!(newRegion->width() < 0.0f)
		&& !(newRegion->height() < 0.0f))
	{
		((ShroudManagerImpl *)this)->_ReallocCells(*newRegion, cellSize);
	}
}
