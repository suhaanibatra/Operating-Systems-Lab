#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    char existing[50];
    char new[50];

    int no_of_bytes;
    printf("Enter name of existing file");
    scanf("%s", existing);

    printf("Enter name of new file");
    scanf("%s", new);

    printf("Enter no of bytes to be copied");
    scanf("%d", &no_of_bytes);

    int fd1 = open(existing, O_RDONLY);
    if(fd1 == -1){
        printf("Error in opening file\n");
        close(fd1);
        return -1;
    }

    int fd2 = open(new, O_CREAT);
    char c;
    while(no_of_bytes--){
        read(fd1, &c, 1);
        write(fd2, &c, 1);
    }

    close(fd1);
    close(fd2);
}