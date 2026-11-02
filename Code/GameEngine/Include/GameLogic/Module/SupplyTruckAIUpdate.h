// Shared BFME2 ABI view, not a claim to have recovered retail's header.
// Native tables: 20 purecall entries at RVA 0x00852EE8 and 20 callbacks at
// RVA 0x00852F38. No virtual destructor is present.
// Names of the additional BFME2 callbacks are unresolved. rva names retain
// their measured AL/EAX/x87 return ABI; slot 17 preserves an unused stack word.
// Signedness and the Coord3D pointer spelling are storage-view choices, not
// recovered original types. Existing semantic names retain donor/consumer leads.
#pragma once
#ifndef BFME2_SUPPLY_TRUCK_AI_INTERFACE_H
#define BFME2_SUPPLY_TRUCK_AI_INTERFACE_H
class Object;
struct Coord3D;
enum ObjectID;
class SupplyTruckAIInterface {
public:
    virtual int getNumberBoxes() const = 0;                       //0
    virtual int rva004A6E29() const = 0;                          //1
    virtual bool loseOneBox() = 0;                               //2
    virtual bool gainOneBox(int remainingStock) = 0;              //3
    virtual bool isAvailableForSupplying() const = 0;             //4
    virtual bool isCurrentlyFerryingSupplies() const = 0;          //5
    virtual unsigned char rva004A6FE5() const = 0;                 //6
    virtual float rva004A6FEF() const = 0;                        //7
    virtual int rva004A6FF9() const = 0;                          //8
    virtual unsigned int rva004A7003() const = 0;                 //9
    virtual float rva004A6FBF() const = 0;                        //10
    // Legacy semantic setter names already own different retail bodies.
    virtual void rva00210CD3(bool value) = 0;                    //11
    virtual bool isForcedIntoWantingState() const = 0;            //12
    virtual void rva005975D7(bool value) = 0;                    //13
    virtual bool isForcedIntoBusyState() const = 0;               //14
    virtual ObjectID getPreferredDockID() const = 0;              //15
    virtual unsigned char rva004A6A44(Coord3D *result) const = 0;  //16
    virtual void rva0047A69C(unsigned int unusedWord) = 0;         //17
    virtual int rva000D43D0() const = 0;                          //18
    virtual unsigned int getActionDelayForDock(Object *dock) = 0; //19
};

#endif
