// cl: /MD /EHsc
//
// Zero Hour profile_result.cpp as built into BFME2 (retail 0x006C6E80-
// 0x006C837F): the CSV, DOT and BFME2-new GTT result writers (layouts and
// vtables in internal_result.h). Each writer's GetName is the header inline
// its vtable slot 2 holds (0x006C7580 DOT, 0x006C7590 GTT, 0x006C75F0 CSV).
// ProfileFuncLevel accessors are the !HAS_PROFILE empty bodies
// (profile_funclevel.cpp); retail ICF-folds most of them onto identical
// bodies elsewhere.

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <new>
#include "internal.h"

// This 300-byte named buffer covers retail's strncpy request and terminator;
// its initial target span is zero, but the original allocation extent is unknown.
char profile_csv_source[300];
// The private helper also survives out of line at native 6C6E80, between
// independent int3 runs. MSVC emits its private source-argument ABI in EAX.
// Full byte verification checks that ABI; its original name is unknown.
static __forceinline const char *rva006C6E80CsvName(const char *name)
{
    strncpy(profile_csv_source, name, sizeof(profile_csv_source));
    profile_csv_source[sizeof(profile_csv_source)-1] = 0;
    for (char *p = profile_csv_source; *p; ++p)
        if (*p == ',') *p = ';';
    return profile_csv_source;
}
// ??0ProfileResultFileDOT@@QAE@PBD0H@Z
ProfileResultFileDOT::ProfileResultFileDOT(const char *fileName,
		const char *frameName, int foldThreshold)
{
	if (!fileName)
		fileName = "profile.dot";
	m_fileName = (char *)ProfileAllocMemory(strlen(fileName) + 1);
	strcpy(m_fileName, fileName);
	if (frameName)
	{
		m_frameName = (char *)ProfileAllocMemory(strlen(frameName) + 1);
		strcpy(m_frameName, frameName);
	}
	else
		m_frameName = 0;
	m_foldThreshold = foldThreshold;
}

