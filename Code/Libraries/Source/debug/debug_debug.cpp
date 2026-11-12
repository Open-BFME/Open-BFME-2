// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Debug-stack link view first: the 3-argument StackWalk (rowed 0x0003C110)
// shadows Zero Hour two-argument header so outgoing calls resolve.
struct _CONTEXT;
#include "../../../../reference/shims/debugstacklayout/debug_stack.h"
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/debug/debug_debug.cpp); this unit had no counterpart under Code/.
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/////////////////////////////////////////////////////////////////////////EA-V1
// $File: //depot/GeneralsMD/Staging/code/Libraries/Source/debug/debug_debug.cpp $
// $Author: mhoffe $
// $Revision: #2 $
// $DateTime: 2003/07/09 10:57:23 $
//
// �2003 Electronic Arts
//
// Debug class implementation
//////////////////////////////////////////////////////////////////////////////
// Retail calls the wvsprintfA import with callee cleanup (__stdcall shape,
// no add-esp after the call), while the headers below declare it __cdecl.
// Hide the header declaration under a dummy name so a TU-local __stdcall
// declaration can name the same import (cf. StartOutput, which inlines the
// only wvsprintf use in this TU; wsprintfA is unaffected).
#define wvsprintfA wvsprintfA_cdecl_unused
// Retail LookupFrame (0x00038330) indexes frameHash at +0x18. The donor
// header places it at +0x14; frameStatus (0x0003A6A0) also writes +0x14
// before the lookup. Preserve that otherwise unreconstructed word in this
// TU's view. firstCmdGroup occurs only in its field declaration in the shim.
#define firstCmdGroup firstCmdGroup; unsigned bfmeUnreconstructed014
#include "_pch.h"
#undef firstCmdGroup
#undef wvsprintfA
extern "C" __declspec(dllimport) int __stdcall wvsprintfA(char *out, const char *fmt, void *args);
// (windows.h's `wvsprintf` macro was captured while the dummy name was
// active; repoint it at the TU-local declaration. Its only user is
// StartOutput below, which names wvsprintfA explicitly.)
#undef wvsprintf
#define wvsprintf wvsprintfA
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <new>      // needed for placement new prototype

// a little dummy variable that makes the linker actually include
// us...
extern "C" bool __DebugIncludeInLink1;
bool __DebugIncludeInLink1;

// Zero Hour hooked Debug::PreStaticInit into .CRT$XCB and Debug::PostStaticInit into .CRT$XCY here. BFME 2 has
// neither: its own pre-static hook is the initializer at retail index 1 (rva0003A210, 0x0003A210:
// InitializeCriticalSection, PreStaticInit() creating theDebug, atexit(StaticExit)) and its post-static hook is
// the last one (rva0088C4E0PostStaticInitLookup, 0x0003B7F0). Both are rowed in their own units (LINK-633).

// ??0LogDescription@Debug@@QAE@PBD0@Z defined in WWDebug/Debug_LogDescriptionCtor.cpp (its row's unit).

// our global Debug instance
Debug Debug::Instance;

// more class static members
unsigned Debug::curStackFrame;

// ??0Debug@@AAE@XZ defined in WWDebug/DebugConstructor.cpp (its row's unit).

// ?PostStaticInit@Debug@@CAXXZ defined in WWDebug/DebugPostStaticInit.cpp (its row's unit).

// ?StaticExit@Debug@@CAXXZ defined in WWDebug/DebugStaticExit.cpp (its row's unit).

Debug& Debug::operator<<(RepeatChar &c)
{
  if (c.m_count>=10)
  {
    char help[10];
    memset(help,c.m_char,10);
    while ((c.m_count-=10)>=0)
      AddOutput(help,10);
  }
  while (c.m_count-->0)
    AddOutput(&c.m_char,1);
  return *this;
}

Debug::Format::Format(const char *format, ...)
{
  va_list va;
  va_start(va,format);
  _vsnprintf(m_buffer,sizeof(m_buffer)-1,format,va);
  va_end(va);
}

// ??1Debug@@QAE@XZ present-unmatched
Debug::~Debug()
{
  // again, do not put any code in here
}

static void LocalSETranslator(unsigned, struct _EXCEPTION_POINTERS *pExPtrs)
{
  // simply call our regular exception handler
  DebugExceptionhandler::ExceptionFilter(pExPtrs);
}

void Debug::InstallExceptionHandler(void)
{
  _set_se_translator(LocalSETranslator);
}

// ?SkipNext@Debug@@SA_NXZ present-unmatched
bool Debug::SkipNext(void)
{
  // this is typically set while an assertion
  // is running
  if (Instance.disableAssertsEtc)
    return true;

  // do not implement this function inline, we do need
  // a valid frame pointer here!
  unsigned help;
  _asm 
  {
    mov eax,[ebp+4]   // return address
    mov help,eax
  };
  curStackFrame=help;

  // do we know if to skip the following code?
  FrameHashEntry *frameHashEntry=Instance.LookupFrame(curStackFrame);
  if (!frameHashEntry||                // unknown frame, will be added later
       frameHashEntry->status==NoSkip) // frame known but active
    return false;

  // status is unknown, must update
  if (frameHashEntry->status==Unknown)
    Instance.UpdateFrameStatus(*frameHashEntry);

  // now we now wether to skip or not
  return frameHashEntry->status==Skip;
}

