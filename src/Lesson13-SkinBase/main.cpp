#include <stdio.h>
#include "WinApp.h"
int main(void)
{
	printf("Lesson13-SkinBase\n");	
	WinApp  app;	
	app.Initialize(800, 600, "Lesson13-SkinBase");	
	app.Run();
   
}
