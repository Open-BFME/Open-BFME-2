// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCC94Do@@YAXXZ @0x003BCC94 14B: free Do calling g_00DFEF18 slot 0x28 with (1).
// Evidence: mov ecx,[0xDFEF18] mov eax,[ecx] push 1 call [eax+0x28] ret; caller 0x003CDC68; neighbours Rva003BCC08Do Rva003BCCA2Do same dir.
class Rva003BCC94Host
{
public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void slot10(int v);
};
extern Rva003BCC94Host *g_00DFEF18;

void __cdecl Rva003BCC94Do()
{
	g_00DFEF18->slot10(1);
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00DFEF18@@3PAVRva003BCC94Host@@A=?g_00DFEF18@@3PAVRva002D3627Host@@A")
