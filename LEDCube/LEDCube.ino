  
// Initialize LEDs to designated pins
int rows = 4;
int columns = 16;
int layer[4] = {A3, A2, A1, A0};
int cols[16] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, A5, A4};

// Standard delay for all transitions
int del = 250;

/* Initial setup of components */
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

/* Infinite Loop */
void loop()
{
  // Pattern order and selection

  displayWords("Happy 21 Anniversary");
  delay(del);
  flickerLEDs(false);
  cascadeLayer();
  cascadeLayerGroup();
  spiral();
  cascadeColumn();
  circleEdge();
  randomFlicker();
  randomRain();
  flickerAll();
  propellerRotate();
  spiral();
  flickerLEDs(true);
  turnOffAll();
  delay(2000);
}

/* Turns on all LEDs */
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

/* Turns off all LEDs */
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

/* 3D Coordinate system to turn on an individual LED */
void turnOnLED(int x, int y, int z)
{
  digitalWrite(layer[z], HIGH);
  digitalWrite(cols[x + (4 * y)], LOW);
}

/* 3D Coordinate system to turn off a individual LED */
void turnOffLED(int x, int y, int z)
{
  digitalWrite(layer[z], LOW);
  digitalWrite(cols[x + (4 * y)], HIGH);
}

/* Turns off only the LED rows */
void turnOffRows()
{
  for(int i = 0; i<4; i++)
  {
    digitalWrite(layer[i], LOW);
  }
}

/* Turns on only the LED rows */
void turnOnRows()
{
  for(int i = 0; i<4; i++)
  {
    digitalWrite(layer[i], HIGH);
  }
}

/* Turns on only the LED columns */
void turnOnCols()
{
  for(int i = 0; i<16; i++)
  {
    digitalWrite(cols[i], LOW);
  }
}

/* Turns off only the LED columns */
void turnOffCols()
{
  for(int i = 0; i<16; i++)
  {
    digitalWrite(cols[i], HIGH);
  }
}

/********** PATTERNS **********/

/* Flickers all LEDs with an increasing/decreasing time interval */
void flickerLEDs(bool rev)
{
  int timer = 150;
  if (!rev)
  {
    for(int i = timer;i >= 5;i -= 5)
    {
      turnOnAll();
      delay(i);
      turnOffAll();
      delay(i);
    }
    turnOnAll();
  }
  else
  {
    turnOnAll();
    for(int i = 5;i < timer;i += 5)
    {
      turnOffAll();
      delay(i);
      turnOnAll();
      delay(i);
    }
    turnOnAll();
  }
}

/* Cascade LEDs per row */
void cascadeLayer()
{
  int cTime = 75;
  
  turnOnAll();

  // Number of times to repeat the whole pattern
  for(int i = 0;i < 5;i++)
  {
    // Turns off all LED rows and turns them back on in
    // a reverse order
    
    for(int r = 0;r < rows;r++)
    {
      digitalWrite(layer[r], LOW);
      delay(cTime);
    }
    delay(cTime);
    
    for(int r = rows - 1;r >= 0;r--)
    {
      digitalWrite(layer[r], HIGH);
      delay(cTime);
    }
    delay(cTime);
    
    for(int r = rows - 1;r >= 0;r--)
    {
      digitalWrite(layer[r], LOW);
      delay(cTime);
    }
    delay(cTime);
    
    for(int r = 0;r < rows;r++)
    {
      digitalWrite(layer[r], HIGH);
      delay(cTime);
    }
    delay(cTime);
  }
}

/* Cascade in groups */
void cascadeLayerGroup()
{
  int timer = 75;
  
  turnOffRows();
  // Number of times to repeat the whole pattern
  for(int times = 0; times < 5;times++)
  {
    for(int x = 0; x < 1;x++)
    { 
      for(int i = 0; i < rows;i++)
      {
        digitalWrite(layer[i], HIGH);
        delay(timer);
        digitalWrite(layer[i], LOW);
      }
      for(int i = rows - 1; i >= 0;i--)
      {
        digitalWrite(layer[i], HIGH);
        delay(timer);
        digitalWrite(layer[i], LOW);
      }
    }
    for(int i = 0; i < rows;i++)
    {
      digitalWrite(layer[i], 1);
      delay(timer);
    }
    for(int i = rows; i >= 0;i--)
    {
      digitalWrite(layer[i], 0);
      delay(timer);
    }
  }
}

