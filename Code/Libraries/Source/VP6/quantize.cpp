// cl: /MD
// Retail 64-coefficient squared reconstruction error, scaled by four.
// Donor PDB supplies name/ABI; target arithmetic and zigzag table establish role.
// Source-handoff placement guided discovery; original body text not imported.
// Provenance: reverse/vp6_structural_evidence.json, quantization_error.
extern unsigned vp6DequantIndex[64];
extern "C" void GetQuantizedCoeffsMSE_RD(short *original,short *quantized,short *dequantizer,unsigned *error)
{
    unsigned total=0;
    for(int i=0;i<64;++i) {
        int delta=quantized[i]*dequantizer[i]-original[vp6DequantIndex[i]];
        total+=delta*delta;
    }
    *error=total<<2;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?vp6DequantIndex@@3PAIA=?g_rva01142308@@3PAHA")
