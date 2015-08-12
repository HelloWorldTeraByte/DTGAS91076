#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <algorithm>

//an enum to hold the final choice after some calculations 
enum class Catergories
{
    Countries,
    Food,
    Technology,
    Uninitialized
};

//when the function is called it store the files content into a passed array
void FiletoArray(std::ifstream &file, std::vector<std::string> &array, std::string &currentLine);
void MainLoop(std::string currentWord);		//the main game loop
void Clear();					//prints 20 empty lines

//fucntions to display the hangman
void Hangman1();
void Hangman2();
void Hangman3();
void Hangman4();
void Hangman5();
void Hangman6();
void Hangman7();
void Hangman8();
void UpdateHangman(int hangmanNumber);
void PrintWord(std::string currentWord);	//iterate through the word and prints a space or a * for a letter

int main(int argc, char* argv[])
{
    using namespace std;

    //variables to store the name of the files(the default ones)
    string countryTextFile = "Countries.txt";
    string foodTextFile = "Food.txt";
    string technologyTextFile = "Technology.txt";

    //if the user passes in the name of the files, override the default variable to the passed in arguments  
    if(argc > 1)
    {
	countryTextFile = argv[1];
	foodTextFile = argv[2];
	technologyTextFile = argv[3];
    }

    string currentLine;

    //variables to open a text stream(the file name is passed in)
    ifstream countriesFile(countryTextFile);
    ifstream foodFile(foodTextFile);
    ifstream technologyFile(technologyTextFile);

    //these arrays store the hangman words
    std::vector<std::string> countriesArray{};
    std::vector<std::string> foodArray{};
    std::vector<std::string> technologyArray{};

    FiletoArray(countriesFile, countriesArray, currentLine);	//This reads from the text file and store that data in the passed in array/vector
    FiletoArray(foodFile, foodArray, currentLine);		//This reads from the text file and store that data in the passed in array/vector
    FiletoArray(technologyFile, technologyArray, currentLine);	//This reads from the text file and store that data in the passed in array/vector

    string useresCatergory = "";				//this handles raw data from the buffer used and string so I can test it easier
    int useresCatergoryNumber = 0;				//this stores the number of the users chosen catergory
    bool isValidCatergory = false;
    Catergories catergory = Catergories::Uninitialized;		//intialize the variable as null so if the loop fails it is easier to debug

    //repeat the loop till a valid catergory is chosen 
    while(!isValidCatergory)
    {
	cout << "Choose the number of category to play hangman :)" << endl;
	cout << "1.Countries" << "\t" "2.Food" << "\t" << "\t" << "3.Technology" << endl;

	getline(cin, useresCatergory);				//store the users input in the usersCatergory variable
	useresCatergoryNumber = atoi(useresCatergory.c_str());

	//test the input, if not valid loop throught the loop
	//if the input is valid set the isValidCatergory variable to true, this makes the loop to break and continue the program
	//also set the catergory variable accordingly
	if(useresCatergoryNumber == 1)
	{
	    cout << "Countries? Cool" << endl;
	    catergory = Catergories::Countries;
	    isValidCatergory = true;
	}
	if(useresCatergoryNumber == 2)
	{
	    cout << "Food? Cool" << endl;
	    catergory = Catergories::Food;
	    isValidCatergory = true;

	}
	if(useresCatergoryNumber == 3)
	{
	    cout << "Technology? Cool" << endl;   
	    catergory = Catergories::Technology;
	    isValidCatergory = true;

	}
    }
    int randomNumberGenerated;
    string currentWord;

    //generate a random word from the vector/array according to users selection
    //then enter the main game loop, also pass in the randomly chosen word
    if(catergory == Catergories::Countries)
    {
	srand(time(0));
	randomNumberGenerated = rand()%countriesArray.size();
	currentWord = countriesArray[randomNumberGenerated];
	//PrintWord(currentWord);
	MainLoop(currentWord);
    }
    else if(catergory == Catergories::Food)
    {
	srand(time(0));
	randomNumberGenerated = rand()%foodArray.size();
	currentWord = foodArray[randomNumberGenerated];
	//PrintWord(currentWord);
	MainLoop(currentWord);
    }

    else if(catergory == Catergories::Technology)
    {
	srand(time(0));
	randomNumberGenerated = rand()%technologyArray.size();
	currentWord = technologyArray[randomNumberGenerated];
	//PrintWord(currentWord);
	MainLoop(currentWord);
    }

    return 0;
}

