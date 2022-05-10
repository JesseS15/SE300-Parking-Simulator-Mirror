#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <algorithm>

// Core GLOBAL sprite vectors for displaying onscreen elements (A dependency for most of the following src files)
std::vector<sf::Sprite> spriteQue;

// Master Scale (This will be base scale for all UI elements)
float Master_Scale;

// Global variable for syncing upo the UI Elements
// 0 = starting screen | 1 = main map screen | 2 = Parking lot map view
int UILevel =0;

// Core simulation Files (drop in for any simulation)
#include "src/Core/Misc.h"
#include "src/Core/SimTime.h"
#include "src/Core/DataLoaders.h"
#include "src/Core/Places.h"
#include "src/Core/Events.h"
#include "src/Core/ParkingIndicator.h"
#include "src/Core/ParkingLots.h"
#include "src/Core/Person.h"
#include "src/Core/Simulation.h"

// ERAU Specific Files (Files made for ERA U but can be edited for the needs of the client)
#include "src/ERAU/PlaceGenerator.h"
#include "src/ERAU/LotGenerator.h"
#include "src/ERAU/PopulationGenerator.h"

// UI Elements Files
#include "src/UI/ButtonBase.h"
#include "src/UI/MenuButtons.h"
#include "src/UI/TimeSelector.h"
#include "src/UI/Slider.h"
#include "src/UI/MainMap.h"
#include "src/UI/LotMaps.h"

sf::Color backGroundColor(25,29,42);


indicatorContainer Indicators("src/ERAU/Indicators.csv");

sf::Text Perful;

