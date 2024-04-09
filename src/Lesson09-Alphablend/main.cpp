#include <stdio.h>
#include "WinApp.h"
int main(void)
{
	printf("Lesson09-alphablend\n");
	
	WinApp  app;
	app.Initialize(800,600,"Lesson09-alphablend");
	app.Run();
   
}