//Main game loop
void MainLoop(std::string  currentWord)
{
    using namespace std;

    int wrongGuesses = 1;
    UpdateHangman(wrongGuesses);
    std::string guessedWord = "";
    std::vector<std::string> guessedLetters{};

    //fill the guessedWord variable with * to initialize the variable
    for(unsigned int i = 0; i < currentWord.size(); i++)
    {
	if(currentWord[i] == ' ')
	{
	    guessedWord.push_back(' ');
	}
	else
	{
	    guessedWord.push_back('*');
	}
    }

    cout << guessedWord << endl;		 //print out the curently guessed word
    //cout << currentWord << endl;

    while(1)
    {

	bool aValidLetter = false;
	string guess;

	//repeat the loop until a valid letter is entered 
	while(!aValidLetter)
	{
	    cout << "Guess a letter in the word :)\t";
	    cin >> guess;
	    if(!atoi(guess.c_str()) && (guess.length() == 1))
	    {
		aValidLetter = true;
	    }
	    else
	    {
		cout << "That's not a valid letter!" << endl;
	    }
	}

	//turn any upper case into lower case
	std::transform(guess.begin(), guess.end(), guess.begin(), ::tolower);

	//add the guess letter to the guessedLetters array only if there is no previous guess entry(to avoid doubles)
	if(!(std::find(guessedLetters.begin(), guessedLetters.end(), guess) !=guessedLetters.end()))
	{
	    guessedLetters.push_back(guess);
	}

	//if the guess is correct
	if(currentWord.find(guess.c_str()) != string::npos)
	{
	    Clear();
	    UpdateHangman(wrongGuesses);

	    //loop throush the current word
	    for(unsigned int i = 0; i < currentWord.size(); i++)
	    {
		//if the current letter equals the guess replace the * of the guessedWord with the guess letter
		if(currentWord[i] == guess[0])
		{
		    guessedWord[i] = guess[0];
		}
	    }
	    cout << guessedWord << endl;
	    cout << "You already guessed: ";

	    //print the already guessed letters array
	    for(unsigned int i = 0; i < guessedLetters.size(); i++)
	    {
		cout << guessedLetters[i];
	    }
	    cout << endl;
	    //cout << "Guessed Word: " << guessedWord << endl;
	    //cout << "guess: " << guess[0] << endl;
	    //cout << "Current Word: " << currentWord << endl;
	}

	else
	{
	    //increase the wrong guesses
	    ++wrongGuesses;
	    Clear();
	    UpdateHangman(wrongGuesses);

	    cout << guessedWord << endl;
	    cout << "You already guessed: ";

	    //print the already guessed array
	    for(unsigned int i = 0; i < guessedLetters.size(); i++)
	    {
		cout << guessedLetters[i];
	    }
	    cout << endl;
	    cout << "Sorry that's not in the word!\t" << "you got: " << 8  - wrongGuesses << " chances left"<< endl;
	}

	//if the user gets more than 8 wrong the game is over 
	if(wrongGuesses >= 8)
	{
	    cout << "Game Over" << endl;
	    cout << "The word was: " << currentWord << endl;
	    break;
	}

	//if no * are found in the guessedWord the user have won 
	if(guessedWord.find('*') == string::npos)
	{
	    cout << "You won!, Thanks for playing :)" << endl;
	    break;
	}
    }
}

void UpdateHangman(int hangmanNumber)
{
    switch(hangmanNumber)
    {
	case 0:
	    Hangman1();
	    break;
	case 1:
	    Hangman1();
	    break;
	case 2:
	    Hangman2();
	    break;
	case 3:
	    Hangman3();
	    break;
	case 4:
	    Hangman4();
	    break;
	case 5:
	    Hangman5();
	    break;
	case 6:
	    Hangman6();
	    break;
	case 7:
	    Hangman7();
	    break;
	case 8:
	    Hangman8();
	    break;
	default:
	    std::cout << "Error! default case!" << std::endl;
	    break;
    }

}

