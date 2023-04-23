#include <iostream>
#include <vector>

using namespace std;

class Light
{
private:
    string location;
    int level;

public:
    Light(string location) : location(location) {}
    void on()
    {
        level = 100;
        cout << location << " light is on" << endl;
    }
    void off()
    {
        level = 0;
        cout << location << " light is off" << endl;
    }
    void dim(int level)
    {
        this->level = level;
        if (level == 0)
        {
            off();
        }
        else
        {
            cout << location << " light is dimmed to " << level << "%" << endl;
        }
    }
    int getLevel()
    {
        return level;
    }
};

class Stereo
{
private:
    string location;

public:
    Stereo(string location) : location(location){};
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

class Hottub
{
    bool on;
    int temperature;

public:
    Hottub()
    {
        on = false;
        temperature = 0;
    }
    void turnOn()
    {
        on = true;
    }
    void turnOff()
    {
        on = false;
    }
    void circulate()
    {
        if (on)
        {
            cout << "Hottub is bubbling!" << endl;
        }
    }
    void jetsOn()
    {
        if (on)
        {
            cout << "Hottub jets are on" << endl;
        }
    }
    void jetsOff()
    {
        if (on)
        {
            cout << "Hottub jets are off" << endl;
        }
    }
    void setTemperature(int temperature)
    {
        if (temperature > this->temperature)
        {
            cout << "Hottub is heating to a steaming " << temperature << " degrees" << endl;
        }
        else
        {
            cout << "Hottub is cooling to " << temperature << " degrees" << endl;
        }
        this->temperature = temperature;
    }
};

class TV
{
private:
    string location;

public:
    TV(string location) : location(location) {}
    void on()
    {
        cout << location << " TV is on" << endl;
    }
    void off()
    {
        cout << location << " TV is off" << endl;
    }
    void setInputChannel(int channel)
    {
        cout << location << " TV change to channel " << channel << endl;
    }
    void setVolume(int volume)
    {
        cout << location << " TV volume set to " << volume << endl;
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

class MacroCommand : public Command
{
private:
    vector<Command *> commands;

public:
    MacroCommand(vector<Command *> commands) : commands(commands) {}
    void execute() override
    {
        for (int i = 0; i < commands.size(); i++)
        {
            commands[i]->execute();
        }
    }
    void undo() override
    {
        for (int i = commands.size() - 1; i >= 0; i--)
        {
            commands[i]->undo();
        }
    }
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
    void undo()
    {
        stereo->off();
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
    void undo()
    {
        stereo->on();
        stereo->setCD();
        stereo->setVolume(11);
    }
};

class HottubOnCommand : public Command
{
private:
    Hottub *hottub;

public:
    HottubOnCommand(Hottub *hottub) : hottub(hottub) {}
    void execute() override
    {
        hottub->turnOn();
        hottub->setTemperature(104);
        hottub->circulate();
        hottub->jetsOn();
    }
    void undo() override
    {
        hottub->turnOff();
    }
};

class HottubOffCommand : public Command
{
private:
    Hottub *hottub;

public:
    HottubOffCommand(Hottub *hottub) : hottub(hottub) {}
    void execute() override
    {
        hottub->setTemperature(98);
        hottub->turnOff();
    }
    void undo() override
    {
        hottub->turnOn();
        hottub->setTemperature(104);
        hottub->circulate();
        hottub->jetsOn();
    }
};

class TVonCommand : public Command
{
private:
    TV *tv;

public:
    TVonCommand(TV *tv) : tv(tv) {}
    void execute() override
    {
        tv->on();
        tv->setInputChannel(16);
        tv->setVolume(100);
    }
    void undo() override
    {
        tv->off();
    }
};

class TVoffCommand : public Command
{
private:
    TV *tv;

public:
    TVoffCommand(TV *tv) : tv(tv) {}
    void execute() override
    {
        tv->off();
    }
    void undo() override
    {
        tv->on();
        tv->setInputChannel(16);
        tv->setVolume(100);
    }
};

class SuperRemote
{
    Command **onCommands;
    Command **offCommands;
    Command *undoCommand;

public:
    SuperRemote()
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
    SuperRemote *remoteControl = new SuperRemote();

    Light *light = new Light("Kitchen");
    LightOnCommand *lightOn = new LightOnCommand(light);
    LightOffCommand *lightOff = new LightOffCommand(light);

    Hottub *hotTub = new Hottub();
    HottubOnCommand *hotTubOn = new HottubOnCommand(hotTub);
    HottubOffCommand *hotTubOff = new HottubOffCommand(hotTub);

    Stereo *stereo = new Stereo("Bathroom");
    StereoOnWithCDCommand *stereoOnWithCD = new StereoOnWithCDCommand(stereo);
    StereoOffCommand *stereoOff = new StereoOffCommand(stereo);

    TV *tv = new TV("Living Room");
    TVonCommand *tvOn = new TVonCommand(tv);
    TVoffCommand *tvOff = new TVoffCommand(tv);

    vector<Command *> partyOnCommands = {lightOn, stereoOnWithCD, hotTubOn, tvOn};
    vector<Command *> partyOffCommands = {lightOff, stereoOff, hotTubOff, tvOff};

    Command *discoOn = new MacroCommand(partyOnCommands);
    Command *discoOff = new MacroCommand(partyOffCommands);

    remoteControl->setCommand(0, discoOn, discoOff);

    cout << remoteControl << endl;
    cout << "--- Pushing Party Mode On ---" << endl;
    remoteControl->onButtonWasPushed(0);
    cout << "\n--- Pushing Party Mode Off ---" << endl;
    remoteControl->offButtonWasPushed(0);

    cout << "\n--- Pushing Undo button ---" << endl;

    remoteControl->undoButtonWasPushed();

    delete remoteControl;

    delete light;
    delete lightOn;
    delete lightOff;

    delete hotTub;
    delete hotTubOn;
    delete hotTubOff;

    delete stereo;
    delete stereoOnWithCD;
    delete stereoOff;

    delete tv;
    delete tvOn;
    delete tvOff;

    delete discoOn;
    delete discoOff;

    return 0;
}