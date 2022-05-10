// Test Person container
PersonContainer Population;

void generatePopulation(){
    Population.addLocations(Buildings);
    Population.addLocations(Dorms);
    Population.loadData("src/ERAU/Full.csv");
    //Population.listOff();
}