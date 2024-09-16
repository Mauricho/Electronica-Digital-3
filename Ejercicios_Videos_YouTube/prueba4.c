#include <stdio.h>
#include <string.h>

typedef struct {
  int id;
  char title[40];
  float hours;
} course;

void update_course(course *class); // Paso la estructura por puntero para modificarla
void display_course(course class); // Paso la estructura por valor para copiarla

int main() {
  course cs2;
  update_course(&cs2); // Paso la dirección en memoria
  display_course(cs2); // Paso el valor
  return 0;
}

void update_course(course *class) {
  strcpy(class->title, "C++ Fundamentals");
  class->id = 111;
  class->hours = 12.30;
}

void display_course(course class) {
  printf("%d\t%s\t%3.2f\n", class.id, class.title, class.hours);
}
