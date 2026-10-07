#pragma once
// Shared address-derived call view of native 0x002615E3. Retail reads the
// two floats at this+0x38/+0x3C and the argument's X/Y prefix at +0/+4.
// This is the provider's proven prefix view; the complete native object
// extent and owning class identity remain unresolved. No caller constructs
// this view or uses sizeof it.
// Argument records retain their own proven extents (8 or 12 bytes), so the
// pointee stays forward-declared here rather than forcing those layouts.
class Rva000CBA20Point;

class Rva000CBA20
{
    char m_pad[0x38];
    float m_x;
    float m_y;
public:
    float distSq(const Rva000CBA20Point *point);
};
