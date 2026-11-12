# Profile command table at RVA 0x008E7CB0

Tested on c59c29cdf6. The startup initializer at 0x007B6690 stores the
profile table and zeroes the two members inline. The constructor row at
0x006C5430 independently installs that same table. The queue shows three
retail targets in order: 0x00118640, 0x006C68C0 (Execute), and the shared
one-byte return at 0x0069E440. The profile object currently emits two slots.

Giving DebugCmdInterface a virtual destructor ahead of the derived Execute
and Delete declarations changed the initializer to an out-of-line call to
the profile constructor. Declaring the profile destructor out of line,
using the imported inline debug constructor found in debug_cmd.cpp, and
retaining novtable on the base did not recover the initializer bytes.
The novtable variant with a throw() profile constructor also failed.
StopRange changed instruction order in the same builds. With the trial
removed, build.sh on GlobalChainCleanup.cpp, profile.cpp and profile_cmd.cpp
verified all 36 rows, both data rows and all 16 named imports.

The constructor fold dry run refuses the third owner's deleting destructor
at 0x00118640. Folding the destructor owner into ProfileCmdInterface also
refuses: its complete destructor installs the base DebugCmdInterface table
at VA 0x00BBE7EC. Next investigate the derived deleting destructor and
the base-table store together with the other retail users of 0x00118640
before assigning that shared target to a class. No coverage changes.