/* Cascade LEDs per column */
void cascadeColumn()
{
  int timer = 75;

  turnOffAll();
  turnOnRows();
  for(int times = 0;times < 3;times++)
  {
    for(int i = 0;i < columns;i++)
    {
      digitalWrite(cols[i], LOW);
      delay(timer);
    }
    delay(timer);
    for(int i = 0;i < columns;i++)
    {
      digitalWrite(cols[i], HIGH);
      delay(timer);
    }
    delay(timer);
    for(int i = 0;i < columns;i+=4)
    {
      int temp = 12 - i;
      for(int j = temp;j < temp+4;j++)
      {
        digitalWrite(cols[j], LOW);
        delay(timer);
      }
    }
    delay(timer);
    for(int i = 0;i < columns;i+=4)
    {
      int temp = 12 - i;
      for(int j = temp;j < temp+4;j++)
      {
        digitalWrite(cols[j], HIGH);
        delay(timer);
      }
    }
  }
}

/* Spiral pattern in columns (counter-clockwise and clockwise) */
void spiral()
{
  turnOnAll();
  int timer = 60;
  int cclockMatrix[] = {0, 1, 2, 3, 7, 11, 15, 14, 13, 12, 8, 4, 5, 6, 10, 9};
  int clockMatrix[] = {0, 4, 8, 12, 13, 14, 15, 11, 7, 3, 2, 1, 5, 9, 10, 6};
  for(int i = 0; i<6; i++)
  {
    // Turns off in a counter clockwise spiral
    for(int s = 0;s <= columns;s++)
    {
      digitalWrite(cols[cclockMatrix[s]], HIGH);
      delay(timer);
    }
    delay(timer);

    // Turns on in a clockwise spiral
    for(int s = columns - 1;s >= 0;s--)
    {
      digitalWrite(cols[cclockMatrix[s]], LOW);
      delay(timer);
    }
    delay(timer);

    // Turns off in a clockwise spiral
    for(int s = 0;s <= columns;s++)
    {
      digitalWrite(cols[clockMatrix[s]], HIGH);
      delay(timer);
    }
    delay(timer);

    // Turns on in a clockwise spiral
    for(int s = columns - 1;s >= 0;s--)
    {
      digitalWrite(cols[clockMatrix[s]], LOW);
      delay(timer);
    }
  }
}

/* Rotation pattern that keeps rotating around the edges of the LED cube */
void circleEdge()
{
  int circle[] = {0, 4, 8, 12, 13, 14, 15, 11, 7, 3, 2, 1};
  for(int timer = 200;timer > 0;timer -=50)
  {
    turnOffAll();
    for(int i = rows - 1;i >= 0; i--)
    {
      digitalWrite(layer[i], HIGH);
      
      // Turns on middle 4 LEDs
      digitalWrite(cols[5], LOW);
      digitalWrite(cols[6], LOW);
      digitalWrite(cols[9], LOW);
      digitalWrite(cols[10], LOW);

      // Turns on the columns based on the pattern in the array
      for(int c = 0;c < columns - 4;c++)
      {
        if(c != 0)
          digitalWrite(cols[circle[c-1]], HIGH);
        digitalWrite(cols[circle[c]], LOW);
        delay(timer);
      }
      digitalWrite(cols[circle[columns - 5]], HIGH);
    }
  }
  turnOffAll();
}

/* Random LEDs turn on to create a disco pattern */
void randomFlicker()
{
  int timer = 10;
  turnOffAll();
  for(int i = 0;i < 255;i++)
  {
    // Generates a random layer and column
    int randLay = random(0, rows);
    int randCol = random(0, columns);

    digitalWrite(layer[randLay], HIGH);
    digitalWrite(cols[randCol], LOW);
    delay(timer);
    digitalWrite(layer[randLay], LOW);
    digitalWrite(cols[randCol], HIGH);
    delay(timer);
  }
}

/* Raining effect in random columns */
void randomRain()
{
  turnOffAll();

  int timer = 100;

  for(int i = 0;i < 30;i++)
  {
    int randCol = random(0, 16);

    digitalWrite(cols[randCol], LOW);

    for(int j = 0;j < rows;j++)
    {
      if(j != 0)
      {
        digitalWrite(layer[j - 1], LOW);
      }
      digitalWrite(layer[j], HIGH);
      delay(timer);
    }
    digitalWrite(layer[rows - 1], LOW);
    digitalWrite(cols[randCol], HIGH);
  }
}

