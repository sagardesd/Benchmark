#include "oop_version.hpp"
#include <chrono>
#include <iostream>
#include <numeric>

int main() {
    constexpr int   ENTITY_COUNT = 1'000'000;
    constexpr int   FRAME_COUNT  = 100;
    constexpr float DT           = 1.f / 60.f;
    OOPWorld world;
    world.create_entities(ENTITY_COUNT);
    std::vector<double> frame_times;
    frame_times.reserve(FRAME_COUNT);
    for (int frame = 0; frame < FRAME_COUNT; ++frame) {
        auto start = std::chrono::high_resolution_clock::now();
        world.update_all(DT);
        auto end   = std::chrono::high_resolution_clock::now();
        frame_times.push_back(
            std::chrono::duration<double, std::milli>(end - start).count()
        );
    }
    double avg = std::accumulate(frame_times.begin(), frame_times.end(), 0.0)
                 / frame_times.size();
    std::cout << "[OOP] Average frame time : " << avg          << " ms\n";
    std::cout << "[OOP] Entities processed : " << ENTITY_COUNT << "\n";
}
