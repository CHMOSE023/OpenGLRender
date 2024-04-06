#include <stdio.h>
#include "WinApp.h"
int main(void)
{
	printf("Lesson05-camera\n");
	
	WinApp  app;
	app.Initialize(800,600,"Lesson05-camera");
	app.Run();
   
}
