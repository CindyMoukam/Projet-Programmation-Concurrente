#include "Timer.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <mutex>

// Mutex global pour l'affichage
std::mutex affichageMutex;

Timer& Timer::instance() {
    static Timer instance;
    return instance;
}

Timer::Timer() : running(false), paused(false), timeSpeed(60), hours(10), minutes(0) {}

Timer::~Timer() {
    stop();
}

void Timer::start() {
    if (running) return;
    running = true;
    timeThread = std::thread(&Timer::run, this);
}

void Timer::pause() {
    if (!paused) {
        paused = true;
        std::lock_guard<std::mutex> lock(affichageMutex);
        std::cout << "Pause activée. Toutes les activités sont arrêtées." << std::endl;
    }
}

void Timer::resume() {
    if (paused) {
        paused = false;
        pauseCond.notify_all();
        std::lock_guard<std::mutex> lock(affichageMutex);
        std::cout << "Pause désactivée. Les activités reprennent." << std::endl;
    }
}

void Timer::stop() {
    running = false;
    if (timeThread.joinable()) {
        timeThread.join();
    }
}

void Timer::setTimeSpeed(int factor) {
    timeSpeed = factor;
}

int Timer::getTimeSpeed() const {
    return timeSpeed;
}

void Timer::setCurrentTime(int h, int m) {
    std::lock_guard<std::mutex> lock(pauseMutex);
    hours = h;
    minutes = m;
}

std::string Timer::getCurrentTime() {
    std::lock_guard<std::mutex> lock(pauseMutex);
    return getTime();
}

std::string Timer::getTime() {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours << ":"
       << std::setfill('0') << std::setw(2) << minutes;
    return ss.str();
}

void Timer::run() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / timeSpeed));

        if (paused) {
            std::unique_lock<std::mutex> lock(pauseMutex);
            pauseCond.wait(lock, [this] { return !paused; });
        }

        // Incrementer l'heure et les minutes
        ++minutes;
        if (minutes >= 60) {
            minutes = 0;
            ++hours;
            if (hours >= 24) {
                hours = 0;
            }

            // Afficher l'heure uniquement lorsqu'elle change
            std::lock_guard<std::mutex> lock(affichageMutex);
            std::cout << "Heure actuelle : " << getTime() << std::endl;
        }
    }
}
