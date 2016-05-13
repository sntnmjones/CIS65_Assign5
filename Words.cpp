#include "Words.h"

//////////////////////
// Public Functions //
//////////////////////

Words::Words()
{
	magicBufferLength = 0;
	magicWordCount = 0;
	contestBufferLength = 0;
	contestCount = 0;
	contestantCount = 0;
	wordsMatching = 0;
	fileout.open("output.txt");
}

void Words::getMagicWords(std::string fileName)
{
	openFile(fileName);
	magicBufferLength = getBufferLength(filein);
	magicBuffer = fillBuffer(filein, fileName);

	///////////////////////////////////////////
	// counts amount of words in "magic.txt" //
	///////////////////////////////////////////
	unsigned int a = 0;
	while (a < magicBufferLength)
	{
		if (magicBuffer[a] == 10)
		{
			magicWordCount++;
			a++;
		}
		else
		{
			a++;
		}
	}
	////////////////////////////////////////////////////////////////////
	// for loop through magicBuffer assigning strings to magicArray[] //
	////////////////////////////////////////////////////////////////////
	a = 0;
	for (int i = 0; i < magicWordCount; i++)
	{
		std::string str = "";
		while (magicBuffer[a] != 10)
		{
			if (magicBuffer[a] > 64 && magicBuffer[a] < 91)
			{
				str += magicBuffer[a];
				a++;
			}
			else if (magicBuffer[a] > 96 && magicBuffer[a] < 123)
			{
				str += magicBuffer[a];
				a++;
			}
			else if (magicBuffer[a] == 32)
			{
				str += magicBuffer[a];
				a++;
			}
			else
			{
				a++;
			}
		}
		magicArray[i] = str;
		a++;
	}
	filein.close();
}

void Words::getContestantWords(std::string fileName)
{
	openFile(fileName);
	contestBufferLength = getBufferLength(filein);
	contestBuffer = fillBuffer(filein, fileName);
	////////////////////////////////////////////////////
	// counts number of contestants in "testpass.txt" //
	////////////////////////////////////////////////////
	unsigned int a = 0;
	while (a < contestBufferLength)
	{
		if (contestBuffer[a] == 10 || contestBuffer[a] == 32)
		{
			contestCount++;
			if (contestBuffer[a] == 10)
			{
				contestantCount++;
			}
			a++;
		}
		else
		{
			a++;
		}
	}
	contestantCount = contestantCount / 2;	// this is used in compareWords();
	//////////////////////////////////////////////////////////////////////////
	// for loop through contestBuffer assigning names to contestArray[]s    //
	//////////////////////////////////////////////////////////////////////////
	a = 0;
	int lineCounter = 0;
	int nameCounter = -1;
	int sentCounter = 0;

	for (int i = 0; i < contestCount; i++)
	{
		std::string str = "";
		while (contestBuffer[a] != 10)
		{
			if (contestBuffer[a] > 64 && contestBuffer[a] < 91)
			{
				str += contestBuffer[a];
				a++;
			}
			else if (contestBuffer[a] > 96 && contestBuffer[a] < 123)
			{
				str += contestBuffer[a];
				a++;
			}
			else if (contestBuffer[a] == 32)
			{
				break;
			}
			else
			{
				a++;
			}
		}
		if (contestBuffer[a] == 10)
		{
			if (lineCounter % 2 == 0)
			{
				nameCounter++;
				contestArray[nameCounter][sentCounter] = str;
				sentCounter++;
				lineCounter++;
			}
			else
			{
				contestArray[nameCounter][sentCounter] = str;
				sentCounter = 0;
				lineCounter++;
			}
			a++;
		}
		else if (contestBuffer[a] == 32)
		{
			contestArray[nameCounter][sentCounter] = str;
			sentCounter++;
			a++;
		}
	}
	filein.close();
}

