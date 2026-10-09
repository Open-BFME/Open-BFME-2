// cl: /O1 /Oy- /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// Target323B callback413C02; WB12E8030 independently exposes four arguments.
// Native strings, scan/import calls and existing named schedule lookup413BC5
// prove map<int,int> at0 and EachRemaining stride at0C. WB establishes purpose;
// target proves one-based key validation followed by decrement before insertion.
// No compatible BFME1/ZH LivingWorld source; existing ancestral INI and STL
// providers are reused. Filename temporary uses canonical AsciiString lifetime.
// The temporary pair and named insertion result reproduce retail stack reuse;
// ordinary INIException throws carry real copy/destructor metadata.
#include <map>
#include <stdio.h>
#include <string.h>
template<class T> struct StringInlineData { int m_refCount,m_length;T m_text[1]; };
#include "ascii_string.h"
class INI { public: const char *getNextToken(const char *);int scanInt(const char *);AsciiString getFilename() const;int getLineNum() const; };
class INIException { public: char *message;int count;INIException(int,const char *,...);INIException(const INIException &);~INIException(); };
typedef _STL::pair<const int,int> Value;
typedef _STL::_Rb_tree<int,Value,_STL::_Select1st<Value>,_STL::less<int>,_STL::allocator<Value> > Tree;
template<> _STL::pair<Tree::iterator,bool> Tree::insert_unique(const Value &);
struct Schedule { Tree entries;int eachRemaining; };
void Rva00413C02Parse(INI *ini,void *instance,void *,const char *key) {
 Schedule *schedule=static_cast<Schedule *>(instance);
 const char *token=ini->getNextToken(0);
 if(_strcmpi(key,"EachRemaining")==0) { schedule->eachRemaining=ini->scanInt(token);return; }
 if(key[0]=='#') throw INIException(5,"Cannot use math operations on AutoResolveReinforcementSchedule army indexes");
 int index;
 if(sscanf(key,"%d",&index)!=1) throw INIException(5,"Unknown field '%s' in block 'AutoResolveReinforcementSchedule'.\n\nError parsing field '%s' in block 'AutoResolveReinforcementSchedule' in file '%s', line %i.\n",key,key,ini->getFilename().str(),ini->getLineNum());
 if(index<=0) throw INIException(5,"Unacceptable army index %d in AutoResolveReinforcementSchedule. Must be > 0",index);
 int round=ini->scanInt(token);
 --index;
 _STL::pair<Tree::iterator,bool> inserted=schedule->entries.insert_unique(Value(index,round));
 if(!inserted.second) throw INIException(3,"AutoResolveReinforcementSchedule. Duplicate entries for army index %d",index+1);
}
