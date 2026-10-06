// cl: /DNDEBUG /MD
//
// Returns true when arg is outside 0..1 (signed less-than-zero or greater-than-one).
// Retail uses xor-inc plus jl-jg plus xor-al shape. Evidence: 1 caller at
// 0x002D8012; honest Rva free function, no donor. Built from the banked
// attempt reverse/attempts/0x002d7acb.cpp: the flag-then-clear form is what
// keeps the bool store as xor al,al.

bool __stdcall Rva002D7ACBCheck(int x)
{
	bool r = true;
	if (x >= 0 && x <= 1)
		r = false;
	return r;
}
