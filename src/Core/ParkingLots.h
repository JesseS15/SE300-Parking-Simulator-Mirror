//// Split Types function ////
// Non class function used to split a string of parking types into a vector of parking types split with a /
// used in both parking lot and people classes
std::vector<std::string> splitTypes(std::string input){
    std::vector<std::string> output;
    std::string word;
    std::stringstream toSplit(input);
    while(getline(toSplit, word,'/')){
        output.push_back(word);
    }
    return output;
}

//// Split Events function ////
// Non class function used to split a string of parking types into a vector of parking types split with a /
// used in both parking lot and people classes
std::vector<std::string> splitEvents(std::string input){
    std::vector<std::string> output;
    std::string word;
    std::stringstream toSplit(input);
    while(getline(toSplit, word,'|')){
        output.push_back(word);
    }
    return output;
}

//// Combine Types functions ////
// Non class function used to split a string of parking types into a vector of parking types split with a /
// used in both parking lot and people classes
std::string combineTypes(std::vector<std::string> input){
    std::string result;
    for(int i=0; i<input.size(); i++){
        result.append(input[i]);
        if(i<input.size()-1) result.append("/");
    }
    return result;
}

//// Parking ID class ////
class parkingID{
    public:
    int spot, type;
    std::string Name;
    parkingID(void);
};

parkingID::parkingID(void){
    Name = "_NONE_";
    spot = 0;
    type = 0;
}
 
//// class Sim Person ////
// Stripped out person class for saving sim data
class simPerson{
    std::string Name;
    parkingID parkingLocation;
    std::string currentEventName;

    public:
    void setName(std::string);
    std::string getName();
    void setparkingLocation(parkingID);
    parkingID getparkingLocation();
    void setEventName(std::string);
    std::string getEventName();
};

//// Parking Spot class  ////
class parkingSpot{
bool isTaken = false;
std::string parkingType;
sf::Vector2i Position;

std::string Occupent = "_NONE_";

int cbox = 50;

public:
void setType(std::string);
void setTypes(std::vector<std::string>);
void setOccupant(std::string);
std::string getOccupant();
std::string getType(int);
std::vector<std::string> getTypes();
void setPos(int,int);
int getX();
void setY(int);
int getY();

bool getStatus();

bool checkHover(sf::Vector2i,sf::Vector2i,float);

bool fill(std::string);
bool fill();
bool empty();

parkingSpot(std::string, int, int);
parkingSpot(std::vector<std::string>,int,int);
};
// - Class functions for Parking spot class
void parkingSpot::setType(std::string input){
    parkingType = input;
}

void parkingSpot::setTypes(std::vector<std::string> input){
    parkingType = combineTypes(input);
}

std::string parkingSpot::getType(int ID = 0){
    std::vector<std::string> tempTypes = splitTypes(parkingType);
    return tempTypes[ID];
}

std::vector<std::string> parkingSpot::getTypes(){
    std::vector<std::string> tempTypes = splitTypes(parkingType);
    return tempTypes;
}

void parkingSpot::setOccupant(std::string input){
    Occupent = input;
}

std::string parkingSpot::getOccupant(){
    return Occupent;
}

bool parkingSpot::checkHover(sf::Vector2i input,sf::Vector2i offSet, float MScale){
    bool result = false;
    if(mouseRangeCheck(input,Position.x*MScale+offSet.x,Position.y*MScale+offSet.y,cbox*MScale,cbox*MScale,1) && isTaken) result = true;
    return result;
}

void parkingSpot::setPos(int inX,int inY){
    Position = {inX,inY};
}

bool parkingSpot::getStatus(){
    return isTaken;
}

int parkingSpot::getX(){
    return Position.x;
}

int parkingSpot::getY(){
    return Position.y;
}

bool parkingSpot::fill(std::string input){
   // std::cout << input << " parked\n";
    bool result = false;
    if(fill()){
        result = true;
        setOccupant(input);
    }
    return result;
}

bool parkingSpot::fill(){
    bool fillCompleted = false;

    if(!isTaken) fillCompleted = isTaken = true;

    return fillCompleted;
}

