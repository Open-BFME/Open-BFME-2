// cl: /MD /EHsc /DNDEBUG
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Donor LanguageFilter normalization with the target StringBase ABI.
// init and filterLine call this on a UnicodeString reference. Target header:
// refcount at 0, length at 4, capacity at 6, wide characters at 8.
typedef unsigned short WideChar;
typedef int Int;
typedef bool Bool;
#include <string.h>
class UnicodeString;
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
// One-character append, expanded in place: retail pushes the character's
// address and a length of 1 to concat(const WideChar *, Int).
inline void appendChar(UnicodeString &text, WideChar c) { text.concat(&c, 1); }
#include "../../Include/GameClient/LanguageFilterClass.h"
// Target RVA 0x9C0728 contains these five ignored characters and terminator.
WideChar ignoredChars[] = L"-_*'\"";
void LanguageFilter::unHaxor(UnicodeString &word)
{
    Int len = ((const StringBase<WideChar>*)&word)->getLength();
    UnicodeString newWord(L"");
    for (Int i = 0; i < len; ++i) {
        WideChar c = ((const StringBase<WideChar>*)&word)->getCharAt(i);
        if ((c == L'p') || (c == L'P')) {
            if (((i + 1) < len) && ((((const StringBase<WideChar>*)&word)->getCharAt(i + 1) == L'h') || (((const StringBase<WideChar>*)&word)->getCharAt(i + 1) == L'H'))) {
                appendChar(newWord, L'f');
                ++i;
            } else {
                appendChar(newWord, c);
            }
        } else if (c == L'1') appendChar(newWord, L'l');
        else if (c == L'3') appendChar(newWord, L'e');
        else if (c == L'4') appendChar(newWord, L'a');
        else if (c == L'5') appendChar(newWord, L's');
        else if (c == L'6') appendChar(newWord, L'b');
        else if (c == L'7') appendChar(newWord, L't');
        else if (c == L'0') appendChar(newWord, L'o');
        else if (c == L'@') appendChar(newWord, L'a');
        else if (c == L'$') appendChar(newWord, L's');
        else if (c == L'+') appendChar(newWord, L't');
        else if (wcsrchr(ignoredChars, c) == 0) appendChar(newWord, c);
    }
    ((StringBase<WideChar>*)&word)->set(*(const StringBase<WideChar>*)&newWord);
}
