// requires #include <String> in main program
// requires the sfml library in main program
// requires #include <cmath> in main program

int getLowest(std::vector<int> input)
{
    sort(input.begin(), input.end());

    return input[0];
}

int getIDLowest(std::vector<int> input)
{
    int result = 0;
    std::vector<int> temp = input;

    sort(input.begin(), input.end());

    for (int i = 0; i < input.size(); i++)
    {
        if (temp[i] == input[0])
            result = i;
    }

    return result;
}

//// Places Class ////
class Places
{
    // Temp Hard Coded
    float PScale, DefaultScale, Scale;

    int nPlaces;
    int ID;
    std::string Name;
    sf::Vector2i Position;
    sf::Vector2i offSet;
    sf::Vector2i ClickBox;

    // Sprite for place shape
    sf::Texture Tex;
    sf::Sprite Shape;

public:
    void setID(int input);
    int getID();
    void setName(std::string input);
    std::string getName();
    void setPos(int, int);
    int getPosX();
    int getPosY();
    sf::Vector2i getPos();
    void setOffset(int, int);
    int getOffX();
    int getOffY();
    void setCBox(int, int);
    int getCBoxX();
    int getCBoxY();
    void setScale(float);
    float getScale();

    void setSprite(std::string filePath);
    sf::Sprite getSprite();

    double getDistTo(int TargetX, int TargetY);

    void loadData(std::vector<std::vector<std::string>>, int, float);

    bool isHovered(int, int);
    void onCLick();
};

// * Class Functions

// ID get and set functions
void Places::setID(int input)
{
    ID = input;
}
int Places::getID()
{
    return ID;
}

// Name get and set functions
void Places::setName(std::string input)
{
    Name = input;
}
std::string Places::getName()
{
    return Name;
}

// Pos get and set functions
void Places::setPos(int inX, int inY)
{
    Position = {inX, inY};
}
int Places::getPosX()
{
    float tempPos = static_cast<float>(Position.x) * PScale;
    return static_cast<int>(tempPos) + offSet.x;
}

int Places::getPosY()
{
    float tempPos = static_cast<float>(Position.y) * PScale;
    return static_cast<int>(tempPos) + offSet.y;
}

sf::Vector2i Places::getPos(){
    return {getPosX(),getPosY()};
}

// Get and

// Click Box functions
void Places::setCBox(int X, int Y)
{
    ClickBox = {X, Y};
}

int Places::getCBoxX()
{
    return static_cast<int>(static_cast<float>(ClickBox.x) * PScale);
}

int Places::getCBoxY()
{
    return static_cast<int>(static_cast<float>(ClickBox.y) * PScale);
}

void Places::setOffset(int inX, int inY)
{
    offSet = {inX, inY};
}

int Places::getOffX()
{
    return offSet.x;
}

int Places::getOffY()
{
    return offSet.y;
}

void Places::setScale(float input)
{
    Scale = PScale = DefaultScale = input;
}

float Places::getScale()
{
    return PScale;
}

// Set up the place shape Sprite
void Places::setSprite(std::string filePath)
{
    if (!Tex.loadFromFile(filePath))
    {
        std::cout << "Error: File for: " << Name << " Place failed to load" << std::endl;
    }
    Shape.setTexture(Tex);

    Shape.setOrigin(Shape.getGlobalBounds().width / 2, Shape.getGlobalBounds().height / 2);
    Shape.setScale(PScale, PScale);
    Shape.setPosition(getPosX(), getPosY());
}

sf::Sprite Places::getSprite()
{
    Shape.setTexture(Tex);
    Shape.setScale(Scale, Scale);
    Shape.setPosition(getPosX(), getPosY());
    Scale = DefaultScale;
    return Shape;
}

double Places::getDistTo(int TargetX, int TargetY)
{
    return sqrt(pow(TargetX - getPosX(), 2) + pow(TargetY - getPosY(), 2));
}

bool Places::isHovered(int inX, int inY)
{
    bool result = false;
    sf::Vector2i in = {inX,inY};
    if (mouseRangeCheck(in,getPosX(),getPosY(),getCBoxX(),getCBoxY(),1))
    {
        result = true;
        Scale = DefaultScale + 0.05;
        // std::cout << Name << std::endl;
    }
    else
    {
        Scale = DefaultScale;
    }
    return result;
}

// Data Loader
// Name | PosX | PosY | ClickBoxX | ClickBoxY | OutlineFilePath
void Places::loadData(std::vector<std::vector<std::string>> inputVector, int ID, float inScale)
{

    // Data Loaders
    setName(inputVector[ID][0]);
    setScale(inScale);
    setPos(stoi(inputVector[ID][1]), stoi(inputVector[ID][2]));
    setCBox(stoi(inputVector[ID][3]), stoi(inputVector[ID][4]));
    setSprite(inputVector[ID][5]);
}
// of place object

//// PlaceContainer ////
// Used to streamline the creation and reference of places in the array
class PlaceContainer
{
    std::vector<Places> PlaceArray;

public:
    PlaceContainer(std::string, float);
    PlaceContainer(std::string);
    PlaceContainer(void);

    void LoadData(std::string, float);
    void setPos(int, int, int);
    int getPosX(int ID);
    int getPosY(int ID);
    sf::Vector2i getPos();
    std::string getName(int ID);
    int nPlaces();
    int getID(int ID);
    int getDistTO(int ID, int TargX, int TargY);
    int getDistTO(int ID1, int ID2);
    void setScale(float);
    void setOffset(int, int);

    void addPlace(Places);
    Places getPlace(int);
    Places getPlace(std::string);

    int getnPlaces();

    sf::Sprite getSprite(int ID);

    void listOff();

