#pragma once

#include <cstddef>

struct sem_t {
    sem_t() = default;
    sem_t(std::size_t count) {}
    void wait() {}
    void signal() {}
};
