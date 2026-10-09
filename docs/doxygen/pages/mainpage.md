# Open-BFME-2 developer guide {#page_mainpage}

Open-BFME-2 rebuilds the engine of *The Lord of the Rings: The Battle for
Middle-earth II*, version 1.06, as C++. The engine binary is `game.dat`, and
every function written here must compile with Visual C++ 7.1 back to exactly
the bytes of the same function in the retail file. The retail binary is the
ground truth: the names and types in the source are reconstructions backed by
evidence, and some are still placeholders.

This guide is for developers who want to understand that code: what each
part of the engine does, how the parts fit together and how to read the
source. The repository's other documents (`README.md`, `AGENTS.md` and
`docs/*.md`) describe the matching work itself.

## Building the guide {#page_mainpage_build}

From the repository root:

    mkdir -p build/doxygen && doxygen docs/doxygen/Doxyfile

Then open `build/doxygen/html/index.html`. It needs Doxygen (tested with
1.9.8) and Python 3, which runs the input filter; nothing is compiled.
Warnings go to `build/doxygen/warnings.log`.

## What the guide covers {#page_mainpage_scope}

The guide is written by hand, and it covers code whose identity and behaviour
are settled. Code that is still being reverse engineered is described by its
contract, or not yet at all. Where a statement comes from the Zero Hour
source that the engine descends from, rather than from BFME 2 itself, it says
so.

Comments inside the source files are working notes for byte matching. They
are not part of this guide; open a file in the repository to read them.

The guide's pages are being written. Contributors start with
`docs/doxygen/README.md`.
