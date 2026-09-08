// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Copyright 2025 Electronic Arts Inc.
// SPDX-License-Identifier: GPL-3.0-or-later
// Reconstructed from BFME2 and the GPL-3.0-or-later EA reference
// Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.cpp.
// Recovered role names and independent identities: docs/reconstruction/dynamic-vertex-buffer.md.
void *__cdecl operator new(unsigned);
void __cdecl operator delete(void *);
struct BfmeFVFDescriptor;
struct BfmeDynamicCapsPrefix {
 unsigned maxDisplayWidth,maxDisplayHeight;
 // Actual 304-byte D3D9 caps aggregate; its internal fields are not accessed.
 unsigned char d3dCaps[304];
 bool supportTnL,supportDXTC,supportGamma,supportNPatches;
};
extern BfmeDynamicCapsPrefix *bfmeDynamicCaps;
class BfmeDynamicVBRefCount {
public:
 virtual void DeleteThis();
 int references;
 void AddRef() { ++references; }
 void ReleaseRef() { --references; if(references==0) DeleteThis(); }
};
class BfmeDynamicVBBase:public BfmeDynamicVBRefCount {
public:
 unsigned type;
 unsigned short vertexCount;
 int engineReferences;
 BfmeFVFDescriptor *format;
 bool usesDeclaration;
};
class BfmeDynamicNativeVB:public BfmeDynamicVBBase {
public:
 void *buffer;
 BfmeDynamicNativeVB(unsigned,unsigned short,unsigned,unsigned);
};
class BfmeDynamicSortingVB:public BfmeDynamicVBBase {
public:
 void *buffer;
 BfmeDynamicSortingVB(unsigned short);
};
typedef char BfmeDynamicVBBaseSize[(sizeof(BfmeDynamicVBBase)==28)?1:-1];
typedef char BfmeDynamicNativeVBSize[(sizeof(BfmeDynamicNativeVB)==32)?1:-1];
extern bool bfmeDynamicVBInUse[15];
extern BfmeDynamicNativeVB *bfmeDynamicVBs[15];
extern unsigned short bfmeDynamicVBSizes[15],bfmeDynamicVBOffsets[15];
extern unsigned bfmeDynamicFVFs[15];
static bool bfmeSortingVBInUse;
static BfmeDynamicSortingVB *bfmeSortingVB;
static unsigned short bfmeSortingVBSize,bfmeSortingVBOffset;
struct BfmeDynamicVBAccess {
 const BfmeFVFDescriptor *format;
 unsigned type,formatIndex,declaration;
 unsigned short vertexCount,vertexOffset;
 BfmeDynamicVBBase *buffer;
 void AllocateNative();
 void AllocateSorting();
};
void BfmeDynamicVBAccess::AllocateNative()
{
 bfmeDynamicVBInUse[formatIndex]=true;
 if(vertexCount>bfmeDynamicVBSizes[formatIndex]) {
  if(bfmeDynamicVBs[formatIndex]) {
   bfmeDynamicVBs[formatIndex]->ReleaseRef();
   bfmeDynamicVBs[formatIndex]=0;
  }
  bfmeDynamicVBSizes[formatIndex]=vertexCount;
  if(bfmeDynamicVBSizes[formatIndex]<5000) bfmeDynamicVBSizes[formatIndex]=5000;
 }
 if(!bfmeDynamicVBs[formatIndex]) {
  unsigned usage=1;
  if(bfmeDynamicCaps->supportNPatches) usage|=4;
  bfmeDynamicVBs[formatIndex]=new BfmeDynamicNativeVB(bfmeDynamicFVFs[formatIndex],bfmeDynamicVBSizes[formatIndex],usage,0);
  bfmeDynamicVBOffsets[formatIndex]=0;
 }
 bfmeDynamicVBs[formatIndex]->usesDeclaration=declaration!=0;
 if((unsigned(vertexCount)+bfmeDynamicVBOffsets[formatIndex])>bfmeDynamicVBSizes[formatIndex]) bfmeDynamicVBOffsets[formatIndex]=0;
 if(bfmeDynamicVBs[formatIndex]) bfmeDynamicVBs[formatIndex]->AddRef();
 if(buffer) buffer->ReleaseRef();
 buffer=bfmeDynamicVBs[formatIndex];
 vertexOffset=bfmeDynamicVBOffsets[formatIndex];
}
void BfmeDynamicVBAccess::AllocateSorting()
{
 bfmeSortingVBInUse=true;
 unsigned newCount=bfmeSortingVBOffset+vertexCount;
 if(newCount>bfmeSortingVBSize) {
  if(bfmeSortingVB) { bfmeSortingVB->ReleaseRef();bfmeSortingVB=0; }
  bfmeSortingVBSize=newCount;
  if(bfmeSortingVBSize<5000) bfmeSortingVBSize=5000;
 }
 if(!bfmeSortingVB) {
  bfmeSortingVB=new BfmeDynamicSortingVB(bfmeSortingVBSize);
  bfmeSortingVBOffset=0;
 }
 if(bfmeSortingVB) bfmeSortingVB->AddRef();
 if(buffer) buffer->ReleaseRef();
 buffer=bfmeSortingVB;
 vertexOffset=bfmeSortingVBOffset;
}
