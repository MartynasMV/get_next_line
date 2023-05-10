# get_next_line

Introduction

In this project we must create a function that returns one line from the specified fd every time it is called, followed by a newline if the line has one. This project introduces the idea of static variables, which will be very useful for future projects. On top of that, we'll also learn a way to define macros right when compiling!

The function to implement is called get_next_line, and will have the following prototype:

char *get_next_line(int fd);
