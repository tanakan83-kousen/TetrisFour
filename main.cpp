#include "header\\tetofour.h"
using namespace std;

int main(int argc, char** argv)
{
	tetofour tetofour;
	int finish = 0;
	do{
		bool success = tetofour.Initialize();
		if (success)
		{
			tetofour.RunLoop();
		}
		finish = tetofour.Finish();
		tetofour.Shutdown();
	} while (finish == 1);
	
	return 0;
}