// ?rva00215ED1@@YAHH@Z
// partial score=1.0 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHsc
// Donor: Open-BFME-1 6d9434269164392c5ba62aaa7c15a86b5b020d76,
// game/GameEngine/Source/Common/Bfme/Rva00581960Link.cpp, compiled /O1.
// Retail 0x00215ED1 is a complete 27B body with a private EAX argument:
// 0 -> 0, 2 -> 1, 3 -> 2, otherwise 3. The input's application meaning
// remains unknown. The donor's adjacent pointer-link setter does not place.

static int rva00215ED1(int value)
{
    switch (value)
    {
    case 0:
        return 0;
    case 2:
        return 1;
    case 3:
        return 2;
    }
    return 3;
}

// ?Rva00215ED1Caller absent-from-retail
// TU-local call context retained from the donor to emit the private register
// convention. This emitter has no retail claim.
int Rva00215ED1Caller(int value)
{
    return rva00215ED1(value);
}
