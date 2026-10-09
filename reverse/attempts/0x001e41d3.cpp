// ?rva001E41D3@Rva001E41D3@@QAE?AURva001E41D3Result@@XZ
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD
// Native1E41D3..1E41FA and WB AF0DB0 establish12B result and hidden
// return-storage construction bit; this corrects the old void/out bank.
// Matrix68 row-translation floats at74/84/94 are target facts. Original
// result class/PODity and constructor form are unresolved structural views.
// This35B value-return trial restores LEA68 but retains first x87 copy
// and reversed XMM load allocation. Never a matched claim.
struct Rva001E41D3Result {
 float x,y,z;
 Rva001E41D3Result(float a,float b,float c):x(a),y(b),z(c){}
};
struct Rva001E41D3Matrix {
 float m[3][4];
 __forceinline Rva001E41D3Result get(){return Rva001E41D3Result(m[0][3],m[1][3],m[2][3]);}
};
class Rva001E41D3 {
 char prefix[0x68];Rva001E41D3Matrix matrix;
public:Rva001E41D3Result rva001E41D3();
};
Rva001E41D3Result Rva001E41D3::rva001E41D3(){return matrix.get();}
