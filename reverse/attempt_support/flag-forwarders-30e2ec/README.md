# Flag-forwarding dependency bank

Two complete native leaves at30E2EC and30E2F5 each span9 bytes. The
first clears bit0x10 of raw receiver word44, the second sets it. Both
then tail-call30DEAE with unchangedECX and no stack argument. RET at
30E2EB precedes the pair; a distinct registered frame begins30E2FE.

The semantic guide is clean BFME1 Common/S3FlagForwarders.cpp at575ba2b0.
A fresh BFME2 O2/SSE2/G6 minimum5 Common pass found both placements.
The guide's Gen_00088B60 owner and application flag meaning are not target
identities. Address-qualified bank names retain that uncertainty.

The complete492-byte native callee takes its receiver fromECX, has no
positiveEBP argument reads, and ends with plainRET. Real calls at30E2DE
and30E36B do not observe its return. These support the bank's physically
observed no-argument call and unused result. The existing BfmeNodeEYE
method declaration is only a candidate spelling carried by symbols.csv;
this bank does not prove its original name or class identity.

Private normal GameEngine O1/SSE/G7 compilation emits the entire9 bytes
for each bank, including the REL32 resolved to actual30DEAE. No naked
body, emitter, alias, added pin, header or Code edit is used. The callee
remains unrowed at current9f50f60e, so neither leaf can be admitted or
credited as a linking recovery. blocked-on=0x0030DEAE. New C++credit0.

Private outcomes are leads, not normal admission. Once the genuine
callee/provider identity and link closure exist, port the supported
pair into its proper audio home and rerun all normal gates.
