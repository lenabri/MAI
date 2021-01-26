 #include <stdio.h>
 #include <string.h>

 #include "student.h"

 int read_txt(STUDENT* student, FILE* input) {
     fscanf(input, "%s %s %s %d %d %d %d %d %d", student->last_name, student->initials, student->sex, &student->group, &student->mark_1, &student->mark_2, &student->mark_3, &student->mark_4, &student->mark_5);
     return !feof(input);
 }

 void write_bin(STUDENT* student, FILE* output) {
     fwrite(student->last_name, sizeof(char), STR_LEN, output);
     fwrite(student->initials, sizeof(char), STR_LEN, output);
     fwrite(&student->sex, sizeof(char), STR_LEN, output);
     fwrite(&student->group, sizeof(int), 1, output);
     fwrite(&student->mark_1, sizeof(int), 1, output);
     fwrite(&student->mark_2, sizeof(int), 1, output);
     fwrite(&student->mark_3, sizeof(int), 1, output);
     fwrite(&student->mark_4, sizeof(int), 1, output);
     fwrite(&student->mark_5, sizeof(int), 1, output);
 }

 void usage(const char* argv[]) {
     fprintf(stderr, "Использование:\n\tРаспечатать: %s <входной файл> <выходной файл>\n", argv[1]);
 }

 int main(int argc, const char * argv[]) {
     if (argc != 3) {
         usage(argv);
         return 1;
     }
     
     FILE* input = fopen(argv[1], "r");
     FILE* output = fopen(argv[2], "w");
     STUDENT student;
     
     if (!input) {
         printf("Не получается открыть файл для чтения!\n");
         fclose(input);
         fclose(output);
         return 2;
     }
     
     if (!output) {
         printf("Не получается открыть файл для записи!\n");
         fclose(input);
         fclose(output);
         return 2;
     }
     
     while (read_txt(&student, input)) {
         write_bin(&student, output);
     }
     
     fclose(input);
     fclose(output);
     return 0;
 }
