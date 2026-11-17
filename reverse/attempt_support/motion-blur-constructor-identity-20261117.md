# Motion-blur constructor identity preflight

The served GapBodiesGE37.cpp constructor at 000FD58A installs native table
007CF410. Its placeholder Rva000FD58A has one virtual destructor; retail has
seven filter methods and no destructor in that table. The source's unchanged
whole-file build passes all matched rows and reference checks.

The same native table already identifies the ScreenMotionBlurFilter method
family in ScreenMotionBlurFilterSet.cpp and ScreenMotionBlurFilterPostRender.cpp:
init, shutdown, preRender, postRender, setup, set and reset. Those views show
the same 1Ch instance layout as this constructor. Existing named providers
should own the table, rather than a new duplicate family, alias or invented
subclass. Constructor caller Rva007AC9B0FilterInits.cpp still uses the old
class spelling too.

The next step is an evidenced class-identity rename through the normal naming
tool, followed by the complete seven-slot declaration and caller verification.
That tool writes reverse/deleted_rows.csv, currently claimed by another
contributor. No source/header/ledger edit is retained; class, table and file
claims are released. The real-link bridge pass test remains open.
