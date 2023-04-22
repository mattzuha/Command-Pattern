#include <iostream>

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
    virtual void undo() = 0;
};

class NoCommand : public Command
{
public:
    void execute() override {}
    void undo() override {}
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
    void undo() override
    {
        light->off();
    }
};

class LightOffCommand : public Command
{
private:
    Light *light;

public:
    LightOffCommand(Light *light) : light(light) {}
    void execute() override
    {
        light->off();
    }
    void undo() override
    {
        light->on();
    }
};

class CeilingFanHighCommand : public Command
{
private:
    CeilingFan *ceilingFan;
    int prevSpeed;

public:
    CeilingFanHighCommand(CeilingFan *ceilingFan) : ceilingFan(ceilingFan) {}
    void execute() override
    {
        prevSpeed = ceilingFan->getSpeed();
        ceilingFan->high();
    }
    void undo() override
    {
        if (prevSpeed == 3)
        {
            ceilingFan->high();
        }
        else if (prevSpeed == 2)
        {
            ceilingFan->medium();
        }
        else if (prevSpeed == 1)
        {
            ceilingFan->low();
        }
        else
        {
            ceilingFan->off();
        }
    }
};

class CeilingFanMediumCommand : public Command
{
private:
    CeilingFan *ceilingFan;
    int prevSpeed;

public:
    CeilingFanMediumCommand(CeilingFan *ceilingFan) : ceilingFan(ceilingFan) {}
    void execute() override
    {
        prevSpeed = ceilingFan->getSpeed();
        ceilingFan->medium();
    }
    void undo() override
    {
        if (prevSpeed == 3)
        {
            ceilingFan->high();
        }
        else if (prevSpeed == 2)
        {
            ceilingFan->medium();
        }
        else if (prevSpeed == 1)
        {
            ceilingFan->low();
        }
        else
        {
            ceilingFan->off();
        }
    }
};

class CeilingFanLowCommand : public Command
{
private:
    CeilingFan *ceilingFan;
    int prevSpeed;

public:
    CeilingFanLowCommand(CeilingFan *ceilingFan) : ceilingFan(ceilingFan) {}
    void execute() override
    {
        prevSpeed = ceilingFan->getSpeed();
        ceilingFan->low();
    }
    void undo() override
    {
        if (prevSpeed == 3)
        {
            ceilingFan->high();
        }
        else if (prevSpeed == 2)
        {
            ceilingFan->medium();
        }
        else if (prevSpeed == 1)
        {
            ceilingFan->low();
        }
        else
        {
            ceilingFan->off();
        }
    }
};

class CeilingFanOffCommand : public Command
{
private:
    CeilingFan *ceilingFan;
    int prevSpeed;

public:
    CeilingFanOffCommand(CeilingFan *ceilingFan) : ceilingFan(ceilingFan) {}
    void execute() override
    {
        prevSpeed = ceilingFan->getSpeed();
        ceilingFan->off();
    }
    void undo() override
    {
        if (prevSpeed == 3)
        {
            ceilingFan->high();
        }
        else if (prevSpeed == 2)
        {
            ceilingFan->medium();
        }
        else if (prevSpeed == 1)
        {
            ceilingFan->low();
        }
        else
        {
            ceilingFan->off();
        }
    }
};

class RemoteControlWithUndo
{
    Command **onCommands;
    Command **offCommands;
    Command *undoCommand;

public:
    RemoteControlWithUndo()
    {
        onCommands = new Command *[7];
        offCommands = new Command *[7];

        Command *noCommand = new NoCommand();
        for (int i = 0; i < 7; i++)
        {
            onCommands[i] = noCommand;
            offCommands[i] = noCommand;
        }
        undoCommand = noCommand;
    }
    void setCommand(int slot, Command *onCommand, Command *offCommand)
    {
        onCommands[slot] = onCommand;
        offCommands[slot] = offCommand;
    }
    void onButtonWasPushed(int slot)
    {
        onCommands[slot]->execute();
        undoCommand = onCommands[slot];
    }
    void offButtonWasPushed(int slot)
    {
        offCommands[slot]->execute();
        undoCommand = offCommands[slot];
    }
    void undoButtonWasPushed()
    {
        undoCommand->undo();
    }
};

int main()
{
    RemoteControlWithUndo *remoteControl = new RemoteControlWithUndo();

    Light *light = new Light("Kitchen");
    LightOnCommand *lightOn = new LightOnCommand(light);
    LightOffCommand *lightOff = new LightOffCommand(light);

    remoteControl->setCommand(0, lightOn, lightOff);

    remoteControl->onButtonWasPushed(0);
    remoteControl->offButtonWasPushed(0);
    remoteControl->undoButtonWasPushed();

    cout << endl;

    CeilingFan *cellingFan = new CeilingFan("Living Room");
    CeilingFanHighCommand *fanHig = new CeilingFanHighCommand(cellingFan);
    CeilingFanMediumCommand *fanMed = new CeilingFanMediumCommand(cellingFan);
    CeilingFanLowCommand *fanLow = new CeilingFanLowCommand(cellingFan);
    CeilingFanOffCommand *fanOff = new CeilingFanOffCommand(cellingFan);

    remoteControl->setCommand(1, fanHig, fanOff);
    remoteControl->setCommand(2, fanMed, fanOff);
    remoteControl->setCommand(3, fanLow, fanOff);

    remoteControl->onButtonWasPushed(3);  // fan on low
    remoteControl->offButtonWasPushed(3); // fan off low
    remoteControl->undoButtonWasPushed(); // fan on low

    remoteControl->onButtonWasPushed(1);  // fan on high
    remoteControl->onButtonWasPushed(2);  // fan on medium
    remoteControl->undoButtonWasPushed(); // fan on high

    delete remoteControl;

    delete light;
    delete lightOn;
    delete lightOff;

    delete cellingFan;
    delete fanHig;
    delete fanMed;
    delete fanLow;
    delete fanOff;

    return 0;
}
