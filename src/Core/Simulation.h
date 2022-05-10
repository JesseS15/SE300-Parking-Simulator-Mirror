////  Simulation Frame class ////
class SimFrame
{
    SimulationTime FrameTime;
    std::vector<simPerson> PersonArray;

public:
    void setFrameTime(SimulationTime);
    SimulationTime getFrameTime();
    void addPerson(simPerson);
    int getnPeople();
    simPerson getPerson(int);
    std::vector<simPerson> getPeople();
};

// -Class functions
void SimFrame::setFrameTime(SimulationTime inTime)
{
    FrameTime = inTime;
}

SimulationTime SimFrame::getFrameTime()
{
    return FrameTime;
}

void SimFrame::addPerson(simPerson inPerson){
    PersonArray.push_back(inPerson);
}

int SimFrame::getnPeople(){
    return PersonArray.size();
}

simPerson SimFrame::getPerson(int ID){
    return PersonArray[ID];
}

std::vector<simPerson> SimFrame::getPeople(){
    return PersonArray;
}


////  Simulation Class  ////
class SimController{
    int simDay;
    int curFrame;

    sf::Texture TimeBackgroundTex;
    sf::Sprite TimeBackGround;
    SimulationTime StartTime, EndTime;
    std::vector<SimFrame> FrameArray;
    PlaceContainer PlaceArray;
    lotContainer LotArray;
    PersonContainer PersonArray;

    std::vector<int> StartingCue;
    std::vector<int> ArrivalCue;
    std::vector<int> DepartureCue;
    std::vector<int> Backlog;

public:
    // Set up functions
    void setDay(int);
    int getDay();

    void setStartTime(SimulationTime);
    void setStartTime(std::string);

    void setCurFrame(SimulationTime);
    void setCurFrame(int);

    int getCurFrame();

    void setEndTime(SimulationTime);
    void setEndTime(std::string);

    SimulationTime getStartTime();
    SimulationTime getEndTime();

    void addPlace(Places);
    void addPlaces(PlaceContainer);

    void addLot(parkingLot);
    void addLots(lotContainer);

    void addPerson(Person);
    void addPeople(PersonContainer);

    // Simsulation functions
    void genArrivalCue(SimulationTime);
    void genStartCue(SimulationTime);
    void genDepartureCue(SimulationTime);
    void listoffArrivalCue();
    void lisfoffStartCue();

    lotContainer getLots();
    SimFrame getFrame(int);
    int getnFrames();
    std::vector<simPerson> getPeople();

    void DisplayFrameBackground(float);
    sf::Text DisplayWorkingMessage(sf::Font,float,int,int);
    sf::Text DisplayCurrentFrameTime(float, sf::Font);


    void Execute();


    SimController(void);   
};

// - Class functions
void SimController::setDay(int Day)
{
    simDay = Day;
}

int SimController::getDay()
{
    return simDay;
}

// Set up and control functions
void SimController::setStartTime(SimulationTime input)
{
    StartTime = input;
}

void SimController::setStartTime(std::string inTime)
{
    SimulationTime tempTime(inTime);
    StartTime = tempTime;
}

void SimController::setEndTime(SimulationTime input)
{
    EndTime = input;
}

void SimController::setEndTime(std::string inTime)
{
    SimulationTime tempTime(inTime);
    EndTime = tempTime;
}

SimulationTime SimController::getStartTime()
{
    return StartTime;
}

SimulationTime SimController::getEndTime()
{
    return EndTime;
}

void SimController::setCurFrame(SimulationTime input){
    int result = 0;
        for(int i=0;i<FrameArray.size();i++){
        if(FrameArray[i].getFrameTime() == input){
            result = i;
            break;
        }
    }
    curFrame = result;
}

void SimController::setCurFrame(int input){
    curFrame = input;
}


int SimController::getCurFrame(){
    return curFrame;
}

// Add Place Functions
void SimController::addPlace(Places input)
{
    PlaceArray.addPlace(input);
}

void SimController::addPlaces(PlaceContainer input)
{
    for (int i = 0; i < input.getnPlaces(); i++)
    {
        std::cout << "adding Place: " << i << " to the simulation\n";
        PlaceArray.addPlace(input.getPlace(i));
    }
    std::cout << "Done adding places\n\n";
}

// Add Lot functions
void SimController::addLot(parkingLot input)
{
    LotArray.addLot(input);
}

void SimController::addLots(lotContainer input)
{
    for (int i = 0; i < input.getnLots(); i++)
    {
        std::cout << "adding lot: " << i << " to the simulation\n";
        LotArray.addLot(input.getLot(i));
    }
    std::cout << "Done adding lots\n\n";
}

