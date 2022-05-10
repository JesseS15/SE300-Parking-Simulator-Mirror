     const std::string strDay[7] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};

//// SImulation Time class
class SimulationTime
{
    int hour;
    int minute;

public:
    bool setHour(int);
    bool setMinute(int);
    bool setTime(int, int);
    bool setTime(sf::Vector2i);
    int getHour();
    int getMinute();
    sf::Vector2i getTime();

    std::string getTime24str();
    std::string getTime12str();

    bool addHour();
    bool addHour(int);
    bool addMinute();
    bool addMinute(int);

    bool subHour();
    bool subHour(int);
    bool subMinute();
    bool subMinute(int);

    SimulationTime(void);
    SimulationTime(int, int);
    SimulationTime(std::string);

    bool operator<(const SimulationTime &ST1)
    {
        bool result = false;
        if (hour < ST1.hour || (hour == ST1.hour && minute < ST1.minute)) result = true;
        return result;
    }

    bool operator == (const SimulationTime &ST1)
    {
        bool result = false;
        if (hour == ST1.hour && minute == ST1.minute) result = true;
        return result;
    }

    bool operator>(const SimulationTime &ST1)
    {
        bool result = false;
    if (hour > ST1.hour || (hour == ST1.hour && minute > ST1.minute)) result = true;
       return result;
    }

    bool operator<=(const SimulationTime &ST1)
    {
        bool result = false;
        if (hour < ST1.hour || (hour == ST1.hour && minute < ST1.minute)) result = true;
        if (hour == ST1.hour && minute == ST1.minute) result = true;
        return result;
    }

    bool operator>=(const SimulationTime &ST1)
    {
        bool result = false;
    if (hour > ST1.hour || (hour == ST1.hour && minute > ST1.minute)) result = true;
    if (hour == ST1.hour && minute == ST1.minute) result = true;
       return result;
    }
};
// -Class functions
bool SimulationTime::setHour(int inHour)
{
    bool result = false;
    if (inHour <= 23 & inHour >= 0)
    {
        hour = inHour;
        result = true;
    }
    return result;
}

bool SimulationTime::setMinute(int inMinute)
{
    bool result = false;
    if (inMinute <= 59 & inMinute >= 0)
    {
        minute = inMinute;
        result = true;
    }
    return result;
}

bool SimulationTime::setTime(int inHour, int inMinute)
{
    bool result = false;
    if (setHour(inHour) & setMinute(inMinute))
        result = true;
    return result;
}

bool SimulationTime::setTime(sf::Vector2i inTime)
{
    return setTime(inTime.x, inTime.y);
}

int SimulationTime::getHour()
{
    return hour;
}

int SimulationTime::getMinute()
{
    return minute;
}

sf::Vector2i SimulationTime::getTime()
{
    sf::Vector2i TempTime = {hour, minute};
    return TempTime;
}

std::string SimulationTime::getTime24str()
{
    std::string result;

    if(getHour() < 10) result.append("0"); 
    result.append(std::to_string(getHour()));
    result.append(":");
    if(getMinute() < 10) result.append("0");
    result.append(std::to_string(getMinute()));
    return result;
}

std::string SimulationTime::getTime12str()
{
    std::string result;
    std::string med = " AM";
    int tempHour = getHour();

    if (tempHour >= 12)
        med = " PM";
    if (tempHour > 12)
        tempHour -= 12;

    result.append(std::to_string(tempHour));
    result.append(":");
    result.append(std::to_string(getMinute()));
    result.append(med);
    return result;
}

// Add functions
bool SimulationTime::addHour(int inHour)
{
    bool result = true;
    int newHour = getHour() + inHour;
    if (!setHour(newHour))
        result = false;
    return result;
}

bool SimulationTime::addHour()
{
    return addHour(1);
}

bool SimulationTime::addMinute(int inMin)
{
    bool result = true;
    int newMinute = getMinute() + inMin;

    if (newMinute >= 60)
    {
        if (getHour() == 23)
            newMinute = getMinute();
        else
            newMinute -= 60;
        if (!addHour())
            result = false;
    }

    if (!setMinute(newMinute))
        result = false;
    return result;
}

bool SimulationTime::addMinute()
{
    return addMinute(1);
}

// Subtract Funtions
bool SimulationTime::subHour(int inHour)
{
    bool result = true;
    int newHour = getHour() - inHour;
    if (!setHour(newHour))
        result = false;
    return result;
}

bool SimulationTime::subHour()
{
    return subHour(1);
}

bool SimulationTime::subMinute(int inMin)
{
    bool result = true;
    int newMinute = getMinute() - inMin;

    if (newMinute <= -1)
    {
        if (getHour() == 0)
            newMinute = getMinute();
        newMinute += 60;
        if (!subHour())
            result = false;
    }

    if (!setMinute(newMinute))
        result = false;
    return result;
}

bool SimulationTime::subMinute()
{
    return subMinute(1);
}

//-Constructors
SimulationTime::SimulationTime() {}

SimulationTime::SimulationTime(int hour, int min)
{
    setTime(hour, min);
}

SimulationTime::SimulationTime(std::string input){
 
 setHour(stoi(input.substr(0,2)));
 setMinute(stoi(input.substr(3,2)));

}