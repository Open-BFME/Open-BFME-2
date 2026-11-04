# RainOfFireUpdate destructor composition prerequisite

Base: `2364d797a3`, following the canonical module hierarchy repair.

With the canonical hierarchy present, the merger first refused the destructor
on its private field name `m_state2C`. The destructor's five fields now use the
existing TU view's names at the same offsets: frame +0x24, darkness +0x28,
scale +0x2C, pending +0x30 and ramp +0x34. The destructor only writes scale.

The next composed object lacked the explicit destructor, deleting destructor
and EH symbols. RainOfFireUpdateView.h had only an implicit destructor; adding
the out-of-line virtual destructor declaration makes the composed definitions
available under their rowed names.

Checks:

- `./build.sh` on RainOfFireUpdate.cpp and RainOfFireUpdateDtor.cpp: 13/13 rows
  exact, both EH funclet labels verified through their parent graphs, two string
  and 13 float literals exact.
- Declared-unmatched check on both sources and the private header: clear.
- The supported merge dry run accepts the main TU and destructor donor: all 13
  rows and the census link guard pass. The constructor still fails on its
  explicit Secondary20 table declaration. The two mixed sources remain out.
- The destructor's link preview before this final declaration-only header change
  was LINKS, 129 -> 129 bytes against census `2f0cb97f52` (2026-11-04 16:16).

The existing Secondary20 alternatename is retained verbatim. No paths move in
this prerequisite commit; apply the supported merge in the next commit.
