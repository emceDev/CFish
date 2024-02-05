const int btnPin = 7;
const int sensorPin = A0;
const int motorPin1 = 5;
const int motorPin2 = 6;
const int rel_cap = 7;
int rel_revs = 0;
int max_revs = 0;
int line = 0;
bool reel_in = true;

// Button things
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 1000; // Adjust this debounce delay as needed
bool buttonPressed = false;
unsigned long setupTimeout = 10000; // Adjust this timeout value as needed (in milliseconds)

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing...");

  pinMode(btnPin, INPUT);
  pinMode(sensorPin, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  unsigned long startTime = millis();
  while (millis() - startTime < 10000)
  {
    if (digitalRead(btnPin) == HIGH)
    {
      // Button is pressed, increment click count
      Serial.println("clicked");
      line = line + 50;
      delay(500); // Debounce delay to prevent multiple counts for a single press
    }
  }

  max_revs = line / rel_cap; // Calculate initial number of revolutions based on line length

  Serial.print("Line length set to: ");
  Serial.print(line);
  Serial.println(" units");
  Serial.print("Maximum revolutions to perform: ");
  Serial.println(max_revs);

  Serial.println("Initialization complete.");
}

void loop()
{
  // Run constant check if sensor hits <300, if true, change rel_revs
  if (analogRead(sensorPin) < 300)
  {
    if (reel_in)
    {
      rel_revs++;
      Serial.println("Reel in: Incrementing rel_revs");
    }
    else
    {
      rel_revs--;
      Serial.println("Reel out: Decrementing rel_revs");
    }

    // Change direction when reaching max_revs or 0
    if (rel_revs == max_revs || rel_revs == 0)
    {
      reel_in = !reel_in;
      Serial.println("Changing direction.");
    }
  }

  // Control motor direction based on reel_in
  if (reel_in)
  {
    reel_in_function();
  }
  else
  {
    reel_out_function();
  }
}

void reel_in_function()
{
  // Motor control for reeling in
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);

  // Add a delay as needed
  delay(100);

  Serial.println("Reeling in...");
}

void reel_out_function()
{
  // Motor control for reeling out
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);

  // Add a delay as needed
  delay(100);

  Serial.println("Reeling out...");
}

void waitForUserInput()
{
  int buttonState = digitalRead(btnPin);

  if (buttonState == HIGH)
  {

    Serial.println("Clicked");
    line += 50;
  }

  delay(10);
}