int main()
{

    std::system("echo Sanity Check");
    
    generatePopulation();

    // Population tesing
    SimulationTime TestTime("09:10");

    setWindowSize();
    setMapSize();

    Buildings.setScale(Master_Scale);
    Buildings.setOffset(0, Top_Buffer_Size);
    Dorms.setScale(Master_Scale);
    Dorms.setOffset(0, Top_Buffer_Size);

    Lost.generateLots("src/ERAU/Lots.csv",Indicators);
    Lost.setScale(Master_Scale);
    Lost.setOffset(0, Top_Buffer_Size);    


    // Sim testing
    MasterSim.addPlaces(Buildings);
    MasterSim.addPlaces(Dorms);
    MasterSim.addLots(Lost);
    MasterSim.addPeople(Population);


    // More sim testing


    //Slider Testing
    sf::Vector2i SliderPos = {2635,225};
    TestSlider.setMScale(Master_Scale);
    TestSlider.setPos(SliderPos);
    TestSlider.setUpSprites();

    // Time Selector testing
    TestSelector.setPosition(4550,1450);


    // Load Fonts
    // Load Beba
    sf::Font Beba;
    if (!Beba.loadFromFile("src/Fonts/Beba/Bebas-Regular.ttf"))
    {
        std::cout << "Font not loaded" << std::endl;
    }

   sf::Font Comic;
    if (!Comic.loadFromFile("src/Fonts/Comic.ttf"))
    {
        std::cout << "Font not loaded" << std::endl;
    }


    // Set up Test Map and sprite
    sf::Texture ERAUMap;
    if (!ERAUMap.loadFromFile("src/images/ERAUBaseMap.png"))
    {
        std::cout << "Map failed to load loaded" << std::endl;
    }

    sf::Sprite Map;
    Map.setTexture(ERAUMap);

    Map.setScale(Master_Scale, Master_Scale);

    // Render Image window
    sf::RenderWindow Imagewindow(sf::VideoMode(WindowSize.x, WindowSize.y), "512 Parking Serivices", sf::Style::Close);
    sf::Vector2i mapPos = {0,Top_Buffer_Size};
    Map.setPosition(mapPos.x,mapPos.y);

    std::cout << "Window Width: " << WindowSize.x << "\n";

    // Creating Master UI buttons
    // Making master back button
    setUpUIButtons(Master_Scale);

    bool Movepng = false;

    Imagewindow.requestFocus();


    while (Imagewindow.isOpen())
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(Imagewindow);

        sf::Event evnt;
        Imagewindow.pollEvent(evnt);


            switch (evnt.type)
            {
            case sf::Event::Resized:
                std::cout << "Window Width: " << evnt.size.width << " Window Height: " << evnt.size.height << std::endl;
                break;

            case sf::Event::Closed:
                Imagewindow.close();
                break;

            case sf::Event::KeyPressed:
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) TestSlider.stepDown();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) TestSlider.stepUp();
            break;

            case sf::Event::KeyReleased:
            TestSlider.keyUnlatch();
            break;

            case sf::Event::MouseButtonPressed:
                TestSlider.clickStatus(true);
                TestSelector.CLickStatus(true);


                switch(UILevel){
                    case 0:
                RunButton.ClickUpate(true);
                    break;

                    case 1:
                ExitButton.ClickUpate(true);
                    break;

                    case 2:
                button_Back.ClickUpate(true);
                    break;

                }


                TestSlider.MoveBall(mousePos);
                break;

            case sf::Event::MouseButtonReleased:
            TestSlider.clickStatus(false);
                switch(UILevel){
                    case 0:
                    StartScreenClickChecker(mousePos);
                    TestSelector.checkForClick(mousePos,Master_Scale);
                    break;
                    case 1:
                    MainMapClickChecker(mousePos);
                    if(ExitButton.onClick(mousePos)) UILevel = 0;
                    break;
                    case 2:
                    checkforMapButtonClick(mousePos);
                    break;
                }
                button_Back.ClickUpate(false);
                ExitButton.ClickUpate(false);
                RunButton.ClickUpate(false);
                break;

            case sf::Event::MouseMoved:
            TestSlider.MoveBall(mousePos);
                switch(UILevel){
                    case 0:
                    StartHoverChecker(mousePos);
                    TestSelector.checkForHover(mousePos,Master_Scale);
                    break;
                    case 1:
                    MainMapHoverChecker(mousePos);
                    ExitButton.isHoveredEnlarge(mousePos.x,mousePos.y);
                    break;
                    case 2:
                    button_Back.isHoveredEnlarge(mousePos.x,mousePos.y);
                    break;
                }
                break;
            }


            //Time Selector tings
            if(UILevel == 0 && TestSelector.getStatus()){
                TestSlider.setTags(TestSelector.getLowTag(),TestSelector.getHighTag());
                TestSlider.setRange(TestSelector.getRange());
            }


            //Frame switching
            if(TestSlider.checkforUpdate()){
                switch(UILevel){
                    case 0:
                        TestSelector.getInput(TestSlider.Output());
                    break;
                    case 1:
                        MasterSim.setCurFrame(TestSlider.Output());
                        Lost.update(MasterSim.getPeople());
                    break;
                    case 2:
                        MasterSim.setCurFrame(TestSlider.Output());
                        Lost.update(MasterSim.getPeople());
                    break;
                }
            }



            Imagewindow.clear(backGroundColor);

            // Display switch statement based on UI level
            //Sprite Displaying
            switch(UILevel){
                case 0:
                spriteQue.push_back(Map);
                spriteQue.push_back(RunButton.getSprite());
                TestSelector.DisplayBackGround(Master_Scale);
                break;
                case 1:
                spriteQue.push_back(Map);
                Buildings.drawOutlines();
                Dorms.drawOutlines();
                Lost.drawOutlines();
                MasterSim.DisplayFrameBackground(Master_Scale);
                MasterSim.DisplayCurrentFrameTime(Master_Scale,Beba);
                spriteQue.push_back(ExitButton.getSprite());
                break;
                case 2:
                Lost.showMap(Master_Scale,mapPos);
                spriteQue.push_back(button_Back.getSprite());
                MasterSim.DisplayFrameBackground(Master_Scale);
                MasterSim.DisplayCurrentFrameTime(Master_Scale,Beba);
                break;
            }


            // Display Slider if not UI level -1
            if(UILevel != -1){
                TestSlider.Display();
                Imagewindow.draw(TestSlider.DisplayTag(Beba,sf::Color::White,Master_Scale,false));
                Imagewindow.draw(TestSlider.DisplayTag(Beba,sf::Color::White,Master_Scale,true));
            }

            // draw all sprites in the global Sprite que
            for (int i = 0; i < spriteQue.size(); i++)
            {
                Imagewindow.draw(spriteQue[i]);
            }

            // Draw other nonsprite elements
            switch(UILevel){
                case -1:
                Imagewindow.draw(MasterSim.DisplayWorkingMessage(Comic,Master_Scale,2550,1000));
                Imagewindow.draw(Garf(Master_Scale));
                break;
                case 0:
                Imagewindow.draw(TestSelector.DisplayStartHour(Beba,Master_Scale));
                Imagewindow.draw(TestSelector.DisplStartMinute(Beba,Master_Scale));
                Imagewindow.draw(TestSelector.DisplayEndHour(Beba,Master_Scale));
                Imagewindow.draw(TestSelector.DisplayEndMinute(Beba,Master_Scale));
                Imagewindow.draw(TestSelector.DisplayDay(Beba,Master_Scale));
                break;
                case 1:
                Imagewindow.draw(MasterSim.DisplayCurrentFrameTime(Master_Scale,Beba));
                //Loop for writing all percentages
                for(int lts=0;lts<Lost.nPlaces();lts++){
                Perful = Lost.showPerfull(lts,Beba,sf::Color::White,Master_Scale);
                Perful.setFont(Beba);
                Imagewindow.draw(Perful); 
                }
                break;
                case 2:
                Imagewindow.draw(Lost.showTitle(Master_Scale,Beba,sf::Color::White,4550,450,170));
                Imagewindow.draw(MasterSim.DisplayCurrentFrameTime(Master_Scale,Beba));
                if(Lost.checkSpotHover(mousePos,mapPos,Master_Scale)) {
                    Imagewindow.draw(Lost.showOccupent(mousePos,Beba,Lost.getSpotHoverID(mousePos,mapPos,Master_Scale),Master_Scale));
                }
                break;
            }


            Imagewindow.display();
            spriteQue.clear();

            // Run Simulation if UI level is -1
            if(UILevel == -1){

                    MasterSim.setDay(TestSelector.getDay());
                    MasterSim.setStartTime(TestSelector.getStartTime());
                    MasterSim.setEndTime(TestSelector.getEndTime());
                    MasterSim.Execute();
                    sf::Vector2i TestRange = {0,MasterSim.getnFrames()};
                    TestSlider.setRange(TestRange);
                    TestSlider.setTags(MasterSim.getStartTime().getTime24str(), MasterSim.getEndTime().getTime24str());
                    UILevel = 1;
            }

    
    }

    return 0;
}