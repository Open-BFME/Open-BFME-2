// cl: /O1 /arch:SSE /G7 /MD
// Retail 0x00331987/66 binary-searches 12-byte records by the first integer at key.
// Caller 0x0033280B passes five cdecl arguments: range, key,
// an empty comparator and a null distance tag. The last two are unused here.
// BFME1 Gen002DFFD0LowerBound.cpp at 34f59164 explains these STLport slots;
// the original target name remains unknown. Both signatures emit the same 66B.
struct S4LowerBoundLess {};
void *Rva00331987(void *first, void *last, const int *key, S4LowerBoundLess, int *)
{
    char *low = (char *)first;
    int count = ((char *)last - low) / 12;
    if (count <= 0)
        return low;
    int value = *key;
    do {
        int half = count >> 1;
        char *middle = low + half * 12;
        if (*(int *)middle < value) {
            low = middle + 12;
            count = count + (-1 - half);
        } else {
            count = half;
        }
    } while (count > 0);
    return low;
}
