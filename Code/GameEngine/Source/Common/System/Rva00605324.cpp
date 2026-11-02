// cl: /MD
// ?Rva00605324@@YAXPAD@Z, retail 0x00605324, 65 bytes.
// Normalizes a backslash path in place: '/' to '\', tolower, then strips
// trailing backslashes. No donor; honest address name.
// Evidence: callers are FilePathGate::allow 0x00600AE5 and two sites in
// 0x00603FF8; callee tolower via IAT; sibling of Rva006053AD 0x006053AD.
#include <ctype.h>

void Rva00605324(char *path)
{
    char *cursor = path;
    if (*cursor == 0)
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
        if (*(cursor - 1) != '\\')
            break;
        --cursor;
    }
done:
    *cursor = 0;
}
