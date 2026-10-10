# Correct virtual cleanup for the 0x00319C84 vector family

Target evidence: reserve0x319C84/105 and clear0x565A60/30 reach the same complete
_Destroy body0x319784/24 as vector destructor0x319B58/63 and assignment0x319BCA/186.
The24-byte body calls0x319331. Its independently rowed26-byte loop loads the
vptr at offset0, pushes deleting-destructor flag0, calls slot0, advances16bytes,
and stops at the end pointer. This establishes virtual in-place destruction and
a16-byte element extent. It does not establish the original element name, other
members, more virtual slots, or the identity of similarly sized string records.

The old reserve/destructor sources copied an AsciiString plus vector<AsciiString>
view solely because its size was16. That view emits direct member cleanup, which
is incompatible with the native virtual cleanup. All four complete local views
now retain only a virtual destructor declaration and12 opaque bytes after vptr.
No new function, pin name/address, alias, header, emission anchor, or compiler
override is used. The same existing _Destroy name/address was re-admitted by
pin_admission --add with fold-proof naming the verified reserve source; the tool
proved its full24-byte body and recursive26-byte callee against the actual
owner. Pin consistency confirms the sole319784 address. The pin count is unchanged;
unrelated tool regeneration of hatch grant stamps was restored.

Donor lane reviewed: committed Open-BFME-1 575ba2b04743f190f069805fbdc59936123c45da,
PAVectorEraseRangeFamily003AF.cpp and Q4VectorDtorPolymorphic.cpp. Their ordinary
STLport virtual-element pattern explains the target loop; their class identities
and retail addresses are not transferred. The BFME2 PAVector owner was already
using this pattern; these four views had not inherited that virtual layout.

Verification at BFME2 65ea26e095: ordinary whole-source gate5/5 across the four
edited sources; supported strict preparation63/63 across seven explicit peers.
Both cleanup-emitting sources produce the complete26-byte helper with no
relocations, plus the complete24-byte caller whose sole REL32 reaches that helper.
The known319331 provider independently links26bytes. All source bodies, imports,
strings and float references retain ordinary full verification.

Scoped current-provider preview against the genuine f739791d66 census:
- RvaVectorDtorFamily.cpp:0 ->3338 linked bytes.
- vector319B58 destructor:0 ->63.
- vector319BCA assignment:0 ->186.
- vector319304 allocation-copy:45 retained.
- reserve/clear135:still blocked ONLY on its preexisting _Construct specialization;
  both old wrong _Destroy findings disappear. Its old blocker count was3, now1.
- unchanged PAVectorEraseRangeFamily003AF.cpp retains six unrelated findings.

Thus new unique C++ bytes0, existing linked bytes+3587, one supported remaining
family blocker. This is a provider/layout repair, not complete reserve closure.
Two bounded declaration-only attempts to suppress reserve's unowned generic
allocation-copy emission (explicit specialization, then extern-template form)
both hit VC7.1 internal compiler error _vector.c:50. They remain private, and the
source retains the original declaration rather than adding an ABI workaround.

Current upstream revalidation (2026-10-10 21:29 UTC): all four changed sources
remain 5/5 exact; seven explicit providers pass 63/63 with strict reusable
receipts, pin admission passes, and converged data has no findings. A controlled
before/after preview against the same current providers measures 71 -> 3658
linked bytes (+3587), despite the retained census already crediting those files.
The reserve's construction blocker and the unrelated PAVector findings persist.
See current-provider-revalidation.json; no new C++ bytes are claimed.
