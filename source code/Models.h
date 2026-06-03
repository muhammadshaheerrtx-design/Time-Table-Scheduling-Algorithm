#ifndef MODELS_H
#define MODELS_H

#include <QString>

struct Course {
    QString code;
    QString title;
    QString instructor;
    int creditHours;
    QString section;
    QString department;
    int expectedStudents;
    bool isLab;
};

struct Room {
    QString name;
    QString building;
    int capacity;
};

struct Assignment {
    Course course;
    Room room;
    int day;
    int slot;
};
#endif