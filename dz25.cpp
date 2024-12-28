#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

double getRandomTime(double averageTime) {
    double random = (double)rand() / RAND_MAX;
    return -averageTime * log(1 - random);
}

void simulateBusStop(double avgPassengerTime, double avgBusTime, int maxPassengers, bool isTerminal, int simulationTime) {
    queue<double> passengers; 
    double currentTime = 0.0; 
    int totalPassengers = 0; 
    double totalWaitTime = 0.0; 

    srand(time(0)); 

    while (currentTime < simulationTime) {
        double nextPassengerTime = getRandomTime(avgPassengerTime);
        double nextBusTime = getRandomTime(avgBusTime);

        currentTime += min(nextPassengerTime, nextBusTime);

        if (nextPassengerTime < nextBusTime) {
            if (passengers.size() < maxPassengers) {
                passengers.push(currentTime);
            }
        }
        else {
            int freeSeats = rand() % 20 + 1; 
            int boarded = min((int)passengers.size(), freeSeats);

            for (int i = 0; i < boarded; i++) {
                double arrivalTime = passengers.front();
                passengers.pop();
                totalWaitTime += (currentTime - arrivalTime);
                totalPassengers++;
            }
        }
    }

    cout << "Симуляція завершена!\n";
    cout << "Загальна кількість обслугованих пасажирів: " << totalPassengers << endl;
    cout << "Середній час очікування пасажира: "
        << (totalPassengers > 0 ? totalWaitTime / totalPassengers : 0.0) << " хв.\n";
    cout << "Максимальна кількість пасажирів, що очікували одночасно: " << maxPassengers << endl;
}

int main() {
    double avgPassengerTime, avgBusTime;
    int maxPassengers, simulationTime;
    bool isTerminal;

    cout << "Введіть середній час між прибуттям пасажирів (хв): ";
    cin >> avgPassengerTime;
    cout << "Введіть середній час між прибуттям маршруток (хв): ";
    cin >> avgBusTime;
    cout << "Введіть максимальну кількість пасажирів на зупинці: ";
    cin >> maxPassengers;
    cout << "Зупинка кінцева? (1 - так, 0 - ні): ";
    cin >> isTerminal;
    cout << "Введіть час симуляції (хв): ";
    cin >> simulationTime;

    simulateBusStop(avgPassengerTime, avgBusTime, maxPassengers, isTerminal, simulationTime);

    return 0;
}
