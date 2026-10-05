// cl: /O1 /MD
// ?Rva006053AD@@YAPADPAD@Z, retail 0x006053AD, 42 bytes.
// Trims a backslash path to its parent in place: scans to NUL then back to
// the last backslash and truncates there, returning the name after it (the
// path itself when there is no backslash). No donor; honest address name.
// Evidence: sole caller is FilePathGate::allow 0x00600AE5, which compares the
// returned pointer with the path and looks the name up; callees none.
char *Rva006053AD(char *p)
{
    char *e = p;
    if (*p != 0) {
        while (*e != 0)
            ++e;
        while (e > p) {
            if (*(e - 1) == '\\')
                break;
            --e;
        }
        if (e != p)
            *(e - 1) = 0;
    }
    return e;
}
