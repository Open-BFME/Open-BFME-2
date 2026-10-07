// ?rva0032E474@SidesList@@QAEXPAXPAVScriptList@@PAVTeamsInfoRec@@@Z
// partial score=0.97 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
class Dict { void* m_data; };
struct Rva0032E474Node {
    short next;
    char m_gap[0xa];
    Dict dictionary;
};
struct Rva0032E474Table {
    char m_lead[0xc];
    Rva0032E474Node* nodes;
    char m_gap[8];
    short count;
};
class ScriptList;
class Rva003B89A7View { public: void rva003B89A7(ScriptList*); };
class TeamsInfoRec {
public:
    void swap(TeamsInfoRec*);
    int addTeam(const Dict*);
};
class SidesList {
public:
    void rva0032E474(void*,ScriptList*,TeamsInfoRec*);
private:
    char m_lead[0xf44];
    TeamsInfoRec m_teams;
};
void SidesList::rva0032E474(void* first,ScriptList* scripts,TeamsInfoRec* teams) {
    ((Rva003B89A7View*)((char*)first+8))->rva003B89A7(scripts);
    Rva0032E474Table* table=(Rva0032E474Table*)teams;
    if(table->count>0) {
        TeamsInfoRec* context=&m_teams;
        context->swap(teams);
        int index=table->nodes[0].next;
        while(index) {
            context->addTeam(&table->nodes[index].dictionary);
            index=table->nodes[index].next;
        }
    }
}
