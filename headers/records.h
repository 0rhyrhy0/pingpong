#ifndef RECORDS_H
#define RECORDS_H

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

void getPlayerNames();
void saveRecords();
int  recordsCount();
void retrieveRecords(gameResult*, int);
void showRecords(gameResult*, int);


#endif