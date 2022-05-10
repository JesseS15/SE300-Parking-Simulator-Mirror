const float Vertical_Window_Percentage = 0.85;

const sf::Vector2i Base_Map_Size = {2697,2773};
const float Top_Buffer_Percetage = .12;
const int Title_Bar_Height = 50;
const float Aspect_Ratio = 1.7;

sf::Vector2i WindowSize;
int Top_Buffer_Size;
sf::Vector2i Map_Size;

sf::Texture TEX;
sf::Sprite TempSp;

// Some Global objects
SimController MasterSim;
BarSlider TestSlider;
TimeSelector TestSelector;

Run RunButton("Run","src/images/Buttons/Run.png", "src/images/Buttons/RunHover.png", 4500, 2000, 500, 100, Master_Scale, Master_Scale*0.1);
backButton ExitButton("Exit","src/images/Buttons/End.png",4500,1500,500,80,Master_Scale,0.1);

sf::Vector2i setWindowSize(){
    WindowSize.y = sf::VideoMode::getDesktopMode().height * Vertical_Window_Percentage;
    WindowSize.x = WindowSize.y * Aspect_Ratio;
    return WindowSize;
}

sf::Vector2i setMapSize(){
    Top_Buffer_Size = static_cast<int>(WindowSize.y*Top_Buffer_Percetage);
    std::cout << "Buffer size: " << Top_Buffer_Size << std::endl;

    Map_Size.y = WindowSize.y-Top_Buffer_Size;
    std::cout << "Y size: " << Map_Size.y << std::endl;
    Master_Scale = static_cast<float>( Map_Size.y)/static_cast<float>(Base_Map_Size.y);
    std::cout << "Scale: " << Master_Scale << std::endl;
    Map_Size.x = static_cast<int>(static_cast<float>(Base_Map_Size.x)*Master_Scale);

    return Map_Size;
}

sf::Sprite Garf(float Mscale){
    float IMScale = 3;
    sf::Vector2i GarfPos = {2550,2500};

    if(!TEX.loadFromFile("src/images/Meme/Garf.png")){
        std::cout << "Lasagna\n";
    }

    TempSp.setTexture(TEX);

    TempSp.setOrigin(TempSp.getLocalBounds().width/2,TempSp.getLocalBounds().height/2);
    TempSp.setScale(Mscale*IMScale,Mscale*IMScale);
    TempSp.setPosition(GarfPos.x*Mscale,GarfPos.y*Mscale);
    TempSp.setTexture(TEX);
    return TempSp;

}

void MainMapHoverChecker(sf::Vector2i mousePos){
    std::vector<int> LowCheck;
                LowCheck.push_back(Buildings.getClosestDist(mousePos.x, mousePos.y));
                LowCheck.push_back(Dorms.getClosestDist(mousePos.x, mousePos.y));
                LowCheck.push_back(Lost.getClosestDist(mousePos.x, mousePos.y));

                switch (getIDLowest(LowCheck))
                {
                case 0:
                    Buildings.CheckHover(mousePos.x, mousePos.y);
                    break;
                case 1:
                    Dorms.CheckHover(mousePos.x, mousePos.y);
                    break;
                case 2:
                    Lost.CheckHover(mousePos.x, mousePos.y);
                    break;
                }
                LowCheck.clear();
}

void MainMapClickChecker(sf::Vector2i mousePos){

    std::vector<int> LowCheck;
                LowCheck.push_back(Buildings.getClosestDist(mousePos.x, mousePos.y));
                LowCheck.push_back(Dorms.getClosestDist(mousePos.x, mousePos.y));
                LowCheck.push_back(Lost.getClosestDist(mousePos.x,mousePos.y));

                switch (getIDLowest(LowCheck))
                {
                case 0:
                    Buildings.CheckClick(mousePos.x, mousePos.y);
                    break;
                case 1:
                    Dorms.CheckClick(mousePos.x, mousePos.y);
                    if(ExitButton.onClick(mousePos)) UILevel = 0;
                    break;
                case 2:
                    if(Lost.CheckClick(mousePos.x, mousePos.y)) UILevel = 2;
                break;
                }
                LowCheck.clear();

}

// Start screen

void StartHoverChecker(sf::Vector2i mousePos){
                RunButton.isHoveredSprite(mousePos.x,mousePos.y);
}

void StartScreenClickChecker(sf::Vector2i mousePos){

                if(RunButton.onClick(mousePos)){
                    if(TestSelector.isValid()) UILevel = -1;
                }

}
