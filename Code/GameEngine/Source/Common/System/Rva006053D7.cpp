// cl: /MD
// ?Rva006053D7@@YA_NPBD0@Z, retail 0x006053D7, 141 bytes.
// Wildcard match with '*' and '?' over NUL-terminated strings. Adapted from
// the BFME1 ArchiveFile::SearchStringMatches donor (AsciiString form) to the
// retail const-char* spelling with strlen guards and self recursion.
// Evidence: callers in 0x00603FF8 plus self; callees strlen via E8 thunks;
// sits after Rva006053AD with the same flags.
extern "C" unsigned int strlen(const char *s);
bool Rva006053D7(const char *str, const char *pat)
{
    if (strlen(str) == 0) {
        if (strlen(pat) == 0)
            return true;
        return false;
    }
    if (strlen(pat) == 0)
        return false;
    const char *c1 = str;
    const char *c2 = pat;
    while ((*c1 == *c2) || (*c2 == '?') || (*c2 == '*')) {
        if ((*c1 == *c2) || (*c2 == '?')) {
            ++c1;
            ++c2;
        } else if (*c2 == '*') {
            ++c2;
            if (*c2 == 0)
                return true;
            while (*c1 != 0) {
                if (Rva006053D7(c1, c2))
                    return true;
                ++c1;
            }
        }
        if (*c1 == 0) {
            if (*c2 == 0)
                return true;
            return false;
        }
        if (*c2 == 0)
            return false;
    }
    return false;
}
