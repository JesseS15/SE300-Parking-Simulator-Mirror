backButton button_Back("Back","src/images/Buttons/Back.png",800,800,100,50,Master_Scale,0.01);

void setUpUIButtons(float inScale){
    button_Back.setScales(inScale*1.5,inScale*0.1);
    button_Back.setPos(4150*inScale,2850*inScale);
    button_Back.setCBox(370*inScale,195*inScale);

    RunButton.setScales(inScale,inScale*0.1);
    RunButton.setPos(4550*inScale,2900*inScale);
    RunButton.setCBox(750*inScale,250*inScale);

    ExitButton.setScales(inScale,inScale*0.06);
    ExitButton.setPos(4540*inScale,2800*inScale);
    ExitButton.setCBox(750*inScale,250*inScale);


}

void checkforMapButtonClick(sf::Vector2i input){
    if(button_Back.onClick(input)){
        //Go back to Map
        UILevel = 1;
    }
}