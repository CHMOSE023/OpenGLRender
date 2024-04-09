#include <stdio.h>
#include "WinApp.h"
int main(void)
{
	printf("Lesson10-Model\n");
	
	WinApp  app;
	app.Initialize(800,600,"Lesson10-Model");
	app.Run();
   
}
