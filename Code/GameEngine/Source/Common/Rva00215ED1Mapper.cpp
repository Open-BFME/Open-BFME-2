// cl: /O1 /DNDEBUG /MD /EHsc
// Open-BFME-1 donor 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24:
// game/GameEngine/Source/Common/Bfme/Rva00581960Link.cpp (whole file tried).
// Native 00215ED1: private EAX input; 0 -> 0, 2 -> 1, 3 -> 2, else 3.
// The predecessor StateName body ends RET at 00215ED0; this complete switch
// ends RET at 00215EEB, immediately before the next stack-argument body.
// Internal zero arm 00215EE9 has no separate Ghidra entry or E8/E9/VA entry
// reference. Its obsolete getter claim was already rejected in deleted_rows.
// Donor carries the same switch and local emission context. Original input
// meaning, source name and callers remain unknown; the spelling is address based.

static int Rva00215ED1(int value)
{
    switch (value)
    {
    case 0: return 0;
    case 2: return 1;
    case 3: return 2;
    }
    return 3;
}

// ?Rva00215ED1Caller absent-from-retail
// Donor's local emission context preserves MSVC's private EAX convention;
// this anchor has no retail claim.
int Rva00215ED1Caller(int value)
{
    return Rva00215ED1(value);
}