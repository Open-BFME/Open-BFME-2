// cl: /MD
// ?rva003B0E83@Rva003B0E83@@QAEPAV1@XZ @0x003B0E83 16B
// Unlock lane: writes four 1.0f floats at +0/+4/+8/+12 then returns this.
// Evidence: no callees; callers 0x001FEB8B and 0x002B0F3C; prev ConstIntGetters next Handicap same dir.
class Rva003B0E83
{
public:
	Rva003B0E83 *rva003B0E83();
private:
	int m_data[4];
};

Rva003B0E83 *Rva003B0E83::rva003B0E83()
{
	for (int i = 0; i < 4; ++i)
		m_data[i] = 0x3f800000;
	return this;
}

// ?rva003B0E75@Rva003B0E75@@QAEXXZ @0x003B0E75 14B
// Leaf: writes four 1.0f ints at +0/+4/+8/+12 void return sibling of 0x003B0E83.
// Evidence: no callees; caller 0x002AFB52; prev ConstIntGetters next Rva003B0E83Init same shape.
class Rva003B0E75
{
public:
	void rva003B0E75();
private:
	int m_data[4];
};

void Rva003B0E75::rva003B0E75()
{
	for (int i = 0; i < 4; ++i)
		m_data[i] = 0x3f800000;
}
