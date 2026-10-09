// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ZH pointgr.cpp's quad index-buffer initialization is the reference lead,
// BFME1 reference revision 874e38488. Target 00177923 uses only two quad
// buffers, 3072 indices each, and a different diagonal: 0,1,2,1,3,2.
// Target globals are owned by Rva00177860Dtor.cpp; original subsystem identity
// remains unknown. Constructor and WriteLock calls identify the buffer types.
#include "dx8indexbuffer.h"
class Rva00177860Ref;
extern Rva00177860Ref *Rva009F7044;
extern Rva00177860Ref *Rva009F7048;

void Rva00177923Init()
{
    if (Rva009F7044) return;
    Rva009F7044 = (Rva00177860Ref *)::new DX8IndexBufferClass(3072, DX8IndexBufferClass::USAGE_DEFAULT);
    Rva009F7048 = (Rva00177860Ref *)::new SortingIndexBufferClass(3072);
    {
        IndexBufferClass::WriteLockClass lock((IndexBufferClass *)Rva009F7044);
        unsigned short *ib=lock.Get_Index_Array();
        unsigned short vert=0;
        for (int i=0;i<3072;i+=6, vert+=4) {
            ib[i]=vert; ib[i+1]=vert+1; ib[i+2]=vert+2;
            ib[i+3]=vert+1; ib[i+4]=vert+3; ib[i+5]=vert+2;
        }
    }
    {
        IndexBufferClass::WriteLockClass lock((IndexBufferClass *)Rva009F7048);
        unsigned short *ib=lock.Get_Index_Array();
        unsigned short vert=0;
        for (int i=0;i<3072;i+=6, vert+=4) {
            ib[i]=vert; ib[i+1]=vert+1; ib[i+2]=vert+2;
            ib[i+3]=vert+1; ib[i+4]=vert+3; ib[i+5]=vert+2;
        }
    }
}
