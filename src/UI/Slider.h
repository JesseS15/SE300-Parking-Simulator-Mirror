//// Slider Class ////
class BarSlider{
    sf::Vector2i Pos , Range;
    int BallPos;
    float M_Scale;
    const float BallScale = .6;
    const float SliderScale = 1.4;
    const float SliderWidthFactor = 5.4;
    const int EndStop = 2500;
    const int CBox = 150;

    std::vector<int> Steps;

    bool ClickInput = false;
    bool Update = false;
    bool KeyLatch = false;
    int keyOverRide = 0;
    int OverRideThreshHold = 20;

    const std::string BallFilePath = "src/images/UI/Ball.png";
    const std::string SliderFilePath = "src/images/UI/Slider.png";

    std::string LowTag, HighTag;

    sf::Texture BallTex, SliderTex;
    sf::Sprite Ball, Slider;

    public:
    void setMScale(float);
    void setPos(sf::Vector2i);
    sf::Vector2i getPos();
    void setRange(sf::Vector2i);
    sf::Vector2i getRange();
    void MoveBall(sf::Vector2i);

    void setTags(std::string,std::string);
    void setTags(std::string[2]);
    std::string getLowTag();
    std::string getHighTag();

    int getClosestStep(int);

    void clickStatus(bool);
    void keyUnlatch();
    bool checkforUpdate();

    void stepUp();
    void stepDown();

    void setUpSprites();
    void Display();
    sf::Text DisplayTag(sf::Font,sf::Color,float, bool);

    int Output();
    

};

// - Class functions
void BarSlider::setMScale(float input){
    M_Scale = input;
}

void BarSlider::setPos(sf::Vector2i input){
    BallPos = (input.x - EndStop)*M_Scale; 
    Pos = input;
}

void BarSlider::setTags(std::string LowName,std::string HighName){
    HighTag = HighName;
    LowTag = LowName;
}

void BarSlider::setTags(std::string Tags[2]){
    setTags(Tags[0],Tags[1]);
}

std::string BarSlider::getHighTag(){
    return HighTag;
}

std::string BarSlider::getLowTag(){
    return LowTag;
}

sf::Vector2i BarSlider::getPos(){
    return Pos;
}

void BarSlider::clickStatus(bool input){
    ClickInput = input;
}

void BarSlider::setRange(sf::Vector2i input){
    Range = input;
    Steps.clear();
    int nSteps = input.y-input.x;
    int BarSize = 2*EndStop;
    int BarMin = Pos.x-EndStop;
    float StepSize = BarSize/(nSteps-1);
    //set the first step
    Steps.push_back(BarMin*Master_Scale);

    // set all of the mid steps
    for(int stp=1;stp<nSteps-1;stp++){
        Steps.push_back((BarMin+(stp*StepSize))*Master_Scale);
    }

    // Now set the final step
    Steps.push_back((Pos.x+EndStop)*Master_Scale);


}

sf::Vector2i BarSlider::getRange(){
    return Range;
}

void BarSlider::setUpSprites(){
    if(!BallTex.loadFromFile(BallFilePath)){
        std::cout << "Failed to load";
    }
    if(!SliderTex.loadFromFile(SliderFilePath)){
    std::cout << "Failed to load";
    }

    Ball.setTexture(BallTex);
    Ball.setOrigin(Ball.getGlobalBounds().width/2,Ball.getGlobalBounds().height/2);

    Slider.setTexture(SliderTex);
    Slider.setOrigin(Slider.getGlobalBounds().width/2,Slider.getGlobalBounds().height/2);

}

void BarSlider::Display(){
    Slider.setTexture(SliderTex);
    Slider.setScale(M_Scale*SliderWidthFactor,M_Scale*SliderScale);
    Slider.setPosition(static_cast<int>(Pos.x*M_Scale),static_cast<int>(Pos.y*M_Scale));

    //for ball testing purposes only
    Ball.setTexture(BallTex);
    Ball.setScale(M_Scale*BallScale,M_Scale*BallScale);
    Ball.setPosition(BallPos,Pos.y*M_Scale);

    spriteQue.push_back(Slider);
    spriteQue.push_back(Ball);
}

sf::Text BarSlider::DisplayTag(sf::Font inFont, sf::Color inColor, float MScale, bool High){
    sf::Text result;

    float TagScale = 2.7;
    sf::Vector2i TagOffset = {0,-200};
    sf::Vector2i TagPos;
    if(High) {
        result.setString(HighTag);
        TagPos.x = (Pos.x + EndStop + TagOffset.x)*MScale;
    }
    else{
        result.setString(LowTag);
        TagPos.x = (Pos.x - EndStop - TagOffset.x)*MScale;
    }
    result.setFont(inFont);
    result.setFillColor(sf::Color::White);
    TagPos.y = (Pos.y + TagOffset.y)*MScale;
    result.setOrigin(result.getGlobalBounds().width/2,result.getGlobalBounds().height/2);
    result.setPosition(TagPos.x,TagPos.y);
    result.setCharacterSize(100*MScale);
    result.setScale(MScale*TagScale,MScale*TagScale);
    return result;
}

void BarSlider::stepUp(){
    if(!KeyLatch || keyOverRide > OverRideThreshHold){
    int stp = getClosestStep(BallPos);
    stp++;
    BallPos = Steps[stp];
    KeyLatch = true;
    Update = true;
    }
    else{
        keyOverRide++;
    }
}

void BarSlider::stepDown(){
    if(!KeyLatch || keyOverRide > OverRideThreshHold){
    int stp = getClosestStep(BallPos);
    stp--;
    BallPos = Steps[stp];
    KeyLatch = true;
    Update = true;
    }
    else {
        keyOverRide++;
    }
}


int BarSlider::getClosestStep(int input){
    int result = 0;
    if(input >= Steps[Steps.size()-1]){
        result = Steps.size()-1;
    }
    else if(input > Steps[0]){
        for(int i=1;i<Steps.size();i++){
            if(input == Steps[i]){
                result = i;
                break;
            }
            if(input>Steps[i-1] && input<Steps[i]){
                if(input - Steps[i-1] < Steps[i]-input ){
                    result = i-1;
                    break;
                }
                else{
                    result = i;
                    break;
                }
            }
    }
    }
    return result;
}

bool BarSlider::checkforUpdate(){
    bool result = false;
    if(Update){
        Update = false;
        result = true;
    }
    return result;
}

void BarSlider::keyUnlatch(){
    keyOverRide = 0;
    KeyLatch = false;
}

void BarSlider::MoveBall(sf::Vector2i input){
    if(input.y <= (Pos.y*M_Scale)+CBox*M_Scale && input.y >= (Pos.y*M_Scale)-CBox*M_Scale){

       if(ClickInput){
           BallPos = input.x;
            Update = true;
       } 
       else{
        BallPos = Steps[getClosestStep(BallPos) ];
       }
    }
    
}

int BarSlider::Output(){

    return getClosestStep(BallPos);
}