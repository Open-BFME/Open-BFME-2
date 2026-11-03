// Target facts: RectClass has no virtual functions or bases. RVA 0x001540D0 translates four floats at +0/+4/+8/+0xC; 0x00154120 unions their bounds. The adjacent rectangles at Render2DSentenceClass+0x8C/+0x9C (stores 0x00157F68..0x00157FA0) establish sizeof 0x10. Ledger ABVRectClass spellings establish class-key class.
// Target facts: 0x00044C71..0x00044C8B constructs all four bounds inline before Add_Outline at 0x00044C90. Set_Coordinate_Range at 0x001188C4..0x001188E3 subtracts +0 from +8 and +4 from +0xC; Zero Hour WWMath/rect.h names these Left, Top, Right, Bottom and Width/Height.
// Target facts: Set_Clipping_Rect calls the four-dword assignment at 0x0004254E from 0x00105DA3. Assignment and the rowed operator+= overloads (0x001540D0, 0x00154120) are declared out of line. No RectClass constructor, destructor or vftable is named in the ledger.

#ifndef BFME2_RECTCLASS_H
#define BFME2_RECTCLASS_H

class Vector2;

class RectClass
{
public:
    float Left;
    float Top;
    float Right;
    float Bottom;

    RectClass() {}
    RectClass(float left, float top, float right, float bottom)
        : Left(left), Top(top), Right(right), Bottom(bottom) {}

    RectClass &operator=(const RectClass &rect);
    RectClass &operator+=(const Vector2 &offset);
    RectClass &operator+=(const RectClass &rect);

    float Width() const { return Right - Left; }
    float Height() const { return Bottom - Top; }
};

#endif