// ?AssertBegin@Debug@@SAAAV1@PBDH0@Z present-unmatched
Debug& Debug::AssertBegin(const char *file, int line, const char *expr)
{
  // avoid infinite recursion...
  ++Instance.disableAssertsEtc;

  // anything to flush first?
  if (Instance.curType!=DebugIOInterface::StringType::MAX)
    Instance.FlushOutput();

  // set new output
  __ASSERT(Instance.curFrameEntry==NULL);
  Instance.curFrameEntry=Instance.GetFrameEntry(curStackFrame,FrameTypeAssert,file,line);
  if (Instance.curFrameEntry->status==NoSkip)
  {
    Instance.StartOutput(DebugIOInterface::StringType::Assert,"%s(%i)",
                  Instance.curFrameEntry->fileOrGroup,
                  Instance.curFrameEntry->line);
    ++Instance.curFrameEntry->hits;

    // if there is a \code\ section in the filename truncate
    // everything before that (including \code\)
    const char *p=strstr(file,"\\code\\");
    p=p?p+6:file;

    Instance << "\n" << RepeatChar('=',80) << "\nAssertion failed in " << p << ", line " << line 
             << ",\nexpression " << expr;
  }

  return Instance;
}

// ?AssertDone@Debug@@UAE_NXZ present-unmatched
bool Debug::AssertDone(void)
{
  --disableAssertsEtc;

  // did we have an active assertion?
  if (curType==DebugIOInterface::StringType::Assert)
  {
    __ASSERT(curFrameEntry!=NULL);

    // hit info?
    if (curFrameEntry->hits>1)
      (*this) << " (hit #" << curFrameEntry->hits << ")";

    // need CR?
    if (!ioBuffer[curType].lastWasCR)
      operator<<("\n");

    // yes, duplicate message
    const char *addInfo="\nPress 'abort' to abort the program,\n"
                        "'retry' for breaking into the debugger, or\n"
                        "'ignore' for ignoring this assertion for the\n"
                        "time being (stops logging this assertion as well).";
    char *help=(char *)DebugAllocMemory(ioBuffer[curType].used+strlen(addInfo)+1);
    strcpy(help,ioBuffer[curType].buffer+82);
    strcat(help,addInfo);
    
    // First hit? Then do a stack trace
    if (curFrameEntry->hits==1)
    {
      DebugStackwalk::Signature sig;
      if (m_stackWalk.StackWalk(sig))
        (*this) << sig;
    }

    // ... and flush out
    operator<<("\n\n");
    FlushOutput();

    // show dialog box only if running windowed
    if (IsWindowed())
    {
      /// @todo replace MessageBox with custom dialog w/ 4 options: abort, skip 1, skip all, break

      // now display message, wait for user input
      int result=MessageBox(NULL,help,"Assertion failed",
                            MB_ABORTRETRYIGNORE|MB_ICONSTOP|MB_TASKMODAL|MB_SETFOREGROUND);
      switch(result)
      {
        case IDABORT:
          curFrameEntry=NULL;
          exit(1);
          break;
        case IDIGNORE:
          {
            // build 'pattern'
            char help[200];
            __ASSERT(strlen(curFrameEntry->fileOrGroup)<190);
            wsprintf(help,"%s(%i)",curFrameEntry->fileOrGroup,
                                   curFrameEntry->line);
            AddPatternEntry(FrameTypeAssert,false,help);
            curFrameEntry->status=Skip;
          }
          break;
        case IDRETRY:
          _asm int 0x03
          break;
        default:
          ((void)0);
      }
    }
    else 
    {
      // we're running fullscreen

      // hit too often?
      if (curFrameEntry->hits==MAX_CHECK_HITS)
      {
        // yup, turn off then
        StartOutput(DebugIOInterface::StringType::Other,"");
        Instance << "Assert hit too often - turning check off.\n";
        FlushOutput();

        // build 'pattern'
        char help[200];
        __ASSERT(strlen(curFrameEntry->fileOrGroup)<190);
        wsprintf(help,"%s(%i)",curFrameEntry->fileOrGroup,
                               curFrameEntry->line);
        AddPatternEntry(FrameTypeAssert,false,help);

        curFrameEntry->status=Skip;
      }
    }
  }

  curFrameEntry=NULL;
  return false;
}


