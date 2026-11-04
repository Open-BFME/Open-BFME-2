# LAN options parser LANAPI header adoption (2026-11-04)

Inspected revision: f5216c1b56 (upstream 7c3b96d739 plus runner backlog).
Scope: Code/GameEngine/Source/GameNetwork/LANGameInfoParseGameOptionsString.cpp.

Replaced the private LANAPI virtual-prefix declaration with the existing
GameNetwork/LANAPI.h. Its AmIHost declaration returns int, matching the
rowed native provider at 0x004499FF; the caller consumes its low byte.
The explicit unsigned-char conversion preserves that native call-site shape.
No shared header, ledger identity, pin, alias or compiler flag changed.

Checks:
- find_declared_unmatched before/after: all definitions already matched.
- ./build.sh for this source: 7/7 matched, including four renumbered funclets
  resolved through their parent's exact EH graph; import/string/float checks pass.
- eh_verify.py: one graph EXACT; zero not-exact, baselined or missing objects.
- header_adopt_lane.py accept --class LANAPI: PASS; retires exactly one queue row.
- Ordinary link_check.py: LINKS, 607 -> 607 linked bytes; census index
  2026-11-04 02:25 at 5a13f2cd61. This is a prediction, not a new census gain.

The selected seven-source automatic adoption trial restored all failed edits.
Remaining constraints: LANAPIRva00582EB0 has ambiguous inherited m_name;
OnAccept has conflicting StringBase template declarations; OnPlayerJoin and
LANAPIhandlers have unmappable padding views; handleSetAccept needs a shared
member declaration; LANGameInfo has a four-byte private port versus canonical
unsigned-short port. These six files remain unchanged. Reconcile one constraint
before retrying it; no class-wide or TU-merge clearance is claimed.
