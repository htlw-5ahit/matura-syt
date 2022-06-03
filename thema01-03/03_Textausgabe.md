# Textausgabe

## sprintf

* Der Befehl `sprintf()` bietet optimale Möglichkeiten zur Ausgabeformatierung von Werten. 

Syntax:

char text[LENGTH]

`sprintf(text, "Formatierung", [variable1, variable2, veriable, …])`

| Format | Bedeutung                                                         |
|--------|-------------------------------------------------------------------|
| %d %i  | Decimal signed Integer                                            |
| %o     | Octal Integer                                                     |
| %x %X  | Hex Integer                                                       |
| %u     | Unsigned Integer                                                  |
| %c     | Character                                                         |
| %s     | String                                                            |
| %f     | Double                                                            |
| %e %E  | Double                                                            |
| %g %G  | Double                                                            |
| %p     | Zeiger                                                            |
| %n     | Number of characters written by this printf. No argument expected |
| %% %   | No argument expected.                                             |

Code:

```c
#define LEN_STR 100

char timeStr[LEN_STR];

sprintf(timeStr, "%04d-%02d-%02d %02d-%02d-%02d", dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);
```

## Spezialfall Arduino

* Der Arduino kann mit keinen Floats beim `sprintf` umgehen.
* Workaround:

```c#
void prepareText(char text[], char *prefix, float value) {
  int ganz, nachk;
  
  ganz = (int) value;
  nachk = abs((int) (value - ganz) * 1000);

  sprintf(text, "%s %4d.%03d", prefix, ganz, nachk);
}
```
