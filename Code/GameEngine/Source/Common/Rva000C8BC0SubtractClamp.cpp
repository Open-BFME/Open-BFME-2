// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common

class Rva000C8BC0SubtractClamp
{
    char padding[4];
    int value;

public:
    void subtract(int amount);
};

void Rva000C8BC0SubtractClamp::subtract(int amount)
{
    value -= amount;
    if (value < 0)
        value = 0;
}