bool parkingSpot::empty(){
    isTaken = false;
    Occupent = "_NONE_";
    return true;
}


// -Constructor
parkingSpot::parkingSpot(std::string inputType, int X, int Y){
    setType(inputType);
    setPos(X,Y);
}

parkingSpot::parkingSpot(std::vector<std::string> input,int X, int Y){
    setTypes(input);
    setPos(X,Y);

}



//// Parking type class  ////
class parkingType{
    std::string Type;
    int nTotalSpaces = 0;
    int nEmptySpaces =0;

    parkingIndicator Dots;


    // Vector for holding parking spots for each lot;
    std::vector<parkingSpot> Spots;

    public:
    void setType(std::string);
    void setType(std::vector<std::string>);
    std::string getType(int);
    std::string getType(void);
    bool findSpot();
    parkingID fillSpot(std::string);
    void fillSpace(parkingID, std::string);
    bool EmptySpot(int);
    std::vector<std::string> getTypes();
    int getEmptySpaces();
    int getTotalSpaces();
    int getArrayLength();
    void addSpot(std::string, int, int);
    int getnSpots();

    parkingSpot getSpot(int);

    void showSpots(float,sf::Vector2i);
    void setIndicator(parkingIndicator);

    int checkHover(sf::Vector2i,sf::Vector2i,float);

    void Clear();


    //Constructors
    parkingType(void);
    parkingType(std::string);


};
// - Class functions
void parkingType::setType(std::string inputName){

    // Move this to its own functions //
    Type = inputName;
}

void parkingType::setType(std::vector<std::string> inputTypes){
    std::string result;
    for(int i=0; i<inputTypes.size(); i++){
        result.append(inputTypes[i]);
        if(i<inputTypes.size()-1) result.append("/");
    }
}

std::string parkingType::getType(int ID){
    std::vector<std::string> tempvect = splitTypes(Type);
    return tempvect[ID];
}

std::string parkingType::getType(){
    return Type;
}

void parkingType::setIndicator(parkingIndicator input){
    Dots = input;
}

std::vector<std::string> parkingType::getTypes(){
    return splitTypes(Type);
}

int parkingType::getEmptySpaces(){
    return nEmptySpaces;
}

int parkingType::getTotalSpaces(){
    return nTotalSpaces;
}

bool parkingType::findSpot(){
    bool result = false;
    for(int spt=0;spt<getArrayLength();spt++){
        if(!Spots[spt].getStatus()){
            result = true;
            break;
        }
    }
    return result;
}

parkingSpot parkingType::getSpot(int spt){
    return Spots[spt];
}

int parkingType::checkHover(sf::Vector2i input, sf::Vector2i offSet, float MScale){
    // return -1 if no hover found
    int result = -1;
    for(int i=0;i<Spots.size();i++){
        if(Spots[i].checkHover(input,offSet,MScale)){
            result = i;
            break;
        }
    }
    return result;
}

parkingID parkingType::fillSpot(std::string inputName){
    parkingID tempID;
    for(int spt=0;spt<getArrayLength();spt++){
        if(Spots[spt].fill(inputName)){ 
            tempID.spot = spt;
            nEmptySpaces--;
            break;
        }
    }
    return tempID;
}

void parkingType::fillSpace(parkingID location, std::string Name){
    nEmptySpaces--;
    Spots[location.spot].fill(Name);
}

bool parkingType::EmptySpot(int Spot){
    nEmptySpaces++;
    return Spots[Spot].empty();
}

int parkingType::getArrayLength(){
    return Spots.size();
}

void parkingType::addSpot(std::string inputType, int PosX, int PosY){
    Spots.push_back(parkingSpot(inputType, PosX, PosY));
    nTotalSpaces++;
    nEmptySpaces++;

    }

    void parkingType::Clear(){
        for(int i=0;i<Spots.size();i++){
            EmptySpot(i);
        }
        nEmptySpaces = nTotalSpaces;
    }

