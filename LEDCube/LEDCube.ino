
// Initialize LEDs to designated pins
int rows = 4;
int columns = 16;
int layer[4] = {A3, A2, A1, A0};
int cols[16] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, A5, A4};

int x = 0;
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
  ///turnOnAll();
  //delay(del);
  while(x == 0)
  {
    displayLetter('y');
    x = 1;
  }
}

/* Turns on all LEDs*/
void turnOnAll()
{
  for(int i = 0; i<16; i++)
  {
    digitalWrite(cols[i], LOW);
  }
  
  for(int i = 0; i<4; i++)
  {
    digitalWrite(layer[i], HIGH);
  }
}

/* Turns off all LEDs*/
void turnOffAll()
{
  for(int i = 0; i<16; i++)
  {
    digitalWrite(cols[i], HIGH);
  }
  
  for(int i = 0; i<4; i++)
  {
    digitalWrite(layer[i], LOW);
  }
}

/* 3D Coordinate system to turn on a LED */
void turnOnLED(int x, int y, int z)
{
  digitalWrite(layer[z], HIGH);
  digitalWrite(cols[x + (4 * y)], LOW);
}

/* 3D Coordinate system to turn off a LED*/
void turnOffLED(int x, int y, int z)
{
  digitalWrite(layer[z], LOW);
  digitalWrite(cols[x + (4 * y)], HIGH);
}


void displayLetter(char letter)
{
  turnOffAll();
  switch(letter)
  {
    case 'a':
      for(int i = 0;i < columns;i+=4)
      {
        digitalWrite(cols[i], LOW);
        digitalWrite(cols[i+3], LOW);
      }
      for(int i = 5;i < 7;i++)
      {
        digitalWrite(cols[i], LOW);
        digitalWrite(cols[i+8], LOW);
      }
      
      // Turn on all rows layer by layer
      for(int i = 0; i<rows; i++)
      {
        digitalWrite(layer[i], HIGH);
        delay(75);
        if(i != rows - 1 && i != 0)
        {
          digitalWrite(layer[i + 1], LOW);
        }
      }
    break;

    case 'h':
      for(int i = 0;i < columns;i+=4)
      {
        digitalWrite(cols[i], LOW);
        digitalWrite(cols[i+3], LOW);
      }
      for(int i = 5;i < 7;i++)
      {
        digitalWrite(cols[i], LOW);
        digitalWrite(cols[i+4], LOW);
      }

      // Turn on all rows layer by layer
      for(int i = 0; i<rows; i++)
      {
        digitalWrite(layer[i], HIGH);
        delay(75);
        if(i != rows - 1 && i != 0)
        {
          digitalWrite(layer[i + 1], LOW);
        }
      }
    break;

    case 'p':
      for(int i = 0;i < columns;i+=4)
      {
        digitalWrite(cols[i], LOW);
      }
      for(int i = 5;i < 7;i++)
      {
        digitalWrite(cols[i], LOW);
        digitalWrite(cols[i+8], LOW);
      }
      
      for(int i = rows - 1; i >= 0;i--)
      {
        digitalWrite(layer[i], HIGH);
        turnOnLED(3, 2, i);
        delay(75);
        if(i != rows - 1 && i != 0)
        {
          digitalWrite(layer[i + 1], LOW);
          turnOffLED(3, 2, i);
        }
      }
    break;

    case 'y':
      int c = 0;
      int m = 0;
      for(int i = 12;i >= 0;i -= 3)
      {
        digitalWrite(cols[i - m], LOW);
        digitalWrite(cols[i + 3 - c + m], LOW);
        c++;
        if(c == 3)
        {
          m = 1;
        }
      }

      for(int i = 0; i<rows; i++)
      {
        digitalWrite(layer[i], HIGH);
        delay(75);
        if(i != rows - 1 && i != 0)
        {
          digitalWrite(layer[i + 1], LOW);
        }
      }
    break;
    
  }
  delay(del);
}






