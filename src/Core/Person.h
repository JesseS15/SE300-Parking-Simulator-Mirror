//// Person Class ////
class Person{
    std::string Name;
    std::string ParkingPass;
    int timeOffset, minLeaveTime;
    // 0 = Sunday, 6 = saturnday
    //std::vector<SimEvents> Schedule[7];
    WeekSchedule Schedule;
    std::string currentLocation = "_NONE_"; 
    parkingID parkingLocation;

    int ParkAttempt = 0;


    public:
    void setName(std::string);
    std::string getName();
    void setPrefferedArrivalOffset(int);
    int getPrefferedArrivalOffset();
    void setMinLeaveTime(int);
    int getMinleaveTime();
    void addParkingPass(std::string);
    std::string getParkingPass();
    void setParkAttempt(int);
    int getParkAttempt();

    //Fuck my life

    void addEvent(int,SimEvents);
    void addSchedule(int,std::string);
    bool checkforArrival(int,SimulationTime);
    bool checkforDeparture(int,SimulationTime);
    void sortSchedule();



    DaySchedule getSch(int);
    
    void setOffsetTime(int);
    int getOffsetTime();
    void setCurrentLoaction(std::string);
    std::string getCurrentLocation();
    void setParkingLocation(parkingID);
    parkingID getParkingLocation();
    void leaveParkingSpot();

    void listOff();
    void listOffLocation();


    // Constructors
    Person(void);
    Person(std::string,int,int);

    
};

// - Class Functions
void Person::setName(std::string inName){
    Name = inName;
}

std::string Person::getName(){
    return Name;
}

// sets how early (or late) a person likes to arrive on location before the start of the event
// Example: if event starts at 12:00 and prefered arrival time is set to 15 the person will attempt to park at 11:45
void Person::setOffsetTime(int input){
    timeOffset = input;
}

// gets how early (or late) a person likes to arrive on location before the start of the event
// Example: if event starts at 12:00 and prefered arrival time is set to 15 the person will attempt to park at 11:45
int Person::getOffsetTime(){
    return timeOffset;
}

void Person::setCurrentLoaction(std::string inputLocation){
    currentLocation = inputLocation;
}

std::string Person::getCurrentLocation(){
    return currentLocation;
}

void Person::setParkingLocation(parkingID inputParking){
    parkingLocation = inputParking;
}

parkingID Person::getParkingLocation(){
    return parkingLocation;
}

void Person::leaveParkingSpot(){
    parkingID tempLocation;
    tempLocation.Name = "_NONE_";
    tempLocation.spot = 0;
    tempLocation.type = 0;

    parkingLocation = tempLocation;   
}

void Person::setParkAttempt(int input){
    ParkAttempt = input;
}

int Person::getParkAttempt(){
    return ParkAttempt;
}

//Sets Minimum time between two event for the person to leave and move their car
// Example if Event 1 ends at 13:00 and event 2 Arrival time is 13:15 the person will not leave if the value is set to 15 or less
void Person::setMinLeaveTime(int input){
    minLeaveTime = input;
}

int Person::getMinleaveTime(){
    return minLeaveTime;
}

void Person::addParkingPass(std::string inParkingPass){
    ParkingPass = inParkingPass;
}

std::string Person::getParkingPass(){
    return ParkingPass;
}

void Person::addEvent(int day, SimEvents inEvent){
    Schedule.addEvent(day, inEvent);
}

void Person::sortSchedule(){
    Schedule.sort();
}

DaySchedule Person::getSch(int Day){
    return Schedule.getDay(Day);
}

bool Person::checkforArrival(int Day, SimulationTime inputTime){
    return Schedule.checkforArrival(Day, inputTime);
}

bool Person::checkforDeparture(int Day, SimulationTime inputTime){
    return Schedule.checkforDeparture(Day, inputTime);
}

void Person::listOff(){
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Prefers to arrive " << getOffsetTime() << " before events\n";
    std::cout << "Will leave if there are  " << getMinleaveTime() << " minutes between events\n";
    std::cout << "With Parking Passes: \n";

    std::vector<std::string> tempPasses = splitTypes(getParkingPass());
    for(int j=0;j<tempPasses.size();j++){
            std::cout << "(" << j << ") " << tempPasses[j] << std::endl;
    }
        std::cout << "\nStarting Event list off: \n";

        Schedule.listOff();
}

void Person::listOffLocation(){
    std::cout << "Name: " << getName() << "\n";
    std::cout << "Lot: " << parkingLocation.Name << "\n";
    std::cout << "Type: " << parkingLocation.type << "\n";
    std::cout << "Spot: " << parkingLocation.spot << "\n";
}

void Person::addSchedule(int Day, std::string Data){

    std::vector<std::string> Eventsin = splitEvents(Data);

    for(int Evnt=0;Evnt<Eventsin.size();Evnt++){
        std::vector<std::string> EventDetails = splitTypes(Eventsin[Evnt]);
        SimEvents tempEvent(EventDetails[0],EventDetails[1],EventDetails[2],EventDetails[3],getOffsetTime());
        addEvent(Day,tempEvent);
    }


}

