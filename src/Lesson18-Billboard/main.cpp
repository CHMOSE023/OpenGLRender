#include <stdio.h>
#include "WinApp.h"
int main(void)
{
	printf("Lesson18-Billboard\n");
	
	WinApp  app;
	app.Initialize(800,600,"Lesson18-Billboard");
	app.Run();
   
}