void parkingType::showSpots(float inScale, sf::Vector2i offset){

    for(int spts=0;spts<getArrayLength();spts++){
        spriteQue.push_back(Dots.getDot(Spots[spts].getX()*inScale+offset.x,Spots[spts].getY()*inScale+offset.y,inScale,Spots[spts].getStatus()));     
    }
}

// -class constructors
parkingType::parkingType(std::string inputName){
    setType(inputName);
    nEmptySpaces = 0;
    nTotalSpaces = 0;
}


//// Parking lot class ////
class parkingLot : public Places{

       std::string PercentFull;
    
    int nTotalSpaces = 0;
    int nEmptySpaces = 0;

    std::vector<parkingSpot> Spots;
    std::vector <parkingType> Types;

    sf::Texture lotTex;
    sf::Sprite lotMap;
    float mapScale;

    public:

    int checkForType(std::string);
    int checkForType(std::vector<std::string>);
    void addNewType(std::string, indicatorContainer);
    void importData(std::string, indicatorContainer);
    void listOffTypes();
    parkingType getType(int);

    bool checkForSpaces(std::string);
    parkingID fillSpot(std::string, std::string);
    void fillSpace(parkingID,std::string);
    bool EmptySpot(int,int);

    parkingID checkHover(sf::Vector2i,sf::Vector2i,float);

    void setMapSprite( float, std::string);
    sf::Sprite getMapSprite(float, sf::Vector2i);

    void CalculatePercentFull();
    std::string getPercentFulle();

    void showSpots(float,sf::Vector2i);
    sf::Text showPerfull(sf::Font, sf::Color, float);

    void Clear();
    

    parkingLot(std::string);
    
};
// -Class fucntions

//void checking if the type exists or not
// returns -1 if type does not exist
int parkingLot::checkForType(std::string inputTypeName){
    int exists = -1;

    for(int i=0; i < Types.size(); i++){
        if( inputTypeName.compare(Types[i].getType()) == 0) {
            exists = i;
        }
    }
    return exists;
}

int parkingLot::checkForType(std::vector<std::string> inputTypes){
    int exists = -1;
    for(int i=0;i<inputTypes.size();i++){
        for(int j=0; j < Types.size(); j++){
            if( inputTypes[i].compare(Types[j].getType()) == 0) {
            exists = j;
            }
        }
    }

    return exists;
}

parkingID parkingLot::fillSpot(std::string Passes, std::string inputName){
    parkingID tempID;

        std::vector<std::string> tempPassTypes = splitTypes(Passes);

    int TypeTarget = -1;

     for(int i=0; i < Types.size(); i++){
         //std::cout << "Working on lotType: " << Types[i].getType() << std::endl; 
         std::vector<std::string> tempParkingType = Types[i].getTypes();
         for(int j=0; j<tempParkingType.size(); j++){
             //std::cout << "Working on Parking Type: " << tempParkingType[j] << std::endl; 
             for(int k=0; k<tempPassTypes.size();k++){
                //std::cout << "Working on Pass Type: " << tempPassTypes[k] << std::endl;
                 if(tempPassTypes[k].compare(tempParkingType[j]) == 0){
                     //std::cout << "Type matched\n";
                     if(Types[i].getEmptySpaces() > 0){
                         //std::cout << "Spot found\n";
                         TypeTarget = i;
                     }
                 }
             }   
         }
     }


     if(Types[TypeTarget].findSpot()) {
         tempID = Types[TypeTarget].fillSpot(inputName);
         tempID.type = TypeTarget;
         tempID.Name = getName();
         nEmptySpaces--;
     }
   
    return tempID;
}

parkingID parkingLot::checkHover(sf::Vector2i input, sf::Vector2i offSet, float MScale){
    parkingID result;
    for(int i=0;i<Types.size();i++){
        if(Types[i].checkHover(input,offSet,MScale) != -1){
            result.Name = "Found";
            result.spot = Types[i].checkHover(input,offSet,MScale);
            result.type = i;
            break;
        }
    }
    return result;
}

void parkingLot::fillSpace(parkingID location, std::string inputName){
    nEmptySpaces--;
    Types[location.type].fillSpace(location,inputName);
}

bool parkingLot::EmptySpot(int Type, int Spot){
    nEmptySpaces++;
     return Types[Type].EmptySpot(Spot);

}