// Add people functions

void SimController::addPerson(Person input)
{
    PersonArray.addPerson(input);
}

void SimController::addPeople(PersonContainer input)
{
    for (int i = 0; i < input.getnPeople(); i++)
    {
        std::cout << "adding Person: " << i << " to the simulation\n";
        PersonArray.addPerson(input.getPerson(i));
    }
    std::cout << "Done adding people\n\n";
}

// Simualtion functions
void SimController::genArrivalCue(SimulationTime inputTime)
{
    ArrivalCue.clear();

    for (int i = 0; i < Backlog.size(); i++)
    {
        ArrivalCue.push_back(Backlog[i]);
    }

    Backlog.clear();

    for (int prsn = 0; prsn < PersonArray.getnPeople(); prsn++)
    {
        if (PersonArray.checkforArrival(prsn, simDay, inputTime))
        {
            ArrivalCue.push_back(prsn);
        }
    }
}

void SimController::listoffArrivalCue()
{
    std::cout << "Arrival Cue list off sarting: \n";
    for (int prsn = 0; prsn < ArrivalCue.size(); prsn++)
    {
        PersonArray.getPerson(ArrivalCue[prsn]);
    }
    std::cout << "Arrival Cue listoff done\n";
}

void SimController::genStartCue(SimulationTime inputTime)
{
    StartingCue.clear();
    for (int prsn = 0; prsn < PersonArray.getnPeople(); prsn++)
    {
        for (int evnt = 0; evnt < PersonArray.getPerson(prsn).getSch(simDay).nEvents(); evnt++)
        {
            SimEvents tempEvent = PersonArray.getPerson(prsn).getSch(simDay).getEvent(evnt);
            if (tempEvent.checkforDuring(inputTime))
                StartingCue.push_back(prsn);
        }
    }
}

void SimController::lisfoffStartCue()
{
    std::cout << "Start listoff sarting: \n";
    for (int prsn = 0; prsn < StartingCue.size(); prsn++)
    {
        PersonArray.getPerson(StartingCue[prsn]);
    }
    std::cout << "StartCue listoff done\n";
}

void SimController::genDepartureCue(SimulationTime inputTime)
{
    DepartureCue.clear();
    for (int prsn = 0; prsn < PersonArray.getnPeople(); prsn++)
    {
        if (PersonArray.checkforDepartrue(prsn, simDay, inputTime))
            DepartureCue.push_back(prsn);
    }
}

lotContainer SimController::getLots(){
    return LotArray;
}

int SimController::getnFrames(){
    return FrameArray.size();
}