// ?CheckDone@Debug@@UAE_NXZ present-unmatched
bool Debug::CheckDone(void)
{
  --disableAssertsEtc;

  // did we have an active check?
  if (curType==DebugIOInterface::StringType::Check)
  {
    __ASSERT(curFrameEntry!=NULL);

    // hit info?
    if (curFrameEntry->hits>1)
      (*this) << " (hit #" << curFrameEntry->hits << ")";

    // need CR?
    if (!ioBuffer[curType].lastWasCR)
      operator<<("\n");

    // First hit? Then do a stack trace
    if (curFrameEntry->hits==1)
    {
      DebugStackwalk::Signature sig;
      if (m_stackWalk.StackWalk(sig))
        (*this) << sig;
    }

    // flush out
    operator<<("\n\n");
    FlushOutput();

    // hit too often?
    if (curFrameEntry->hits==MAX_CHECK_HITS)
    {
      // yup, turn off then
      StartOutput(DebugIOInterface::StringType::Other,"");
      Instance << "Check hit too often - turning check off.\n";
      FlushOutput();

      // build 'pattern'
      char help[200];
      __ASSERT(strlen(curFrameEntry->fileOrGroup)<190);
      wsprintf(help,"%s(%i)",curFrameEntry->fileOrGroup,
                             curFrameEntry->line);
      AddPatternEntry(FrameTypeCheck,false,help);

      curFrameEntry->status=Skip;
    }
  }

  curFrameEntry=NULL;
  return false;
}

Debug& Debug::LogBegin(const char *fileOrGroup)
{
  // avoid infinite recursion...
  ++Instance.disableAssertsEtc;

  // anything to flush first?
  if (Instance.curType!=DebugIOInterface::StringType::MAX&&
      Instance.curType!=DebugIOInterface::StringType::Log)
    Instance.FlushOutput();

  // set new output
  __ASSERT(Instance.curFrameEntry==NULL);
  Instance.curFrameEntry=Instance.GetFrameEntry(curStackFrame,FrameTypeLog,fileOrGroup,0);
  if (Instance.curFrameEntry->status==NoSkip)
  {
    ++Instance.curFrameEntry->hits;

    // we're doing all this extra work so that DLOGs can be spread across
    // multiple calls
    if (Instance.curType==DebugIOInterface::StringType::Log&&
        strcmp(Instance.curSource,Instance.curFrameEntry->fileOrGroup))
      Instance.FlushOutput();

    if (Instance.curType!=DebugIOInterface::StringType::Log)
      Instance.StartOutput(DebugIOInterface::StringType::Log,"%s",
                    Instance.curFrameEntry->fileOrGroup);
  }
  else if (Instance.curType!=DebugIOInterface::StringType::MAX)
    Instance.FlushOutput();
  
  return Instance;
}

// ?LogDone@Debug@@UAE_NXZ present-unmatched
bool Debug::LogDone(void)
{
  --disableAssertsEtc;

  // we're not flushing here on intention!

  curFrameEntry=NULL;
  return false;
}

// ?CrashBegin@Debug@@SAAAV1@PBDH@Z present-unmatched
Debug& Debug::CrashBegin(const char *file, int line)
{
  // avoid infinite recursion...
  ++Instance.disableAssertsEtc;

  // anything to flush first?
  if (Instance.curType!=DebugIOInterface::StringType::MAX)
    Instance.FlushOutput();

  // set new output
  __ASSERT(Instance.curFrameEntry==NULL);
  Instance.curFrameEntry=Instance.GetFrameEntry(curStackFrame,FrameTypeAssert,file,line);
  if (Instance.curFrameEntry->status==NoSkip)
  {
    Instance.StartOutput(DebugIOInterface::StringType::Crash,"%s(%i)",file,line);
    ++Instance.curFrameEntry->hits;

    Instance << "\n" << RepeatChar('=',80) << "\n";
    if (file)
    {
      // if there is a \code\ section in the filename truncate
      // everything before that (including \code\)
      const char *p=strstr(file,"\\code\\");
      p=p?p+6:file;

      Instance << "Crash in " << p << ", line " << line 
               << ", reason:\n";
    }
  }

  return Instance;
}