void parkingLot::Clear(){
    nEmptySpaces = nTotalSpaces;
    for(int i=0;i<Types.size();i++){
        Types[i].Clear();
    }
}

parkingType parkingLot::getType(int typ){
    return Types[typ];
}

void parkingLot::addNewType(std::string typeName, indicatorContainer DotTypes){
    parkingType tempType(typeName);
    tempType.setIndicator(DotTypes.getIndicator(typeName));
    Types.push_back(tempType);
}

void parkingLot::listOffTypes(){
    std::cout << "Listing off Parking spot types for" << getName() << " : \n";
    for(int i = 0; i < Types.size(); i++){
        std::cout << "Type " << i << ": " << Types[i].getType();
        std::cout << " With " << Types[i].getEmptySpaces() <<" out of " << Types[i].getTotalSpaces() << " Spaces\n";
        std::cout << Types[i].getArrayLength() << std::endl;
    }

    std::cout << "Done\n\n";
}

// Import data for the parking spots in the lot
// Type | PosX | PosY
void parkingLot::importData(std::string filePath, indicatorContainer DotTypes){
    std::vector<std::vector<std::string>> lotData = dataScraper(filePath);

    int nSpots = lotData.size();

    for(int i = 0; i < nSpots; i++){
        if(checkForType(lotData[i][0]) == -1){
            addNewType(lotData[i][0],DotTypes);
        }

        int typeNumber = (checkForType(lotData[i][0]));

        std::string newSpotType = lotData[i][0];
        int newXPos = std::stoi(lotData[i][1]);
        int newYPos = std::stoi(lotData[i][2]);

        nTotalSpaces++;
        nEmptySpaces++;

        Types[typeNumber].addSpot(newSpotType, newXPos, newYPos);
    }
    
 }

 //Function to check for spaces
 bool parkingLot::checkForSpaces(std::string Pass){
     std::vector<std::string> tempPassTypes = splitTypes(Pass);
        // std::cout << "Staring to check for a space with types: ";
        // for(int l=0; l<tempPassTypes.size();l++){
        //     std::cout << tempPassTypes[l] << std::endl;
        // }


     for(int i=0; i < Types.size(); i++){
         //std::cout << "Working on lotType: " << Types[i].getType() << std::endl; 
         std::vector<std::string> tempParkingType = Types[i].getTypes();
         for(int j=0; j<tempParkingType.size(); j++){
             //std::cout << "Working on Parking Type: " << tempParkingType[j] << std::endl; 
             for(int k=0; k<tempPassTypes.size();k++){
                //std::cout << "Working on Pass Type: " << tempPassTypes[k] << std::endl;
                 if(tempPassTypes[k].compare(tempParkingType[j]) == 0){
                     //std::cout << "Type matched\n";
                     if(Types[i].getEmptySpaces() > 0){
                         //std::cout << "Spot found\n";
                         return true;
                     }
                 }
             }   
         }
     }
     return false;
 }

 void parkingLot::setMapSprite(float inScale, std::string filePath){
     mapScale = inScale;
    if (!lotTex.loadFromFile(filePath))
    {
        std::cout << "Error: File for: " << getName() << " Place failed to load" << std::endl;
    }
    lotMap.setTexture(lotTex);
 }

sf::Sprite parkingLot::getMapSprite(float masterScale, sf::Vector2i inPos){
    lotMap.setTexture(lotTex);
    lotMap.setScale(mapScale*masterScale,mapScale*masterScale);
    lotMap.setPosition(inPos.x,inPos.y);
    return lotMap;
}

void parkingLot::showSpots(float inScale,sf::Vector2i offset){
    for(int tps=0;tps<Types.size();tps++){
        Types[tps].showSpots(inScale,offset);
    }



}

void parkingLot::CalculatePercentFull(){
    int FilledSpaces = nTotalSpaces - nEmptySpaces;
    float filldec = static_cast<float>(FilledSpaces)/static_cast<float>(nTotalSpaces);
    int fillPercent = filldec*100;
    PercentFull = std::to_string(fillPercent);
    PercentFull.append("%");
}

