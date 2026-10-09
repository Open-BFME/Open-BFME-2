#!/usr/bin/env python3
"""Doxygen INPUT_FILTER: remove every comment from a source file before parsing.

Code/ and reference/ comments are written for byte-matchers: retail
addresses, member offsets, vtable slots, matcher notes and donor banners.
Many of them use Doxygen syntax (a trailing-member comment, an EA todo, a
Zero Hour brief), so Doxygen would publish them as documentation. This
filter turns each comment into whitespace, keeping every newline so line
numbers stay right, and leaves code, string literals and character literals
alone. The guide's own text lives in docs/doxygen/pages/*.md and
docs/doxygen/api/*.dox, which pass through unchanged.

Doxygen runs it as `python3 docs/doxygen/strip_comments.py FILE` and reads
the result from stdout. Nothing in the build or the hooks uses it.
"""
import sys
from pathlib import Path

DOCS_ROOT = Path(__file__).resolve().parent
PASS_THROUGH = (".md", ".dox")


def is_guide_file(path):
    """True for the guide's own pages and .dox files, which keep their comments."""
    resolved = Path(path).resolve()
    return resolved.suffix.lower() in PASS_THROUGH and DOCS_ROOT in resolved.parents


def strip_comments(text):
    """Return text with C and C++ comments blanked; newlines are kept."""
    out = []
    i = 0
    n = len(text)
    while i < n:
        c = text[i]
        if c == "/" and i + 1 < n and text[i + 1] == "/":
            # A line comment runs to the end of the line, and a backslash
            # before the newline splices the next line into it.
            out.append(" ")
            i += 2
            while i < n:
                if text[i] == "\n":
                    if text[i - 1] == "\\" or (text[i - 1] == "\r" and i >= 2 and text[i - 2] == "\\"):
                        out.append("\n")
                        i += 1
                        continue
                    break
                i += 1
            continue
        if c == "/" and i + 1 < n and text[i + 1] == "*":
            end = text.find("*/", i + 2)
            end = n if end < 0 else end + 2
            out.append(" ")
            out.append("\n" * text.count("\n", i, end))
            i = end
            continue
        if c == '"' or c == "'":
            # Copy a string or character literal verbatim, honouring escapes.
            # A quote that does not close on its line (an apostrophe in an
            # #error line or in #if 0 text) is an ordinary character, so the
            # comments after it are still found.
            j = i + 1
            limit = n if c == '"' else min(n, i + 12)
            while j < limit and text[j] != c and text[j] != "\n":
                j += 2 if text[j] == "\\" else 1
            if j < limit and text[j] == c:
                out.append(text[i:j + 1])
                i = j + 1
            else:
                out.append(c)
                i += 1
            continue
        out.append(c)
        i += 1
    return "".join(out)


def main(argv):
    if len(argv) != 1:
        print("usage: strip_comments.py FILE", file=sys.stderr)
        return 2
    data = Path(argv[0]).read_bytes()
    out = sys.stdout.buffer
    if is_guide_file(argv[0]):
        out.write(data)
    else:
        # latin-1 maps every byte to one character, so the round trip is lossless.
        out.write(strip_comments(data.decode("latin-1")).encode("latin-1"))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
