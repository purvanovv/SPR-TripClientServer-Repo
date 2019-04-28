#include <stdio.h>
#include<stdlib.h>
#include<iostream>
#include <string>
#pragma warning(disable:4996)

struct TripPoint {
	int x;
	int y;
	char* trip_name;
};

struct Trip {
	int id;
	struct TripPoint start_point;
	struct TripPoint end_point;
	int avarage_speed;
	int time;
};

typedef struct Trip Trip;

void AddTrip(Trip *trip);
struct Trip* ListTopTrips(int tripCount);
struct Trip* ListAllTrips();
struct Trip GetTripById(int tripId);

void AddTrip(Trip *trip) {
	FILE* file = fopen("trips", "rb");
	if (file != NULL) {
		fread(trip, sizeof(struct Trip), 1, file);
		fclose(file);
		printf("Add trip successfully.");
	}
	else {
		printf("Cannot add trip!");
	}
}


void main() {
	Trip trip;
	trip.id = 1;
	trip.start_point.x = 32;
	trip.start_point.y = 62;
	trip.end_point.x = 40;
	trip.end_point.y = 60;
	strcpy(trip.start_point.trip_name, "Sofia");
	strcpy(trip.end_point.trip_name, "Varna");
	trip.avarage_speed = 80;
	trip.time = 1000;
	AddTrip(&trip);

}