    int getClosestDist(int, int);
    void CheckHover(int, int);
    bool CheckClick(int, int);
    bool CheckforName(std::string);
    void onClick(int);
    void drawOutlines();
};
//-----

// Place Container functions
// Name | PosX | PosY | ClickBoxX | ClickBoxY | OutlineFilePath
void PlaceContainer::LoadData(std::string fileName, float inScale)
{
    // Generate 2D array from data scraper
    std::vector<std::vector<std::string>> placeData = dataScraper(fileName);

    for (int i = 0; i < placeData.size(); i++)
    {
        Places newPlace;

        newPlace.setID(i);
        newPlace.loadData(placeData, i, inScale);
        PlaceArray.push_back(newPlace);
    }
}
// ID get and set functions
int PlaceContainer::getID(int ID)
{
    return PlaceArray[ID].getID();
}

// Name get functions
std::string PlaceContainer::getName(int ID)
{
    return PlaceArray[ID].getName();
}

// PosX get and set functions
void PlaceContainer::setPos(int inX, int inY, int ID)
{
    PlaceArray[ID].setPos(inX, inY);
}
int PlaceContainer::getPosX(int ID)
{
    return PlaceArray[ID].getPosX();
}

int PlaceContainer::getPosY(int ID)
{
    return PlaceArray[ID].getPosY();
}

// get the number of places
int PlaceContainer::nPlaces()
{
    return PlaceArray.size();
}

void PlaceContainer::setScale(float inScale)
{
    for (int i = 0; i < PlaceArray.size(); i++)
    {
        PlaceArray[i].setScale(inScale);
    }
}

void PlaceContainer::setOffset(int inX, int inY)
{
    for (int i = 0; i < PlaceArray.size(); i++)
    {
        PlaceArray[i].setOffset(inX, inY);
    }
}

// Get the sprite of the place
sf::Sprite PlaceContainer::getSprite(int ID)
{
    return PlaceArray[ID].getSprite();
}

// The two get distance to functions
int PlaceContainer::getDistTO(int ID, int TargX, int TargY)
{
    return sqrt(pow(TargX - PlaceArray[ID].getPosX(), 2) + pow(TargY - PlaceArray[ID].getPosY(), 2));
}

int PlaceContainer::getDistTO(int ID1, int ID2)
{
    return sqrt(pow(PlaceArray[ID2].getPosX() - PlaceArray[ID1].getPosX(), 2) + pow(PlaceArray[ID2].getPosY() - PlaceArray[ID1].getPosY(), 2));
}

int PlaceContainer::getClosestDist(int inX, int inY)
{
    std::vector<int> DistArray;

    for (int i = 0; i < PlaceArray.size(); i++)
    {
        DistArray.push_back(PlaceArray[i].getDistTo(inX, inY));
    }

    return getLowest(DistArray);
}

void PlaceContainer::CheckHover(int inX, int inY)
{
    std::vector<int> DistArray;

    for (int i = 0; i < PlaceArray.size(); i++)
    {
        DistArray.push_back(PlaceArray[i].getDistTo(inX, inY));
    }
    int closestID = getIDLowest(DistArray);
    PlaceArray[closestID].isHovered(inX, inY);
}

bool PlaceContainer::CheckClick(int inX, int inY)
{
    bool result = false;
    std::vector<int> DistArray;

    for (int i = 0; i < PlaceArray.size(); i++)
    {
        DistArray.push_back(PlaceArray[i].getDistTo(inX, inY));
    }
    int closestID = getIDLowest(DistArray);
    if (PlaceArray[closestID].isHovered(inX, inY))
    {
        onClick(closestID);
        result = true;
    }

    return result;
}

bool PlaceContainer::CheckforName(std::string lookFor)
{
    bool result = false;
    for (int i = 0; i < PlaceArray.size(); i++)
    {
        if (lookFor.compare(PlaceArray[i].getName()) == 0)
            result = true;
    }
    return result;
}

void PlaceContainer::onClick(int ID)
{
    std::cout << "Clicked " << PlaceArray[ID].getName() << "!!!\n";
}

int PlaceContainer::getnPlaces(){
    return PlaceArray.size();
}

// Fucntion to list off places
void PlaceContainer::listOff()
{
    for (int i = 0; i < PlaceArray.size(); i++)
    {
        std::cout << PlaceArray[i].getName() << ": ID#: " << PlaceArray[i].getID()
                  << " at position: " << PlaceArray[i].getPosX() << " X, " << PlaceArray[i].getPosY() << " Y\n";
    }
    std::cout << "List off done \n\n";
}
void PlaceContainer::drawOutlines()
{
    for (int i = 0; i < PlaceArray.size(); i++)
    {
        spriteQue.push_back(PlaceArray[i].getSprite());
    }
}

void PlaceContainer::addPlace(Places input){
    PlaceArray.push_back(input);
}

Places PlaceContainer::getPlace(int ID)
{
    return PlaceArray[ID];
}

Places PlaceContainer::getPlace(std::string find)
{
    Places tempPlace;
    if (CheckforName(find))
    {
        for (int i = 0; i < PlaceArray.size(); i++)
        {
            if (find.compare(PlaceArray[i].getName()) == 0) tempPlace = PlaceArray[i];
        }
    }
    else{
        tempPlace.setName("_NONE_");
    }
       return tempPlace;
}

// *Constructors
PlaceContainer::PlaceContainer(void){}

PlaceContainer::PlaceContainer(std::string LoaderFileName, float inScale)
{
    LoadData(LoaderFileName, inScale);
}

PlaceContainer::PlaceContainer(std::string LoaderFileName)
{
    LoadData(LoaderFileName, 0.6);
}