#include <iostream>

using namespace std;

class Light
{
public:
    void on()
    {
        cout << "Light is on" << endl;
    }
    void off()
    {
        cout << "Light is off" << endl;
    }
};

class GarageDoor
{
public:
    void up()
    {
        cout << "Garage door is up" << endl;
    }
    void down()
    {
        cout << "Garage door is down" << endl;
    }
    void stop()
    {
        cout << "Garage door is stop" << endl;
    }
    void lightOn()
    {
        cout << "Garage door is on" << endl;
    }
    void lightOff()
    {
        cout << "Garage door is off" << endl;
    }
};

class Command
{
public:
    virtual void execute() = 0;
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

class GarageDoorOpenCommand : public Command
{
private:
    GarageDoor *garageDoor;

public:
    GarageDoorOpenCommand(GarageDoor *garageDoor) : garageDoor(garageDoor) {}
    void execute() override
    {
        garageDoor->up();
    }
};

class SimpleRemoteControl
{
private:
    Command *slot;

public:
    SimpleRemoteControl() {}
    void setCommand(Command *command)
    {
        slot = command;
    }
    void buttonWasPressed()
    {
        slot->execute();
    }
};

int main()
{
    SimpleRemoteControl *remote = new SimpleRemoteControl();

    Light *light = new Light();
    LightOnCommand *lightOn = new LightOnCommand(light);

    GarageDoor *garageDoor = new GarageDoor();
    GarageDoorOpenCommand *garageOpen = new GarageDoorOpenCommand(garageDoor);

    remote->setCommand(lightOn);
    remote->buttonWasPressed();
    remote->setCommand(garageOpen);
    remote->buttonWasPressed();

    delete remote;
    delete light;
    delete garageDoor;
    delete lightOn;
    delete garageOpen;

    return 0;
}
