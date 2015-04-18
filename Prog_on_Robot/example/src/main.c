#include "../h/main.h"

#include "../h/rob_strg.h"

#include "../h/search.h"
#include "../src/search.c"

#include "../h/card.h"
#include "../src/card.c"

#include "../h/list.h"
#include "../src/list.c"

// Start des Hauptprogramms

TASK( OSEK_Main_Task) {
	wait(100);
	init();			// Initialisierung des Roboters

	beep();

	init_logfile(&logbook);
	set_robot(&r);
	runbot(&r);		//Start des Suchprogramms

	beep();
	wait(10000);
	// lustiges Piepen

	TerminateTask();
}

TASK(OSEK_Task_Background)
{
  while(1){
    ecrobot_status_monitor("Hello, World!");
    systick_wait_ms(500);
  }
}


