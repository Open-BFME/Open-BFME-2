// ?Rva0027DA6A@Rva0062AF7@@QAE_NPBMPAM@Z
// partial score=0.9846701731 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Oy-
extern "C" __declspec(dllimport) double __cdecl floor(double);
__forceinline int CameraFieldFloatToInt(float value){int result;__asm{fld value
 fistp result}return result;}
class Rva0062AF7{public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot10();
virtual float slot11();
bool Rva0027DA6A(const float*,float*);
char gap04[0x18];int width,height;unsigned char*data;unsigned gridWidth,gridHeight;
};
bool Rva0062AF7::Rva0027DA6A(const float*pos,float*out){
 if(!data||width<1||height<1)return false;
 float border=slot11();
 float x=pos[0]+border,y=pos[1]+border;
 if(x<0)x=0;else if(x>width*10.0f)x=width*10.0f;
 if(y<0)y=0;else if(y>height*10.0f)y=height*10.0f;
 x*=gridWidth/(width*10.0f);y*=gridHeight/(height*10.0f);
 float xf=(float)floor((double)x);int ix=CameraFieldFloatToInt(xf);
 float yf=(float)floor((double)y);int iy=CameraFieldFloatToInt(yf);
 if((unsigned)ix>=gridWidth-1)ix=gridWidth-2;
 if((unsigned)iy>=gridHeight-1)iy=gridHeight-2;
 x-=ix;y-=iy;if(x>1)x=1;if(y>1)y=1;
 unsigned char*p=data+ix*3+iy*3*gridWidth;unsigned char*q=p+gridWidth*3;
 for(int i=0;i<3;i++,p++,q++){
  float*o=i==0?out+2:(i==1?out+1:out);
  *o=((q[0]*(1-x)+q[3]*x)*y+(p[0]*(1-x)+p[3]*x)*(1-y))*(1.0f/255.0f);
 }
 return true;
}
