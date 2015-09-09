/*
The MIT License (MIT)

Copyright (c) 2015 Josh Gould

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

//gcc check_battery_status.c --std=c99 -fstack-protector-all -fpie -fPIC -o battery
#include<stdio.h>
#define CHARGE_NOW "/sys/class/power_supply/BAT0/charge_now"
#define ENERGY_NOW "/sys/class/power_supply/BAT0/energy_now"
#define CHARGE_FULL "/sys/class/power_supply/BAT0/charge_full"
#define ENERGY_FULL "/sys/class/power_supply/BAT0/energy_full"
#define STATE "/sys/class/power_supply/BAT0/state"

int main(void)
{
  FILE *fp;
  long lnum1;
  long lnum2;
  char state;
  char statz[4];

  // open state file
  if((fp = fopen(CHARGE_NOW, "r")) == NULL)
  {
    // check for stupid file name change for some batteries
    fp = fopen(ENERGY_NOW, "r");
  }
  fscanf(fp, "%ld\n", &lnum1);
  fclose(fp);

  // open state file
  if((fp = fopen(CHARGE_FULL, "r")) == NULL)
  {
    // this is the same check as above ^^
    fp = fopen(ENERGY_FULL, "r");
  }
  fscanf(fp, "%ld\n", &lnum2);
  fclose(fp);

  // load into array
  sprintf(statz, "%ld%%", (lnum1/(lnum2/100)));

  // send to stdout
  fprintf(stdout, "%s\n", statz);
  return 0;
}