std::string parkingLot::getPercentFulle(){
    return PercentFull;
}

sf::Text parkingLot::showPerfull(sf::Font inFont, sf::Color inColor, float MScale){
    int BaseSize = 100;

    sf::Text tempText;
    tempText.setFont(inFont);
    tempText.setFillColor(inColor);
    tempText.setString(PercentFull);
    tempText.setCharacterSize(BaseSize);
    tempText.setOrigin(tempText.getGlobalBounds().width/2,tempText.getGlobalBounds().height/2);
    tempText.setScale(MScale,MScale);
    tempText.setPosition(getPosX(),getPosY());
    return tempText;
}

 // - Constructor
 parkingLot::parkingLot(std::string inputName){
     setName(inputName);
 }



//// Lot Container Class ////
class lotContainer{
    std::vector<parkingLot> Lots;

    indicatorContainer Dots;

    int selectedLot = 0;

    public:
    void setIndicators(indicatorContainer);
    void generateLots(std::string, indicatorContainer);
    //lotContainer(std::string);

    void LoadData(std::string, float);
    void setPos(int, int, int);
    int getPosX(int ID);
    int getPosY(int ID);
    parkingLot getLot(int);
    parkingLot getLot(std::string);
    int getLotID(std::string);
    std::string getName(int ID);
    int nPlaces();
    int getID(int ID);
    int getDistTO(int ID, int TargX, int TargY);
    int getDistTO(int ID1, int ID2);
    void setScale(float);
    void setOffset(int,int);


    parkingID getSpotHoverID(sf::Vector2i,sf::Vector2i,float);
    bool checkSpotHover(sf::Vector2i,sf::Vector2i,float);
   
    sf::Sprite getSprite(int ID);

    void listOff();
    void listOffNames();
    void addLot(parkingLot);
    int getnLots();

    int getClosestDist(int,int);
    void CheckHover(int,int);
    bool CheckClick(int,int);
    void onClick(int);
    void drawOutlines();

    bool checkForSpaces(int, std::string);
    parkingID findSpot(int, std::string, std::string);
    parkingID findSpot(std::string, std::string);
    bool EmptySpot(std::string, int,int);
    bool EmptySpot(parkingID);

    void showMap(float,sf::Vector2i);
    sf::Text showTitle(float Scale, sf::Font, sf::Color, int, int, int);
    sf::Text showPerfull(int,sf::Font, sf::Color, float);

    sf::Text showOccupent(sf::Vector2i,sf::Font,parkingID,float);

    void Clear();

    void fillSpot(parkingID,std::string);
    void update(std::vector<simPerson>);

    // Simulation functions
    void sortbyDist(sf::Vector2i);

    lotContainer(void);

};
// -class functions
// Name | Posx | PosY | CboxX | CboxY | Outline FilePath | Data FilePath | Map FilePath | Map Scale
void lotContainer::generateLots(std::string filePath, indicatorContainer DotTypes){
    std::vector<std::vector<std::string>> lotData = dataScraper(filePath);

    setIndicators(DotTypes);

    for(int i = 0; i<lotData.size(); i++){
        parkingLot tempLot(lotData[i][0]);
        tempLot.setPos(stoi(lotData[i][1]),stoi(lotData[i][2]));
        tempLot.setCBox(stoi(lotData[i][3]),stoi(lotData[i][4]));
        tempLot.setSprite(lotData[i][5]);

        tempLot.importData(lotData[i][6],Dots);
        tempLot.setMapSprite(stof(lotData[i][8]),lotData[i][7]);

        Lots.push_back(tempLot);
    }

}

void lotContainer::setIndicators(indicatorContainer input){
    Dots = input;
}

void lotContainer::listOff(){
    for(int i = 0; i < Lots.size(); i++){
        Lots[i].listOffTypes();
    }
}

void lotContainer::listOffNames(){
    for(int i = 0; i < Lots.size(); i++){
        std::cout << Lots[i].getName() << "\n";
    }    
}

int lotContainer::getnLots(){
    return Lots.size();
}