/* Flicker through all LEDs */
void flickerAll()
{
  turnOffAll();
  int timer = 15;
  for(int x = 0;x < 5;x++)
  {
    // LED Columns 0 - 3
    for(int count = rows - 1; count >= 0; count--)
    {
      digitalWrite(layer[count], HIGH);
      for(int i = 0; i < 4; i++)
      {
        digitalWrite(cols[i], LOW);
        delay(timer);
        digitalWrite(cols[i], HIGH);
        delay(timer);
      }
      digitalWrite(layer[count], LOW);
    }
    
    // LED Columns 4 - 8
    for(int count = 0; count < 4; count++)
    {
      digitalWrite(layer[count], HIGH);
      for(int i = 4; i < 8; i++)
      {
        digitalWrite(cols[i], LOW);
        delay(timer);
        digitalWrite(cols[i], HIGH);
        delay(timer);
      }
      digitalWrite(layer[count], LOW);
    }
    
    // LED Columns 8 - 11
    for(int count = rows - 1; count >= 0; count--)
    {
      digitalWrite(layer[count], HIGH);
      for(int i = 8; i < 12; i++)
      {
        digitalWrite(cols[i], LOW);
        delay(timer);
        digitalWrite(cols[i], HIGH);
        delay(x);
      }
      digitalWrite(layer[count], LOW);
    }
    
    // LED Columns 12 - 15
    for(int count = 0; count < rows; count++)
    {
      digitalWrite(layer[count], HIGH);
      for(int i = 12; i < 16; i++)
      {
        digitalWrite(cols[i], LOW);
        delay(timer);
        digitalWrite(cols[i], HIGH);
        delay(timer);
      }
      digitalWrite(layer[count], LOW);
    }
  }
}

/* Generates a propeller rotating pattern */
void propellerRotate()
{
  turnOffAll();
  int timer = 90;

  for(int i = rows - 1;i >= 0;i--)
  {
    for(int rot = 0;rot < 6;rot++)
    {
      digitalWrite(layer[i], HIGH);

      // A1
      turnOffCols();
      digitalWrite(cols[0], 0);
      digitalWrite(cols[5], 0);
      digitalWrite(cols[10], 0);
      digitalWrite(cols[15], 0);
      delay(timer);
      
      // B1
      turnOffCols();
      digitalWrite(cols[4], 0);
      digitalWrite(cols[5], 0);
      digitalWrite(cols[10], 0);
      digitalWrite(cols[11], 0);
      delay(timer);
      
      // C1
      turnOffCols();
      digitalWrite(cols[6], 0);
      digitalWrite(cols[7], 0);
      digitalWrite(cols[8], 0);
      digitalWrite(cols[9], 0);
      delay(timer);
      
      // D1
      turnOffCols();
      digitalWrite(cols[3], 0);
      digitalWrite(cols[6], 0);
      digitalWrite(cols[9], 0);
      digitalWrite(cols[12], 0);
      delay(timer);
      
      // D2
      turnOffCols();
      digitalWrite(cols[2], 0);
      digitalWrite(cols[6], 0);
      digitalWrite(cols[9], 0);
      digitalWrite(cols[13], 0);
      delay(timer);
      
      // D3
      turnOffCols();
      digitalWrite(cols[1], 0);
      digitalWrite(cols[5], 0);
      digitalWrite(cols[10], 0);
      digitalWrite(cols[14], 0);
      delay(timer);
    }
  }
}

/********** ENF OF PATTERNS **********/

/* Displays words by using the displayLetter function */
void displayWords(String word)
{
  word.toLowerCase();
  for(int i = 0;i < word.length();i++)
  {
    displayLetter(word.charAt(i));
  }
}

