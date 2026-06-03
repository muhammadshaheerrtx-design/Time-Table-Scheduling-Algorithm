#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <queue>
#include <unordered_map>
#include "Models.h"
#include "Constants.h"

class Scheduler {
    // Bitmask storage for O(1) checks
    std::unordered_map<QString, uint64_t> teacherMask;
    std::unordered_map<QString, uint64_t> roomMask;
    std::unordered_map<QString, uint64_t> sectionMask;

public:
    std::vector<Assignment> result;

    bool schedule(std::vector<Course>& courses, std::vector<Room>& rooms) {
        // DAA: Priority Queue (Heap) for MRV Heuristic
        auto cmp = [](const Course& a, const Course& b) {
            return a.creditHours < b.creditHours; // Heavier courses first
        };
        std::priority_queue<Course, std::vector<Course>, decltype(cmp)> pq(cmp);
        for(auto& c : courses) pq.push(c);

        return backtrack(pq, rooms);
    }

private:
    bool backtrack(std::priority_queue<Course, std::vector<Course>, decltype(cmp)> pq, std::vector<Room>& rooms) {
        if (pq.empty()) return true;

        Course current = pq.top();
        pq.pop();

        for (int d = 0; d < Config::DAYS; ++d) {
            for (int s = 0; s < Config::SLOTS; ++s) {
                int bit = d * 8 + s;
                for (auto& r : rooms) {
                    if (isSafe(current, r, bit)) {
                        toggle(current, r, bit, true);
                        if (backtrack(pq, rooms)) {
                            result.push_back({current, r, d, s});
                            return true;
                        }
                        toggle(current, r, bit, false);
                    }
                }
            }
        }
        return false;
    }

    bool isSafe(const Course& c, const Room& r, int bit) {
        if (r.capacity < c.expectedStudents) return false;
        if (r.building != Config::normalizeBuilding(c.department)) return false;
        
        return !(teacherMask[c.instructor] & (1ULL << bit)) &&
               !(roomMask[r.name] & (1ULL << bit)) &&
               !(sectionMask[c.section + c.department] & (1ULL << bit));
    }

    void toggle(const Course& c, const Room& r, int bit, bool state) {
        if (state) {
            teacherMask[c.instructor] |= (1ULL << bit);
            roomMask[r.name] |= (1ULL << bit);
            sectionMask[c.section + c.department] |= (1ULL << bit);
        } else {
            teacherMask[c.instructor] &= ~(1ULL << bit);
            roomMask[r.name] &= ~(1ULL << bit);
            sectionMask[c.section + c.department] &= ~(1ULL << bit);
        }
    }
};
#endif