// ?WriteResults@ProfileResultFileDOT@@UAEXXZ (vtable 0x00CE84D0 slot 0). Retail keeps
// the folded path's caller-source scan but writes no folded edges.
void ProfileResultFileDOT::WriteResults(void)
{
  // search "main" thread
  ProfileFuncLevel::Thread t,tMax;
  if (!ProfileFuncLevel::EnumThreads(0,tMax))
    return;

  unsigned curMax=0;
  for (unsigned k=1;ProfileFuncLevel::EnumThreads(k,t);k++)
  {
    for (;curMax++;)
    {
      ProfileFuncLevel::Id help;
      if (!tMax.EnumProfile(curMax,help))
      {
        tMax=t;
        break;
      }
      if (!t.EnumProfile(curMax,help))
        break;
      curMax++;
    }
  }

  // search frame
  unsigned frame=ProfileFuncLevel::Id::Total;
  if (m_frameName)
  {
    for (unsigned k=0;k<Profile::GetFrameCount();k++)
      if (!strcmp(Profile::GetFrameName(k),m_frameName))
      {
        frame=k;
        break;
      }
  }

  // determine number of active functions
  int active=0;
  ProfileFuncLevel::Id id;
  for (k=0;tMax.EnumProfile(k,id);k++)
    if (id.GetCalls(frame))
      active++;

  FILE *f=fopen(m_fileName,"wt");
  if (!f)
    return;

  // DOT header
  fprintf(f,"digraph G { rankdir=\"LR\";\n");
  fprintf(f,"node [shape=box, fontname=Arial]\n");
  fprintf(f,"edge [arrowhead=%s, labelfontname=Arial, labelfontsize=10, labelangle=0, labelfontcolor=blue]\n",
    active>m_foldThreshold?"closed":"open");

  // fold or not?
  if (active>m_foldThreshold)
  {
    // folding version

    // build source code clusters first
    FoldHelper *fold=NULL;
    for (k=0;tMax.EnumProfile(k,id);k++)
    {
      const char *source=id.GetSource();
      for (FoldHelper *cur=fold;cur;cur=cur->next)
        if (!strcmp(source,cur->source))
        {
          if (cur->numId<MAX_FUNCTIONS_PER_FILE)
            cur->id[cur->numId++]=id;
          break;
        }
      if (!cur)
      {
        cur=(FoldHelper *)ProfileAllocMemory(sizeof(FoldHelper));
        cur->next=fold;
        fold=cur;
        cur->source=source;
        cur->numId=1;
        cur->id[0]=id;
      }
    }

    // now write data
    for (FoldHelper *cur=fold;cur;cur=cur->next)
    {
      FoldHelper *cur2;
      for (cur2=fold;cur2;cur2=cur2->next)
        cur2->mark=false;
      
      fprintf(f,"\"%s\";\n",cur->source);
      for (k=0;k<cur->numId;k++)
      {
        ProfileFuncLevel::IdList idlist=cur->id[k].GetCaller(frame);
        ProfileFuncLevel::Id caller;
        for (unsigned i=0;idlist.Enum(i,caller);i++)
        {
          const char *s=caller.GetSource();
          for (FoldHelper *candidate=fold;candidate;candidate=candidate->next)
            if (!strcmp(candidate->source,s))
              break;
          // Retail retains this source lookup and emits no folded edge.
          // The lookup remains for the native access behavior; no folded edge
          // write survives in this target path.
        }
      }
    }

    // cleanup
    while (fold)
    {
      FoldHelper *next=fold->next;
      ProfileFreeMemory(fold);
      fold=next;
    }
  }
  else
  {
    // non-folding version
    for (k=0;tMax.EnumProfile(k,id);k++)
      if (id.GetCalls(frame))
        fprintf(f,"f%08x [label=\"%s\"]\n",id.GetAddress(),id.GetFunction());
    for (k=0;tMax.EnumProfile(k,id);k++)
    {
      ProfileFuncLevel::IdList idlist=id.GetCaller(frame);
      ProfileFuncLevel::Id caller;
      unsigned count;
      for (unsigned i=0;idlist.Enum(i,caller,&count);i++)
        fprintf(f,"f%08x -> f%08x [headlabel=\"%i    \"];\n",caller.GetAddress(),id.GetAddress(),count);
    }
  }

  fprintf(f,"}\n");
  fclose(f);
}

// ?MarkVisited@ProfileResultFileGTT@@QAE_NII@Z: visited-edge set, grown 1000 at a time.
bool ProfileResultFileGTT::MarkVisited(unsigned from, unsigned to)
{
    Edge *visited=m_visited;
    Edge *edge=visited;
    for (unsigned i=0;i<m_numVisited;i++,edge++)
        if (edge->from==from && edge->to==to)
            return true;
    if (m_numVisited==m_visitedAlloc)
    {
        m_visitedAlloc+=1000;
        m_visited=(Edge *)ProfileReAllocMemory(visited,m_visitedAlloc*sizeof(Edge));
    }
    m_visited[m_numVisited].from=from;
    m_visited[m_numVisited].to=to;
    m_numVisited++;
    return false;
}

// ?Delete@ProfileResultFileDOT@@UAEXXZ; the CSV and GTT bodies are
// identical and ICF-fold onto it (0x006C74C0).
void ProfileResultFileDOT::Delete(void)
{
	this->~ProfileResultFileDOT();
	ProfileFreeMemory(this);
}

void ProfileResultFileCSV::Delete(void)
{
	this->~ProfileResultFileCSV();
	ProfileFreeMemory(this);
}

void ProfileResultFileGTT::Delete(void)
{
	this->~ProfileResultFileGTT();
	ProfileFreeMemory(this);
}

