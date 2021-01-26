#ifndef student_h
#define student_h

#define STR_LEN 32

typedef struct STUDENT STUDENT;

struct STUDENT {
    char last_name[STR_LEN];
    char initials[STR_LEN];
    char sex[STR_LEN];
    int group;
    int mark_1;
    int mark_2;
    int mark_3;
    int mark_4;
    int mark_5;
};

#endif /* student_h */
