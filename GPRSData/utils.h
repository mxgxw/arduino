// Este archivo contiene las definiciones
// de funciones para evitar errores de compilador
void clearBuffer();
void appendToBuffer(char c);
void pushSlow(char* command,int charaterDelay=100,int endLineDelay=1000);
bool waitForString(char* string, long waitForMilliseconds=5000);
bool waitForString(char *string, int waitForMilliseconds=5000);
void waitForData(int wait_delay);
void bridge();