/// Main Simulation function
void SimController::Execute()
{
    //Clear out the last simulation if there is one
    FrameArray.clear();

    bool SimFinish = false;
    SimulationTime currentTime = StartTime;
    // Set up working lot array
    lotContainer WorkingLots = LotArray;
    // Set up working population array
    PersonContainer workingPop = PersonArray;
    // Listing off PLaces
    std::cout << "Listing off places in the simulations: \n";
    //PlaceArray.listOff();

    // generate array of people who will already be parked when the simulation starts
    genStartCue(currentTime);

    //lisfoffStartCue();

    // Find a parking Spot for each person in the start cue
    for (int prsn = 0; prsn < StartingCue.size(); prsn++)
    {

        std::cout << "Placing starting que: " << prsn << "/" << StartingCue.size() << "\n";
        SimEvents workingEvent = workingPop.getPerson(StartingCue[prsn]).getSch(simDay).getEvent_DuringTime(currentTime);
        // get the target location from the working event
        Places TargetLocation = PlaceArray.getPlace(workingEvent.getLocation());

        //std::cout << "Target Location: X: " << TargetLocation.getPosX() << " Y: " << TargetLocation.getPosY() << "\n";

        // set the event location as the persons current locations
        workingPop.setCurrentLocation(StartingCue[prsn], TargetLocation.getName());

        //std::cout << "Pre sort list off: \n";
        // WorkingLots.listOffNames();

        WorkingLots.sortbyDist(TargetLocation.getPos());
        //std::cout << "Distance sorting complete\n\n";
        //WorkingLots.listOff();
        //std::cout << "Looking for the closest parking spot:\n";

        // Set the parking lot for the person
        Person TargetPerson = workingPop.getPerson(StartingCue[prsn]);
        workingPop.setParkingLocation(StartingCue[prsn], WorkingLots.findSpot(TargetPerson.getParkingPass(), TargetPerson.getName()));
       // std::cout << "Name: " << workingPop.getPerson(StartingCue[prsn]).getName() << " is parked at: " << workingPop.getPerson(StartingCue[prsn]).getParkingLocation().Name;
        //std::cout << "in Type: " << workingPop.getPerson(StartingCue[prsn]).getParkingLocation().type << " in spot: ";
        //std::cout << workingPop.getPerson(StartingCue[prsn]).getParkingLocation().spot << "\n";
        // WorkingLots.listOff();
    }

    // create initial frame

    SimFrame StartingFrame;

    StartingFrame.setFrameTime(currentTime);
    
    for(int prsn=0;prsn<workingPop.getnPeople();prsn++){
        simPerson tempPerson;
        tempPerson.setparkingLocation(workingPop.getPerson(prsn).getParkingLocation());
        tempPerson.setName(workingPop.getPerson(prsn).getName());
        tempPerson.setEventName(workingPop.getPerson(prsn).getSch(simDay).getEvent_DuringTime(currentTime).getName());
        StartingFrame.addPerson(tempPerson);
    }

    // Add starting frame to frame array
    FrameArray.push_back(StartingFrame);


    while (!SimFinish)
    {
        // add minute to start loop
        currentTime.addMinute();
        // Generate the departure cue
        genDepartureCue(currentTime);

        // For each person in the departure cue either leave the spot or stay on property //
        for (int prsn = 0; prsn < DepartureCue.size(); prsn++)
        {
            // check if the person will be staying on property or not
            if (workingPop.getPerson(DepartureCue[prsn]).getSch(simDay).checkforHoldOver(workingPop.getPerson(DepartureCue[prsn]).getMinleaveTime(), currentTime))
            {
                // If they are not leaving the property, just remove them from the POI and not the parking spot
                std::cout << workingPop.getPerson(DepartureCue[prsn]).getName() << "Is staying on campus\n";
                workingPop.setCurrentLocation(DepartureCue[prsn], "_NONE_");
                // Check if the person should go directly to the next event
                if (workingPop.getPerson(DepartureCue[prsn]).getSch(simDay).checkforOverlap(currentTime))
                    Backlog.push_back(DepartureCue[prsn]);
            }
            else
            {
                // If not remove them from the POI and the parking spot
                // Remove people from both the lot and the POI
                std::cout << workingPop.getPerson(DepartureCue[prsn]).getName() << " is leaving campus\n";
                WorkingLots.EmptySpot(workingPop.getPerson(DepartureCue[prsn]).getParkingLocation());
                workingPop.leaveParkingSpot(DepartureCue[prsn]);
                workingPop.setCurrentLocation(DepartureCue[prsn], "_NONE_");
            }
        }

        // starting with the arrivals
        //  Generate Arrival cue
        genArrivalCue(currentTime);

        for (int prsn = 0; prsn < ArrivalCue.size(); prsn++)
        {

            std::cout << "Working on arrival Cue person: " << prsn << "out of: " << ArrivalCue.size() << "\n";

            if (workingPop.getPerson(ArrivalCue[prsn]).getCurrentLocation().compare("_NONE_") == 0)
            {

                // get the target event and target location for each person
                SimEvents workingEvent = workingPop.getPerson(ArrivalCue[prsn]).getSch(simDay).getEvent_DuringTime(currentTime);
                // get the target location from the working event
                Places TargetLocation = PlaceArray.getPlace(workingEvent.getLocation());


                // Determine if the person is parked on campus or not
                if (workingPop.getPerson(ArrivalCue[prsn]).getParkingLocation().Name.compare("_NONE_") != 0)
                {

                    // If the person is already on campus just set their POI location
                    workingPop.setCurrentLocation(ArrivalCue[prsn], TargetLocation.getName());
                    std::cout << workingPop.getPerson(ArrivalCue[prsn]).getName() << " is staying on campus for event at: ";
                    std::cout << workingPop.getPerson(ArrivalCue[prsn]).getCurrentLocation() << "\n";
                }
                else
                {
                    // If the person is not already on campus find a place for them to park
                    WorkingLots.sortbyDist(TargetLocation.getPos());
                    workingPop.setCurrentLocation(ArrivalCue[prsn], TargetLocation.getName());

                    Person TargetPerson = workingPop.getPerson(ArrivalCue[prsn]);
                    // Attempt to park
                    workingPop.setParkingLocation(ArrivalCue[prsn], WorkingLots.findSpot(TargetPerson.getParkAttempt(), TargetPerson.getParkingPass(), TargetPerson.getName()));
                    TargetPerson = workingPop.getPerson(ArrivalCue[prsn]);

                    std::cout << TargetPerson.getName() << " is attempting to park\n";

                    // check if the parking attempt worked
                    if (workingPop.getPerson(ArrivalCue[prsn]).getParkingLocation().Name.compare("_NONE_") == 0)
                    {
                        // if it did not work add them to the backlog
                        Backlog.push_back(ArrivalCue[prsn]);
                        workingPop.addParkingAttempt(ArrivalCue[prsn]);
                        std::cout << "Attempted lot full, will try again\n";
                    }
                    else
                    {
                        workingPop.resetParkingAttempt(ArrivalCue[prsn]);
                        std::cout << "Parked at: " << TargetPerson.getParkingLocation().Name << "for event at: " << TargetPerson.getCurrentLocation() << "\n";
                    }
                }
            }
            else{
                std::cout << workingPop.getPerson(ArrivalCue[prsn]).getName() << " is currently in an event, but would like to arrive at next event\n";
            }
        }
        // Done with cues
        //  Generating frame for simulation
        SimFrame tempFrame;

        tempFrame.setFrameTime(currentTime);

        for(int prsn=0;prsn<workingPop.getnPeople();prsn++){
        simPerson tempPerson;
        tempPerson.setparkingLocation(workingPop.getPerson(prsn).getParkingLocation());
        tempPerson.setName(workingPop.getPerson(prsn).getName());
        tempPerson.setEventName(workingPop.getPerson(prsn).getSch(simDay).getEvent_DuringTime(currentTime).getName());
        tempFrame.addPerson(tempPerson);
    }

        FrameArray.push_back(tempFrame);

        std::cout << " *** End of Frame: " << currentTime.getTime12str() << std::endl;

        // exit loop condition checking
        if (currentTime == EndTime)
        {
            SimFinish = true;
        }
    }

    std::cout << FrameArray.size() << " created\n";
}

