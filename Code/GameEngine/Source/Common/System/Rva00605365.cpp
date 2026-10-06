// cl: /MD
// ?Rva00605365@@YAPADPAD@Z, retail 0x00605365, 72 bytes.
// Normalizes a backslash path in place then trims to its parent, returning
// the new end. Combines the Rva00605324 normalize loop with the Rva006053AD
// parent scan. No donor; honest address name.
// Evidence: four callers in 0x00603C5F-0x00604783 band; callee tolower via
// IAT; sits between Rva00605324 and Rva006053AD with the same flags.
extern "C" __declspec(dllimport) int __cdecl tolower(int c);
char *Rva00605365(char *p)
{
    char *s = p;
    if (*p == 0)
        goto done;
    do {
        char c = *s;
        if (c == '/')
            *s = '\\';
        else
            *s = (char)tolower(c);
        ++s;
    } while (*s != 0);
    while (s > p) {
        if (*(s - 1) == '\\')
            break;
        --s;
    }
    if (s != p)
        *(s - 1) = 0;
done:
    return s;
}
