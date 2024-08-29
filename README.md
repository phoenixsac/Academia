
# Academia

## Project Structure

The file structure is organized into the following components:


### Explanation:

- **DAL (Data Access Layer)**: Contains repositories responsible for accessing and managing data related to courses, students, and faculty.
  - `CourseRepository`
  - `StudentRepository`
  - `FacultyRepository`

- **DB**: Directory containing text files that act as the database for storing course, faculty, and student data.
  - `course.txt`
  - `faculty.txt`
  - `student.txt`

- **Model**: Contains the data models representing the core entities in the system.
  - `course`
  - `faculty`
  - `model`
  - `student`
  - `user_type`

- **User Handler**: Contains handlers for managing different user roles and common functionalities.
  - `adminHandler`
  - `facultyHandler`
  - `studentHandler`
  - `common`

- **client.c**: The client-side code that interacts with the server.

- **server.c**: The server-side code that handles requests and manages the application logic.





