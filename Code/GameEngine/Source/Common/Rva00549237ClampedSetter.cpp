// cl: /O1 /DNDEBUG /MD
//
// Clamped setter, retail 0x00549237 (27 bytes).
//
// Leaf thiscall: clamps the argument into [2, 6] and stores it at +0x04.
// Retail shares one pop for both clamp arms (push 2 then jump into the
// pop; push 6 then fall into it), which is the natural lowering of the
// if/else-if below under /O1.
//
// Provenance: sole caller is the 0x00549556 site inside the 0x1BC-stride
// element loop of the drawable-creating region; the owning class is
// otherwise unknown, so this uses an address-honest Rva vehicle.

class Rva00549237Setter
{
public:
	void set(int value);

private:
	int m_pad00;
	int m_clamped04;
};

// ?set@Rva00549237Setter@@QAEXH@Z, retail 0x00549237 (27B).
void Rva00549237Setter::set(int value)
{
	if (value < 2)
		value = 2;
	else if (value > 6)
		value = 6;
	m_clamped04 = value;
}
