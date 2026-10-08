// cl: /O1 /G7 /arch:SSE /MD
struct BfmePod28 {int a[7];};
BfmePod28 *Rva0021618AFind(BfmePod28 *,BfmePod28 *,int);
class Rva00216245 {
public:BfmePod28 *rva00216245(int key);
private:unsigned char m_pad[0x28];BfmePod28 *m_begin,*m_end;
};
BfmePod28 *Rva00216245::rva00216245(int key) {
 BfmePod28 *end=m_end;
 BfmePod28 *found=Rva0021618AFind(m_begin,end,key);
 return found!=end ? found : 0;
}

// Target evidence: WB B6ED70 and BannerUI caller2166BB establish28-byte banner entry lookup; begin28 end2C and by-value integer key from native216245..216267; return found unless end; retained unknown method name; prior fill ABI corrected.
// The record view models only seven native words; original field names
// and source-level template spelling remain unknown.
