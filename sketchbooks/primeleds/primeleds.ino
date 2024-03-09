#define LED_EVEN 11
#define LED_ODD 10
#define LED_PRIME 9

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_EVEN, OUTPUT);
    pinMode(LED_ODD, OUTPUT);
    pinMode(LED_PRIME, OUTPUT);
}

bool isEven(int n) {
    if (n % 2 == 0) {
        return true;
    }

    return false;
}

bool isPrime(int n) {
    int square_root = sqrt(n);
    
    for (int i = 2; i <= square_root; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    
    return true;
}

int decideLed(int n) {
    int r = 0;

    if (isEven(n)) {
        r = 0;
        if (isPrime(n)) {
            r = 2;
        }
    } else {
        r = 1;
        if (isPrime(n)) {
            r = 3;
        }
    }

    return r;
}

void turnOffAllLeds() {
    digitalWrite(LED_EVEN, LOW);
    digitalWrite(LED_ODD, LOW);
    digitalWrite(LED_PRIME, LOW);
}

void blink (int n) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(n);
    digitalWrite(LED_BUILTIN, LOW);
}

void feedback (int n) {
    if (n < 1 && n > 4) {
        blink(500);
    }

    for (int i = 1; i == n; ++i) {
        blink(100);
    }
}

void loop() {
    int i = 1;

    do {
        if (decideLed(i) == 0) {
            feedback(1);
            /* if even and not prime */
            digitalWrite(LED_EVEN, HIGH);
            digitalWrite(LED_ODD, LOW);
            digitalWrite(LED_PRIME, LOW);
            Serial.println(String(i) + " :: EVEN");
        } else if (decideLed(i) == 1) {
            feedback(2);
            /* if odd and not prime */
            digitalWrite(LED_EVEN, LOW);
            digitalWrite(LED_ODD, HIGH);
            digitalWrite(LED_PRIME, LOW);
            Serial.println(String(i) + " :: ODD");
        } else if (decideLed(i) == 2) {
            feedback(3);
            /* if even and prime */
            digitalWrite(LED_EVEN, HIGH);
            digitalWrite(LED_ODD, LOW);
            digitalWrite(LED_PRIME, HIGH);
            Serial.println(String(i) + " :: EVEN / PRIME");
        } else if (decideLed(i) == 3) {
            feedback(4);
            /* if odd and prime */
            digitalWrite(LED_EVEN, LOW);
            digitalWrite(LED_ODD, HIGH);
            digitalWrite(LED_PRIME, HIGH);
            Serial.println(String(i) + " :: ODD / PRIME");
        }

        delay(1000);

        turnOffAllLeds();

        delay(500);

        i++;
    } while (i <= 100);
}