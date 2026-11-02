// cl: /MD
// ?Rva00605365@@YAPADPAD@Z, retail 0x00605365, 72 bytes.
// Normalizes a backslash path in place then trims to its parent, returning
// the new end. Combines the Rva00605324 normalize loop with the Rva006053AD
// parent scan. No donor; honest address name.
// Evidence: four callers in 0x00603C5F-0x00604783 band; callee tolower via
// IAT; sits between Rva00605324 and Rva006053AD with the same flags.
#include <ctype.h>

char *Rva00605365(char *path)
{
    char *cursor = path;
    if (*path == 0)
        goto done;
    do {
        char character = *cursor;
        if (character == '/')
            *cursor = '\\';
        else
            *cursor = (char)tolower(character);
        ++cursor;
    } while (*cursor != 0);
    while (cursor > path) {
        if (*(cursor - 1) == '\\')
            break;
        --cursor;
    }
    if (cursor != path)
        *(cursor - 1) = 0;
done:
    return cursor;
}
