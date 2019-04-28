#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#pragma warning(disable:4996)

using namespace std;

struct TripPoint {
	int x;
	int y;
	char trip_name[20];
};

struct Trip {
	int id;
	struct TripPoint start_point;
	struct TripPoint end_point;
	int avarage_speed;
	int time;
};

void addTrip(struct Trip trip);
void readAllTrips();
int getLastId();
bool getTripById(int tripId, struct Trip *trip);
void printTrip(struct Trip trip);
void getTopTrips(struct Trip *topTrips[],int top);

void main() {
	//struct TripPoint startPoint = { 3,4,"Sofia" };
	//struct TripPoint endPoint = { 30,40,"Varna" };
	//struct Trip trip = { 1,startPoint,endPoint,70,1000 };

	//addTrip(trip);
	//addTrip(trip);
	//addTrip(trip);

	//readAllTrips();

	struct Trip foundedTrip;
	if (getTripById(3, &foundedTrip)) {
		printTrip(foundedTrip);
	}
	else {
		printf("Can't find trip with id: %d\n", 5);
	}


	system("pause");
}

void addTrip(struct Trip trip) {
	FILE * file;

	int tripId = getLastId() + 1;
	trip.id = tripId;

	file = fopen("trips.txt", "ab");
	if (file == NULL) {
		fprintf(stderr, "\nError opend file!\n");
		exit(1);
	}

	fwrite(&trip, sizeof(struct Trip), 1, file);

	if (fwrite != 0)
		printf("contents to file written successfully !\n");
	else
		printf("error writing file !\n");

	fclose(file);
}

void readAllTrips() {
	FILE * file;
	struct Trip trip;

	file = fopen("trips.txt", "rb");
	if (file == NULL) {
		fprintf(stderr, "\nError opend file!\n");
		exit(1);
	}

	while (fread(&trip, sizeof(struct Trip), 1, file)) {
		printTrip(trip);
	}

	fclose(file);
}

int getLastId() {
	FILE * file;
	struct Trip trip;
	int lastId = 0;

	file = fopen("trips.txt", "rb");
	if (file == NULL) {
		return lastId;
	}

	while (fread(&trip, sizeof(struct Trip), 1, file)) {
		if (trip.id > lastId) {
			lastId = trip.id;
		}
	}
	fclose(file);
	return lastId;
}

bool getTripById(int tripId, struct Trip *tripIn) {
	FILE * file;
	struct Trip trip;

	file = fopen("trips.txt", "rb");
	if (file == NULL) {
		return false;
	}

	while (fread(&trip, sizeof(struct Trip), 1, file)) {
		if (trip.id == tripId) {
			tripIn->id = trip.id;
			tripIn->start_point = trip.start_point;
			tripIn->end_point = trip.end_point;
			tripIn->avarage_speed = trip.avarage_speed;
			tripIn->time = trip.time;
			return true;
		}
	}

	fclose(file);

	return false;

}

void printTrip(struct Trip trip) {
	printf("id = %d\n", trip.id);
	printf("start from = %s\n", trip.start_point.trip_name);
	printf("end to = %s\n", trip.end_point.trip_name);
	printf("avarage speed = %d\n", trip.avarage_speed);
	printf("trip time = %d\n", trip.time);
	printf("\n");
}

void getTopTrips(struct Trip *topTrips[], int top) {
	int index = 0;

	FILE * file;
	struct Trip trip;

	file = fopen("trips.txt", "rb");
	if (file == NULL) {
	}

	while (fread(&trip, sizeof(struct Trip), 1, file)) {
		if (index == 0) {
			topTrips[index]->id = trip.id;
			topTrips[index]->start_point = trip.start_point;
			topTrips[index]->end_point = trip.end_point;
			topTrips[index]->avarage_speed = trip.avarage_speed;
			topTrips[index]->time = trip.time;
			index++;
		}
		else if (index != 0) {
			for (int i = 0; i < index; i++)
			{
				if (trip.time > topTrips[i]->time)
				{
					struct Trip tempTrip = topTrips[i];
				}
			}
				
		}

	}

	fclose(file);

}