void Words::compareWords()
{
	using namespace std;

	/////////////////
	// Sort Arrays //
	/////////////////
	std::string temp = "";
	int it = 0;
	// sorts magicArray
	for (int i = 0; i < MAGIC_ARRAY_NUM; i++)
	{
		while (it < magicWordCount)
		{
			if (magicArray[it] == "" || magicArray[it + 1] == "")
			{
				it++;
				continue;
			}
			else if (magicArray[it] > magicArray[it + 1])
			{
				temp = magicArray[it];
				magicArray[it] = magicArray[it + 1];
				magicArray[it + 1] = temp;
			}
			it++;
		}
		it = 0;
	}
	temp = "";
	it = 1;
	// sorts contestArray
	for (int it2 = 0; it2 < CONTESTANT_ARRAY_NUM; it2++)	// loops for amount of contestants
	{
		for (int i = 1; i < CONTESTANT_SENT_ARRAY_NUM; i++)	// loops for amount of words in sentence
		{
			while (it < contestCount)
			{
				if (contestArray[it2][it] == "" || contestArray[it2][it + 1] == "")
				{
					it++;
					continue;
				}
				else if (contestArray[it2][it] > contestArray[it2][it + 1])
				{
					temp = contestArray[it2][it];
					contestArray[it2][it] = contestArray[it2][it + 1];
					contestArray[it2][it + 1] = temp;
				}
				it++;
			}
			it = 1;
		}
	}
	/////////////////////////////////////////
	// Does the word comparision operation //
	/////////////////////////////////////////
	int a = 0;	// current magic word counter
	int c = 0;	// current contestant counter
	int w = 1;	// current contestant word counter

	for (int i = 0; i < contestantCount; i++)	// goes for the amount of contestants
	{
		string wordsNotFound[MAGIC_ARRAY_NUM] = {};
		int notFoundCounter = 0;

		while (a < magicWordCount)	// loops the amount of magic words in "magic.txt"
		{
			bool found = false;
			int first = 0;
			int last = (CONTESTANT_SENT_ARRAY_NUM - 1);
			bool moreToSearch = first <= last;
			int midPoint = 0;

			while (moreToSearch && !found)
			{
				midPoint = (first + last) / 2;
				if ((magicArray[a] < contestArray[i][midPoint]) || contestArray[i][midPoint] == "")
				{
					last = midPoint - 1;
					moreToSearch = first <= last;
					continue;
				}
				else if (magicArray[a] > contestArray[i][midPoint])
				{
					first = midPoint + 1;
					moreToSearch = first <= last;
					continue;
				}
				else if (magicArray[a] == contestArray[i][midPoint])
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				wordsNotFound[notFoundCounter] = magicArray[a];
				notFoundCounter++;
			}
			
			a++;	// next magic word
		}
		if (notFoundCounter == 0)
		{
			fileout << "Congratulations " << contestArray[i][0] << "! You named the correct magic words!" << endl;
			cout << "Congratulations " << contestArray[i][0] << "! You named the correct magic words!" << endl;
		}
		else
		{
			fileout << contestArray[i][0] << ", you failed to name these magic words:\n\n";
			cout << contestArray[i][0] << ", you failed to name these magic words:\n\n";
			for (int z = 0; z < notFoundCounter; z++)
			{
				fileout << wordsNotFound[z] << endl;
				cout << wordsNotFound[z] << endl;
			}
			fileout << endl;
			cout << endl;
		}
		
		c++;	// next contestant
		a = 0;	// resets word count to prepare to go back through list
	}
}

Words::~Words()
{
	delete[] magicBuffer;
	delete[] contestBuffer;
	fileout.close();
}

///////////////////////
// Private Functions //
///////////////////////

void Words::openFile(std::string str)
{
	filein.open(str);
}

int Words::getBufferLength(std::ifstream& inf)
{
	unsigned int len = 0;
	inf.seekg(0, inf.end);
	len = (int)inf.tellg();
	inf.seekg(0, inf.beg);
	return len;
}

char* Words::fillBuffer(std::ifstream& in, std::string fileName)
{
	using namespace std;

	do
	{
		char* buffer;
		if (in.is_open())
		{
			unsigned int bufferLength = getBufferLength(in);


			buffer = new char[bufferLength];
			in.read(buffer, bufferLength);
			return buffer;
		}
		else
		{
			cout << "Input file is not open..." << endl;
			cout << "Attempting to open file..." << endl;
			in.open(fileName);
			buffer = new char;
			return buffer;
			continue;
		}
		delete[] buffer;
	} while (!in.is_open());
}

