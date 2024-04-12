#include <stdio.h>
#include "WinApp.h"
int main(void)
{
	printf("Lesson15-Culling\n");
	
	WinApp  app;
	app.Initialize(800,600,"Lesson15-Culling");
	app.Run();
   
}