// ??0ProfileResultFileGTT@@QAE@PBD0H@Z
ProfileResultFileGTT::ProfileResultFileGTT(const char *fileName,
		const char *frameName, int percentThreshold)
{
	m_visited = 0;
	m_numVisited = 0;
	m_visitedAlloc = 0;
	if (!fileName)
		fileName = "profile_gtt.dot";
	m_fileName = (char *)ProfileAllocMemory(strlen(fileName) + 1);
	strcpy(m_fileName, fileName);
	if (frameName)
	{
		m_frameName = (char *)ProfileAllocMemory(strlen(frameName) + 1);
		strcpy(m_frameName, frameName);
	}
	else
		m_frameName = 0;
	m_percentThreshold = percentThreshold;
}

// ??0ProfileResultFileCSV@@QAE@PBD@Z
ProfileResultFileCSV::ProfileResultFileCSV(const char *fileName)
{
	if (fileName)
	{
		m_fileName = (char *)ProfileAllocMemory(strlen(fileName) + 1);
		strcpy(m_fileName, fileName);
	}
	else
		m_fileName = 0;
}

// ?WriteThread@ProfileResultFileCSV@@AAEXAAVThread@ProfileFuncLevel@@@Z
void ProfileResultFileCSV::WriteThread(ProfileFuncLevel::Thread &thread)
{
    char help[40];
    sprintf(help,"prof%08x-all.csv",thread.GetId());
    FILE *f=fopen(m_fileName ? m_fileName : help,"wt");
    fprintf(f,"Function,File,Call count,PTT (all),GTT (all),PT/C (all),GT/C (all),Caller (all)");
    for (unsigned k=0;k<Profile::GetFrameCount();k++)
    {
        const char *s=Profile::GetFrameName(k);
        fprintf(f,",Call (%s),PTT (%s),GTT (%s),PT/C (%s),GT/C (%s),Caller (%s)",s,s,s,s,s,s);
    }
    fprintf(f,"\n");
    ProfileFuncLevel::Id id;
    for (k=0;thread.EnumProfile(k,id);k++)
    {
        const char *function = rva006C6E80CsvName(id.GetFunction());
        fprintf(f,"%s[%08x],%s#%i",function,id.GetAddress(),id.GetSource(),id.GetLine());
        for (unsigned i=ProfileFuncLevel::Id::Total;i!=Profile::GetFrameCount();i++)
        {
            if (!id.GetCalls(i))
            {
                fprintf(f,",,,,,,");
                continue;
            }
            fprintf(f,",%I64i",id.GetCalls(i));
            fprintf(f,",%I64i",id.GetFunctionTime(i));
            fprintf(f,",%I64i",id.GetTime(i));
            fprintf(f,",%I64i",id.GetFunctionTime(i)/id.GetCalls(i));
            fprintf(f,",%I64i",id.GetTime(i)/id.GetCalls(i));
            ProfileFuncLevel::IdList idlist=id.GetCaller(i);
            fprintf(f,",");
            ProfileFuncLevel::Id callid;
            unsigned j;
            if (idlist.Enum(50,callid))
            {
                unsigned threshold=1;
                unsigned number;
                do
                {
                    number=0;
                    unsigned next=~0U;
                    unsigned count;
                    for (j=0;idlist.Enum(j,callid,&count);j++)
                        if (count > threshold)
                        {
                            number++;
                            if (count < next) next=count;
                        }
                    if (number > 50) threshold=next;
                } while (number > 50);
                unsigned misc=0;
                unsigned count;
                for (j=0;idlist.Enum(j,callid,&count);j++)
                    if (count > threshold)
                    {
                        const char *function=rva006C6E80CsvName(callid.GetFunction());
                        fprintf(f," %s[%08x](%i)",function,callid.GetAddress(),count);
                    }
                    else misc+=count;
                if (misc > 0) fprintf(f," misc(%i)",misc);
            }
            else
            {
                unsigned count;
                for (j=0;idlist.Enum(j,callid,&count);j++)
                {
                    const char *function=rva006C6E80CsvName(callid.GetFunction());
                    fprintf(f," %s[%08x](%i)",function,callid.GetAddress(),count);
                }
            }
        }
        fprintf(f,"\n");
    }
    fclose(f);
}

