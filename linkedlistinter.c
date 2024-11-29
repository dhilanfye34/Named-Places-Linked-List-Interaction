#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct np {
  int code;
  char state[3];
  char name[46];
  int population;
  double area;
  double latitude;
  double longitude;
  int road;
  double distance;
  struct np* next;
} np;

void trim(char* str) {
  int len = strlen(str) - 1;
  while (len >= 0 && str[len] == ' ') {
    str[len] = '\0';
    len--;
  }
}

np* create_place(int code, char* state, char* name, int population, double area, double lat, double lon, int road, double distance) {
  np* place = (np*)malloc(sizeof(np));
  place->code = code;
  strcpy(place->state, state);
  strcpy(place->name, name);
  place->population = population;
  place->area = area;
  place->latitude = lat;
  place->longitude = lon;
  place->road = road;
  place->distance = distance;
  place->next = NULL;
  return place;
}

np* insert_place(np* head, np* new_place) {
  if (head == NULL) {
    return new_place;
  }
  
  np* temp = head;
  while (temp->next != NULL) {
    temp = temp->next;
  }

  temp->next = new_place;
    return head;
}

void read_places(const char* fn, np** head) {
  FILE* placeslist = fopen(fn, "r");
  if (!placeslist) {
    printf("Error with File.\n");
    return;
  }

  char line[250];
  
  while(fgets(line, sizeof(line), placeslist)) {
    np* place = (np*)malloc(sizeof(np));
    char code_str[9];
    char population_str[12];
    char area_str[15];
    char lat_str[11];
    char lon_str[12];
    char road_str[6];
    char distance_str[8];

    sscanf(line, "%8s%2s%45c%11s%14s%10s%11s%5s%7s", code_str, place->state, place->name, population_str, area_str, lat_str, lon_str, road_str, distance_str);
    place->state[2] = '\0';
    place->name[45] = '\0';

    place->code = atoi(code_str);
    place->population = atoi(population_str);
    place->area = atof(area_str);
    place->latitude = atof(lat_str);
    place->longitude = atof(lon_str);
    place->road = atoi(road_str);
    place->distance = atof(distance_str);  

    trim(place->name);
    * head = insert_place(* head, place);
  }

  fclose(placeslist);
}

void print(np* place) {
  if (place != NULL) {
    printf("State: %s\n", place->state);
    printf("Name: %s\n", place->name);
    printf("Population: %d\n", place->population);
    printf("Area: %.2f\n", place->area);
    printf("Latitude: %.2f\n", place->latitude);
    printf("Longitude: %.2f\n", place->longitude);
    printf("Road: %d\n", place->road);
    printf("Distance: %.2f miles\n", place->distance);
  }
}

void search_name(np* head, char* name) {
  np* temp = head;
  bool found = false;
  while (temp != NULL) {
    if(strcmp(temp->name, name) == 0) {
      printf("State: %s\n", temp->state);
      found = true;
    }
    temp = temp->next;
  }
  if(found == false) {
    printf("No place found.\n");
  }
}

np* search_name_and_state(np* head, char* name, char* state) {  
  np* temp = head;
  while (temp != NULL) {
    if (strcmp(temp->name, name) == 0 && strcmp(temp->state, state) == 0) {
      return temp;
    }
    temp = temp->next;
  }
  return NULL;
}

int main() {
  np* head = NULL;
  read_places("/home/www/class/een318/named-places.txt", &head);

  char user_place[46], user_state[3];
  while(true) {
    printf("Enter place name or 'exit' to exit: ");
    fgets(user_place, sizeof(user_place), stdin);
    user_place[strcspn(user_place, "\n")] = '\0'; 
    if (strcmp(user_place, "exit") == 0) {
      break;
    }

    search_name(head, user_place);

    bool found = false;
    np* temp = head;
    while (temp != NULL) {
      if (strcmp(temp->name, user_place) == 0) {
        found = true;
        break;
      }
      temp = temp->next;
    }

    if (!found) {
      continue;
    }

    printf("Enter State Abbreviation: ");
    scanf("%2s", user_state);
    getchar();

    np* place = search_name_and_state(head, user_place, user_state);
    if (place != NULL) {
      print(place);
    } 
    else {
      printf("No such place exists.\n");
    }
  }
  
  return 0;
}