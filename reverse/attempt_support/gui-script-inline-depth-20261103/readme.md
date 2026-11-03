# Script TU inline-depth composition defect

At the revision in before.json, the ordinary Script build verifies all 30 rows,
26 string literals, two empty-string references and three imports. The merge dry
run exits 2 with zero accepted donors and rejects its own seed for bytes.

The source brackets four AsciiString globals with inline_depth(0) and its reset.
Calling tu_skeleton.compose on the seed alone moves both directives before all
four objects. before.json records the exact original/composed token order.
This is a composition defect, separate from the private class layouts, manager
virtual slots, strtok linkage and donor anchor declarations the dry run also
rejects. No source row, extent, flags, pin, alias or baseline was changed.

Reproduction: call composition_chunks/compose on a fixture containing a class
constructor declaration, inline_depth(0), four object declarations and the
inline_depth() reset. Both directives must continue to bracket the objects.
The tool currently emits the reset ahead of the objects.

The next useful change is a regression-tested composition repair preserving
closed declaration-only inline_depth scopes. It must retain normal byte and
link judgments; success would not establish that the remaining donors merge.

Repair validation: [validation.json](validation.json) records the two failing
regression fixtures, the passing composition/exploit suite and the real merge
dry run. Preserving the closed declaration scope restores the seed and permits
its three-row parseTooltip donor: 33 rows pass the existing byte/link guards.
Other donors retain their compile/view conflicts. This receipt applies no
source move and claims no census change; the accepted merge is the next step.
