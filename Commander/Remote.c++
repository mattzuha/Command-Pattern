#include <iostream>
#include <typeindex>
using namespace std;

class Light
{
private:
    string location;

public:
    Light(string location) : location(location) {}
    void on()
    {
        cout << location << " light is on" << endl;
    }
    void off()
    {
        cout << location << " light is off" << endl;
    }
};

class Stereo
{
private:
    string location;

public:
    Stereo(string location) : location(location) {}
    void on()
    {
        cout << location << " stereo is on" << endl;
    }
    void off()
    {
        cout << location << " stereo is off" << endl;
    }
    void setCD()
    {
        cout << location << " stereo is set for CD input" << endl;
    }
    void setDVD()
    {
        cout << location << " stereo is set for DVD input" << endl;
    }
    void setRadio()
    {
        cout << location << " stereo is set for Radio" << endl;
    }
    void setVolume(int volume)
    {
        cout << location << " stereo volume set to " << volume << endl;
    }
};

class CeilingFan
{
private:
    string location;
    int speed;

public:
    static const int HIGH = 3;
    static const int MEDIUM = 2;
    static const int LOW = 1;
    static const int OFF = 0;

    CeilingFan(string location) : location(location) {}
    void high()
    {
        speed = HIGH;
        cout << location << " ceiling fan is on high" << endl;
    }
    void medium()
    {
        speed = MEDIUM;
        cout << location << " ceiling fan is on medium" << endl;
    }
    void low()
    {
        speed = LOW;
        cout << location << " ceiling fan is on low" << endl;
    }
    void off()
    {
        speed = OFF;
        cout << location << " ceiling fan is off" << endl;
    }
    int getSpeed()
    {
        return speed;
    }
};

class Command
{
public:
    virtual void execute() = 0;
};

class NoCommand : public Command
{
public:
    void execute() {}
};

class LightOnCommand : public Command
{
private:
    Light *light;

public:
    LightOnCommand(Light *light) : light(light) {}
    void execute() override
    {
        light->on();
    }
};

class LightOffCommand : public Command
{
private:
    Light *light;

public:
    LightOffCommand(Light *light) : light(light) {}
    void execute()
    {
        light->off();
    }
};

class StereoOnWithCDCommand : public Command
{
private:
    Stereo *stereo;

public:
    StereoOnWithCDCommand(Stereo *stereo) : stereo(stereo) {}
    void execute()
    {
        stereo->on();
        stereo->setCD();
        stereo->setVolume(11);
    }
};

class StereoOffCommand : public Command
{
private:
    Stereo *stereo;

public:
    StereoOffCommand(Stereo *stereo) : stereo(stereo) {}
    void execute()
    {
        stereo->off();
    }
};

class CeilingFanOnCommand : public Command
{
private:
    CeilingFan *ceilingFan;

public:
    CeilingFanOnCommand(CeilingFan *ceilingFan) : ceilingFan(ceilingFan) {}
    void execute()
    {
        ceilingFan->high();
    }
};

class CeilingFanOffCommand : public Command
{
private:
    CeilingFan *ceilingFan;

public:
    CeilingFanOffCommand(CeilingFan *ceilingFan) : ceilingFan(ceilingFan) {}
    void execute()
    {
        ceilingFan->off();
    }
};

class RemoteControl
{
    Command **onCommands;
    Command **offCommands;

public:
    RemoteControl()
    {
        onCommands = new Command *[7];
        offCommands = new Command *[7];

        Command *noCommand = new NoCommand();
        for (int i = 0; i < 7; i++)
        {
            onCommands[i] = noCommand;
            offCommands[i] = noCommand;
        }
    }
    void setCommand(int slot, Command *onCommand, Command *offCommand)
    {
        onCommands[slot] = onCommand;
        offCommands[slot] = offCommand;
    }
    void onButtonWasPushed(int slot)
    {
        onCommands[slot]->execute();
    }
    void offButtonWasPushed(int slot)
    {
        offCommands[slot]->execute();
    }
};

int main()
{
    RemoteControl *remoteControl = new RemoteControl();

    Light *livingRoomLight = new Light("Living Room");
    LightOnCommand *livingRoomLightOn = new LightOnCommand(livingRoomLight);
    LightOffCommand *livingRoomLightOff = new LightOffCommand(livingRoomLight);
    remoteControl->setCommand(0, livingRoomLightOn, livingRoomLightOff);

    Light *kitchenLight = new Light("Kitchen");
    LightOnCommand *kitchenLightOn = new LightOnCommand(kitchenLight);
    LightOffCommand *kitchenLightOff = new LightOffCommand(kitchenLight);
    remoteControl->setCommand(1, kitchenLightOn, kitchenLightOff);

    CeilingFan *ceilingFan = new CeilingFan("Dinning Room");
    CeilingFanOnCommand *ceilingFanOn = new CeilingFanOnCommand(ceilingFan);
    CeilingFanOffCommand *ceilingFanOff = new CeilingFanOffCommand(ceilingFan);
    remoteControl->setCommand(2, ceilingFanOn, ceilingFanOff);

    Stereo *stereo = new Stereo("Bath Room");
    StereoOnWithCDCommand *stereoOnWithCD = new StereoOnWithCDCommand(stereo);
    StereoOffCommand *stereoOff = new StereoOffCommand(stereo);
    remoteControl->setCommand(3, stereoOnWithCD, stereoOff);

    remoteControl->onButtonWasPushed(0);  // light living room on
    remoteControl->offButtonWasPushed(0); // light living room off

    cout << endl;

    remoteControl->onButtonWasPushed(1);  // light kitchen on
    remoteControl->offButtonWasPushed(1); // light kitchen off

    cout << endl;

    remoteControl->onButtonWasPushed(2);  // fan on
    remoteControl->offButtonWasPushed(2); // fan off

    cout << endl;

    remoteControl->onButtonWasPushed(3);  // stereo on
    remoteControl->offButtonWasPushed(3); // stereo off

    cout << endl;

    delete remoteControl;
    delete livingRoomLight;
    delete kitchenLight;
    delete ceilingFan;
    delete stereo;
    delete livingRoomLightOn;
    delete livingRoomLightOff;
    delete kitchenLightOn;
    delete kitchenLightOff;
    delete ceilingFanOn;
    delete ceilingFanOff;
    delete stereoOnWithCD;
    delete stereoOff;

    return 0;
}
