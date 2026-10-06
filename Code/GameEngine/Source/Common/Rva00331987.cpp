// cl: /O1 /arch:SSE /G7 /MD
// Retail 0x00331987/66 binary-searches 12-byte records by the first integer at key; two callers pass the range and key by address.
void *Rva00331987(void *first, void *last, const int *key)
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
