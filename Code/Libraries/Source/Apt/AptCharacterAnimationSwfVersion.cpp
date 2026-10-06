// cl: /MD
// APT0.19.03 May2006 release PDB/MAP supplies getSwfVersion and pFile/GetAptData.
// Target caller6D17F0 passes this at6D1982 and sends the result to6CD210, which
// stores the version globalE17724 (read by6CD220). Target full26-byte body at
// 6E3E00 matches the release donor including ':' and ASCII-digit/default6 logic.
// Its branch6E3E0A ->6E3E14 proves the return6 tail is not a separate function;
// the old6-byte claim was retracted before landing this complete body.
// Target independently proves pFile+34 and data+10; the final donor uses data+C
// and must NOT supply that field offset. Release PDB AptFile agrees with data+10.
// These are partial views; unused file/animation fields and ownership are opaque.
class AptFile {
    unsigned char unaccessed[16];
    void *mAptData;
public:
    void *GetAptData() { return mAptData; }
};
template<class T> class AptSharedPtr {
    T *pointer;
public:
    T *operator->() const { return pointer; }
};
struct AptCharacterAnimationInst {
    unsigned char unaccessed[52];
    AptSharedPtr<AptFile> pFile;
    int getSwfVersion();
};
int AptCharacterAnimationInst::getSwfVersion()
{
    const char *data=(const char *)pFile->GetAptData();
    if (data[8]==':') return data[9]-'0';
    return 6;
}
