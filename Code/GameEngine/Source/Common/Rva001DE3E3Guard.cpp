// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: self-assign guard at 0x1DE3E3 (31B). Skips when the
// argument equals this; otherwise runs the rowed 0x3A2A41 clear helper
// then the 0x1DDCC5 copy. Returns this. (First callee was VA 0x7A2A41 in
// draft; retail REL32 proves RVA 0x3A2A41, which already has a rowed name.)

class Rva000427195
{
public:
	void rva003A2A41();
};
class Rva001DDCC5
{
public:
	void rva001DDCC5(void *other);
};
class Rva001DE3E3
{
public:
	Rva001DE3E3 *rva001DE3E3(Rva001DE3E3 *other);
};

// ?rva001DE3E3@Rva001DE3E3@@QAEPAV1@PAV1@@Z
Rva001DE3E3 *Rva001DE3E3::rva001DE3E3(Rva001DE3E3 *other)
{
	if (other != this) {
		((Rva000427195 *)this)->rva003A2A41();
		((Rva001DDCC5 *)this)->rva001DDCC5(other);
	}
	return this;
}