SimFrame SimController::getFrame(int input){
    return FrameArray[input];
}

std::vector<simPerson> SimController::getPeople(){
    return getFrame(curFrame).getPeople();
}

void SimController::DisplayFrameBackground(float M_Scale){
    sf::Vector2i TimePos = {4550,1150};
    TimeBackGround.setTexture(TimeBackgroundTex);
    TimeBackGround.setScale(M_Scale*1.2,M_Scale*1.2);
    TimeBackGround.setPosition(TimePos.x*M_Scale,TimePos.y*M_Scale);
    spriteQue.push_back(TimeBackGround);
}

sf::Text SimController::DisplayCurrentFrameTime(float M_Scale, sf::Font inFont){
    sf::Text FrameTimeTag;

    sf::Vector2i TimePos = {4400,1000};

    FrameTimeTag.setString(FrameArray[curFrame].getFrameTime().getTime24str());
    FrameTimeTag.setFont(inFont);
    FrameTimeTag.setCharacterSize(600);
    FrameTimeTag.setOrigin(FrameTimeTag.getLocalBounds().width/2,FrameTimeTag.getLocalBounds().height/2);
    FrameTimeTag.setLetterSpacing(5*M_Scale);
    FrameTimeTag.setScale(M_Scale,M_Scale);
    FrameTimeTag.setFillColor(sf::Color::Black);
    FrameTimeTag.setPosition(TimePos.x*M_Scale,TimePos.y*M_Scale);
    return FrameTimeTag;
}

sf::Text SimController::DisplayWorkingMessage(sf::Font inFont, float MScale, int Xpos, int Ypos){
    int BaseSize = 350;
    sf::Text tempText;

    tempText.setString("          Simulation running \n Check Terminal for progress");
    std::cout << "Sanity Check Sim Start\n";
    tempText.setFont(inFont);
    tempText.setCharacterSize(BaseSize);
    tempText.setOrigin(tempText.getGlobalBounds().width/2,tempText.getGlobalBounds().height/2);
    tempText.setFillColor(sf::Color::White);
    tempText.setScale(MScale,MScale);
    tempText.setPosition(Xpos*MScale,Ypos*MScale);
    return tempText;

}

// -Class constructors
SimController::SimController(){
    if(!TimeBackgroundTex.loadFromFile("src/images/UI/TimeBackground.png")){
        std::cout << "Failed to load Time Background\n";
    }
    TimeBackGround.setTexture(TimeBackgroundTex);
    TimeBackGround.setOrigin(TimeBackGround.getGlobalBounds().width/2,TimeBackGround.getGlobalBounds().height/2);
}