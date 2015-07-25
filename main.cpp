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

//when the fucntion is called it store the files content into a passed array
void FiletoArray(std::ifstream &file, std::vector<std::string> &array, std::string &currentLine);
void MainLoop(std::string currentWord);		//the main game loop
void Clear();					//prints 20 empty lines
void Hangman1();
void Hangman2();
void Hangman3();
void Hangman4();
void Hangman5();
void Hangman6();
void Hangman7();
void Hangman8();
void UpdateHangman(int hangmanNumber);
void PrintWord(std::string currentWord);	//iterate throught the word and prints a space or a * for a letter

int main(int argc, char* argv[])
{
  using namespace std;

  //variables to store the name of the files(the default ones)
  string countryTextFile = "Countries.txt";
  string foodTextFile = "Food.txt";
  string technologyTextFile = "Technology.txt";
 
  //if the user passes in the name of the file, overide the default variable to the passed in variable  
  if(argc > 1)
  {
    countryTextFile = argv[1];
    foodTextFile = argv[2];
    technologyTextFile = argv[3];
  }
  
  string currentLine;
  ifstream countreisFile(countryTextFile);
  ifstream foodFile(foodTextFile);
  ifstream technologyFile(technologyTextFile);
  
  std::vector<std::string> countriesArray{};
  std::vector<std::string> foodArray{};
  std::vector<std::string> technologyArray{};
  
  FiletoArray(countreisFile, countriesArray, currentLine);
  FiletoArray(foodFile, foodArray, currentLine);
  FiletoArray(technologyFile, technologyArray, currentLine);

  
  string useresCatergory = "";
  int useresCatergoryNumber = 0;
  bool isValidCatergory = false;
  Catergories catergory = Catergories::Uninitialized;

  // 
  while(!isValidCatergory)
  {
    cout << "Choose the number of catergory to play hangman :)" << endl;
    cout << "1.Countries" << "\t" "2.Food" << "\t" << "\t" << "3.Techonlogy" << endl;
    
    getline(cin, useresCatergory);
    useresCatergoryNumber = atoi(useresCatergory.c_str());
    
    if(useresCatergoryNumber == 1)
    {
      cout << "Countries? niceee" << endl;
      catergory = Catergories::Countries;
      isValidCatergory = true;
    }
    if(useresCatergoryNumber == 2)
    {
      cout << "Food? niceee" << endl;
      catergory = Catergories::Food;
      isValidCatergory = true;
      
    }
    if(useresCatergoryNumber == 3)
    {
      cout << "Technology? niceee" << endl;   
      catergory = Catergories::Technology;
      isValidCatergory = true;

    }
  }
  int randomNumberGenerated;
  string currentWord;
  
  if(catergory == Catergories::Countries)
  {
    srand(time(0));
    randomNumberGenerated = rand()%countriesArray.size();
    currentWord = countriesArray[randomNumberGenerated];
    PrintWord(currentWord);
    MainLoop(currentWord);
  }
  else if(catergory == Catergories::Food)
  {
    srand(time(0));
    randomNumberGenerated = rand()%foodArray.size();
    currentWord = foodArray[randomNumberGenerated];
    PrintWord(currentWord);
    MainLoop(currentWord);
  }
  
  else if(catergory == Catergories::Technology)
  {
    srand(time(0));
    randomNumberGenerated = rand()%technologyArray.size();
    currentWord = technologyArray[randomNumberGenerated];
    PrintWord(currentWord);
    MainLoop(currentWord);
  }
  
  return 0;
}

void MainLoop(std::string  currentWord)
{
  using namespace std;
  
  int wrongGuesses = 0;
  UpdateHangman(wrongGuesses);
  
  while(1)
  {
    
    bool aValidLetter = false;
    string guess;
    
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
    
  std::transform(guess.begin(), guess.end(), guess.begin(), ::tolower);

  if(currentWord.find(guess.c_str()) != string::npos)
  {
    //if guess is correct
    Clear();
    UpdateHangman(wrongGuesses);

    for(unsigned int i = 0; i < currentWord.size(); i++)
    {
      if(currentWord[i] == ' ')
      {
	  std::cout << " ";
      }
      else
      {
	if(currentWord[i] == guess[0])
	{
	  std::cout << guess;
	}
	else
	{
	  std::cout << "*";
	}
      }
      
    }
    cout << endl;
  }
  
  else
  {
    wrongGuesses++;
    Clear();
    UpdateHangman(wrongGuesses);
    cout << "Sorry that's not in the word!\t" << "you got: " << 8 - wrongGuesses << " chances left"<< endl;
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
   cout << endl;
  }
  if(wrongGuesses == 8)
  {
    cout << "Game Over" << endl;
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
      std::cout << "Error!" << std::endl;
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

void FiletoArray(std::ifstream &file, std::vector<std::string> &array, std::string &currentLine)
{
  if(file.is_open())
  {
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
