//  ************* IT STEP *************
// FIRST ROBO SUMO COMPETITION LVIV 2024
//  ***********************************

#define startSwitch 12
#define buzzer 11

const int dirPin_1 = 3, stepPin_1 = 4, enPin_1 = 5;
const int dirPin_2 = 8, stepPin_2 = 9, enPin_2 = 10;

bool switchState, clockwise = false;

void setup()
{
    Serial.begin(9600);

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
        delay(random(2000, 4000));

        // звуковий сигнал
        tone(buzzer, 2000, 500);

        // старт двигунів
        digitalWrite(enPin_1, LOW);
        digitalWrite(enPin_2, LOW);
        while (switchState)
        {
            int rand_number = random(1, 4);
            if (rand_number == 1)
            {
                // рух вниз
                clockwise = !clockwise;
            }
            else if (rand_number == 2)
            {
                // нікуди не рухаємось, залишаємось в рівень з поверхністю
                delay(random(1000, 4000));
                continue;
            }
            // в іншому випадку, при генерації 3-йки, рух вгору 
            
            // старт руху
            start_rotate();
            delay(random(1000, 4000));

            // для повернення в позицію з якої почали
            clockwise = !clockwise;
            start_rotate();

            // повторно перевіряємо положення тумблера
            switchState = digitalRead(startSwitch);
            delay(random(1000, 4000));
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


void start_rotate()
{
    digitalWrite(dirPin_1, !clockwise);
    digitalWrite(dirPin_2, clockwise);
    for (int x = 0; x < 1100; x++)
    {
        digitalWrite(stepPin_1, HIGH);
        digitalWrite(stepPin_2, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin_1, LOW);
        digitalWrite(stepPin_2, LOW);
        delayMicroseconds(500);
    }
}