void PrintWord(std::string currentWord)
{
    std::cout << currentWord << std::endl;
    for(unsigned int i = 0; i < currentWord.size(); i++)
    {
	if(currentWord[i] == ' ')
	{
	    std::cout << " ";
	}
	else
	{
	    std::cout << "*";
	}
    }

    std::cout << std::endl;
}

//function to copy data from the file to the passed in array
void FiletoArray(std::ifstream &file, std::vector<std::string> &array, std::string &currentLine)
{
    //open the file
    if(file.is_open())
    {
	//read the data from the file line by line and store it in the array
	while(file)
	{
	    getline(file, currentLine);
	    if(!currentLine.empty())
	    {
		array.push_back(currentLine);
	    }
	}
    }
    else
    {
	std::cout << "Cant open file" << std::endl;
    }
    file.close();
}
void Clear()
{
    for(int i = 0; i <= 75; i++)
    {
	std::cout << std::endl;
    }
}

void Hangman1()
{
    std::cout << 
	"								\n"
	"               ||--------------------------------		\n"
	"               ||						\n"
	"               ||						\n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       \n"
	"                                                               \n"
	"                                                                "<< std::endl;
}

void Hangman2()
{
    std::cout << 
	"                                                               \n"
	"               ||--------------------------------              \n"
	"               ||                  |                           \n"
	"               ||                  |                           \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       \n"
	"                                                               \n"
	"                                                                "<< std::endl;
}

void Hangman3()
{
    std::cout << 
	"                                                               \n"
	"               ||--------------------------------              \n"
	"               ||                  |                           \n"
	"               ||                  |                           \n"
	"               ||                  O                           \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       \n"
	"                                                               \n"
	"                                                                "<< std::endl;
}

void Hangman4()
{
    std::cout << 
	"                                                               \n"
	"               ||--------------------------------              \n"
	"               ||                  |                           \n"
	"               ||                  |                           \n"
	"               ||                  O                           \n"
	"               ||                  X                           \n"
	"               ||                  X                           \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       \n"
	"                                                               \n"
	"                                                                "<< std::endl;
}

void Hangman5()
{
    std::cout << 
	"                                                               \n"
	"               ||--------------------------------              \n"
	"               ||                  |                           \n"
	"               ||                  |                           \n"
	"               ||                  O                           \n"
	"               ||                  X                           \n"
	"               ||                  X                           \n"
	"               ||                 /                            \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       \n"
	"                                                               \n"
	"                                                                "<< std::endl;
}
void Hangman6()
{
    std::cout << 
	"                                                               \n"
	"               ||--------------------------------              \n"
	"               ||                  |                           \n"
	"               ||                  |                           \n"
	"               ||                  O                           \n"
	"               ||                  X                           \n"
	"               ||                  X                           \n"
	"               ||                 / \\                         \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               ||                                              \n"
	"               XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       \n"
	"                                                               \n"
	"                                                                "<< std::endl;
}
void Hangman7()
{
    std::cout << 
	"								\n"
	"		||--------------------------------		\n"
	"		||		    |				\n"
	"		||		    |				\n"
	"		||		    O				\n"
	"		||		    X\\				\n"
	"		||		    X				\n"
	"		||		   / \\				\n"
	"		||						\n"
	"		||						\n"
	"		||						\n"
	"		||						\n"
	"		||						\n"
	"		||						\n"
	"		||						\n"
	"		XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX	\n"
	"								\n"
	"								 "<< std::endl;
}
void Hangman8()
{
    std::cout << 
	"                                                               \n"
	"		||--------------------------------              \n"
	"		||		    |                           \n"
	"		||		    |                           \n"
	"		||		    O                           \n"
	"		||		   /X\\                         \n"
	"		||		    X				\n"
	"		||		   / \\				\n"
	"		||						\n"
	"		||						\n"
	"		||						\n"
	"		||						\n"
	"		||						\n"
	"		||						\n"
	"		||						\n"
	"		XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX	\n"
	"								\n"
	"								   "<< std::endl;
}