// CSV vtable 0x00CE85E4 slot 0 calls native 6C7A60. The body ends in a
// return at 6C7C49 followed by padding. With an explicit filename, retail
// chooses the thread with the most IDs and writes only that thread; otherwise
// it writes every thread and the high-level summary, using comma separators.
void ProfileResultFileCSV::WriteResults()
{
    if (m_fileName)
    {
        ProfileFuncLevel::Thread t;
        unsigned best=0;
        unsigned bestCount=0;
        for (unsigned k=0;ProfileFuncLevel::EnumThreads(k,t);k++)
        {
            ProfileFuncLevel::Id id;
            unsigned count=0;
            while (t.EnumProfile(count,id)) count++;
            if (count > bestCount)
            {
                bestCount=count;
                best=k;
            }
        }
        ProfileFuncLevel::EnumThreads(best,t);
        WriteThread(t);
        return;
    }
    ProfileFuncLevel::Thread t;
    for (unsigned k=0;ProfileFuncLevel::EnumThreads(k,t);k++)
        WriteThread(t);
    FILE *f=fopen("profile-high.csv","wt");
    if (!f) return;
    fprintf(f,"Profile,Unit,total");
    for (k=0;k<Profile::GetFrameCount();k++)
        fprintf(f,",%s",Profile::GetFrameName(k));
    fprintf(f,"\n");
    {
        ProfileHighLevel::Id id;
        for (k=0;ProfileHighLevel::EnumProfile(k,id);k++)
        {
            fprintf(f,"%s,%s,%s",id.GetName(),id.GetUnit(),id.GetTotalValue());
            for (unsigned i=0;i<Profile::GetFrameCount();i++)
            {
                const char *p=id.GetValue(i);
                fprintf(f,",%s",p?p:"");
            }
            fprintf(f,"\n");
        }
    }
    fclose(f);
}


// ?Create@ProfileResultFileCSV@@SAPAVProfileResultInterface@@HPBQBD@Z
ProfileResultInterface *ProfileResultFileCSV::Create(int argn, const char *const *argv)
{
	return new (ProfileAllocMemory(sizeof(ProfileResultFileCSV)))
		ProfileResultFileCSV(argn > 0 ? argv[0] : 0);
}

// ?Create@ProfileResultFileDOT@@SAPAVProfileResultInterface@@HPBQBD@Z
ProfileResultInterface *ProfileResultFileDOT::Create(int argn, const char *const *argv)
{
	return new (ProfileAllocMemory(sizeof(ProfileResultFileDOT)))
		ProfileResultFileDOT(argn > 0 ? argv[0] : 0,
			argn > 1 ? argv[1] : 0,
			argn > 2 ? atoi(argv[2]) : 999);
}

// ?Create@ProfileResultFileGTT@@SAPAVProfileResultInterface@@HPBQBD@Z
ProfileResultInterface *ProfileResultFileGTT::Create(int argn, const char *const *argv)
{
	return new (ProfileAllocMemory(sizeof(ProfileResultFileGTT)))
		ProfileResultFileGTT(argn > 0 ? argv[0] : 0,
			argn > 1 ? argv[1] : 0,
			argn > 2 ? atoi(argv[2]) : 100);
}

