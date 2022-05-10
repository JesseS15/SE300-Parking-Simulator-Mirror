// Main file must include #include <fstream>

std::vector<std::vector<std::string>> dataScraper(std::string fileName){

    std::vector<std::vector<std::string>> content;
	std::vector<std::string> row;
	std::string line, word;


    // Create file pointer
    std::fstream inputData;

    inputData.open(fileName, std::ios::in);

    if(!inputData.is_open()){
        std::cout << "Sorry Sam :(, FIle failed to load \n";
    }
    else{
        while(std::getline(inputData, line))
		{
			row.clear();
 
			std::stringstream str(line);
 
			while(getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}

    }

	return content;
}