int lotContainer::getID(int ID)
{
    return Lots[ID].getID();
}


// returns -1 if lot is not found
int lotContainer::getLotID(std::string name){
    int result = -1;
    for(int lt=0;lt<getnLots();lt++){
        if(name.compare(Lots[lt].getName()) ==0){
            result = lt;
            break;
        }
    }
    return result;
}

parkingLot lotContainer::getLot(int ID){
    return Lots[ID];
}

// Name get functions
std::string lotContainer::getName(int ID)
{
    return Lots[ID].getName();
}

// PosX get and set functions
void lotContainer::setPos(int inX, int inY, int ID)
{
    Lots[ID].setPos(inX,inY);
}
int lotContainer::getPosX(int ID)
{
    return Lots[ID].getPosX();
}

int lotContainer::getPosY(int ID)
{
    return Lots[ID].getPosY();
}

// get the number of places
int lotContainer::nPlaces()
{
    return Lots.size();
}

void lotContainer::addLot(parkingLot input){
    Lots.push_back(input);
}

void lotContainer::setScale(float inScale){
    for(int i = 0; i < Lots.size(); i++){
    Lots[i].setScale(inScale);
    }
}

void lotContainer::setOffset(int inX, int inY){
    for(int i = 0; i < Lots.size(); i++){
    Lots[i].setOffset(inX,inY);
    }
}

parkingID lotContainer::getSpotHoverID(sf::Vector2i input,sf::Vector2i offSet, float MScale){
    return  Lots[selectedLot].checkHover(input,offSet,MScale);
}

bool lotContainer::checkSpotHover(sf::Vector2i input, sf::Vector2i offSet,float MScale){
    bool result = false;
    parkingID tempID = getSpotHoverID(input,offSet, MScale);
    if(tempID.Name.compare("_NONE_") != 0 ){
        result = true;
    }
    return result;
}

sf::Text lotContainer::showOccupent(sf::Vector2i inPos,sf::Font inFont,parkingID input, float MScale){
    std::string OnName = Lots[selectedLot].getType(input.type).getSpot(input.spot).getOccupant();

    int BaseHeight = 80;

    sf::Text tempText;
    tempText.setString(OnName);
    tempText.setFont(inFont);
    tempText.setFillColor(sf::Color::White);
    tempText.setCharacterSize(BaseHeight);
    tempText.setScale(MScale,MScale);
    tempText.setOrigin(0,tempText.getLocalBounds().height+50*MScale);
    tempText.setPosition(inPos.x,inPos.y);
    return tempText;
}

// Get the sprite of the place
sf::Sprite lotContainer::getSprite(int ID)
{
    return Lots[ID].getSprite();
}

// The two get distance to functions
int lotContainer::getDistTO(int ID, int TargX, int TargY)
{
    return sqrt(pow(TargX - Lots[ID].getPosX(), 2) + pow(TargY - Lots[ID].getPosY(), 2));
}

int lotContainer::getDistTO(int ID1, int ID2)
{
    return sqrt(pow(Lots[ID2].getPosX() - Lots[ID1].getPosX(), 2) + pow(Lots[ID2].getPosY() - Lots[ID1].getPosY(), 2));
}

int lotContainer::getClosestDist(int inX, int inY)
{
    std::vector<int> DistArray;

    for (int i = 0; i < Lots.size(); i++)
    {
        DistArray.push_back(Lots[i].getDistTo(inX, inY));
    }

    return getLowest(DistArray);
}


void lotContainer::CheckHover(int inX, int inY){
 std::vector<int> DistArray;

    for(int i = 0; i < Lots.size(); i++){
        DistArray.push_back(Lots[i].getDistTo(inX,inY));
    }
    int closestID = getIDLowest(DistArray);
    Lots[closestID].isHovered(inX, inY);
}

bool lotContainer::CheckClick(int inX, int inY){
    bool result = false;
    std::vector<int> DistArray;

    for (int i = 0; i < Lots.size(); i++)
    {
        DistArray.push_back(Lots[i].getDistTo(inX, inY));
    }
    int closestID = getIDLowest(DistArray);
    if(Lots[closestID].isHovered(inX, inY)){
        onClick(closestID);
        result = true;
        }

    return result;
}


