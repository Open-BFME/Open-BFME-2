### LINK-695: render-object copy virtual provider identities

Status: Blocked. Inspected `579a7e91d2`, 2026-11-20.

`Rva003AE6A9CopyCtor.cpp` retains three bridged tables at 0x0081D4E4,
0x0081D4F4 and 0x0081D520. Native secondary name/transfer slots belong to
different rowed owners than the inherited RenderObjectDrawModuleInfo
methods. The primary view leaves nine concrete native slots pure.

The prerequisite is class/provider reconciliation with ConstIntGetters4,
GapForwardersSeat8 and the existing destructor/transfer owners, not new
aliases. Include the explicit consumer Rva005634F7Ctor.cpp and preserve its
0x18 secondary-base ABI. The unchanged owner passes 3/3 function rows;
no table repair or bridge retirement is claimed.

[Native slot inventory and next checks](../../reverse/attempt_support/fx-renderobject-copy-bridges-20261120.md).
Confirmation requires the next maintainer-published real link; no such run
was started by this investigation.
