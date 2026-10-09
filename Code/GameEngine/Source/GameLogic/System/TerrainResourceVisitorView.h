#ifndef BFME_TERRAIN_RESOURCE_VISITOR_VIEW_H
#define BFME_TERRAIN_RESOURCE_VISITOR_VIEW_H
// Native vtables8153D4/8153D8 each contain one cell callback, not a destructor.
// WB E5F960 installs the base then derived table; E60670 resets the base on
// destruction. Original visitor names and the distribution of fields between
// base and derived remain unknown; only the complete28-byte layout is used.
class Rva0035A97EVisitor {
public:
    virtual void slot00(int,int);
    ~Rva0035A97EVisitor() {}
};
class Rva0035986C: public Rva0035A97EVisitor {
public:
    Rva0035986C(int,bool,int,bool);
    virtual void slot00(int,int);
private:
    int m_04, m_08, m_0C, m_10, m_14;
    bool m_18;
};
// Sibling table8153DC: a claim callback forwards both counters by address.
class Rva003598D3: public Rva0035A97EVisitor {
public:
    Rva003598D3(int,int,int,bool);
    virtual void slot00(int,int);
private:
    int m_04, m_08, m_0C, m_10, m_14;
    bool m_18;
};
#endif
