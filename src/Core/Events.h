//// Day String to Day code ///
// Non class fuction to convert string code [Sun,Mon,Tus,Wed,Thu,Fri,Sat] to [0,1,2,3,4,5,6] //
int daytoCode(std::string day)
{
    std::string Codes[7] = {"Sun", "Mon", "Tus", "Wed", "Thu", "Fri", "Sat"};

    for (int i = 0; i < 7; i++)
    {
        if (day.compare(Codes[i]) == 0)
            return i;
    }

    return 0;
}

//// Events Class ////
class SimEvents
{
    std::string Name;
    SimulationTime ArrivalTime, startTime, endTime, DepartureTime;

    std::string EventPlace;

public:
    void setName(std::string);
    std::string getName();

    void setStartTime(SimulationTime);
    SimulationTime getStartTime();
    void setEndTime(SimulationTime);
    SimulationTime getEndTime();

    void setStartMin(int);
    void setStartHour(int);
    void setEndHour(int);
    void setEndMin(int);

    void setLocation(std::string);
    std::string getLocation();

    void setArrivalTime(SimulationTime);
    void setArrivalTime(int);
    SimulationTime getArrivalTime();

    void setDepartureTime(SimulationTime);
    void setDepartureTime();
    SimulationTime getDepartureTime();

    int getStartMin();
    int getStartHour();
    int getEndHour();
    int getEndMin();

    bool checkforArrival(SimulationTime);
    bool checkforDeparture(SimulationTime);
    bool checkforDuring(SimulationTime);

    void ListoffDetails();

    bool operator<(const SimEvents &SE1)
    {
        bool result = false;
        if (ArrivalTime < SE1.ArrivalTime || (ArrivalTime == SE1.ArrivalTime && endTime > SE1.endTime))
            result = true;
        return result;
    }

    bool operator>(const SimEvents &SE1)
    {
        bool result = false;
        if (ArrivalTime > SE1.ArrivalTime || (ArrivalTime == SE1.ArrivalTime && endTime < SE1.endTime))
            result = true;
        return result;
    }

    SimEvents(void);
    SimEvents(std::string, SimulationTime, SimulationTime, std::string, int);
    SimEvents(std::string, int, int, int, int, std::string, int);
    SimEvents(std::string, std::string, std::string, std::string, int);
};
// -Class Functions
void SimEvents::setName(std::string input)
{
    Name = input;
}

std::string SimEvents::getName()
{
    return Name;
}

void SimEvents::setStartTime(SimulationTime input)
{
    startTime = input;
}

SimulationTime SimEvents::getStartTime()
{
    return startTime;
}

void SimEvents::setEndTime(SimulationTime input)
{
    endTime = input;
}

SimulationTime SimEvents::getEndTime()
{
    return endTime;
}

// set times
void SimEvents::setStartMin(int input)
{
    startTime.setMinute(input);
}

void SimEvents::setStartHour(int input)
{
    startTime.setHour(input);
}

void SimEvents::setEndMin(int input)
{
    endTime.setMinute(input);
}

void SimEvents::setEndHour(int input)
{
    endTime.setHour(input);
}

// get times
int SimEvents::getStartMin()
{
    return startTime.getMinute();
}

int SimEvents::getStartHour()
{
    return startTime.getHour();
}

int SimEvents::getEndMin()
{
    return endTime.getMinute();
}

int SimEvents::getEndHour()
{
    return endTime.getHour();
}

void SimEvents::setArrivalTime(SimulationTime input)
{
    ArrivalTime = input;
}

void SimEvents::setArrivalTime(int offset)
{
    int variance = rand()%5;
    ArrivalTime.setTime(startTime.getTime());
    if (offset >= 0)
        ArrivalTime.subMinute(offset+variance);
    else
        ArrivalTime.addMinute(-offset-variance);
}

SimulationTime SimEvents::getArrivalTime()
{
    return ArrivalTime;
}

void SimEvents::setDepartureTime(SimulationTime input)
{
    DepartureTime = input;
}

void SimEvents::setDepartureTime()
{
    int depOffset = rand()%10;
    DepartureTime = endTime;
    DepartureTime.addMinute(depOffset);
}

