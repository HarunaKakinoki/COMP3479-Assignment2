# COMP3479-Assignment2
COMP 3479 (C++ for C programmers) Assignment 2.

What does this program do?

1. Generates a student list (students.txt) with student number, GPA, preferred courses(first choice to fifth choice) and priority to get into a course.
2. After generating a student list, read the text file and assign them into 5 courses based on their preferred course & priority. There are 2 outputs such as GPA.txt and maxhappy.txt
3. gpa.txt is the result of assigning students based on GPA & priority.
4. maxhappy.txt is the result of assigning students in the other way.
   For this, program will calculate their statisfaction level and assign students to maximize thier satisfaction levels. 
   For example, if a student is assinged to the first choice, the student's satisfaction level is considered as 5.
                if a student is assigned to the fifth choice, the student's satisfaciton level is considered as 1.
   When all students are assigned to the course which is same or closed to thier preferred course, the entire satisfaciton level is going to be the highest.
