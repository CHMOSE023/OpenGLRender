#include <stdio.h>
#include "WinApp.h"
int main(void)
{
	printf("Lesson08-FrameBuffer\n");
	
	WinApp  app;
	app.Initialize(800,600,"Lesson08-FrameBuffer");
	app.Run();
   
}
