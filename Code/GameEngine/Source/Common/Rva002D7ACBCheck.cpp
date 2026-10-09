// cl: /DNDEBUG /MD
//
// Returns true when arg is outside 0..1 (signed less-than-zero or greater-than-one).
// Retail uses xor-inc plus jl-jg plus xor-al shape. Evidence: 1 caller at
// 0x002D8012; WB 0x0110A570 saves ECX as this, and its Radar::addObject
// caller passes Radar in ECX. ZH Radar::isPriorityVisible supplies the name
// and priority enum; BFME2 keeps the outside-0..1 range. Built from the banked
// attempt reverse/attempts/0x002d7acb.cpp: the flag-then-clear form is what
// keeps the bool store as xor al,al.

enum RadarPriorityType
{
	RADAR_PRIORITY_INVALID,
	RADAR_PRIORITY_NOT_ON_RADAR,
	RADAR_PRIORITY_STRUCTURE,
	RADAR_PRIORITY_UNIT,
	RADAR_PRIORITY_LOCAL_UNIT_ONLY
};

class Radar
{
public:
	bool isPriorityVisible(RadarPriorityType priority) const;
};

bool Radar::isPriorityVisible(RadarPriorityType x) const
{
	bool r = true;
	if (x >= 0 && x <= 1)
		r = false;
	return r;
}
