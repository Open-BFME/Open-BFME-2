#ifndef BFME2_ARMY_MOVE_COORDINATE_VIEW_H
#define BFME2_ARMY_MOVE_COORDINATE_VIEW_H
// Native AdjustArmyMoveTargetPos at 0x002B2858 returns two floats through a hidden
// pointer; callers 0x002B28B1 and 0x002B2702 copy those floats into an eight-byte
// by-value argument for 0x002B26D0. Its empty nontrivial lifetime is part of ABI.
struct Rva002B2858Coord
{
	Rva002B2858Coord() {}
	Rva002B2858Coord(const Rva002B2858Coord &that) : x(that.x), y(that.y) {}
	~Rva002B2858Coord() {}
	float x;
	float y;
};
#endif