// ?CrashDone@Debug@@UAE_N_N@Z present-unmatched
bool Debug::CrashDone(bool die)
{
  --disableAssertsEtc;

  // did we have an active assertion?
  if (curType==DebugIOInterface::StringType::Crash)
  {
    __ASSERT(curFrameEntry!=NULL);

    // hit info?
    if (curFrameEntry->hits>1)
      (*this) << " (hit #" << curFrameEntry->hits << ")";

    // need CR?
    if (!ioBuffer[curType].lastWasCR)
      operator<<("\n");

    // duplicate message
    const char *addInfo=
      "\nBecause of the severity of this error the "
      "game will now exit.";
#ifdef HAS_LOGS
    if (IsWindowed()&&!die)
      addInfo=
        "\nPress 'abort' to abort the program,\n"
        "'retry' for breaking into the debugger, or\n"
        "'ignore' for ignoring this assertion for the\n"
        "time being (stops logging this assertion as well).";
#endif
    char *help=(char *)DebugAllocMemory(ioBuffer[curType].used+strlen(addInfo)+1);
    strcpy(help,ioBuffer[curType].buffer+82);
    strcat(help,addInfo);
    
    // First hit? Then do a stack trace
    if (curFrameEntry->hits==1)
    {
      DebugStackwalk::Signature sig;
      if (m_stackWalk.StackWalk(sig))
        (*this) << sig;
    }

    // ... and flush out
    operator<<("\n\n");
    FlushOutput();

    // now display message, wait for user input
#ifdef HAS_LOGS
    // show dialog box only if running windowed
    if (!die)
    {
      if (IsWindowed())
      {
        /// @todo replace MessageBox with custom dialog w/ 4 options: abort, skip 1, skip all, break

        // now display message, wait for user input
        int result=MessageBox(NULL,help,"Crash hit",
                              MB_ABORTRETRYIGNORE|MB_ICONSTOP|MB_TASKMODAL|MB_SETFOREGROUND);
        switch(result)
        {
          case IDABORT:
            curFrameEntry=NULL;
            exit(1);
            break;
          case IDIGNORE:
            {
              // build 'pattern'
              char help[200];
              __ASSERT(strlen(curFrameEntry->fileOrGroup)<190);
              wsprintf(help,"%s(%i)",curFrameEntry->fileOrGroup,
                                     curFrameEntry->line);
              AddPatternEntry(FrameTypeAssert,false,help);
              curFrameEntry->status=Skip;
            }
            break;
          case IDRETRY:
            _asm int 0x03
            break;
          default:
            ((void)0);
        }
      }
      else
      {
        // running fullscreen...

        // hit too often?
        if (curFrameEntry->hits==MAX_CHECK_HITS)
        {
          // yup, turn off then
          StartOutput(DebugIOInterface::StringType::Other,"");
          Instance << "Crash hit too often - turning check off.\n";
          FlushOutput();

          // build 'pattern'
          char help[200];
          __ASSERT(strlen(curFrameEntry->fileOrGroup)<190);
          wsprintf(help,"%s(%i)",curFrameEntry->fileOrGroup,
                                 curFrameEntry->line);
          AddPatternEntry(FrameTypeAssert,false,help);

          curFrameEntry->status=Skip;
        }
      }
    }
    else
#endif
    {
      MessageBox(NULL,help,"Game crash",
                          MB_OK|MB_ICONSTOP|MB_TASKMODAL|MB_SETFOREGROUND);
      curFrameEntry=NULL;
      _exit(1);
    }
  }

  curFrameEntry=NULL;
  return false;
}

// Retail Debug ABI in this TU: curType sits at this+0x9cf4 with 7 string
// types (this TU's headers have 8: ioBuffer carries one entry fewer),
// m_width at +0x9f50 and m_fillChar at +0x9f54. TU-local view so the placed
// stream bodies in this TU keep their layout (cf. RetailDebugVersionView).
struct RetailDebugOutView {
  char _pad0[0xc];
  // (Private in the headers, so kept typeless here and cast back to
  // Debug::IOFactoryListEntry inside Debug members, which may access it.)
  void *firstIOFactoryLink;             // 0xc (retail FlushOutput loop)
  char _pad0b[0x9c84 - 0x10];
  struct IoEntry {
    char *buffer;
    unsigned used;
    unsigned alloc;
    bool lastWasCR;
  } ioBuffer[7];                      // 0x9c84, 16B stride; lastWasCR at +12
  int curType;                        // 0x9cf4; retail bails when it is 7
  char curSource[256];                // 0x9cf8
  char _pad1[0x9e78 - 0x9df8];
  bool alwaysFlush;                   // 0x9e78 (retail FlushOutput second Write)
  char _pad1b;                        // 0x9e79 (open: byte tested in AssertDone path)
  bool timeStamp;                     // 0x9e7a (retail AddOutput timestamp split)
  char _pad1c[0x9f50 - 0x9e7b];
  int m_width;                        // 0x9f50
  char m_fillChar;                    // 0x9f54
};

// Retail DebugIOInterface carries one more virtual than this TU's headers
// declare: a bool query at slot +8 between Read (+4) and Write (+12). Proven
// by the DebugIOFlat/Net/Ods/Con vtables (Write called at +0xc from retail
// FlushOutput; slot +8 holds a shared return-false body at 0x73B660 except
// for the console class, which returns its m_allocatedConsole flag at
// 0x408C0). Only the Write slot is used below; the query keeps its slot.
struct RetailDebugIOInterface {
  virtual ~RetailDebugIOInterface() = 0;
  virtual int Read(char *buf, int maxchar) = 0;
  virtual bool OwnsConsole() = 0;     // slot +8; identity open (see above)
  virtual void Write(int type, const char *src, const char *str) = 0;
};

Debug& Debug::operator<<(const char *str)
{
  RetailDebugOutView *retail = (RetailDebugOutView *)this;
  if (retail->curType==7)
    // yes, this is valid and simply means not to
    // write anything...
    return *this;

  // buffer large enough?
  if (!str)
    str="[NULL]";
  else if (!*str)
    return *this;

  int len=strlen(str);

  // forced width?
  if (len<retail->m_width)
  {
    for (int k=len;k<retail->m_width;k++)
      Debug::AddOutput(&retail->m_fillChar,1);
  }

  // reset width after each insertion
  retail->m_width=0;

  Debug::AddOutput(str,len);

  return *this;
}

// ?SetPrefixAndRadix@Debug@@UAEXPBDH@Z present-unmatched
void Debug::SetPrefixAndRadix(const char *prefix, int radix)
{
  strncpy(m_prefix,prefix?prefix:"",sizeof(m_prefix)-1);
  m_prefix[sizeof(m_prefix)-1]=0;
  m_radix=radix;
}

