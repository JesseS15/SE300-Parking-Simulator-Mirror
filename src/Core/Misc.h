// Basic functions for checking for hover over in the gui
bool mouseRangeCheck(sf::Vector2i MouseInput, int CenterX, int CenterY, int XCbox, int YCbox, float MScale){
    bool result = false;
    int XLow= (CenterX-XCbox)*MScale;
    int XHight = (CenterX+XCbox)*MScale;
    int YLow = (CenterY-YCbox)*MScale;
    int YHight = (CenterY+YCbox)*MScale;

    if (MouseInput.x >= XLow && MouseInput.x <= XHight && MouseInput.y >= YLow && MouseInput.y<= YHight)
    {
        result = true;
    }
    return result;
}