SimulationTime SimEvents::getDepartureTime(){
    return DepartureTime;
}

bool SimEvents::checkforArrival(SimulationTime input)
{
    return getArrivalTime() == input;
}

bool SimEvents::checkforDeparture(SimulationTime input)
{
    return getDepartureTime() == input;
}

bool SimEvents::checkforDuring(SimulationTime inputTime){
    bool result = false;
    if(ArrivalTime <= inputTime & endTime >= inputTime) result = true;
    return result;
}

void SimEvents::setLocation(std::string input)
{
    EventPlace = input;
}

std::string SimEvents::getLocation()
{
    return EventPlace;
}

void SimEvents::ListoffDetails()
{
    std::cout << "Listing off Detailes for Event: " << getName() << std::endl;
    std::cout << "Location: " << getLocation() << std::endl;
    // std::cout << "Day of the week: " << getstrDay() << std::endl;
    std::cout << "Arrival Time: " << getArrivalTime().getTime12str() << std::endl;
    std::cout << "Start Time: " << getStartTime().getTime12str() << std::endl;
    std::cout << "End Time: " << getEndTime().getTime12str() << std::endl;
    std::cout << "Departure Time: " << getDepartureTime().getTime12str() << std::endl;

    std::cout << "Listoff done!\n\n";
}

// - Class Constructors
SimEvents::SimEvents() {}

SimEvents::SimEvents(std::string inName, SimulationTime inStartTime, SimulationTime inEndTime, std::string location, int offset = 15)
{
    setName(inName);
    setStartTime(inStartTime);
    setEndTime(inEndTime);
    setArrivalTime(offset);
    setDepartureTime();
    setLocation(location);
}

SimEvents::SimEvents(std::string inName, int startHour, int startMin, int endHour, int endMin, std::string location, int offset = 15)
{
    SimulationTime tempStart(startHour, startMin);
    SimulationTime tempEnd(endHour, endMin);
    setName(inName);
    setStartTime(tempStart);
    setEndTime(tempEnd);
    setArrivalTime(offset);
    setDepartureTime();
    setLocation(location);
}

SimEvents::SimEvents(std::string inName, std::string inStartTime, std::string inEndTime, std::string location, int offset = 15)
{
    SimulationTime tempStart(inStartTime);
    SimulationTime tempEnd(inEndTime);
    setName(inName);
    setStartTime(tempStart);
    setEndTime(tempEnd);
    setArrivalTime(offset);
    setDepartureTime();
    setLocation(location);
}

//// Day Class ////
class DaySchedule
{
    std::vector<SimEvents> EventArray;

public:
    void addEvent(SimEvents);
    SimEvents getEvent(int);
    SimEvents getEvent_ArrivalTime(SimulationTime);
    SimEvents getEvent_DuringTime(SimulationTime);
    void sortSchedule();
    bool checkforArrival(SimulationTime);
    bool checkforDeparture(SimulationTime);
    bool checkforDuring(SimulationTime);
    bool checkforHoldOver(int, SimulationTime);
    bool checkforOverlap(SimulationTime);
    int nEvents();
    void listoff();
};
// - ClassFunctions
void DaySchedule::addEvent(SimEvents input)
{
    EventArray.push_back(input);
}

SimEvents DaySchedule::getEvent(int ID)
{
    return EventArray[ID];
}

SimEvents DaySchedule::getEvent_ArrivalTime(SimulationTime inputTime)
{
    SimEvents tempEvent;

    if (checkforArrival(inputTime))
    {
        for (int i = 0; i < nEvents(); i++)
        {
            if (getEvent(i).checkforArrival(inputTime)) tempEvent = getEvent(i);
        }
    }
    else  tempEvent.setName("_NONE_");

    return tempEvent;
}

SimEvents DaySchedule::getEvent_DuringTime(SimulationTime inputTime)
{
    SimEvents tempEvent;

    if (checkforDuring(inputTime))
    {
        for (int i = 0; i < nEvents(); i++)
        {
            if (getEvent(i).checkforDuring(inputTime)) tempEvent = getEvent(i);
        }
    }
    else  tempEvent.setName("_NONE_");

    return tempEvent;
}