// ??6Debug@@UAEAAV0@H@Z and ??6Debug@@UAEAAV0@I@Z defined in WWDebug/Debug_OperatorInteger.cpp (their rows' unit).

Debug& Debug::operator<<(long val)
{
  // usually having a fixed size buffer and a function
  // that doesn't check for buffer overflow isn't a good idea
  // but in this case we know how long it can be at max...
  char help[1+32+1]; // sign, 32 digits, NUL
  AddOutput(m_prefix,strlen(m_prefix));
  return (*this) << _itoa(val,help,m_radix);
}

Debug& Debug::operator<<(unsigned long val)
{
  // usually having a fixed size buffer and a function
  // that doesn't check for buffer overflow isn't a good idea
  // but in this case we know how long it can be at max...
  char help[32+1]; // 32 digits, NUL
  AddOutput(m_prefix,strlen(m_prefix));
  return (*this) << _ultoa(val,help,m_radix);
}



Debug& Debug::operator<<(float val)
{
  /// @todo_opt shouldn't use snprintf here - brings in most of the old C IO lib...
  char help[200];
  _snprintf(help,sizeof(help),"%f",val);
  return (*this) << help;
}

Debug& Debug::operator<<(double val)
{
  /// @todo_opt shouldn't use snprintf here - brings in most of the old C IO lib...
  char help[200];
  _snprintf(help,sizeof(help),"%f",val);
  return (*this) << help;
}

// ??6Debug@@UAEAAV0@F@Z and ??6Debug@@UAEAAV0@G@Z defined in Common/BfmeThreeHundred.cpp and Common/BfmeThreeHundredOne.cpp (their rows' units).





Debug& Debug::operator<<(const void *ptr)
{
  (*this) << "ptr:";
  if (ptr)
  {
    char help[9];
    (*this) << "0x" << _ultoa((unsigned long)ptr,help,16);
  }
  else
    (*this) << "NULL";
  return *this;
}

Debug& Debug::operator<<(const MemDump &dump)
{
  RetailDebugOutView *retail = (RetailDebugOutView *)this;
  if (retail->curType==7)
    return *this;

  // need CR?
  if (!retail->ioBuffer[retail->curType].lastWasCR)
    operator<<("\n");

  // How many items per line? We're assuming an output
  // width of 73 chars. Left border is address thus
  // leaving 65 chars effectively. If character dump is
  // enabled then an additional space is needed (64 chars
  // then).
  unsigned itemPerLine=(dump.m_withChars?64:65)/
                          (1+2*dump.m_bytePerItem+(dump.m_withChars?1:0));
  if (!itemPerLine)
    itemPerLine=1;

  // now dump line by line
  const unsigned char *cur=dump.m_startPtr;
  for (unsigned i=0;i<dump.m_numItems;i+=itemPerLine,cur+=itemPerLine*dump.m_bytePerItem)
  {
    // address
    char buf[9];
    sprintf(buf,"%08x",dump.m_absAddr?unsigned(cur):cur-dump.m_startPtr);
    operator<<(buf);

    // items
    const unsigned char *curByte=cur;
    for (unsigned k=0;k<itemPerLine;k++,curByte+=dump.m_bytePerItem)
    {
      operator<<(" ");

      if (k+i>=dump.m_numItems)
      {
        for (unsigned l=dump.m_bytePerItem;l;--l)
          operator<<("  ");
      }
      else if (IsBadReadPtr(curByte,dump.m_bytePerItem))
      {
        for (unsigned l=dump.m_bytePerItem;l;--l)
          operator<<("??");
      }
      else
      {
        curByte+=dump.m_bytePerItem;
        for (unsigned l=0;l<dump.m_bytePerItem;++l)
        {
          sprintf(buf,"%02x",*--curByte);
          operator<<(buf);
        }
      }
    }

    // characters
    if (!dump.m_withChars)
      continue;
    operator<<(" ");
    curByte=cur;
    for (k=0;k<itemPerLine;k++,curByte+=dump.m_bytePerItem)
    {
      if (k+i>=dump.m_numItems)
        break;
      else if (IsBadReadPtr(curByte,dump.m_bytePerItem))
      {
        for (unsigned l=dump.m_bytePerItem;l;--l)
          operator<<("?");
      }
      else
      {
        buf[1]=0;
        for (unsigned l=0;l<dump.m_bytePerItem;++l)
        {
          *buf=curByte[l]>' '?curByte[l]:'.';
          operator<<(buf);
        }
      }
    }

    operator<<("\n");
  }

  return *this;
}

Debug& Debug::operator<<(HResult hres)
{
  for (unsigned k=0;k<numHrTranslators;k++)
    if (hrTranslators[k].func(*this,hres.m_hresult,hrTranslators[k].user))
      return *this;
  (*this) << "HResult:0x";
  char help[9];
  return (*this) << _ultoa(hres.m_hresult,help,16);
}

