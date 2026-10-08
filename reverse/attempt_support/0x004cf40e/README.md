# Acknowledgment sender continuation

Native 0x004CF40E..0x004CF578 RET8, 362 bytes; the original complete clean
attempt in `reverse/attempts/0x004cf40e.cpp` remains unchanged at score0.8.

At BFME1 34f59164 and BFME2 2aaddc7d22, the established native sibling flags
/G7 /O1 reproduce the first135 bytes, including both 40-byte allocations and
constructor branches, but emit377 bytes. The first difference is+0x88: target
reloads the original message into EBX and keeps the acknowledgment in EDI;
the compiler gives the original message EDI and spills the acknowledgment.
The source-address loop's byte counter then determines the remaining lifetime
allocation. The target does check the nullable source inside that loop.

/G6 /O1 emits385 bytes; /G7 /O2 emits496. Const pointer, zero initialization,
source tested in the loop condition, and a reference local leave the G7/O1
wall unchanged. A local address changes the prologue and emits376; named sender
locals emit373 but retain the same register mismatch. These bounded trials do
not improve the existing bank, so no bank replacement or Code/ edit was made.

The BFME1 native donor still exposes this body as a naked queueLocalCommand
lift; it supplies no new clean source repair for this wall. Continue with an
independent candidate until new lifetime or reference evidence is available.
