# INI consolidation boundary after lifetime reconciliation

The supported INI.cpp merge was tried against the refreshed local index at
e9f0686bd3. Its only eligible whole-file donor is
stlport_nocase_asciistring_set_cleanup.cpp; all other relevant files are mixed or
unapproved (one is vendored). The ordinary dry run rejects the donor's bytes.
No source path or TU approval was changed and no merge is credited.

New private evidence: the three donor bodies (53/41/56 bytes) can retain exact
native bytes with the seed's inline AsciiString view when the erase specialization
uses the actual public StringBase<char>::clear provider at48BA39. The old pin at
36410 is not proof of the call's destination: the matched row and real object
provide48BA39. Existing mapped-row names are used, with no pin/alias admission.

That isolated success does not compose. The seed has declaration-only node
allocator/proxy deallocation and tree/base destructors. Together they cause the
erase body to call a deallocation wrapper instead of native free and suppress
the complete tree destructor's definition. A char-allocator view preserves the
erase operation in isolation. Making the base destructor visible restores its
inline teardown but emits a competing shared _Rb_tree_base destructor: the
ordinary LinkGuard refuses it because another unit's copy would break. An
extern-template declaration did not suppress that copy on this compiler.

A TU-local imported force-inline base destructor specialization was also tested
privately. It changes the complete destructor's EH-state instruction sequence
and does not match the native56-byte extent. It was not applied. No gate was
changed, no shared header was edited, and no nonmatching source was left in Code.

Next: reconcile the shared _Rb_tree_base<AsciiString> provider and its consumers
with its actual native owner, then rerun the supported merge. Do not remove the
declaration-only bindings merely to make compilation pass. Keep all136 seed rows,
the donor's three rows, current EH and consumer/provider guards together.

The same-subsystem INIAudioEventInfo dry run also remains blocked: the nine
whole-file donors have AudioManager/private-view, duplicate STL facade, INIException
or byte discrepancies. No audio source was edited and its temporary claims were
released. The unapproved Rva004335BCFinish.cpp donor was not moved.
