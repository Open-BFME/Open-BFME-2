// ?rva00559AF9@Rva00559AC1@@QAEMH@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /Oy- /EHsc /DNDEBUG /MD /arch:SSE
class Rva00559AC1 {
public:int rva00559AC1(int);float rva00559AF9(int);
private:int values[11];
};
int Rva00559AC1::rva00559AC1(int v) {for(int i=1;i<11;++i)if(values[i]>v)return i-1;return 10;}
float Rva00559AC1::rva00559AF9(int value) {
 int rank=rva00559AC1(value);
 if(rank!=0 && rank<10) {
  float base=float(values[rank]);float difference=float(values[rank+1])-base;
  if(!(0.0001f>difference))return (float(value)-base)/difference;
 }
 return 0.0f;
}