// - CLass Constructors
Person::Person(){}

Person::Person(std::string inName,int Offset,int minLeave){
    setName(inName);
    setOffsetTime(Offset);
    setMinLeaveTime(minLeave);

}

// -class functions
void simPerson::setName(std::string input){
    Name = input;
}

std::string simPerson::getName(){
    return Name;
}

void simPerson::setparkingLocation(parkingID input){
    parkingLocation = input;
}

parkingID simPerson::getparkingLocation(){
    return parkingLocation;
}

void simPerson::setEventName(std::string input){
    currentEventName = input;
}

std::string simPerson::getEventName(){
    return currentEventName;
}


//// Person container ////
class PersonContainer{
    std::vector<Person> PeopleArray;
    std::vector<PlaceContainer> alllocations;

    public:
    void addLocations(PlaceContainer);
    int getnPeople();
    bool checkforArrival(int,int,SimulationTime);
    bool checkforDepartrue(int,int,SimulationTime);
    void addPerson(Person);
    Person getPerson(int);
    void listOff();
    void listOffNames();

    void setCurrentLocation(int,std::string);
    std::string getCurrentLocation(int);
    void setParkingLocation(int,parkingID);
    parkingID getParkingLocation(int);
    void leaveParkingSpot(int);
    void addParkingAttempt(int);
    void resetParkingAttempt(int);

    void loadData(std::string);
    void testData(int, std::string);

    void Clear();
    void ShuffleOrder();

};
// - Class functions
Person PersonContainer::getPerson(int ID){
    return PeopleArray[ID];
}

void PersonContainer::addPerson(Person input){
    PeopleArray.push_back(input);
}

int PersonContainer::getnPeople(){
    return PeopleArray.size();
}

bool PersonContainer::checkforArrival(int ID, int Day, SimulationTime inputTime){
    return getPerson(ID).checkforArrival(Day,inputTime);
}

bool PersonContainer::checkforDepartrue(int ID, int Day, SimulationTime inputTime){
    return getPerson(ID).checkforDeparture(Day,inputTime);
}

void PersonContainer::addLocations(PlaceContainer inLocation){
    alllocations.push_back(inLocation);

}

void PersonContainer::listOff(){
    std::cout << "Listing off People: \n";
    for(int i = 0; i<PeopleArray.size();i++){
        PeopleArray[i].listOff();
    }
    std::cout << "People isting off done \n\n";
}

void PersonContainer::listOffNames(){
    std::cout << "Listing off names: \n";
    for(int i = 0; i<PeopleArray.size();i++){
        std::cout << PeopleArray[i].getName() << "\n";
    }
    std::cout << "People isting off done \n\n";    
}

void PersonContainer::setCurrentLocation(int ID, std::string inputLocation){
    PeopleArray[ID].setCurrentLoaction(inputLocation);
}

void PersonContainer::addParkingAttempt(int ID){
    int ParkingAttempets = PeopleArray[ID].getParkAttempt();
    ParkingAttempets++;
    PeopleArray[ID].setParkAttempt(ParkingAttempets);
}

void PersonContainer::resetParkingAttempt(int ID){
    PeopleArray[ID].setParkAttempt(0);
}

std::string PersonContainer::getCurrentLocation(int ID){
    return PeopleArray[ID].getCurrentLocation();
}

void PersonContainer::setParkingLocation(int ID, parkingID inputLocation){
    PeopleArray[ID].setParkingLocation(inputLocation);
}

parkingID PersonContainer::getParkingLocation(int ID){
    return PeopleArray[ID].getParkingLocation();
}

void PersonContainer::leaveParkingSpot(int prsn){
    PeopleArray[prsn].leaveParkingSpot();
}

void PersonContainer::Clear(){
    PeopleArray.clear();
}

void PersonContainer::ShuffleOrder(){
    //std::_Random_shuffle1(PeopleArray.begin(),PeopleArray.end());
}

// -Class Constructors;
void PersonContainer::loadData(std::string filePath){
    std::vector<std::vector<std::string>> importedData = dataScraper(filePath);

    for(int prsn = 1; prsn<importedData.size();prsn++){
        Person tempPerson(importedData[prsn][0],stoi(importedData[prsn][1]),stoi(importedData[prsn][2]));
        tempPerson.addParkingPass(importedData[prsn][3]);

        for(int Day = 0;Day<6;Day++){
            tempPerson.addSchedule(Day,importedData[prsn][4+Day]);
        }

        tempPerson.sortSchedule();

        PeopleArray.push_back(tempPerson);
    }

}

void PersonContainer::testData(int nPeople, std::string filePath){
    std::vector<std::vector<std::string>> importedData = dataScraper(filePath);

    for(int prsn = 1; prsn<nPeople;prsn++){
        std::cout << "Generating Person: " << prsn << "\n";
        Person tempPerson(importedData[1][0],stoi(importedData[1][1]),stoi(importedData[1][2]));
        tempPerson.addParkingPass(importedData[1][3]);

        for(int Day = 0;Day<6;Day++){
            tempPerson.addSchedule(Day,importedData[1][4+Day]);
        }

        PeopleArray.push_back(tempPerson);
    }

}