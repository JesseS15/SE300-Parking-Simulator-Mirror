//// Time Selector clss ////
class TimeSelector{
    SimulationTime StartTime;
    SimulationTime EndTime;
     int DayOfWeek = 0;

    float BackgroundScale = 1.75;
    int TimeBaseHeight = 625;
    int DayBaseHeight = 325;
    sf::Vector2i TimeCBox = {300,250};
    sf::Vector2i DayCBox = {600,200};

    std::vector<std::vector<std::string>> Tags = {{"512","PS"},{"0","23"},{"0","59"},{"0","23"},{"0","59"},{"Sun","Sat"}};
    std::vector<sf::Vector2i> Ranges = {{0,2},{0,24},{0,60},{0,24},{0,60},{0,7}};

    bool Update = true;
    bool Clickinput = false;


    sf::Vector2i Pos;
    sf::Texture BackGroundTex;
    sf::Sprite Background;

    sf::Vector2i StartHourOffset = {-425,-600};
    sf::Vector2i StartMinuteOffset = {350, -600};
    sf::Vector2i EndHourOffset = {-425, 100};
    sf::Vector2i EndMinuteOffset = {350, 100};
    sf::Vector2i DayOffset = {0,725};


    int EditLevel = 0;

    sf::Color StartHourColor, StartMinuteColor, EndHourColor, EndMinuteColor, DayColor = sf::Color::Black;

