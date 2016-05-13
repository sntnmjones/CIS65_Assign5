#include "Contestant.h"
/*******************************************************************************
* Program Name:	Compare Word Thingy
* Created Date:	5/8/16
* Created By:	Troy Jones
* Purpose:	To input words from a magic file and compare them with words from
			a contestants words
* Acknowledgements:	Red Bull for putting Kyvat back to Torro Rosso
*******************************************************************************/
int main()
{
	Contestant newContestant;
	bool wordsSame = false;

	newContestant.getMagicWords("magic.txt");	
	newContestant.getContestantWords("textpass.txt");
	newContestant.compareWords();	

	system("pause");
	return 0;
}