/* Displays letter provided on the cube with a cascading effect */
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

    case 'e':
    {
      for(int i = 0;i < columns;i++)
      {
        if(i < 4 || i % 4 == 0 || i > 11)
          digitalWrite(cols[i], LOW);
      }

      for(int i = rows - 1; i >= 0;i--)
      {
        digitalWrite(layer[i], HIGH);
        turnOnLED(1, 2, i);
        turnOnLED(2, 1, i);
        turnOnLED(3, 2, i);
        delay(75);
        if(i != rows - 1 && i != -1)
        {
          digitalWrite(layer[i + 1], LOW);
          turnOnLED(1, 2, i);
          turnOnLED(2, 1, i);
          turnOnLED(3, 2, i);
        }
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

    case 'i':
    {
      for(int i = 0;i < columns;i++)
      {
        if(i != 4 && i != 7 && i != 8 && i != 11)
          digitalWrite(cols[i], LOW);
      }
      
      for(int i = rows - 1; i >= 0;i--)
      {
        digitalWrite(layer[i], HIGH);
        delay(75);
        if(i != rows - 1 && i != -1)
        {
          digitalWrite(layer[i + 1], LOW);
        }
      }
    }
    break;
    
    case 'n':
    {
      int k = 0;
      for(int i = 0;i < columns; i += 4)
      {
        digitalWrite(cols[i], LOW);
        digitalWrite(cols[i + 3], LOW);
        digitalWrite(cols[i + 3 - k], LOW);
        k++;
      }


      for(int i = rows - 1; i >= 0;i--)
      {
        digitalWrite(layer[i], HIGH);
        delay(75);
        if(i != rows - 1 && i != -1)
        {
          digitalWrite(layer[i + 1], LOW);
        }
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

    case 'r':
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
        turnOnLED(3, 0, i);
        delay(75);
        if(i != rows - 1 && i != 0)
        {
          digitalWrite(layer[i + 1], LOW);
          turnOffLED(3, 0, i);
        }
      }
    break;

    case 's':
    {
      int k = 0;
      for(int i = 0;i < rows; i ++)
      {
        digitalWrite(cols[i], LOW);
        digitalWrite(cols[i + 12], LOW);
        digitalWrite(cols[12 - (3 * i)], LOW);
        k++;
      }


      for(int i = rows - 1; i >= 0;i--)
      {
        digitalWrite(layer[i], HIGH);
        delay(75);
        if(i != rows - 1 && i != -1)
        {
          digitalWrite(layer[i + 1], LOW);
        }
      }
    }
    break;

    case 'v':
    {
      for(int i = 4;i < columns;i+=4)
      {
        digitalWrite(cols[i], LOW);
        digitalWrite(cols[i + 3], LOW);
      }

      for(int i = rows - 1; i >= 0;i--)
      {
        digitalWrite(layer[i], HIGH);
        turnOnLED(1, 1, i);
        turnOnLED(2, 1, i);
        turnOnLED(1, 0, i);
        turnOnLED(2, 0, i);
        delay(75);
        if(i != rows - 1 && i != 0)
        {
          digitalWrite(layer[i + 1], LOW);
          turnOffLED(1, 1, i);
          turnOffLED(2, 1, i);
          turnOffLED(1, 0, i);
          turnOffLED(2, 0, i);
        }
      }
    }
    break;
    
    case 'y':
    {
      int m = 0;
      for(int i = 12;i >= 0;i -= 3)
      {
        digitalWrite(cols[i - m], LOW);
        if(i <= 6)
          m = 1;
      }
      m = 0;
      for(int i = 15;i >= 0; i -= 5)
      {
         digitalWrite(cols[i + m], LOW);
         if(i <= 5)
            m = 1;
      }
      
      for(int i = rows - 1; i >= 0;i--)
      {
        digitalWrite(layer[i], HIGH);
        delay(75);
        if(i != rows - 1 && i != -1)
        {
          digitalWrite(layer[i + 1], LOW);
        }
      }
    }
    break;

    case '1':
    {
      for(int i = 0;i < columns;i++)
      {
        if((i+1) % 4 != 0 && i % 4 != 0 || i == 0)
          digitalWrite(cols[i], LOW);
      }

      for(int i = rows - 1; i >= 0;i--)
      {
        digitalWrite(layer[i], HIGH);
        delay(75);
        turnOnLED(3, 0, i);
        if(i != rows - 1 && i != 0)
        {
          digitalWrite(layer[i + 1], LOW);
          turnOffLED(3, 0, i);
        }
      }
    }
    break;

    case '2':
    { 
      for(int i = rows - 1; i >= 0;i--)
      {
        turnOnLED(0, 0, i);
        turnOnLED(1, 0, i);
        turnOnLED(2, 0, i);
        turnOnLED(3, 0, i);
        turnOnLED(0, 3, i);
        turnOnLED(1, 1, i);
        turnOnLED(2, 1, i);
        turnOnLED(3, 2, i);
        turnOnLED(1, 3, i);
        turnOnLED(2, 3, i);
        delay(75);
        if(i != 0)
        {
          turnOffLED(0, 0, i);
          turnOffLED(1, 0, i);
          turnOffLED(2, 0, i);
          turnOffLED(3, 0, i);
          turnOffLED(0, 3, i);
          turnOffLED(1, 1, i);
          turnOffLED(2, 1, i);
          turnOffLED(3, 2, i);
          turnOffLED(1, 3, i);
          turnOffLED(2, 3, i);
        }
      }
    }
    break;
    
  }
  delay(del+100);
}







