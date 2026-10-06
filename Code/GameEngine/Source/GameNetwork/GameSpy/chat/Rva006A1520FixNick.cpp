// cl: /DNDEBUG /MD -Ireference/shims/gamespy
// Retail behavior is nickname sanitization: a leading digit or '-' and every
// character outside the GameSpy VALID_NICK_CHARS set become '_'.  Transferred
// from the exact BFME1 source (their chat/Rva00860620.cpp, named for the
// address it holds in the BFME1 image); it holds 0x006A1520 here, so the
// address-derived name tracks this image.  peerFixNickA tail-calls it.

#include <ctype.h>
#include <string.h>

#define VALID_NICK_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789[]\\`_^{|}-"

extern "C" void Rva006A1520FixNick(char *translated, const char *nick)
{
    if (isdigit(*nick) || (*nick == '-'))
        *translated++ = '_';

    char *out = translated;
    for (;;)
    {
        int character = *nick;
        if (character == 0)
            break;
        ++nick;
        if (strchr(VALID_NICK_CHARS, character) == NULL)
            character = '_';
        *out++ = (char)character;
    }
    *out = '\0';
}
