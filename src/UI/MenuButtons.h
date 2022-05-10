class backButton : public Button{
    public:
    bool onClick(sf::Vector2i);
    backButton(std::string,std::string,int,int,int,int,float,float);
};

bool backButton::onClick(sf::Vector2i input){
    bool result = false;
    if(isHoveredEnlarge(input.x,input.y) && getClickStatus()){
        ClickUpate(false);
        result = true;
    }
    return result;
}

backButton::backButton(std::string Namein,std::string SpriteFilePath,int inXpos, int inYpos, int ClickX, int ClickY, float bScale, float cScale ){
    Build(Namein, SpriteFilePath, inXpos,inYpos,ClickX,ClickY,bScale,cScale);
}


class Run : public Button{
    public:
    bool onClick(sf::Vector2i);
    Run(std::string,std::string,std::string,int,int,int,int,float,float);
};

bool Run::onClick(sf::Vector2i input){
    bool result = false;
    if(isHoveredEnlarge(input.x,input.y) && getClickStatus()){
        ClickUpate(false);
        result = true;
    }
    return result;
}

Run::Run(std::string Namein,std::string SpriteFilePath,std::string HoverfilePath,int inXpos, int inYpos, int ClickX, int ClickY, float bScale, float cScale ){
    Build(Namein, SpriteFilePath, inXpos,inYpos,ClickX,ClickY,bScale,cScale);
    setHoverSprite(HoverfilePath);
}