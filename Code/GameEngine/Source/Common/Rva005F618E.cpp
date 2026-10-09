// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /Oy-
// Native5F618E..5F61E4 complete86B setter. The cached boolean at36
// suppresses duplicate SetLeaderIconState calls. Target strings selected/up,
// field4 level, field8 string header and existing Apt call50E9FE are proven
// by retail. The original class identity stays address-derived.
// A bool input with a separate const-char state local naturally reuses the
// dead input home and preserves BL; the earlier uchar bank did not.
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
int Rva0050E9FEAptCall(Rva00222A8BTarget *, void *, const char *, const char *, const char **);
class Rva005F618E {public:void rva005F618E(bool);private:
 char pad0[4];unsigned int level;const unsigned char *prefixHeader;
 char pad0C[0x36-0x0C];bool cached;
};
void Rva005F618E::rva005F618E(bool value){
 if(value==cached)return;
 bool original=value;
 const char *state=original?"_selected":"_up";
 const char *prefix=prefixHeader?(const char*)(prefixHeader+8):"";
 Rva0050E9FEAptCall((Rva00222A8BTarget*)g_bfmeAptWindowManager,(void*)level,prefix,"SetLeaderIconState",&state);
 cached=original;
}