// BFME 2 has no static Debug::Instance: retail constructs Debug only in Debug::PreStaticInit (0x00038634),
// and none of its initializers constructs one. Zero Hour bodies built on the static instance that nothing
// references are gone: Add/RemoveHResultTranslator, RemoveCommands, IsLogEnabled, AddIOFactory and AddCommands.
// Retail's debug-library code (0x000382E0-0x0003FFFC) is rowed without gaps; none of these is among its rows.
// Still here: AssertBegin and CrashBegin (this unit's only emitters of the RepeatChar constructor row 0x00038310,
// which waits for TU evidence), SkipNext(void) (they call it), and the instance itself (LINK-633).
void Debug::Update(void)
{
  // check all existing IO interfaces
  for (IOFactoryListEntry *cur=Instance.firstIOFactory;cur;cur=cur->next)
  {
    if (!cur->io)
      continue;

    // any input?
    bool hadInput=false;
    for (;;)
    {
      if (cur->inputAlloc-cur->inputUsed<64)
        // must grow input buffer...
        cur->input=(char *)DebugReAllocMemory(cur->input,(cur->inputAlloc+=64)+1);
      int numChars=cur->io->Read(cur->input+cur->inputUsed,cur->inputAlloc-cur->inputUsed);
      if (!numChars)
        break;

      cur->inputUsed+=numChars;
      cur->input[cur->inputUsed]=0;
      hadInput=true;
    } 
    
    if (!hadInput)
      // skip then
      continue;

    // else look for completed commands and try to process them
    for (;;)
    {
      char *p=strchr(cur->input,'\n');
      if (!p)
        break;

      Instance.ExecCommand(cur->input,p);
      strcpy(cur->input,p+1);
      cur->inputUsed=strlen(cur->input);
    }
  }
}

// ?AddFrameEntry@Debug@@AAEPAUFrameHashEntry@1@IIPBDH@Z defined in WWDebug/Debug_AddFrameEntry.cpp (its row's unit).

// ?UpdateFrameStatus@Debug@@EAEXAAUFrameHashEntry@1@@Z present-unmatched
void Debug::UpdateFrameStatus(FrameHashEntry &entry)
{
  // build pattern match entry
  char help[512];
  if (entry.frameType==FrameTypeAssert||
      entry.frameType==FrameTypeCheck)
    wsprintf(help,"%s(%i)",entry.fileOrGroup,entry.line);
  else
    strcpy(help,entry.fileOrGroup);
  
  // update frame status
  bool active=entry.frameType!=FrameTypeLog;
  for (PatternListEntry *cur=firstPatternEntry;cur;cur=cur->next)
  {
    if (!(cur->frameTypes&entry.frameType))
      continue;
    if (SimpleMatch(help,cur->pattern))
      active=cur->isActive;
  }
  entry.status=active?NoSkip:Skip;
}

// ?AddLogGroup@Debug@@AAEPBDPBD0@Z defined in WWDebug/Debug_AddLogGroup_0088A020.cpp (its row's unit).

// ?StartOutput@Debug@@EAAXW4StringType@DebugIOInterface@@PBDZZ
void Debug::StartOutput(DebugIOInterface::StringType type, const char *fmt, ...)
{
  RetailDebugOutView *retail = (RetailDebugOutView *)this;
  // Retail keeps 7 string types with Log==1 (this TU's headers have 8 with
  // Log==2); a pending Log line is flushed first.
  if (retail->curType==1)
    Debug::FlushOutput(true);
  retail->curType=type;

  // potentially dangerous (fixed string buffer...)
  va_list va;
  va_start(va,fmt);
  wvsprintfA(retail->curSource,fmt,va);
  va_end(va);
}

void Debug::AddOutput(const char *str, unsigned remainingLen)
{
  RetailDebugOutView *retail = (RetailDebugOutView *)this;
  // bail out if no valid destination type
  // (valid, can happen if hitting a disabled log for the first time)
  if (retail->curType==7)
    return;

  while (remainingLen)
  {
    // if we're doing timestamps we have to split at each '\n'
    unsigned len;
    if (retail->timeStamp)
    {
      // add timestamp now?
      if (retail->ioBuffer[retail->curType].lastWasCR)
      {
        SYSTEMTIME systime;
        GetLocalTime(&systime);

        char ts[40];
        wsprintf(ts,"[%02i:%02i.%02i.%03i] ",systime.wHour,systime.wMinute,
                      systime.wSecond,systime.wMilliseconds);

        unsigned tsLen=strlen(ts);
        memcpy(retail->ioBuffer[retail->curType].buffer+retail->ioBuffer[retail->curType].used,ts,tsLen+1);
        retail->ioBuffer[retail->curType].used+=tsLen;
      }

      // search for next '\n'
      const char *p=str;
      const char *end=str+remainingLen;
      if (p!=end) {
        do {
          if (*p=='\n') { ++p; break; }
          ++p;
        } while (p!=end);
      }
      len=p-str;
    }
    else
      len=remainingLen;

    // count newlines: each one gains a CR when stored
    unsigned newlines=0;
    for (unsigned i=0;i<len;++i)
      if (str[i]=='\n')
        ++newlines;

    if (retail->ioBuffer[retail->curType].used+newlines+len+64>=retail->ioBuffer[retail->curType].alloc)
    {
      // no, must grow buffer
      retail->ioBuffer[retail->curType].alloc+=newlines+len+1024;
      retail->ioBuffer[retail->curType].buffer=(char *)
          DebugReAllocMemory(retail->ioBuffer[retail->curType].buffer,retail->ioBuffer[retail->curType].alloc);
    }

    if (newlines)
    {
      // expand LFs to CRLF while storing (with NUL)
      const char *src=str;
      char *dst=retail->ioBuffer[retail->curType].buffer+retail->ioBuffer[retail->curType].used;
      if (len>0)
      {
        unsigned n=len;
        do
        {
          *dst++=*src++;
          if (dst[-1]=='\n')
          {
            dst[-1]='\r';
            *dst++='\n';
          }
        } while (--n);
      }
      *dst=0;
      retail->ioBuffer[retail->curType].used+=len+newlines;
    }
    else
    {
      // add to buffer (with NUL)
      memcpy(retail->ioBuffer[retail->curType].buffer+retail->ioBuffer[retail->curType].used,str,len+1);
      retail->ioBuffer[retail->curType].used+=len;
    }

    // last char CR?
    retail->ioBuffer[retail->curType].lastWasCR=str[len-1]=='\n';
    str+=len;
    remainingLen-=len;

    // are we writing a log string? (retail keeps Log==1)
    if (retail->curType==1&&retail->ioBuffer[retail->curType].lastWasCR)
    {
      // yes, flush out now
      Debug::FlushOutput(true);
      retail->curType=1;
    }
  }
}

