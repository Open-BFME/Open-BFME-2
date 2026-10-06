// cl: /DNDEBUG /MD
// Transferred unchanged from Open-BFME-1 5cae4bdff game/GameEngine/Source/Common/Rva009A78E0.cpp;
// bfme1_sweep places the same masked body: Rva009A78E0 at BFME2 0x001B8340. Addresses in the donor text are BFME1.
// 0x009A78E0..0x009A794E: INT3 before entry and after complete RET.
// Source bytes at +0 and +startIndex are weighted into 32-bit destinations.
void Rva009A78E0(const unsigned char *source, int *destination,
                int sourcePitch, int startIndex, int rows, int columns,
                const int *weights)
{
    if ((unsigned)rows > 0) {
        unsigned rowCount = (unsigned)rows;
        do {
            unsigned column = 0;
            if ((unsigned)columns > 0) {
                do {
                    int value = source[startIndex] * weights[1];
                    value += source[0] * weights[0];
                    destination[column] = (value + 0x40) >> 7;
                    ++source;
                    ++column;
                } while (column < (unsigned)columns);
            }
            source += sourcePitch - columns;
            destination += columns;
        } while (--rowCount != 0);
    }
}
