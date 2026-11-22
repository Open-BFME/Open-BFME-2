# Preserve six new upstream changes

Integrate the six commits through1e57cb278a without rewriting the existing
branch. They touch three GUI sources, the WindowVideoManager shim and records;
they do not change AGENTS.md, native tools, the record header or its five
sources. Retain the two incoming native derived queues verbatim rather than
restamping a measurement as the combined tree.

Those published queues explicitly describe source5b758c893d2b, and report a
missing ??0BfmeVNITree@@QAE@XZ from Common/BfmeRectVNI_ctor.cpp. This is a
shared upstream unresolved link obligation, not a successful current image.
The independent local complete image with0unresolved/0duplicates belongs only
to16a726a1c0. Neither result proves the new integrated source or runtime.
No extra local task/body/unique-byte credit is assigned to integration.
