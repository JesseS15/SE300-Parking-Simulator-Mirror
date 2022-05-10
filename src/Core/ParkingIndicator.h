//// Parking Indicator class ////
class parkingIndicator{

    std::string Name;
    sf::Texture EmptyTex, FilledTex;
    sf::Sprite EmptyDot, FilledDot;

    public:

    void setName(std::string);
    std::string getName();

    void setEmptyTexture(std::string);
    void setFilledTextrue(std::string);

    sf::Sprite getDot(int,int,float,bool);

    parkingIndicator(std::string,std::string,std::string);
    parkingIndicator(void);

};

// -Class functions
void parkingIndicator::setName(std::string input){
    Name = input;
}

std::string parkingIndicator::getName(){
    return Name;
}

void parkingIndicator::setEmptyTexture(std::string filePath){
    if (!EmptyTex.loadFromFile(filePath))
    {
        std::cout << "Error: File failed to load" << std::endl;
    }

    EmptyDot.setTexture(EmptyTex);
    EmptyDot.setOrigin(EmptyDot.getGlobalBounds().width/2,EmptyDot.getGlobalBounds().height/2);
}

void parkingIndicator::setFilledTextrue(std::string filePath){
    if (!FilledTex.loadFromFile(filePath))
    {
        std::cout << "Error: File failed to load" << std::endl;
    }

    FilledDot.setTexture(FilledTex);
    FilledDot.setOrigin(FilledDot.getGlobalBounds().width/2,FilledDot.getGlobalBounds().height/2);    
}

sf::Sprite parkingIndicator::getDot(int PosX, int PosY, float Scale, bool isFilled){
    sf::Sprite tempSprite;
    if(isFilled){
        FilledDot.setTexture(FilledTex);
        FilledDot.setScale(Scale/4,Scale/4);
        FilledDot.setPosition(PosX,PosY);
        tempSprite = FilledDot;
    }
    else{
        EmptyDot.setTexture(EmptyTex);
        EmptyDot.setScale(Scale/4,Scale/4);
        EmptyDot.setPosition(PosX,PosY);
        tempSprite = EmptyDot;       
    }

    return tempSprite;
}

parkingIndicator::parkingIndicator(){}
parkingIndicator::parkingIndicator(std::string Name, std::string emptyFilepath, std::string filledFilePath){
    setName(Name);
    setEmptyTexture(emptyFilepath);
    setFilledTextrue(filledFilePath);
}


//// indicator Container class////
class indicatorContainer{
    std::vector<parkingIndicator> DotTypes;

    public:
    parkingIndicator getIndicator(std::string);
    void importData(std::string);

    indicatorContainer(void);
    indicatorContainer(std::string);

};

// -Class functions
// Type Name | Empty file path | Filled filepath
parkingIndicator indicatorContainer::getIndicator(std::string Find){
    int Target = 0;

    for(int i=0;i<DotTypes.size();i++){
        if(DotTypes[i].getName().compare(Find) == 0){
            Target = i;
            break;
        }
    }

    return DotTypes[Target];
}

void indicatorContainer::importData(std::string filePath){
    std::vector<std::vector<std::string>> dotData = dataScraper(filePath);
    for(int i=0;i<dotData.size();i++){
        parkingIndicator tempInd(dotData[i][0],dotData[i][1],dotData[i][2]);
        DotTypes.push_back(tempInd);
    }
}

indicatorContainer::indicatorContainer(){};

indicatorContainer::indicatorContainer(std::string filePath){
    importData(filePath);
}