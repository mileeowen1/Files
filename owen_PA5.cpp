/*
Name: Milee Owen
Class: CPSC 121, Spring 2019
Date: February 19, 2019
Programming Assignment: PA5
Description: Create a program that opens a file for reading and read information from the file, open a file for writing and write information to the file, and close the files.
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	// assign variables with data types
	string nameOfinputFile = "";
	string nameOfoutputFile = "";
	ifstream inputFile;
	ofstream outputFile;
	string origin = "";
	string destination = "";
	double travelDistance = 0;
	double travelDistanceMiles = 0;
	string temporary = "";
	string waypoint = "";
	double numOfWaypoints = 0;
	int days = 0;
	double numOfDays = 0.0;
	double totalTravelDistance = 0.0;
	double longestDistance = 0.0;
	int longestDays = 0;
	string longestWaypointDisBegin = "";
	string longestWaypointDisEnd = "";
	string longestWaypointDays = "";
	double averageDistance = 0.0;
	double averageDays = 0.0;
	// prompt user to enter in name of file
	cout << "Please enter the name of the road trip file: ";
	cin >> nameOfinputFile;
	// assign the input with names for input file and output file
	nameOfoutputFile = nameOfinputFile + "_stats.txt";
	nameOfinputFile = nameOfinputFile + ".txt";
	// open files
	inputFile.open(nameOfinputFile);
	outputFile.open(nameOfoutputFile);
	// introduce file to user
	cout << "\nWelcome to the road trip analyzer program!\nRoadtrip origin, destination, waypoints, distance between waypoints in meters, and number of days spent at each waypoint will be read in from a file.\nThe program write to an output file the distance in miles between each waypoint on the trip and statistics about the trip. Enjoy!" << endl << endl;
	// test if the file was successfully opened or not
	if (inputFile.is_open()) {
		cout << "Reading in road trip stop information from " << nameOfinputFile << "..." << endl << endl;
	}
	else {
		cout << "Failed to open input file" << endl << endl;
		exit(-1);
	}
	// read in the first line: origin of trip
	getline(inputFile, origin);
	if (inputFile.good()) {
		cout << "Roadtrip origin: " << origin << endl;
		destination = origin;
	}
	// create a loop that reads from the file until it reaches the end
	while (!inputFile.eof()) {
		inputFile >> travelDistance;
		travelDistanceMiles = travelDistance / 1609.344;
		totalTravelDistance += travelDistanceMiles;
		// gets rid of pesky newline
		getline(inputFile, temporary);
		// reads waypoints and increments them
		getline(inputFile, waypoint);
		outputFile << destination << " to " << waypoint << ": " << travelDistanceMiles << " miles" << endl;
		numOfWaypoints++;
		// reads days and increments them
		inputFile >> days;
		if (inputFile.good()) {
			numOfDays += days;
		}
		// tests to see which distance is the longest traveled
		if (travelDistanceMiles > longestDistance) {
			longestDistance = travelDistanceMiles;
			longestWaypointDisBegin = destination;
			longestWaypointDisEnd = waypoint;
		}
		// tests to see which days is the longest stay
		if (days > longestDays) {
			longestWaypointDays = waypoint;
			longestDays = days;
		}
		// assigns waypoint to destination for outputing the waypoint as the origin for the next waypoing
		destination = waypoint;
		// outputs the waypoints and days
		if (inputFile.good()) {
			cout << "Processing waypoint " << waypoint << " (" << days << " days)..." << endl;
		}
		// gets rid of pesky newline
		getline(inputFile, temporary);
	}
	// outputs the destination
	cout << "Roadtrip destination: " << destination << endl << endl;
	numOfWaypoints--;
	// calculates the average of distance and days
	averageDistance = totalTravelDistance / (numOfWaypoints + 1);
	averageDays = numOfDays / numOfWaypoints;
	// outputs the end of program
	cout << "Writing stop stats to " << nameOfoutputFile << "..." << endl;
	cout << "Closing files..." << endl;
	// writes to output file
	outputFile << "\n**Road Trip Stats**" << endl;
	outputFile << "Number of waypoints on roadtrip: " << numOfWaypoints << endl;
	outputFile << "Number of days on roadtrip: " << numOfDays << endl;
	outputFile << "Total miles traveled on roadtrip: " << totalTravelDistance << endl;
	outputFile << "Longest roadtrip distance between waypoints is " << longestWaypointDisBegin << " to " << longestWaypointDisEnd << ": " << longestDistance << " miles" << endl;
	outputFile << "Longest roadtrip days at one waypoint is " << longestWaypointDays << ": " << longestDays << " days" << endl;
	outputFile << "Average roadtrip distance between stops is: " << averageDistance << endl;
	outputFile << "Average roadtrip days at one waypoint: " << averageDays << endl;
	// closes files
	inputFile.close();
	outputFile.close();

	return 0;
}
