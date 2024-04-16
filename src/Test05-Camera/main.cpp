#include <stdio.h>
#include "WinApp.h"
int main(void)
{
	printf("Test05-Camera\n");
	
	WinApp  app;
	app.Initialize(800,600,"Test05-Camera");
	app.Run();
   
}
