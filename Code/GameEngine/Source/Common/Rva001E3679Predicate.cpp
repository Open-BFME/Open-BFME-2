// cl: /O1
// BFME1 reference 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24:
// game/GameEngine/Source/Common/BoundedIndexPredicates.cpp (whole file tried).
// Target: Ghidra entry 001E3679 is 21 bytes, ending RET at 001E368D.
// Native caller 002E7B47 pushes its integer, tests AL, and pops the argument;
// the body uses signed comparisons against 2 and 15 and returns 0 or 1.
// Donor: the same closed-interval predicate. Its five closed-interval names fold to this
// target in the donor trial; none establishes an application identity here.
// The underlying enumeration and the meaning of this interval remain unknown.

bool Rva001E3679(int value)
{
    return value >= 2 && value <= 15;
}