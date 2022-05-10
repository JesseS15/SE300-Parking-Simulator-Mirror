class Button{
std::string Name;
sf::Vector2i Position, CBox;
sf::Texture ButTex, HoverTex;
bool CLickInput = false;
sf::Sprite ButSprite;
float Scale, BaseScale, ScaleChange;
bool useHoverSprite = false;

public:
void setName(std::string);
std::string getName();
void setPos(int,int);
int getPosX();
int getPosY();
void setCBox(int,int);
void setSprite(std::string);
void setHoverSprite(std::string);
sf::Sprite getSprite();
void setScales(float,float);
float getCurrentScale();
float getBaseScale();
float getScaleChange();

bool isHovered(int,int);
bool isHovered(sf::Vector2i);
bool isHoveredEnlarge(int, int);
bool isHoveredSmaller(int, int);
bool isHoveredSprite(int,int);

void ClickUpate(bool);
bool getClickStatus();

Button(void);
void Build(std::string,std::string,int, int, int, int, float, float);
void Build(std::string,std::string,int, int, int, int, float, float,std::string);
Button(std::string,std::string,int, int, int, int, float, float);
Button(std::string,std::string,int, int, int, int, float, float, std::string);


};

// - Button Class Functions
void Button::setName(std::string inName){
    Name = inName;
}

std::string Button::getName(){
    return Name;
}

void Button::setPos(int Xin, int Yin){
    Position = {Xin,Yin};
}

int Button::getPosX(){
    return Position.x;
}

int Button::getPosY(){
    return Position.y;
}

void Button::setCBox(int inX, int inY){
    CBox = {inX, inY};
}

void Button::setSprite(std::string filePath){
    if (!ButTex.loadFromFile(filePath))
    {
        std::cout << "Button " << Name <<": main image failed to load" << std::endl;
    }
    ButSprite.setTexture(ButTex);
    ButSprite.setOrigin(ButSprite.getGlobalBounds().width / 2, ButSprite.getGlobalBounds().height / 2);
}

void Button::setHoverSprite(std::string filePath){
    if (!HoverTex.loadFromFile(filePath))
    {
        std::cout << "Button " << Name <<": Hover image failed to load" << std::endl;
    }
}

sf::Sprite Button::getSprite(){
    if(useHoverSprite){
        ButSprite.setTexture(HoverTex);
    }
    else{
        ButSprite.setTexture(ButTex);
    }

    ButSprite.setScale(Scale,Scale);
    ButSprite.setPosition(Position.x, Position.y);

    return ButSprite;
}

void Button::setScales(float BaseIn, float ChangeIn){
    Scale = BaseScale = BaseIn;
    ScaleChange = ChangeIn;
}

float Button::getCurrentScale(){
    return Scale;
}

float Button::getBaseScale(){
    return BaseScale;
}

float Button::getScaleChange(){
    return ScaleChange;
}

// Hovered functions
bool Button::isHovered(int inX, int inY){
    bool result = false;
    if (inX >= Position.x - CBox.x && inX <= Position.x + CBox.x && inY >= Position.y - CBox.y && inY <= Position.y + CBox.y ){
        result = true;
    }
    return result;
}

void Button::ClickUpate(bool input){
    CLickInput = input;
}

bool Button::getClickStatus(){
    return CLickInput;
}

bool Button::isHovered(sf::Vector2i input){
    return isHovered(input.x,input.y);
}

bool Button::isHoveredEnlarge(int inX, int inY){
    bool result = false;
    if(isHovered(inX,inY)){
        Scale = BaseScale + ScaleChange;
        result = true;
    }
    else{
        Scale = BaseScale;
    }
    return result;
}

bool Button::isHoveredSmaller(int inX, int inY){
    bool result = false;
    if(isHovered(inX,inY)){
        Scale = BaseScale - ScaleChange;
        result = true;
    }
    else{
        Scale = BaseScale;
    }
    return result;
}

bool Button::isHoveredSprite(int inX, int inY){
    bool result = false;
    if(isHovered(inX,inY)){
        useHoverSprite = true;
        result = true;
    }
    else{
        useHoverSprite = false;
    }
    return result;
}
// - Constructors
void Button::Build(std::string Namein,std::string SpriteFilePath,int inXpos, int inYpos, int ClickX, int ClickY, float bScale, float cScale ){
    Name = Namein;
    setPos(inXpos, inYpos);
    setCBox(ClickX, ClickY);
    setScales(bScale, cScale);
    setSprite(SpriteFilePath);
}

void Button::Build(std::string Namein,std::string SpriteFilePath,int inXpos, int inYpos, int ClickX, int ClickY, float bScale, float cScale , std::string HoverFilePath){
    Build(Namein,SpriteFilePath,inXpos,inYpos,ClickX,ClickY,bScale,cScale);
    setHoverSprite(HoverFilePath);
}

Button::Button(){
    
}

Button::Button(std::string Namein,std::string SpriteFilePath,int inXpos, int inYpos, int ClickX, int ClickY, float bScale, float cScale ){
    Build(Namein,SpriteFilePath,inXpos,inYpos,ClickX,ClickY,bScale,cScale);
}

Button::Button(std::string Namein,std::string SpriteFilePath,int inXpos, int inYpos, int ClickX, int ClickY, float bScale, float cScale , std::string HoverFilePath){
    Build(Namein,SpriteFilePath,inXpos,inYpos,ClickX,ClickY,bScale,cScale,HoverFilePath);
}