#include <stdio.h>
#include "WinApp.h"
int main(void)
{
	printf("Lesson04-mvp\n");
	
	WinApp  app;
	app.Initialize(800,600,"Lesson04-mvp");
	app.Run();
   
}