// ?FlushOutput@Debug@@EAEX_N@Z
void Debug::FlushOutput(bool defaultLog)
{
  (void)defaultLog;
  RetailDebugOutView *retail = (RetailDebugOutView *)this;
  // Retail bails when no valid destination type is set (this TU's headers
  // have 8 string types with MAX==8; retail has 7 with MAX==7).
  if (retail->curType==7)
    return;

  // bail out early if buffer is still empty
  if (!retail->ioBuffer[retail->curType].used)
  {
    retail->curType=7;
    return;
  }

  // need CR?
  if (!retail->ioBuffer[retail->curType].lastWasCR)
    operator<<("\n");

  // send string to all active I/O interfaces
  for (Debug::IOFactoryListEntry *cur=(Debug::IOFactoryListEntry *)retail->firstIOFactoryLink;cur;cur=cur->next)
  {
    if (!cur->io)
      continue;

    // Retail's DebugIOInterface carries a bool query at slot +8 (see
    // RetailDebugIOInterface), so Write sits at +0xc, not +0x8.
    ((RetailDebugIOInterface *)cur->io)->Write(retail->curType,retail->curSource,retail->ioBuffer[retail->curType].buffer);

    if (retail->alwaysFlush)
      ((RetailDebugIOInterface *)cur->io)->Write(retail->curType,retail->curSource,NULL);
  }

  // empty buffer etc.
  retail->ioBuffer[retail->curType].used=0;
  *retail->ioBuffer[retail->curType].buffer=0;
  retail->curType=7;
  *retail->curSource=0;
}

// ?AddPatternEntry@Debug@@EAEXI_NPBD@Z present-unmatched
void Debug::AddPatternEntry(unsigned types, bool isActive, const char *pattern)
{
  __ASSERT(pattern);

  // alloc new pattern entry
  PatternListEntry *cur=(PatternListEntry *)
      DebugAllocMemory(sizeof(PatternListEntry));

  // init
  cur->next=NULL;
  cur->frameTypes=types;
  cur->isActive=isActive;
  cur->pattern=(char *)DebugAllocMemory(strlen(pattern)+1);
  strcpy(cur->pattern,pattern);

  // add to list
  if (lastPatternEntry)
    lastPatternEntry->next=cur;
  else
    firstPatternEntry=cur;
  lastPatternEntry=cur;
}

// Debug::SimpleMatch: defined in WWDebug/DebugSimpleMatch.cpp (its row's unit).

// ?SetBuildInfo@Debug@@SAXPBD00@Z defined in GameEngine/Source/Main/WinMain.cpp (its row's unit).

// Retail Debug ABI in this TU: m_version/m_intVersion/m_buildDate sit 4 bytes
// later than this TU's headers place them (retail reads m_version at
// this+0x9e90, m_intVersion at +0x9ed0, m_buildDate at +0x9f10). TU-local view
// so the placed stream bodies in this TU keep their layout.
struct RetailDebugVersionView {
  char _pad[0x9e90];
  char m_version[64];
  char m_intVersion[64];
  char m_buildDate[64];
};

void Debug::WriteBuildInfo(void)
{
  const RetailDebugVersionView * retail = (const RetailDebugVersionView *)this;
  operator<<("Version:");
  if (*retail->m_version)
    (*this) << " " << retail->m_version;
  if (*retail->m_intVersion)
    (*this) << " internal " << retail->m_intVersion;
  #if defined(_INTERNAL)
    operator<<(" internal");
  #elif defined(_DEBUG)
    operator<<(" debug");
  #elif defined(_PROFILE)
    operator<<(" profile");
  #else
    operator<<(" release");
  #endif
  if (*retail->m_buildDate)
    (*this) << " build " << retail->m_buildDate;
}

