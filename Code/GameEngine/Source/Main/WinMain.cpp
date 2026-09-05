/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Modified for BFME2: local CRT declaration and original-binary compiler flags.
// cl: /O1 /arch:SSE2
//
// nextParam is the command-line tokenizer used by the BFME entry point.
// Open-BFME-1's GeneralsMD Code/Main/WinMain.cpp defines the same helper:
// it keeps a static source cursor, treats a run of the first separator as a
// quote-like wrapper, and uses strpbrk for both the opening and closing scan.
// BFME2's caller at 0x00002CFF passes the command-line buffer and the literal
// separator string at 0x00BBB64C.  The retail cursor is at 0x00DDE034 and
// strpbrk is the MSVCR71 import at 0x00BBA6CC.

extern "C" __declspec(dllimport) char *__cdecl strpbrk(const char *,
                                                         const char *);

char *nextParam(char *newSource, char *seps)
{
    static char *source = 0;
    if (newSource)
    {
        source = newSource;
    }
    if (!source)
    {
        return 0;
    }

    // Find the next token, preserving the first separator as a quote marker.
    char *first = source;
    if (first)
    {
        char *firstSep = strpbrk(first, seps);
        char firstChar[2] = {0, 0};
        if (firstSep == first)
        {
            firstChar[0] = *first;
            while (*first == firstChar[0]) first++;
        }

        char *end;
        if (firstChar[0])
            end = strpbrk(first, firstChar);
        else
            end = strpbrk(first, seps);

        if (end)
        {
            source = end + 1;
            *end = 0;

            if (!*source)
                source = 0;
        }
        else
        {
            source = 0;
        }

        if (first && !*first)
            first = 0;
    }

    return first;
}
