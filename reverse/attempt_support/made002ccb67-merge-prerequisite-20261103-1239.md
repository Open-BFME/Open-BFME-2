# Made002CCB67: consolidation stopped by native provider guard

At the starting revision f13dcc93a2910bb6bdbcb067805ea75747038fd1, the approved two-source
candidate has a137B method and29B constructor. No prior exact merge result was
found before this trial. Native tu_skeleton --merge --dry-run accepts zero
donors: the constructor source links at the dated census, but the merged
object would introduce three unresolved virtual members:

- ?vslot01@Rva00507823@@UAEEPBXPAVObject@@@Z
- ?vslot02@Rva00507823@@UAEEPBXH@Z
- ?vslot03@Rva00507823@@UAEXPBXPAX@Z

The canonical Rva00507823.h view has14 slots; the current helpers retain their
nonvirtual ledger spellings. This is a concrete provider/class-identity
prerequisite, not evidence for adding guessed aliases or forwarding wrappers.
The native map accepts the group, but that does not establish compatible
composition. No flags, bodies, headers, rows, paths or bindings were changed;
both source files still equal the starting revision. No merge claim was taken.
Resolve independently evidenced member identities/provider bindings before
revisiting. This rejected trial is not a completed task or a runtime gain.
The dry-run output is preserved in the delivery's Arbeitslauf/bfme2-made-dry.log.
