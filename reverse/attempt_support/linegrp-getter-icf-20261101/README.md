# Verified LineGroup shader getter fold

Bank the existing clean C++ Get_Shader body as a 12-byte ICF twin of the
already-rowed PointGroup getter at 0x0013EDB0. add_match --icf-owner performs
the ordinary admission, byte verification and marker removal. The existing
LineGroup pin already names that address; no pin is added or edited. Both
class layouts read the shader at +0x28. Native calls at 0x001A7B3C,
0x001AE11F and 0x001AE1FB in matched ParticleBuffer getter/copy-constructor
rows all reach the same target. The method name, receiver contract and return
view are supported by these callers and the existing class declarations.

The consumer report distinguishes current authenticated object evidence from
the older census digest. The source and object match their recorded receipt;
the current object differs from the census copy, which was not locally
available. No new original-TU or cross-game identity is inferred from bytes.

Normal and strict verification pass all 16 rows in this isolated pre-merge
seed. Later application to the consolidated unit must verify that complete
unit again. The redundant present-unmatched marker retires through the counter
tool. This is a named folded body and debt cleanup, not 12 new covered bytes.
Set_Texture remains unchanged with its existing pointer-to-word ABI boundary.
