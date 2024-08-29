#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h> 
#include "../Model/model.h"
#include "../config.h"

// Function to get the next course ID by reading the last course record in the file
int getNextCourseId()
{
    // Variables to store the number of bytes read/written
    // Variable to store the last course record
    ssize_t readBytes, writeBytes;
    Course previousCourse;

    // Open the course file in read-only mode
    // If the file doesn't exist, return 1 as the first course ID (handle file opening errors)
    int CourseFileDescriptor = open(COURSE_FILE, O_RDONLY);
    if (CourseFileDescriptor == -1 && errno == ENOENT)
    {
        // course file was never created
        return 1;
    }
    else if (CourseFileDescriptor == -1)
    {
        perror("Error while opening Course file");
        return -1;
    }
    else
    {
        // Seek to the last course record in the file
        int offset = lseek(CourseFileDescriptor, -sizeof(Course), SEEK_END);
        if (offset == -1)
        {
            perror("Error seeking to last Course record!");
            return false;
        }

        // Setup a read lock on the last course record
        struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(Course), getpid()};
        int lockingStatus = fcntl(CourseFileDescriptor, F_SETLKW, &lock);
        if (lockingStatus == -1)
        {
            perror("Error obtaining read lock on Course record!");
            return false;
        }

        // Read the last course record
        readBytes = read(CourseFileDescriptor, &previousCourse, sizeof(Course));
        if (readBytes == -1)
        {
            perror("Error while reading Course record from file!");
            return false;
        }

        // Unlock the record after reading
        lock.l_type = F_UNLCK;
        fcntl(CourseFileDescriptor, F_SETLK, &lock);

        // close file
        close(CourseFileDescriptor);

        // return next course id
        return previousCourse.id + 1;
    }

}

// create a course and append it to the end of a course file
void createCourse(Course newCourse)
{
    ssize_t readBytes, writeBytes;
    int CourseFileDescriptor = open(COURSE_FILE, O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
    if (CourseFileDescriptor == -1)
    {
        perror("Error while creating / opening Course file!");
        return;
    }

     // Setup a write lock on the file
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = 0;
    lock.l_len = sizeof(Course);
    lock.l_pid = getpid();

    // handle if any locking errors
    int lockingStatus = fcntl(CourseFileDescriptor, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining write lock on course record!");
        return;
    }

    // Write the new course record to the file
    writeBytes = write(CourseFileDescriptor, &newCourse, sizeof(newCourse));
    if (writeBytes == -1)
    {
        perror("Error while writing Course record to file!");
        return;
    }

    // unlock file
    lock.l_type = F_UNLCK;
    fcntl(CourseFileDescriptor, F_SETLKW, &lock);
    // close file
    close(CourseFileDescriptor);
}

// Function to retrieve a course record by its ID
Course getCourseById(int courseID)
{
    Course course;
    course.id = -1;
    ssize_t readBytes;
    off_t offset;
    int lockingStatus;
    int courseFileDescriptor = open(COURSE_FILE, O_RDONLY);

    // seek to just the top row of the required course by id * sizeOf course
    offset = lseek(courseFileDescriptor, (courseID-1) * sizeof(Course), SEEK_SET);
    if (offset == -1)
    {
        perror("Error while seeking to required course record!");
        return course;
    }
    struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(Course), getpid()};

    // Lock the record to be read
    lockingStatus = fcntl(courseFileDescriptor, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Couldn't obtain lock on course record!");
        return course;
    }

    readBytes = read(courseFileDescriptor, &course, sizeof(Course));
    if (readBytes == -1)
    {
        perror("Error while reading course record from the file!");
        return course;
    }

    // Unlock the record
    lock.l_type = F_UNLCK;
    fcntl(courseFileDescriptor, F_SETLK, &lock);

    // close file and return course
    close(courseFileDescriptor);

    return course;

}

// Function to update an existing course record in the file
bool updateCourse(Course course)
{
    ssize_t writeBytes;

    // Open the course file in write-only mode
    int courseFileDescriptor = open(COURSE_FILE, O_WRONLY);
    if (courseFileDescriptor == -1)
    {
        perror("Error while opening course file");
        return false;
    }
    // move to the start of the required course by using seek_set
    int offset = lseek(courseFileDescriptor, (course.id-1) * sizeof(Course), SEEK_SET);
    if (offset == -1)
    {
        perror("Error while seeking to required course record!");
        return false;
    }

    // write lock implementation
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_start = offset;
    lock.l_whence = SEEK_SET;
    lock.l_len = sizeof(Course);
    lock.l_pid = getpid();

    // manage locking status error handling
    int lockingStatus = fcntl(courseFileDescriptor, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining write lock on course record!");
        return false;
    }

    // write the passed on Course, (overwrite) over the existing one
    writeBytes = write(courseFileDescriptor, &course, sizeof(Course));
    if (writeBytes == -1)
    {
        perror("Error while writing update course into file");
    }

    // unlock lock, close file and return true to indicate successful modification
    lock.l_type = F_UNLCK;
    fcntl(courseFileDescriptor, F_SETLK, &lock);

    close(courseFileDescriptor);
    return true;
}
