#ifndef TIMER_H
#define TIMER_H

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <thread>
#include <string>

class Timer {
public:
    static Timer& instance();

    void start();            // Démarrer le temps
    void pause();            // Mettre en pause
    void resume();           // Reprendre
    void stop();             // Arrêter définitivement
    std::string getTime();   // Obtenir l'heure actuelle au format HH:MM
    void setCurrentTime(int h, int m); // Définir l'heure initiale
    std::string getCurrentTime();     // Obtenir l'heure actuelle en tant que chaîne

    void setTimeSpeed(int factor); // Changer la vitesse d'écoulement du temps
    int getTimeSpeed() const;

private:
    Timer();
    ~Timer();

    void run(); // Thread principal pour l'écoulement du temps

    std::atomic<bool> running;
    std::atomic<bool> paused;
    std::atomic<int> timeSpeed; // Multiplicateur de vitesse du temps
    int hours;
    int minutes;

    std::thread timeThread;
    std::mutex pauseMutex;
    std::condition_variable pauseCond;
};

#endif // TIMER_H
