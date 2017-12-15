// Initialize LEDs to designated pins
int rows = 4;
int columns = 16;
int layer[4] = {A3, A2, A1, A0};
int cols[16] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, A5, A4};

// Standard delay for all transitions
int del = 250;

void setup() 
{
  // Initialize the pins to OUTPUT
  for(int i = 0;i < rows;i++)
  {
    pinMode(layer[i], OUTPUT);
  }
  for(int i = 0;i < columns;i++)
  {
    pinMode(cols[i], OUTPUT);
  }
}

void loop()
{
  turnOnAll();
}

/* Turns on all LEDs*/
void turnOnAll()
{
  for(int i = 0;i < rows;i++)
  {
    digitalWrite(layer[i], HIGH);
  }
    for(int i = 0;i < columns;i++)
  {
    digitalWrite(cols[i], LOW);
  }
}

/* Turns off all LEDs*/
void turnOffAll()
{
  for(int i = 0;i < rows;i++)
  {
    digitalWrite(layer[i], LOW);
  }
    for(int i = 0;i < columns;i++)
  {
    digitalWrite(cols[i], HIGH);
  }
}

