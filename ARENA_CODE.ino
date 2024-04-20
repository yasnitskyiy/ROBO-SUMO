//  ************* IT STEP *************
// FIRST ROBO SUMO COMPETITION LVIV 2024
//  ***********************************

#define startSwitch 12
#define buzzer 11

const int dirPin_1 = 3, stepPin_1 = 4, enPin_1 = 5;
const int dirPin_2 = 8, stepPin_2 = 9, enPin_2 = 10;
const int min_delay = 2000, max_delay = 5000;

bool switchState, clockwise = false;
int rand_number;

bool inZero = true;
int start_step, end_step;

void setup()
{
    randomSeed(analogRead(0));
    pinMode(startSwitch, INPUT_PULLUP);
    pinMode(buzzer, OUTPUT);

    pinMode(stepPin_1, OUTPUT);
    pinMode(dirPin_1, OUTPUT);
    pinMode(enPin_1, OUTPUT);

    pinMode(stepPin_2, OUTPUT);
    pinMode(dirPin_2, OUTPUT);
    pinMode(enPin_2, OUTPUT);
}

void loop()
{
    // дізнаємось положення тумблера
    switchState = digitalRead(startSwitch);

    // якщо вкючений, стартуємо раунд
    if (switchState)
    {
        delay(random(min_delay, max_delay));

        // звуковий сигнал
        tone(buzzer, 2000, 500);

        // старт двигунів
        digitalWrite(enPin_1, LOW);
        digitalWrite(enPin_2, LOW);
        while (switchState)
        {
            rand_number = random(1, 4);
            
            // повний цикл руху поршня
            action();
        }
        
        // якщо не в нульовому положенні, повертаємось
        if(!inZero)
        {
          rand_number = 1;
          action();
        }

        // якщо в нульовому, сигналізуємо пищалкою
        if(inZero)
        {
          for(int i = 0; i < 2; i++)
          {
            tone(buzzer, 1500);
            delay(100);
            noTone(buzzer);
            delay(100);
          }
       }
    }
    else
    {
        // вимикаємо двигуни коли гра не триває
        digitalWrite(enPin_1, HIGH);
        digitalWrite(enPin_2, HIGH);
    }

    // для зменшення навантаження на ардуіно
    delay(300);
}


void start_rotate(int steps)
{
    digitalWrite(dirPin_1, !clockwise);
    digitalWrite(dirPin_2, clockwise);
    for (int x = 0; x < steps; x++)
    {
        digitalWrite(stepPin_1, HIGH);
        digitalWrite(stepPin_2, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin_1, LOW);
        digitalWrite(stepPin_2, LOW);
        delayMicroseconds(500);
    }
}

void action()
{
    if (rand_number == 1)
    {
        // рух вниз
        clockwise = !clockwise;
        if(inZero)
        {
          start_step = 1100;
          end_step = 1100;
        }
        else
        {
          start_step = 1080;
          end_step = 1100;
          inZero = !inZero;
        }
    }
    else if (rand_number == 3)
    {
        // рух вгору
        if(inZero)
        {
          start_step = 1080;
          end_step = 1100;
          inZero = !inZero;
        }
        else
        {
          start_step = 1100;
          end_step = 1100;
        }
    }
    else
    {
      // нікуди не рухаємось, залишаємось в рівень з поверхністю
        delay(random(min_delay, max_delay));
        return;
    }

    // старт руху
    start_rotate(start_step);
    delay(random(min_delay, max_delay));
    
    // для повернення в позицію з якої почали
    clockwise = !clockwise;
    start_rotate(end_step);
    
    // повторно перевіряємо положення тумблера
    switchState = digitalRead(startSwitch);
    delay(random(min_delay, max_delay));
    
    // повертаємо у початкове положення
    clockwise = false;
}
