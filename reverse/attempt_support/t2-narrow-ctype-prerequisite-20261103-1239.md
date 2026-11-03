# Remove unused ctype specialization before T2NarrowCtype consolidation

The native merge dry-run rejected the real STLport ctype<char> definition as
a duplicate of this seed's partial local declaration. The seed's only two
defined methods are widenRange/narrowRange; both use the named memmove import
and neither references _STL or the case-map declarations. The obsolete local
ctype declaration and its stale case-map comment are removed; no real header,
compiler/profile/ABI switch, body, import binding, pin or baseline changes.

Native normal/frozen/EH and strict-provider checks pass for both existing39B
methods. Every retained external code body/relocation and all non-debug
sections including directives are identical. Before/after objects are kept
separately from any later merge. This removes a demonstrated composition
prerequisite; it is not new coverage or a runtime improvement.