    const std::string DayNames[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    public:

    void setPosition(int,int);
    SimulationTime getStartTime();
    SimulationTime getEndTime();
    int getDay();
    void DisplayBackGround(float);

    std::string getLowTag();
    std::string getHighTag();
    sf::Vector2i getRange();

    void getInput(int);

    int checkForHover(sf::Vector2i,float);
    bool checkForClick(sf::Vector2i,float);
    bool getStatus();
    bool CLickStatus(bool);

    bool isValid();

    sf::Text DisplayStartHour(sf::Font, float);
    sf::Text DisplStartMinute(sf::Font, float);
    sf::Text DisplayEndHour(sf::Font,float);
    sf::Text DisplayEndMinute(sf::Font,float);
    sf::Text DisplayDay(sf::Font,float);

    TimeSelector();

};
// -Class Functions
void TimeSelector::setPosition(int Xin, int Yin){
    Pos = {Xin,Yin};
}

SimulationTime TimeSelector::getStartTime(){
    return StartTime;
}

SimulationTime TimeSelector::getEndTime(){
    return EndTime;
}

int TimeSelector::getDay(){
    return DayOfWeek;
}

std::string TimeSelector::getLowTag(){
    return Tags[EditLevel][0];
}
std::string TimeSelector::getHighTag(){
    return Tags[EditLevel][1];
}

sf::Vector2i TimeSelector::getRange(){
    return Ranges[EditLevel];
}

void TimeSelector::DisplayBackGround(float MScale){
    Background.setTexture(BackGroundTex);
    Background.setScale(MScale*BackgroundScale,MScale*BackgroundScale);
    Background.setPosition(Pos.x*MScale,Pos.y*MScale);
    spriteQue.push_back(Background);
}

sf::Text TimeSelector::DisplayStartHour(sf::Font inFont, float MScale){
    sf::Text tempText;
    std::string TimeString;
    if(StartTime.getHour() < 10){
        TimeString.append("0");
    }
    TimeString.append(std::to_string(StartTime.getHour()));
    tempText.setFont(inFont);
    tempText.setString(TimeString);
    tempText.setFillColor(StartHourColor);
    tempText.setCharacterSize(TimeBaseHeight);
    tempText.setOrigin(tempText.getGlobalBounds().width/2,tempText.getGlobalBounds().height/2);
    tempText.setScale(MScale,MScale);
    tempText.setPosition((Pos.x+StartHourOffset.x)*MScale,(Pos.y+StartHourOffset.y)*MScale);
    return tempText;
}

sf::Text TimeSelector::DisplayEndHour(sf::Font inFont, float MScale){
    sf::Text tempText;
    std::string TimeString;
    if(EndTime.getHour() < 10){
        TimeString.append("0");
    }
    TimeString.append(std::to_string(EndTime.getHour()));
    tempText.setFont(inFont);
    tempText.setString(TimeString);
    tempText.setFillColor(EndHourColor);
    tempText.setCharacterSize(TimeBaseHeight);
    tempText.setOrigin(tempText.getGlobalBounds().width/2,tempText.getGlobalBounds().height/2);
    tempText.setScale(MScale,MScale);
    tempText.setPosition((Pos.x+EndHourOffset.x)*MScale,(Pos.y+EndHourOffset.y)*MScale);
    return tempText;
}

sf::Text TimeSelector::DisplStartMinute(sf::Font inFont, float MScale){
        sf::Text tempText;
    std::string TimeString;
    if(StartTime.getMinute() < 10){
        TimeString.append("0");
    }
    TimeString.append(std::to_string(StartTime.getMinute()));
    tempText.setFont(inFont);
    tempText.setString(TimeString);
    tempText.setFillColor(StartMinuteColor);
    tempText.setCharacterSize(TimeBaseHeight);
    tempText.setOrigin(tempText.getGlobalBounds().width/2,tempText.getGlobalBounds().height/2);
    tempText.setScale(MScale,MScale);
    tempText.setPosition((Pos.x+StartMinuteOffset.x)*MScale,(Pos.y+StartMinuteOffset.y)*MScale);
    return tempText;
}

sf::Text TimeSelector::DisplayEndMinute(sf::Font inFont, float MScale){
        sf::Text tempText;
    std::string TimeString;
    if(EndTime.getMinute() < 10){
        TimeString.append("0");
    }
    TimeString.append(std::to_string(EndTime.getMinute()));
    tempText.setFont(inFont);
    tempText.setString(TimeString);
    tempText.setFillColor(EndMinuteColor);
    tempText.setCharacterSize(TimeBaseHeight);
    tempText.setOrigin(tempText.getGlobalBounds().width/2,tempText.getGlobalBounds().height/2);
    tempText.setScale(MScale,MScale);
    tempText.setPosition((Pos.x+EndMinuteOffset.x)*MScale,(Pos.y+EndMinuteOffset.y)*MScale);
    return tempText;
}

sf::Text TimeSelector::DisplayDay(sf::Font inFont, float MScale){
     sf::Text tempText;
    tempText.setFont(inFont);
    tempText.setString(DayNames[DayOfWeek]);
    tempText.setFillColor(DayColor);
    tempText.setCharacterSize(DayBaseHeight);
    tempText.setOrigin(tempText.getGlobalBounds().width/2,tempText.getGlobalBounds().height/2);
    tempText.setScale(MScale,MScale);
    tempText.setPosition((Pos.x+DayOffset.x)*MScale,(Pos.y+DayOffset.y)*MScale);
    return tempText;
}

void TimeSelector::getInput(int input){
    switch(EditLevel){
        case 1:
        StartTime.setHour(input);
        break;
        case 2:
        StartTime.setMinute(input);
        break;
        case 3:
        EndTime.setHour(input);
        break;
        case 4:
        EndTime.setMinute(input);
        break;
        case 5:
        DayOfWeek = input;
        break;
    }
}

int TimeSelector::checkForHover(sf::Vector2i mouseIn, float MScale){
    // return 0 is there is no hover
    int result = 0;
    
    // Check for start Hour 
    if(mouseRangeCheck(mouseIn,Pos.x+StartHourOffset.x ,Pos.y+StartHourOffset.y+150,TimeCBox.x,TimeCBox.y,MScale)){ 
        StartHourColor = sf::Color::Cyan;
        result = 1;
    }
    else{
        if(EditLevel == 1){
            StartHourColor = sf::Color::Blue;
        }
        else{
        StartHourColor = sf::Color::Black;
        }
    }


    // Check for startMinute
    if(mouseRangeCheck(mouseIn,Pos.x+StartMinuteOffset.x ,Pos.y+StartMinuteOffset.y+150,TimeCBox.x,TimeCBox.y,MScale)){ 
        StartMinuteColor = sf::Color::Cyan;
        result = 2;
    }
    else{
        if(EditLevel == 2){
            StartMinuteColor = sf::Color::Blue;
        }
        else{
        StartMinuteColor = sf::Color::Black;
        }
    }

    // Check for End Hour
    if(mouseRangeCheck(mouseIn,Pos.x+EndHourOffset.x ,Pos.y+EndHourOffset.y+150,TimeCBox.x,TimeCBox.y,MScale)){ 
        EndHourColor = sf::Color::Cyan;
        result = 3;
    }
    else{
        if(EditLevel == 3){
            EndHourColor = sf::Color::Blue;
        }
        else{
        EndHourColor = sf::Color::Black;
        }
    }

    //Check for End Minute
    if(mouseRangeCheck(mouseIn,Pos.x+EndMinuteOffset.x ,Pos.y+EndMinuteOffset.y+150,TimeCBox.x,TimeCBox.y,MScale)){ 
        EndMinuteColor = sf::Color::Cyan;
        result = 4;
    }
    else{
        if(EditLevel == 4){
            EndMinuteColor = sf::Color::Blue;
        }
        else{
            EndMinuteColor = sf::Color::Black;
        }
    }

    // Check for Day of week
    if(mouseRangeCheck(mouseIn,Pos.x+DayOffset.x ,Pos.y+DayOffset.y+100,DayCBox.x,DayCBox.y,MScale)){ 
        DayColor = sf::Color::Cyan;
        result = 5;
    }
    else{
        if(EditLevel == 5){
            DayColor = sf::Color::Blue;
        }
        else{
            DayColor = sf::Color::Black;
        }
    }

    return result;

}

bool TimeSelector::checkForClick(sf::Vector2i mouseIn, float MScale){
    bool result = false;
    int selection = checkForHover(mouseIn,MScale);
    if(selection != 0 && Clickinput){
        Update = true;
        if(EditLevel == selection){
            EditLevel = 0;
        }
        else{
            EditLevel = selection;
        }
        Clickinput = false;
    }
    return result;
}

bool TimeSelector::getStatus(){
    bool result = Update;
    if(result == true ) Update = false;
    return result;
}

bool TimeSelector::CLickStatus(bool input){
    Clickinput = input;
    return input;
}

bool TimeSelector::isValid(){
    bool result = false;
    if(EndTime > StartTime) result = true;
    return result;
}

// - Constructors
TimeSelector::TimeSelector(){
    if(!BackGroundTex.loadFromFile("src/images/UI/TimeSelector.png")){
        std::cout << "Failed to open Timeselector background\n";
    }
    Background.setTexture(BackGroundTex);
    Background.setOrigin(Background.getGlobalBounds().width/2,Background.getGlobalBounds().height/2);
    StartTime.setTime(8,0);
    EndTime.setTime(18,0);
}