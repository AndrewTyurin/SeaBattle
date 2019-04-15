#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <map>
#include <cstdlib>
#include <chrono>
#include <set>


std::map<int, std::string> shipsTemplate = { {1, "four-decker"} , {2, "three-decker"} , {3, "two-decker"} , {4, "one-decker"} };
std::map<std::string, int> shipsSize = { {"four-decker", 4}, {"three-decker", 3}, {"two-decker", 2} ,{"one-decker", 1} };


struct DialogResult {
	int type = 0;
	int difficulty = 0;
	std::string address = "null";
};

struct Area {
	char lx = ' ';
	int ly = 0;
	char rx = ' ';
	int ry = 0;
};

struct FormattedShip {
	int start = 0;
	int finish = 0;
	int constant = 0;
	bool perNumber = true;
};

struct Ship {
	char lx = ' ';
	int ly = 0;
	char rx = ' ';
	int ry = 0;
	int type = 0;
	int health = 0;
	int number = 0;
};

struct Move {
	char letter = ' ';
	int number = 0;
	char firstHitLetter = ' ';
	int firstHitNumber = 0;
	char letterPrediction = ' ';
	char numberPrediction = 0;
	bool result = false;
	int ship = 0;
};

void DialogRules() {
	std::fstream rules("sb_rules.txt");
	std::vector<std::string> rulesVector;
	std::vector<std::string> shipsVector;
	bool flag = true;

	if (rules) {
		std::string inputString;
		while (getline(rules, inputString)) {
			if (inputString == "*table*") {
				flag = false;
				continue;
			}
			if (flag) {
				rulesVector.push_back(inputString);
			}
			else{
				shipsVector.push_back(inputString);
			}
			
		}
	}

	for (auto& i : rulesVector) {
		std::cout << i << std::endl;
	}

	std::cout << std::endl;
	
	for (auto& i : shipsVector) {
		std::vector<std::string> tempRow;
		int j = 0;

		while (j < i.size()) {
			std::string tempCell;
			while (j < i.size()) {
				if (i[j] != ':') {
					tempCell.push_back(i[j++]);
				}
				else {
					j++;
					break;
				}
			}
			tempRow.push_back(tempCell);
		}
		
		int cellNumber = 0;
		for (auto& j : tempRow) {
			if (cellNumber == 0) {
				std::cout << std::setw(30);
			}
			else if(cellNumber == 1){
				std::cout << std::setw(6);
			}
			else {
				std::cout << std::setw(20);
			}
			cellNumber++;
			std::cout << std::left << j;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void DialogScores() {
	std::fstream scores("sb_scores.txt");
	std::vector<std::string> scoresVector;

	if (scores) {
		std::string inputString;
		while (getline(scores, inputString)) {
			scoresVector.push_back(inputString);
		}
		if (scoresVector.size() != 0) {
			// Module unfinished!
		}
		else {
			std::cout << "There are no scores yet." << std::endl;
		}
	}
}

DialogResult DialogLoad() {
	std::cout << "Enter full address of game: ";
	std::string address;
	std::cin >> address;
	return { 2, 0, address };
	// Module unfinished!
}

DialogResult DialogDifficulty() {
	std::cout << std::endl;
	std::cout << "Choose difficulty level:" << std::endl;
	std::cout << '\t';
	std::cout << "(E) - Easy" << std::endl;
	std::cout << '\t';
	std::cout << "(M) - Medium" << std::endl;
	std::cout << '\t';
	std::cout << "(H) - Hard" << std::endl;
	std::cout << '\t';
	std::cout << "(B) - Backward" << std::endl;

	std::string answer;
	
	while (true) {

		std::cin >> answer;

		if (answer == "E") {
			return { 1, 1, "null" };
		}
		else if (answer == "M") {
			return { 1, 2, "null" };
		}
		else if (answer == "H") {
			return { 1, 3, "null" };
		}
		else if (answer == "B") {
			DialogResult backwards;
			return backwards;
		}
		else {
			std::cout << "Unknown command: " << "\"" << answer << "\". Try again." << std::endl;
		}
	}
}

DialogResult DialogMenu() {
	while (true) {
		std::cout << std::endl;
		std::cout << "Choose proper key to continue:" << std::endl;
		std::cout << '\t';
		std::cout << "(N) - New game" << std::endl;
		std::cout << '\t';
		std::cout << "(L) - Load game" << std::endl;
		std::cout << '\t';
		std::cout << "(S) - Scores" << std::endl;
		std::cout << '\t';
		std::cout << "(R) - Read rules" << std::endl;
		std::cout << '\t';
		std::cout << "(Q) - Quit game" << std::endl;

		std::string answer;

		std::cin >> answer;

		if (answer == "N") {
			DialogResult dialogResult = DialogDifficulty();
			if (dialogResult.type == 1) {
				return dialogResult;
			}
		}
		else if (answer == "L") {
			DialogResult dialogResult = DialogLoad();
			if (dialogResult.type == 2) {
				return dialogResult;
			}
		}
		else if (answer == "S") {
			DialogScores();
			std::cout << "Press any key to get back to menu" << std::endl;
			// Waiting for any key here!
		}
		else if (answer == "R") {
			DialogRules();
			std::cout << "Press any key to get back to menu" << std::endl;
			// Waiting for any key here!
		}
		else if (answer == "Q") {
			exit(1);
		}
		else {
			std::cout << "Unknown command: " << "\"" << answer << "\". Try again." << std::endl;
		}
	}
}

int LetterToNumber(char letter) {
	return letter - 64;
}

char NumberToLetter(int number) {
	return number + 64;
}

class Player {
public:
	Player() {

	}
	Player(int& compDiff) {
		difficulty = compDiff;
	}
	int ReturnDifficulty() {
		return difficulty;
	}
	int GetCellValue(const char& letter, const int& number) const {
		return grid[number - 1][LetterToNumber(letter) - 1];
	}
	void SetCellValue(const char& letter, const int& number, int value) {
		grid[number - 1][LetterToNumber(letter) - 1] = value;
	}
	void ShipsSetUp() {
		int shipSize = 4;
		for (const auto& i : shipsTemplate) {
			for (int j = 0; j < i.first; j++) {
				while (true) {
					bool shipPlaced = false;
					std::cout << "Set position of " << i.second;
					if (i.second != "one-decker") {
						std::cout << " (first and last cells)";
					}
					if (i.second != "four-decker") {
						std::cout << " #" << j + 1;
					}
					std::cout << ": ";

					if (i.second != "one-decker") {
						char letterFirst = ' ';
						int numberFirst = 0;
						char letterSecond = ' ';
						int numberSecond = 0;
						std::cin >> letterFirst >> numberFirst >> letterSecond >> numberSecond;
						
						if (!((('A' <= letterFirst) && (letterFirst <= 'J')) && ((1 <= numberFirst) && (numberFirst <= 10)) && (('A' <= letterSecond) && (letterSecond <= 'J')) && ((1 <= numberSecond) && (numberSecond <= 10)))) {
							std::cout << "Wrong coordinates. Repeat entry." << std::endl;
							continue;
						}

						if (!ShipDiagonal(letterFirst, numberFirst, letterSecond, numberSecond)) {
							FormattedShip ship = FormatShip(letterFirst, numberFirst, letterSecond, numberSecond);
							if (ShipCorrectLength(i.second, ship)) {
								Area area = GetArea(ship);
								if (AreaAvailable(area, ship)) {
									int a = 0;
									PlaceShip(area, ship);
									shipPlaced = true;
								}
								else {
									std::cout << "Ship can't be placed at this position. Repeat entry." << std::endl;
								}
							}
							else {
								std::cout << "Wrong length of the ship. Repeat entry." << std::endl;
							}
						}
						else {
							std::cout << "Ship can't be diagonal. Repeat entry." << std::endl;
						}
					}
					else {
						char letter = ' ';
						int number = 0;
						std::cin >> letter >> number;
						Area area = GetArea(letter, number);
						if (AreaAvailable(area, letter, number)) {
							PlaceShip(area, letter, number);
							shipPlaced = true;
						}
						else {
							std::cout << "Ship can't be placed at this position. Enter the position again." << std::endl;
						}
					}
					if (shipPlaced) {
						break;
					}
				}
			}
			shipSize--;
		}
	}
	void ShipsSetUp(int& parameter) {
		if (parameter == 1) {
			GridGenEasy();
		}
		else if ((parameter == 2) || (parameter == 3)) {
			GridGenHard();
		}
	}
	void PrintGrid() {
		std::cout << "   ";

		for (char i = 'A'; i <= 'J'; i++) {
			std::cout << std::setw(2) << i;
		}
		std::cout << std::endl;

		for (int i = 1; i <= 10; i++) {
			std::cout << std::setw(3) << i;
			for (int j = 'A'; j <= 'J'; j++) {
				if (GetCellValue(j, i) == 1) {
					std::cout << std::setw(2) << "H";
				}
				else if (GetCellValue(j, i) == 0) {
					std::cout << std::setw(2) << " ";
				}
				else if (GetCellValue(j, i) == 2) {
					std::cout << std::setw(2) << " ";
				}
				else if (GetCellValue(j, i) == 3) {
					std::cout << std::setw(2) << "X";
				}
				else if (GetCellValue(j, i) == 4) {
					std::cout << std::setw(2) << "*";
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	void PrintGridHiddenShips() {
		std::cout << "   ";

		for (char i = 'A'; i <= 'J'; i++) {
			std::cout << std::setw(2) << i;
		}
		std::cout << std::endl;

		for (int i = 1; i <= 10; i++) {
			std::cout << std::setw(3) << i;
			for (int j = 'A'; j <= 'J'; j++) {
				if (GetCellValue(j, i) == 1) {
					std::cout << std::setw(2) << "~";
				}
				else if (GetCellValue(j, i) == 0) {
					std::cout << std::setw(2) << "~";
				}
				else if (GetCellValue(j, i) == 2) {
					std::cout << std::setw(2) << "~";
				}
				else if (GetCellValue(j, i) == 3) {
					std::cout << std::setw(2) << "X";
				}
				else if (GetCellValue(j, i) == 4) {
					std::cout << std::setw(2) << "*";
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	bool CellAvailable(char letter, int number) {
		if (((letter < 'A') || (letter > 'J')) || ((number < 1) || (number > 10))) {
			return false;
		}
		else {
			if ((GetCellValue(letter, number) != 3) && (GetCellValue(letter, number) != 4)) {
				return true;
			}
			return false;
		}
	}
	bool Shoot(char& letter, int& number) {
		if (GetCellValue(letter, number) == 1) {
			std::cout << "Hit at " << letter << ":" << number << std::endl;
			lastHit = true;
			SetCellValue(letter, number, 3);
			Area area = GetArea(letter, number);
			FillHitArea(letter, number);
			return true;
		}
		else {
			std::cout << "Missed at " << letter << ":" << number << std::endl;
			lastHit = false;
			if (GetCellValue(letter, number) != 3) {
				SetCellValue(letter, number, 4);
			}
			return false;
		}
	}
	void AttackedByHuman() {
		char letter = ' ';
		int number = 0;
		while (true) {
			std::cout << "Enter cell to attack: ";
			std::cin >> letter >> number;
			if (CellAvailable(letter, number)) {
				break;
			}
			else {
				std::cout << "Wrong coordinates. Repeat entry.";
				continue;
			}
		}
		Shoot(letter, number);
		PrintGridHiddenShips();
	}
	void PredictEasy(Move& aiMove) {
		if (alreadyHit == 1) {
			while (!CellAvailable(aiMove.letterPrediction, aiMove.numberPrediction)) {
				aiMove.letterPrediction = aiMove.firstHitLetter;
				aiMove.numberPrediction = aiMove.firstHitNumber;

				int direction = Random(4);

				if (direction == 1) {
					aiMove.letterPrediction++;
				}
				else if (direction == 2) {
					aiMove.numberPrediction--;
				}
				else if (direction == 3) {
					aiMove.letterPrediction--;
				}
				else {
					aiMove.numberPrediction++;
				}
			}
		}
		
		if (alreadyHit > 1) {
			if (!aiMove.result) {
				searchDelta *= (-1);
			}
			aiMove.letterPrediction = aiMove.letter;
			aiMove.numberPrediction = aiMove.number;
			while (!CellAvailable(aiMove.letterPrediction, aiMove.numberPrediction)) {
				if (aiMove.letter == aiMove.firstHitLetter) {
					if (((aiMove.numberPrediction > aiMove.firstHitNumber) && (aiMove.numberPrediction >= 10)) || ((aiMove.numberPrediction < aiMove.firstHitNumber) && (aiMove.numberPrediction <= 1))) {
						searchDelta *= (-1);
					}
					aiMove.numberPrediction += searchDelta;
					if (aiMove.numberPrediction == aiMove.firstHitNumber) {
						aiMove.numberPrediction += searchDelta;
					}
				}
				if (aiMove.number == aiMove.firstHitNumber) {
					if (((aiMove.letterPrediction > aiMove.firstHitLetter) && (aiMove.letterPrediction >= 'J')) || ((aiMove.letterPrediction < aiMove.firstHitLetter) && (aiMove.letterPrediction <= 'A'))) {
						searchDelta *= (-1);
					}
					aiMove.letterPrediction += searchDelta;
					if (aiMove.letterPrediction == aiMove.firstHitLetter) {
						aiMove.letterPrediction += searchDelta;
					}
				}
			}
		}
		// Catch some bugs here please!
	}
	void PredictHard(Move& aiMove) {
		// Module unfinished!
	}
	void AttackedByComputer() {
		Move aiMove;
		if (difficulty != 3) {
			if ((!log.size()) || (!alreadyHit)) {
				while (!CellAvailable(aiMove.letter, aiMove.number)) {
					aiMove.letter = NumberToLetter(Random(10));
					aiMove.number = Random(10);
				}
			}
			else {
				aiMove.letter = log[log.size() - 1].letterPrediction;
				aiMove.number = log[log.size() - 1].numberPrediction;
			}

			aiMove.result = Shoot(aiMove.letter, aiMove.number);

			if (aiMove.result) {
				if (ShipByCell(aiMove.letter, aiMove.number).health) {
					alreadyHit++;
				}
				else {
					alreadyHit = 0;
				}
			}

			if (alreadyHit == 1) {
				if (aiMove.result) {
					aiMove.firstHitLetter = aiMove.letter;
					aiMove.firstHitNumber = aiMove.number;
				}
				else {
					aiMove.firstHitLetter = log[log.size() - 1].firstHitLetter;
					aiMove.firstHitNumber = log[log.size() - 1].firstHitNumber;
				}
				aiMove.ship = ShipByCell(aiMove.letter, aiMove.number).number;
			}
			else if (alreadyHit > 1) {
				aiMove.firstHitLetter = log[log.size() - 1].firstHitLetter;
				aiMove.firstHitNumber = log[log.size() - 1].firstHitNumber;
				aiMove.ship = log[log.size() - 1].ship;
			}
			
			if (alreadyHit) {
				PredictEasy(aiMove);
			}
			
			log.push_back(aiMove);
		}
		else {
			//PredictHard(aiMove);
		}
	}
	int ShipsAlive() const{
		int numberOfShips = 0;
		for (auto& i : shipsVector) {
			if (i.health) {
				numberOfShips++;
			}
		}
		return numberOfShips;
	}
	
	bool lastHit = false;
private:
	int difficulty = 0;
	std::vector<std::vector<int>> grid = { 10, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
	std::vector<Ship> shipsVector;
	std::vector<Move> log;

	int alreadyHit = 0;
	int searchDelta = 1;
	

	Area GetArea(const char& letter, const int& number) {
		char leftX = letter;
		int leftY = number;
		char rightX = letter;
		int rightY = number;

		if (leftX > 'A') {
			leftX--;
		}
		if (leftY > 1) {
			leftY--;
		}
		if (rightX < 'J') {
			rightX++;
		}
		if (rightY < 10) {
			rightY++;
		}

		return { leftX, leftY, rightX, rightY };
	}
	Area GetArea(const FormattedShip& ship) {
		char startX = ' ';
		int startY = 0;
		char finishX = ' ';
		int finishY = 0;

		if (ship.perNumber) {
			startX = NumberToLetter(ship.constant);
			startY = ship.start;
			finishX = NumberToLetter(ship.constant);
			finishY = ship.finish;
		}
		else {
			startX = NumberToLetter(ship.start);
			startY = ship.constant;
			finishX = NumberToLetter(ship.finish);
			finishY = ship.constant;
		}

		if (startX > 'A') {
			startX--;
		}
		if (startY > 1) {
			startY--;
		}
		if (finishX < 'J') {
			finishX++;
		}
		if (finishY < 10) {
			finishY++;
		}

		return { startX, startY, finishX, finishY };
	}
	bool AreaAvailable(Area area, const char& letter, const int& number) const{
		for (char i = area.lx; i <= area.rx; i++) {
			for (int j = area.ly; j <= area.ry; j++) {
				if ((i == letter) && (j == number)) {
					if (grid[j - 1][LetterToNumber(i) - 1] != 0) {
						return false;
						
					}
				}
				else {
					if (grid[j - 1][LetterToNumber(i) - 1] == 1) {
						return false;
					}
				}
			}
		}
		return true;
	}
	bool AreaAvailable(Area area, FormattedShip ship) const {
		for (char i = area.lx; i <= area.rx; i++) {
			for (int j = area.ly; j <= area.ry; j++) {
				if (ship.perNumber) {
					if ((i == NumberToLetter(ship.constant)) && ((j >= ship.start) && (j <= ship.finish))) {
						if (grid[j - 1][LetterToNumber(i) - 1] != 0) {
							return false;
						}
					}
					else {
						if (grid[j - 1][LetterToNumber(i) - 1] == 1) {
							return false;
						}
					}
				}
				else {
					if (((i >= NumberToLetter(ship.start)) && (i <= NumberToLetter(ship.finish))) && (i == ship.constant)) {
						if (grid[j - 1][LetterToNumber(i) - 1] != 0) {
							return false;
						}
					}
					else {
						if (grid[j - 1][LetterToNumber(i) - 1] == 1) {
							return false;
						}
					}
				}

			}
		}
		return true;
	}
	Ship& ShipByCell (char letter, int number) {
		for (auto& i : shipsVector) {
			if (((letter >= i.lx) && (letter <= i.rx)) && ((number >= i.ly) && (number <= i.ry))) {
				return i;
			}
		}
	}
	void FillHitArea(char& letter, int& number) {
		if (ShipByCell(letter, number).health == 1) {
			ShipByCell(letter, number).health--;
			Area area = GetArea(FormatShip(ShipByCell(letter, number).lx, ShipByCell(letter, number).ly, ShipByCell(letter, number).rx, ShipByCell(letter, number).ry));
			for (int i = area.ly; i <= area.ry; i++) {
				for (char j = area.lx; j <= area.rx; j++) {
					if ((GetCellValue(j, i) != 1) && (GetCellValue(j, i) != 3)) {
						SetCellValue(j, i, 4);
					}
				}
			}
		}
		else {
			ShipByCell(letter, number).health--;
		}
	}
	bool ShipDiagonal(const char& letterFirst, const int& numberFirst, const char& letterSecond, const int& numberSecond) const{
		if (letterFirst == letterSecond) {
			return false;
		}
		else {
			if (numberFirst == numberSecond) {
				return false;
			}
			else {
				return true;
			}
		}
	}
	bool ShipCorrectLength(const std::string& type, const FormattedShip& ship) const{
		if ((ship.finish - ship.start + 1) == shipsSize[type]) {
			return true;
		}
		else {
			return false;
		}
	}
	void PlaceShip(const Area& area, const FormattedShip& ship) {
		Ship shipToSave;
		for (char i = area.lx; i <= area.rx; i++) {
			for (int j = area.ly; j <= area.ry; j++) {
				if (ship.perNumber) {
					shipToSave.lx = NumberToLetter(ship.constant);
					shipToSave.rx = NumberToLetter(ship.constant);
					shipToSave.ly = ship.start;
					shipToSave.ry = ship.finish;
					if ((i == NumberToLetter(ship.constant)) && ((ship.start <= j) && (j <= ship.finish))) {
						grid[j - 1][LetterToNumber(i) - 1] = 1;
					}
					else {
						grid[j - 1][LetterToNumber(i) - 1] = 2;
					}
				}
				else {
					shipToSave.lx = NumberToLetter(ship.start);
					shipToSave.rx = NumberToLetter(ship.finish);
					shipToSave.ly = ship.constant;
					shipToSave.ry = ship.constant;
					if (((NumberToLetter(ship.start) <= i) && (i <= NumberToLetter(ship.finish))) && (j == ship.constant)) {
						grid[j - 1][LetterToNumber(i) - 1] = 1;
					}
					else {
						grid[j - 1][LetterToNumber(i) - 1] = 2;
					}
				}
				
			}
		}
		shipToSave.health = ship.finish - ship.start + 1;
		shipToSave.type = 5 - shipToSave.health;
		if (shipsVector.size()) {
			shipToSave.number = shipsVector[shipsVector.size() - 1].number + 1;
		}
		else {
			shipToSave.number = 1;
		}
		shipsVector.push_back(shipToSave);
	}
	FormattedShip FormatShip(const char& letterFirst, const int& numberFirst, const char& letterSecond, const int& numberSecond) {
		FormattedShip ship;
		if (letterFirst == letterSecond) {
			if (numberFirst <= numberSecond) {
				ship.start = numberFirst;
				ship.finish = numberSecond;
				ship.constant = LetterToNumber(letterFirst);
			}
			else {
				ship.start = numberSecond;
				ship.finish = numberFirst;
				ship.constant = LetterToNumber(letterFirst);
			}
		}
		else if (numberFirst == numberSecond) {
			if (letterFirst <= letterSecond) {
				ship.start = LetterToNumber(letterFirst);
				ship.finish = LetterToNumber(letterSecond);
				ship.constant = numberFirst;
			}
			else {
				ship.start = LetterToNumber(letterSecond);
				ship.finish = LetterToNumber(letterFirst);
				ship.constant = numberFirst;
			}
			ship.perNumber = false;
		}
		return ship;
	}
	void PlaceShip(const Area& area, const char& letter, const int& number) {
		for (char i = area.lx; i <= area.rx; i++) {
			for (int j = area.ly; j <= area.ry; j++) {
				if ((i == letter) && (j == number)) {
					grid[j - 1][LetterToNumber(i) - 1] = 1;
				}
				else {
					grid[j - 1][LetterToNumber(i) - 1] = 2;
				}
			}
		}
		Ship shipToSave = { letter, number, letter, number, 4, shipsSize[shipsTemplate[4]] };
		if (shipsVector.size()) {
			shipToSave.number = shipsVector[shipsVector.size() - 1].number + 1;
		}
		else {
			shipToSave.number = 1;
		}
		shipsVector.push_back(shipToSave);
	}
	long long CurrentTimeNanosec() {
		std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
		auto duration = now.time_since_epoch();
		typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<8>
		>::type> Days;
		auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
		return nanoseconds.count();
	}
	int Random(int range) {
		srand(CurrentTimeNanosec());
		return (rand() % range) + 1;
	}
	void GridGenEasy() {																							 
		for (auto& i : shipsTemplate) {
			for (int j = 0; j < i.first; j++) {
				bool positionGood = false;
				while (!positionGood) {
					char letter1 = NumberToLetter(Random(10));
					int number1 = Random(10);
					char letter2 = 0;
					int number2 = 0;
					if (grid[number1 - 1][LetterToNumber(letter1) - 1] == 0) {
						if (shipsSize[i.second] == 1) {
							Area currentArea = GetArea(letter1, number1);
							if (AreaAvailable(currentArea, letter1, number1)) {
								PlaceShip(currentArea, letter1, number1);
								break;
							}
						}
						else {
							std::set<int> directions = { 1, 2, 3, 4 };
							
							while (true) {
								if (directions.size()) {
									int direction = Random(4);
									if (directions.count(direction)) {
										directions.erase(direction);
										if (direction == 1) {
											if ((letter1 + shipsSize[i.second] - 1) <= 'J') {
												letter2 = letter1 + shipsSize[i.second] - 1;
												number2 = number1;
												positionGood = true;
											}
										}
										else if (direction == 2) {
											if ((number1 - shipsSize[i.second] + 1) >= 1) {
												number2 = number1 - shipsSize[i.second] + 1;
												letter2 = letter1;
												positionGood = true;
											}
										}
										else if (direction == 3) {
											if ((letter1 - shipsSize[i.second] + 1) >= 'A') {
												letter2 = letter1 - shipsSize[i.second] + 1;
												number2 = number1;
												positionGood = true;
											}
										}
										else if (direction == 4) {
											if ((number1 + shipsSize[i.second] - 1) <= 10) {
												number2 = number1 + shipsSize[i.second] - 1;
												letter2 = letter1;
												positionGood = true;
											}
										}
										if (positionGood) {
											FormattedShip currentShip = FormatShip(letter1, number1, letter2, number2);
											Area currentArea = GetArea(currentShip);

											if (AreaAvailable(currentArea, currentShip)) {
												PlaceShip(currentArea, currentShip);
												break;
											}
										}
										else {
											positionGood = false;
											continue;
										}
									}
									else {
										continue;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	void RotateGrid(int angle) {
		for (int i = 0; i < angle; i++) {
			std::vector<std::vector<int>> temporaryGrid;
			for (int j = grid.size() - 1; j >= 0; j--) {
				std::vector<int> temporaryRow; 
				for (int k = 0; k < grid.size(); k++) {
					temporaryRow.push_back(grid[k][j]);
				}
				temporaryGrid.push_back(temporaryRow);
			}
			grid = temporaryGrid;
		}
	}
	void GridGenHard(){
		std::map<int, int> bigShips = { {1, shipsSize[shipsTemplate[1]]}, {2, shipsSize[shipsTemplate[2]]}, {3, shipsSize[shipsTemplate[2]]},
										{4, shipsSize[shipsTemplate[3]]}, {5, shipsSize[shipsTemplate[3]]}, {6, shipsSize[shipsTemplate[3]]} };
		int strategy = Random(3);

		if (strategy == 1) {
			char letter = 'J';
			int number = 1;
			while (bigShips.size()) {
				int type = 0;
				if (bigShips.size() == 1) {
					for (auto& i : bigShips) {
						type = i.first;
					}
				}
				else {
					type = Random(6);
				}
				if (bigShips.count(type)) {
					if ((type == 5) || (type == 6)) {
						FormattedShip ship1 = FormatShip(letter, number, letter, number + 1);
						FormattedShip ship2 = FormatShip(letter - 2, number, letter - 2, number + 1);
						Area ship1Area = GetArea(ship1);
						Area ship2Area = GetArea(ship2);
						PlaceShip(ship1Area, ship1);
						PlaceShip(ship2Area, ship2);
						number += 3;
						bigShips.erase(5);
						bigShips.erase(6);
					}
					else {
						FormattedShip ship = FormatShip(letter, number, letter - bigShips[type] + 1, number);
						Area shipArea = GetArea(ship);
						PlaceShip(shipArea, ship);
						number += 2;
						bigShips.erase(type);
					}				
				}
			}
			for (int i = 0; i < 4; i++) {
				while (true) {
					letter = NumberToLetter(Random(10));
					number = Random(10);
					Area area = GetArea(letter, number);
					if (AreaAvailable(area, letter, number)) {
						PlaceShip(area, letter, number);
						break;
					}
				}
			}
			RotateGrid((Random(40) - 1) / 10);
		}
		else if (strategy == 2) {
			char letter1 = 'A';
			int number1 = 1;
			char letter2 = 'C';
			int number2 = 1;

			if (Random(2) == 1) {
				letter2 = 'J';
			}

			if (Random(2) == 1) {
				char tempLetter = letter2;
				letter2 = letter1;
				letter1 = tempLetter;
			}

			while (bigShips.size()) {
				int type = 0;
				if (bigShips.size() == 1) {
					for (auto& i : bigShips) {
						type = i.first;
					}
				}
				else {
					type = Random(6);
				}
				
				if (bigShips.count(type)) {
					FormattedShip ship;
					Area shipArea;
					if (type == 1) {
						ship = FormatShip(letter1, number1, letter1, number1 + bigShips[type] - 1);
						shipArea = GetArea(ship);
						number1 += (bigShips[type] + 1);
					}
					else if ((type >= 2) && (type <= 3)) {
						ship = FormatShip(letter2, number2, letter2, number2 + bigShips[type] - 1);
						shipArea = GetArea(ship);
						number2 += (bigShips[type] + 1);
					}
					else if ((type == 4) || (type == 5)) {
						ship = FormatShip(letter1, number1, letter1, number1 + bigShips[type] - 1);
						shipArea = GetArea(ship);
						number1 += (bigShips[type] + 1);
					}
					else if (type == 6) {
						ship = FormatShip(letter2, number2, letter2, number2 + bigShips[type] - 1);
						shipArea = GetArea(ship);
						number2 += (bigShips[type] + 1);
					}
					else{
						continue;
					}
					
					PlaceShip(shipArea, ship);
					bigShips.erase(type);
				}
			}
			for (int i = 0; i < 4; i++) {
				while (true) {
					letter1 = NumberToLetter(Random(10));
					number1 = Random(10);
					Area area = GetArea(letter1, number1);
					if (AreaAvailable(area, letter1, number1)) {
						PlaceShip(area, letter1, number1);
						break;
					}
				}
			}
			RotateGrid((Random(40) - 1) / 10);
		}
		else if (strategy == 3){
			char letter1 = 'A';
			int number1 = 1;
			char letter2 = 'C';
			int number2 = 1;
			
			int position = Random(2);
			if (position == 2) {
				letter2 = 'A';
				number2 = 3;
			}

			while (bigShips.size()) {
				int type = 0;
				if (bigShips.size() == 1) {
					for (auto& i : bigShips) {
						type = i.first;
					}
				}
				else {
					type = Random(6);
				}

				if (bigShips.count(type)) {
					FormattedShip ship;
					Area shipArea;
					if ((type == 1) || (type == 2)) {
						if (position == 1) {
							ship = FormatShip(letter1, number1, letter1, number1 + bigShips[type] - 1);
							number1 += (bigShips[type] + 1);
						}
						else {
							ship = FormatShip(letter1, number1, letter1 + bigShips[type] - 1, number1);
							letter1 += (bigShips[type] + 1);
						}
						shipArea = GetArea(ship);
					}
					else if ((type == 3) || (type == 4)) {
						if (position == 1) {
							ship = FormatShip(letter2, number2, letter2 + bigShips[type] - 1, number2);
							letter2 += (bigShips[type] + 1);
						}
						else {
							ship = FormatShip(letter2, number2, letter2, number2 + bigShips[type] - 1);
							number2 += (bigShips[type] + 1);
						}
						shipArea = GetArea(ship);
					}
					else if (type == 5) {
						ship = FormatShip('A', 10, 'B', 10);
						shipArea = GetArea(ship);
					}
					else if (type == 6) {
						ship = FormatShip('J', 1, 'J', 2);
						shipArea = GetArea(ship);
					}
					else {
						continue;
					}

					PlaceShip(shipArea, ship);
					bigShips.erase(type);
				}
			}
			for (int i = 0; i < 4; i++) {
				while (true) {
					letter1 = NumberToLetter(Random(10));
					number1 = Random(10);
					Area area = GetArea(letter1, number1);
					if (AreaAvailable(area, letter1, number1)) {
						PlaceShip(area, letter1, number1);
						break;
					}
				}
			}
			RotateGrid((Random(40) - 1) / 10);
		}
	}
};

void GameProgress(int& difficulty) {
	Player human;
	Player computer(difficulty);
	
	computer.ShipsSetUp(difficulty);
	human = computer;

	//human.ShipsSetUp();

	while ((computer.ShipsAlive()) && (human.ShipsAlive())) {
		while (true) {
			computer.AttackedByHuman();
			computer.PrintGridHiddenShips();
			if (!computer.lastHit) {
				std::cout << "MISSED!" << std::endl;
				break;
			}
		}
		while (true) {
			human.AttackedByComputer();
			human.PrintGridHiddenShips();
			if (!human.lastHit) {
				std::cout << "MISSED!" << std::endl;
				break;
			}
		}
	}

	if (computer.ShipsAlive() > 0) {
		if (human.ShipsAlive() == 0) {
			std::cout << "Computer wins!" << std::endl;
		}
	}
	else {
		if (human.ShipsAlive() > 0) {
			std::cout << "Human wins!" << std::endl;
		}
	}
}

int main() {
	std::cout << "Welcome to Sea Battle!" << std::endl;

	DialogResult result = DialogMenu();

	GameProgress(result.difficulty);

	return 0;
}