// ?rva006C7DD0WriteGraph@ProfileResultFileGTT@@AAEXAAVThread@ProfileFuncLevel@@PAU_iobuf@@I_KI@Z
// Recursive graph walk; original private name unknown.
void ProfileResultFileGTT::rva006C7DD0WriteGraph(ProfileFuncLevel::Thread &thread, FILE *f,
    unsigned rootIndex, unsigned __int64 maxTime, unsigned frame)
{
    if (maxTime<10000) return;
    ProfileFuncLevel::Id root;
    thread.EnumProfile(rootIndex,root);
    unsigned rootAddress=root.GetAddress();
    ProfileFuncLevel::Id id;
    for (unsigned k=0;thread.EnumProfile(k,id);k++)
    {
        ProfileFuncLevel::IdList callers=id.GetCaller(frame);
        ProfileFuncLevel::Id caller;
        unsigned count;
        for (unsigned i=0;callers.Enum(i,caller,&count);i++)
            if (caller.GetAddress()==rootAddress)
            {
                unsigned __int64 time=id.GetTime(frame);
                unsigned __int64 calls=id.GetCalls(frame);
                unsigned __int64 edgeTime=count*time/calls;
                unsigned percent=(unsigned)(edgeTime/(maxTime/10000));
                if (percent<m_percentThreshold || MarkVisited(rootIndex,k)) continue;
                fprintf(f,"f%08x [label=\"%s\\n%I64iM, %I64i calls\"];\n",root.GetAddress(),root.GetFunction(),
                    (root.GetTime(frame)+500000)/1000000,root.GetCalls(frame));
                fprintf(f,"f%08x [label=\"%s\\n%I64iM, %I64i calls\"];\n",id.GetAddress(),id.GetFunction(),
                    (id.GetTime(frame)+500000)/1000000,id.GetCalls(frame));
                fprintf(f,"f%08x ",root.GetAddress());
                fprintf(f,"-> f%08x",id.GetAddress());
                fprintf(f,"[headlabel=\"\\n%I64iM\\n%i.%02i%%\"];\n",(edgeTime+500000)/1000000,
                    percent<100?0:percent/100,percent%100);
                rva006C7DD0WriteGraph(thread,f,k,maxTime,frame);
            }
    }
}

// ?WriteResults@ProfileResultFileGTT@@UAEXXZ (vtable 0x00CE85D8 slot 0)
void ProfileResultFileGTT::WriteResults()
{
  // search "main" thread
  ProfileFuncLevel::Thread t,tMax;
  if (!ProfileFuncLevel::EnumThreads(0,tMax))
    return;

  unsigned curMax=0;
  for (unsigned k=1;ProfileFuncLevel::EnumThreads(k,t);k++)
  {
    for (;curMax++;)
    {
      ProfileFuncLevel::Id help;
      if (!tMax.EnumProfile(curMax,help))
      {
        tMax=t;
        break;
      }
      if (!t.EnumProfile(curMax,help))
        break;
      curMax++;
    }
  }

  // search frame
  unsigned frame=ProfileFuncLevel::Id::Total;
  if (m_frameName)
  {
    for (unsigned k=0;k<Profile::GetFrameCount();k++)
      if (!strcmp(Profile::GetFrameName(k),m_frameName))
      {
        frame=k;
        break;
      }
  }


  ProfileFuncLevel::Id id;
  bool hasCallers=false;
  for (k=0;tMax.EnumProfile(k,id);k++)
  {
    ProfileFuncLevel::Id caller;
    if (id.GetCaller(frame).Enum(0,caller))
    {
      hasCallers=true;
      break;
    }
  }
  if (!hasCallers) return;
  FILE *f=fopen(m_fileName,"wt");
  if (!f) return;
  fprintf(f,"digraph G {\n");
  fprintf(f,"node [shape=box, fontname=Arial]\n");
  fprintf(f,"edge [arrowhead=open, labelfontname=Arial, labelfontsize=10, labelangle=0, labelfontcolor=red]\n");
  unsigned __int64 largest=0;
  unsigned root=0;
  for (k=0;tMax.EnumProfile(k,id);k++)
    if (id.GetTime(frame)>largest)
    {
      largest=id.GetTime(frame);
      root=k;
    }
  rva006C7DD0WriteGraph(tMax,f,root,largest,frame);
  fprintf(f,"}\n");
  fclose(f);
}
