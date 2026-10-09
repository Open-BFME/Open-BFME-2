// cl: /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// Native 4DF983..4DF98B is a cdecl field-address callback, ending before
// the independently owned collector dispatch at 4DF98B. The collector
// constructor at 4E030B passes its address into the tracker at +10.
// Target bytes establish only the +38 field address, not its original name.
void *Rva004DF983Field(void *owner) {
    return static_cast<char *>(owner)+0x38;
}
