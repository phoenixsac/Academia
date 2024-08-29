#ifndef COURSES_H
#define COURSES_H
#include "../config.h"
// model or entity structure of course
typedef struct {
    int id;
    char name[20];
    int facultyId;
    int noEnrolledStudents;
    int enrolledStudents[COURSE_MAX_SEATS];
    int maxSeats;
    bool isActive;
} Course;

#endif
