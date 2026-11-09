# Pin names whose kept body differs from retail, image 1a6707e43c

Read-only, from diagnostic image `diagnostic-link-1a6707e43c9ab9952a5c02031b3c742843e40a3a`, its map and
retail's `game.dat`, on 2026-11-09. For each name in `reverse/symbols.csv` that has no row, take the body the
map keeps under that name and compare its instruction mnemonics with retail's at the pinned address, up to the
extent of the row there. Relocated operands aren't compared.

`pins 8366 kept under the pin's name 5261 same 5064 differ 196 no retail extent 1`

The kept-copies list in `../kept-copies-20261109/` reads rowed names only, so it can't see these. This is a
lead list, not a list of defects: many will be folds that behave the same, or scheduling differences. One is
proven harmful, 0x00155490 (LINK-655). No entry here has been run.
