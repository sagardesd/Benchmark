// ecs_benchmark.cpp
#include "ecs.hpp"
#include "systems.hpp"
#include <chrono>
#include <iostream>
#include <numeric>

int main() {
    constexpr int   ENTITY_COUNT = 1'000'000;
    constexpr int   FRAME_COUNT  = 100;
    constexpr float DT           = 1.f / 60.f;
    ECSWorld world;
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        Entity e = world.create_entity();
        world.add_position(e,    {static_cast<float>(i), 0.f, 0.f});
        world.add_velocity(e,    {1.f, 0.5f, 0.25f});
        world.add_health(e,      {100});
        world.add_active_flag(e, {i % 10 != 0});  // 90% active
    }
    std::vector<double> frame_times;
    frame_times.reserve(FRAME_COUNT);
    for (int frame = 0; frame < FRAME_COUNT; ++frame) {
        auto start = std::chrono::high_resolution_clock::now();
        movement_system(world, DT);
        auto end   = std::chrono::high_resolution_clock::now();
        frame_times.push_back(
            std::chrono::duration<double, std::milli>(end - start).count()
        );
    }
    double avg = std::accumulate(frame_times.begin(), frame_times.end(), 0.0)
                 / frame_times.size();
    std::cout << "[ECS] Average frame time : " << avg          << " ms\n";
    std::cout << "[ECS] Entities processed : " << ENTITY_COUNT << "\n";
}
