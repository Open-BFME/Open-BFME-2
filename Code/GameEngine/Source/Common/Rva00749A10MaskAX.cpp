// cl: -GR- -EHsc -MD -DNDEBUG /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common

// Near-twin of BfmeMaskAX::bfmeMarkAX (twin 0x00749830, BfmeMaskAX.cpp):
// identical two-dimensional bounds-checked bit setter, only the padding
// before the begin/end byte-range pointers differs (0x3C bytes here instead
// of 0x0C), moving m_bits from +0x44/+0x48 to +0x74/+0x78. Concrete class
// identity is not present in the available BFME source or symbols, so the
// address-derived class name is intentional.

struct Rva00749A10Bytes
{
	unsigned char *m_begin;
	unsigned char *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	unsigned char &operator[](int index) { return m_begin[index]; }
};

class Rva00749A10MaskAX
{
public:
	void bfmeMarkAX(int x, int y, unsigned char value);

private:
	char m_pad00[8];
	int m_width;
	int m_height;
	char m_pad10[0x24];
	int m_pitch;
	char m_pad38[0x3C];
	Rva00749A10Bytes m_bits;
};

// address-derived: ?bfmeMarkAX@Rva00749A10MaskAX@@QAEXHHE@Z
void Rva00749A10MaskAX::bfmeMarkAX(int x, int y, unsigned char value)
{
	Rva00749A10MaskAX *self = this;

	if (x < 0)
		return;
	if (y < 0)
		return;
	if (y >= self->m_height)
		return;
	if (x >= self->m_width)
		return;

	int index = self->m_pitch * y + (x >> 3);
	if ((unsigned int)index >= self->m_bits.size())
		return;

	unsigned char *slot = self->m_bits.m_begin + index;
	if (value)
		*slot |= (unsigned char)(1 << (x & 7));
	else
		*slot &= (unsigned char)~(1 << (x & 7));
}

// Whole clean donor Rva007498E0MaskMark.cpp at BFME1 revision
// 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 supplies this sibling's
// control-flow lead. Independent complete Ghidra entry ADA1A/83 and
// native RET12 prove signed x/y bounds against +8/+C, stride +34,
// begin/end +50/+54, and a byte set/clear selected by the third argument.
// The existing ADADC/83 sibling above has the same verified transfer
// pattern with its separate buffer at +74/+78. This declares only a
// distinct observed prefix; original owners, names, unused fields and
// any relationship between these owners remain unknown.
struct Rva000ADA1AMaskBytes
{
    unsigned char *begin;
    unsigned char *end;

    // ?Rva000ADA1AMaskBytes::size present-unmatched
    unsigned size() const { return (unsigned)(end - begin); }
};

class Rva000ADA1AMask
{
public:
    void markBit(int x, int y, unsigned char value);
private:
    unsigned char reserved00[8];
    int width;
    int height;
    unsigned char reserved10[0x24];
    int pitch;
    unsigned char reserved38[0x18];
    Rva000ADA1AMaskBytes bits;
};

void Rva000ADA1AMask::markBit(int x, int y, unsigned char value)
{
    Rva000ADA1AMask *self = this;
    if (x < 0)
        return;
    if (y < 0)
        return;
    if (y >= self->height)
        return;
    if (x >= self->width)
        return;

    int index = self->pitch * y + (x >> 3);
    if ((unsigned int)index >= self->bits.size())
        return;

    unsigned char *slot = self->bits.begin + index;
    if (value)
        *slot |= (unsigned char)(1 << (x & 7));
    else
        *slot &= (unsigned char)~(1 << (x & 7));
}