void lotContainer::onClick(int ID){
        std::cout << "Clicked Lot" << Lots[ID].getName() << "!!!\n";
        selectedLot = ID;
}


void lotContainer::drawOutlines(){
    for(int i = 0; i < Lots.size();i++){
        spriteQue.push_back(Lots[i].getSprite());
    }
}

void lotContainer::showMap(float masterScale, sf::Vector2i inPos){
    spriteQue.push_back(Lots[selectedLot].getMapSprite(masterScale,inPos));
    Lots[selectedLot].showSpots(masterScale,inPos);
}

sf::Text lotContainer::showTitle(float inScale, sf::Font inFont, sf::Color inColor, int PosX, int PosY, int Height){
    sf::Text tempText;
    tempText.setString(Lots[selectedLot].getName());
    tempText.setFont(inFont);
    tempText.setCharacterSize(static_cast<int>(Height*inScale));
    tempText.setOrigin(tempText.getGlobalBounds().width/2,tempText.getGlobalBounds().height/2);
    tempText.setPosition(static_cast<int>(PosX*inScale),static_cast<int>(PosY*inScale));

    return tempText;
}

sf::Text lotContainer::showPerfull(int Lot,sf::Font inFont, sf::Color inColor, float MScale){
    sf::Text tempText = Lots[Lot].showPerfull(inFont,inColor,MScale);

    return tempText;
}   

//Simulation Functions
bool lotContainer::checkForSpaces(int ID, std::string Type){
    return Lots[ID].checkForSpaces(Type);
}

parkingID lotContainer::findSpot(int ID, std::string Passes, std::string Name){
    parkingID TempID;
    TempID.Name = "_None_";
    TempID.type = 0;
    TempID.spot = 0;
    int validn=0;
    for(int lt=0; lt<getnLots();lt++){
        if(Lots[lt].checkForSpaces(Passes)) {
            if(validn == ID){
                TempID = Lots[lt].fillSpot(Passes, Name);
                break;
            }
            validn++;
        }
    }
    return TempID;
}

parkingID lotContainer::findSpot(std::string Passes, std::string Name){
    parkingID TempID;
    TempID.Name = "_None_";
    TempID.type = 0;
    TempID.spot = 0;
    for(int lt=0; lt<getnLots();lt++){
        if(Lots[lt].checkForSpaces(Passes)) {
                TempID = Lots[lt].fillSpot(Passes, Name);
                break;
        }
    }
    return TempID;
}
    
bool lotContainer::EmptySpot(std::string name, int Type, int Spot){
    bool result = false;
    int lotID = getLotID(name);
    if(lotID != -1){
        Lots[lotID].EmptySpot(Type,Spot);
        result = true;
    }

    return result;
}

bool lotContainer::EmptySpot(parkingID input){
    return EmptySpot(input.Name,input.type,input.spot);
}

void lotContainer::sortbyDist(sf::Vector2i pos){
    for(int i=0; i<getnLots()-1;i++){
        for(int j=0; j<getnLots()-i-1;j++){
            if(Lots[j].getDistTo(pos.x,pos.y) > Lots[j+1].getDistTo(pos.x,pos.y)){
                parkingLot swapLot = Lots[j];
                Lots[j] = Lots[j+1];
                Lots[j+1]= swapLot;
            }
        }
    }
}

void lotContainer::Clear(){
    for(int i=0;i<Lots.size();i++){
        Lots[i].Clear();
    }
}

void lotContainer::fillSpot(parkingID location, std::string Name){
    if(location.Name.compare("_NONE_") != 0) 
        Lots[getLotID(location.Name)].fillSpace(location,Name);
}

void lotContainer::update(std::vector<simPerson> input){
    Clear();
    for(int i=0;i<input.size();i++){
        fillSpot(input[i].getparkingLocation(),input[i].getName());
    }

    for(int j=0;j<Lots.size();j++){
        Lots[j].CalculatePercentFull();
    }
}

// -Constructors

lotContainer::lotContainer(){}