// ?ExecCommand@Debug@@EAEXPBD0@Z present-unmatched
void Debug::ExecCommand(const char *cmdstart, const char *cmdend)
{
  // split off into command and arguments

  // alloc & copy string
  char *strbuf=(char *)DebugAllocMemory(cmdend-cmdstart+1);
  memcpy(strbuf,cmdstart,cmdend-cmdstart);
  strbuf[cmdend-cmdstart]=0;

  // for simplicity I'm using a fixed size argv array here...
  // if there are more arguments given than we have we're
  // just dropping the excess arguments
  char *parts[100];
  int numParts=0;
  char *lastNonWhitespace=NULL;
  char *cur=strbuf;

  // regular reply or structured reply?
  DebugIOInterface::StringType reply;
  DebugCmdInterface::CommandMode mode;
  if (*cur=='!')
  {
    cur++;
    reply=DebugIOInterface::StringType::StructuredCmdReply;
    mode=DebugCmdInterface::CommandMode::Structured;
  }
  else
  {
    reply=DebugIOInterface::StringType::CmdReply;
    mode=DebugCmdInterface::CommandMode::Normal;
  }

  for (;;)
  {
    if (!lastNonWhitespace&&(*cur=='\''||*cur=='"'))
    {
      char quote=*cur++;

      if (numParts<sizeof(parts)/sizeof(*parts))
        parts[numParts++]=cur;

      while (*cur&&*cur!=quote)
        ++cur;
      if (*cur)
        *cur++=0;
    }
    else if (*cur==' '||*cur=='\t'||!*cur||*cur==';')
    {
      if (*cur==';')
        *cur=0;
      if (lastNonWhitespace)
      {
        if (numParts<sizeof(parts)/sizeof(*parts))
          parts[numParts++]=lastNonWhitespace;
        lastNonWhitespace=NULL;
        if (*cur)
          *cur++=0;
      }
      else if (*cur)
        ++cur;
      else
        break;
    }
    else
    {
      if (!lastNonWhitespace)
        lastNonWhitespace=cur;
      ++cur;
    }
  }

  if (numParts)
  {
    // part[0] is the command, part[1..numParts] are arguments

    // split off command group (if any)
    char *p=strchr(parts[0],'.');
    if (p&&p-parts[0]<sizeof(curCommandGroup))
    {
      memcpy(curCommandGroup,parts[0],p-parts[0]);
      curCommandGroup[p-parts[0]]=0;
      ++p;
    }
    else
      p=parts[0];

    StartOutput(reply,"%s.%s",curCommandGroup,p);

    if (mode!=DebugCmdInterface::CommandMode::Structured)
      AddOutput("> ",2);
  
    // repeat current command first
    AddOutput(cmdstart,cmdend-cmdstart);
    AddOutput("\n",1);

    // command group known?
    for (CmdInterfaceListEntry *cur=firstCmdGroup;cur;cur=cur->next)
      if (!strcmp(curCommandGroup,cur->group))
        break;
    if (!cur)
    {
      // nope, show error message
      (*this) << "Unknown command group " << curCommandGroup;
      *p=0;
    }

    if (*p)
    {
      // must have command...

      // search for a matching command handler
      for (CmdInterfaceListEntry *cur=firstCmdGroup;cur;cur=cur->next)
      {
        if (strcmp(curCommandGroup,cur->group))
          continue;

        bool doneCommand=cur->cmdif->Execute(*this,p,mode,numParts-1,parts+1);
        if (doneCommand&&(strcmp(p,"help")||numParts>1))
          break;
      }

      // display error message if command not found, break away
      if (!cur&&mode==DebugCmdInterface::CommandMode::Normal)
      {
        if (strcmp(p,"help"))
          operator<<("Unknown command");
        else if (numParts>1)
          operator<<("Unknown command, help not available");
      }
    }

    // flush output only if there is already an active I/O class
    FlushOutput(false);
  }

  // cleanup
  DebugFreeMemory(strbuf);
}

// little helper to get app window
BOOL CALLBACK EnumThreadWndProc(HWND hwnd, LPARAM lParam)
{
  *(HWND *)lParam=hwnd;
  return FALSE;
}

// ?IsWindowed@Debug@@EAE_NXZ present-unmatched
bool Debug::IsWindowed(void)
{
  // use cached result if possible
  if (m_isWindowed)
    return m_isWindowed>0;

  // find main app window
  HWND appHWnd=NULL;
  EnumThreadWindows(GetCurrentThreadId(),EnumThreadWndProc,(LPARAM)&appHWnd);
  if (!appHWnd)
  {
    // couldn't find main window, assume we're windowed anyway
    m_isWindowed=1;
    return true;
  }

  // we assume full screen if WS_CAPTION is not set
  m_isWindowed=(GetWindowLong(appHWnd,GWL_STYLE)&WS_CAPTION)?1:-1;
  return m_isWindowed>0;
}

//////////////////////////////////////////////////////////////////////////////

// And finally for a little list of C/C++ runtime replacement functions.

// Abort process due to fatal heap error
void __cdecl _heap_abort(void)
{
  DCRASH_RELEASE("Fatal heap error.");
}