void DaySchedule::sortSchedule()
{
    std::sort(EventArray.begin(), EventArray.end());
}

int DaySchedule::nEvents()
{
    return EventArray.size();
}

bool DaySchedule::checkforArrival(SimulationTime input)
{
    bool result = false;
    for (int i = 0; i < nEvents(); i++)
    {
        if (getEvent(i).checkforArrival(input))
            result = true;
    }
    return result;
}

bool DaySchedule::checkforDeparture(SimulationTime input)
{
    bool result = false;
    for (int i = 0; i < nEvents(); i++)
    {
        if (getEvent(i).checkforDeparture(input))
            result = true;
    }
    return result;
}

bool DaySchedule::checkforDuring(SimulationTime inputTime){
    bool result = false;
    for(int evnt=0; evnt<nEvents();evnt++){
        if(EventArray[evnt].checkforDuring(inputTime)) result = true;
    }
    return result;
}
 
bool DaySchedule::checkforHoldOver(int mlt, SimulationTime inputTime){
    bool result = false;
    for(int tm=0;tm<=mlt;tm++){
        if(checkforDuring(inputTime)){
            result = true;
            break;
        }
    }
    return result;
}

bool DaySchedule::checkforOverlap(SimulationTime inputTime){
    bool result = false;
        for(int evnt=0; evnt<nEvents()-1;evnt++){
            if(EventArray[evnt].checkforDeparture(inputTime)){
                if(EventArray[evnt].getDepartureTime() > EventArray[evnt+1].getArrivalTime()) result = true;
            }
        }
    return result;
}

void DaySchedule::listoff()
{
    for (int i = 0; i < nEvents(); i++)
    {
        EventArray[i].ListoffDetails();
    }
}

//// Week class ////
class WeekSchedule
{
    DaySchedule DayArray[7];

public:
    void addEvent(int, SimEvents);
    int nEvents(int);
    SimEvents getEvent(int, int);
    SimEvents getEvent_ArrivalTime(int,SimulationTime);
    DaySchedule getDay(int);
    bool checkforArrival(int, SimulationTime);
    bool checkforDeparture(int, SimulationTime);
    bool chechforDuring(int, SimulationTime);
    bool checkforHoldOver(int, int, SimulationTime);
    bool checkforOverLap(int, SimulationTime);
    void sort();
    void listOff();
};

// -Class functions
void WeekSchedule::addEvent(int Day, SimEvents input)
{
    DayArray[Day].addEvent(input);
}

SimEvents WeekSchedule::getEvent(int Day, int ID)
{
    return DayArray[Day].getEvent(ID);
}

SimEvents WeekSchedule::getEvent_ArrivalTime(int Day, SimulationTime inputTime){
   return DayArray[Day].getEvent_ArrivalTime(inputTime);
}

DaySchedule WeekSchedule::getDay(int Day)
{
    return DayArray[Day];
}

bool WeekSchedule::checkforArrival(int Day, SimulationTime input)
{
    return getDay(Day).checkforArrival(input);
}

bool WeekSchedule::checkforDeparture(int Day, SimulationTime input)
{
    return getDay(Day).checkforDeparture(input);
}

bool WeekSchedule::chechforDuring(int Day, SimulationTime inputTime){
    return getDay(Day).checkforDuring(inputTime);
}

bool WeekSchedule::checkforHoldOver(int Day, int mlt, SimulationTime inputTime){
    return DayArray[Day].checkforHoldOver(mlt,inputTime);
}

bool WeekSchedule::checkforOverLap(int Day, SimulationTime inputTime){
    return DayArray[Day].checkforOverlap(inputTime);
}

void WeekSchedule::sort()
{
    for (int i = 0; i < 7; i++)
    {
        DayArray[i].sortSchedule();
    }
}

void WeekSchedule::listOff()
{
    std::string dayNames[7] = {"Sunday: ", "Monday: ", "Tuesday: ", "Wednesday: ", "Thrusday: ", "Friday: ", "Saturday: "};
    for (int i = 0; i < 7; i++)
    {
        std::cout << dayNames[i] << "\n";
        DayArray[i].listoff();
    }
}

int WeekSchedule::nEvents(int Day)
{
    return DayArray[Day].nEvents();
}