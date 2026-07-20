class ST_LocationZone
{
    string Name;
    string Type;
    float X;
    float Z;
    float Radius;
}


class ST_CustomThoughtZone
{
    string Name;
    string Type;
    float X;
    float Z;
    float Radius;
    float Chance;
    float CooldownSeconds;
    ref array<string> Messages;
}
