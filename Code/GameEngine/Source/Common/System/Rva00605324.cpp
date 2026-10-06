// cl: /MD
// ?Rva00605324@@YAXPAD@Z, retail 0x00605324, 65 bytes.
// Normalizes a backslash path in place: '/' to '\', tolower, then strips
// trailing backslashes. No donor; honest address name.
// Evidence: callers are FilePathGate::allow 0x00600AE5 and two sites in
// 0x00603FF8; callee tolower via IAT; sibling of Rva006053AD 0x006053AD.
extern "C" __declspec(dllimport) int __cdecl tolower(int c);
void Rva00605324(char *p)
{
    char *s = p;
    if (*s == 0)
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
        if (*(s - 1) != '\\')
            break;
        --s;
    }
done:
    *s = 0;
}
