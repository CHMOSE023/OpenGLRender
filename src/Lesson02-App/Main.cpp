#include <stdio.h>
#include "WinApp.h"
int main(void)
{
	printf("Lesson02\n");
	
	WinApp  app;
	app.Initialize(800,600,"lesson002-App");
	app.Run();
   
}
