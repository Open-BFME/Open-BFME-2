# Fire-logic vector merge environment

2026-11-04, prerequisite parent `98e6487d7a`.

After the payload-view repair, the guarded merge still rejected all four
candidates with `bytes`. A scratch composition through tu_skeleton's Verifier
isolated the vector refusal: the seed's explicit specialization declarations
suppressed both rowed definitions, even beside the donor's explicit vector
instantiation. Removing those declarations restored push_back, but overflow
then emitted STLport's catch/rethrow wrapper. Adding the donor's existing
`_STLP_NO_EXCEPTIONS` setting made all 31 seed-plus-vector rows exact, and
LinkGuard.prepare/judge returned no objections for that two-source scope.
No verifier or admission check was changed.

Apply that environment repair to the seed separately before consolidation:
remove only the vector's two suppression declarations and unused forward
declaration, and carry the donor's STLport exception-macro setting. C++ EH
remains enabled, including the seed's existing parent unwind graphs.

Checks on the edited seed:

- `./build.sh .../Map/FireLogicSystem.cpp`: 29/29 matched; six funclet pins
  verified through parent EH data after compiler-label renumbering. Literal and
  import checks pass.
- `find_declared_unmatched.py`: all definitions matched.
- `link_check.py`: LINKS, 2,521 -> 2,521 bytes against the 2026-11-04 07:28
  index at a62ac1c10b. Preview only; no new census measurement.

Next: apply the normal guarded tu_skeleton merge; investigate other donors
only if their failures remain after composition under this environment.
