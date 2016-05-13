#pragma once
#include <iostream>
#include <fstream>
#include <string>
constexpr int MAGIC_ARRAY_NUM = 10;
constexpr int CONTESTANT_ARRAY_NUM = 5;
constexpr int CONTESTANT_SENT_ARRAY_NUM = 100;
class Words
{
public:
	///////////////
	// functions //
	///////////////
	Words();
	/*******************************************************************************
	* Function Name:	getMagicWords()
	* Parameters:		std::string 
	* Return Value:		void
	* Purpose:			public function to allow main() to access private functions
						that relate to getting magic words together
	*******************************************************************************/
	void getMagicWords(std::string);

	/*******************************************************************************
	* Function Name:	getContestantWords()
	* Parameters:		None
	* Return Value:		void
	* Purpose:			public function to allow main() to access private functions
						that relate to getting contestant words together
	*******************************************************************************/
	void getContestantWords(std::string);

	/*******************************************************************************
	* Function Name:	compareWords()
	* Parameters:		None
	* Return Value:		void
	* Purpose:			public function to allow main() to access private functions
						that relate to comparing words
	*******************************************************************************/
	void compareWords();
	~Words();

	///////////////
	// variables //
	///////////////
	std::string magicArray[MAGIC_ARRAY_NUM];
	std::string contestArray[CONTESTANT_ARRAY_NUM][CONTESTANT_SENT_ARRAY_NUM];
private:
	///////////////
	// functions //
	///////////////
	/*******************************************************************************
	* Function Name:	openFile()
	* Parameters:		std::string
	* Return Value:		void
	* Purpose:			opens the file of the name passed in
	*******************************************************************************/
	void openFile(std::string);

	/*******************************************************************************
	* Function Name:	getBufferLength()
	* Parameters:		std::ifstream&
	* Return Value:		int
	* Purpose:			returns the length of the stream being passed in
	*******************************************************************************/
	int getBufferLength(std::ifstream&);

	/*******************************************************************************
	* Function Name:	fillBuffer()
	* Parameters:		std::ifstream&, std::string
	* Return Value:		char*
	* Purpose:			creates a new char array (deleted in destructor), and fills
						it with the chars in whatever file was passed in
	*******************************************************************************/
	char* fillBuffer(std::ifstream&, std::string);

	///////////////
	// variables //
	///////////////
	std::ifstream filein;
	std::ofstream fileout;
	unsigned int magicBufferLength;
	unsigned int contestBufferLength;
	char* magicBuffer;
	char* contestBuffer;
	int magicWordCount;
	int contestCount;
	int contestantCount;
	int wordsMatching;
};