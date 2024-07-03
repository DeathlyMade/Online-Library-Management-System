#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <bits/pthreadtypes.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#define PORT 8110
#define MAXLINE 1024

char buffer[MAXLINE];
char choice[100];
int n1,n2;
struct User
{
    char username[10];
    char password[10];
};
struct Book
{
    char bookID[10];
    char bookname[10];
    char quantity[10];
};
struct Admin
{
    char username[10];
    char password[10];
};
void* client_handler(void* n)
{
    int nsd=*(int *)n;
    int x=0;
            while(x==0)
            {
                memset(buffer, 0, sizeof(buffer));
                int n = recv(nsd, buffer, sizeof(buffer)-1, 0);
                if(n == -1)
                {
                    perror("Receive failed");
                    exit(1);
                }
                buffer[n] = '\0';
                printf("User's choice: %s\n", buffer);
                if(strcmp(buffer,"Login")==0)
                {
                    char username[10],password[10];
                    memset(choice, 0, sizeof(choice));
                    n=recv(nsd, choice, sizeof(choice)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    choice[n]='\0';
                    if(strcmp(choice,"Admin")==0)
                    {
                        memset(username, 0, sizeof(username));
                        printf("Waiting from Username\n");
                        n1=recv(nsd, username, sizeof(username)-1, 0);
                        if(n1==-1)
                        {
                            perror("Receive failed");
                            exit(1);
                        }
                        username[n1]='\0';
                        printf("Received Username\n");
                        memset(password, 0, sizeof(password));
                        printf("Waiting for Password\n");
                        n2=recv(nsd, password, sizeof(password)-1, 0);
                        if(n2==-1)
                        {
                            perror("Receive failed");
                            exit(1);
                        }
                        password[n2]='\0';
                        printf("Received Password\n");
                        int fp=open("admin_login.txt",O_RDONLY);
                        if(fp==-1)
                        {
                            perror("File not found");
                            exit(1);
                        }
                        struct flock lock;
                        lock.l_type = F_RDLCK;
                        lock.l_whence = SEEK_SET;
                        lock.l_start = 0;
                        lock.l_len = 0;
                        lock.l_pid = getpid();
                        fcntl(fp, F_SETLKW, &lock);
                        int flag=0;
                        struct Admin admin;
                        while(read(fp,&admin,sizeof(struct Admin))>0)
                        {
                            if(strcmp(admin.username,username)==0 && strcmp(admin.password,password)==0)
                            {
                                flag=1;
                                break;
                            }
                        }
                        fcntl(fp, F_UNLCK, &lock);
                        close(fp);
                        if(flag==1)
                        {
                            char *msg="Login successful";
                            x=1;
                            send(nsd, msg, strlen(msg), 0);
                        }
                        else
                        {
                            char *msg="Login failed";
                            send(nsd, msg, strlen(msg), 0);
                        }
                    }
                    else if(strcmp(choice,"User")==0)
                    {
                        memset(username, 0, sizeof(username));
                        printf("Waiting from Username\n");
                        n1=recv(nsd, username, sizeof(username)-1, 0);
                        if(n1==-1)
                        {
                            perror("Receive failed");
                            exit(1);
                        }
                        username[n1]='\0';
                        printf("Received Username\n");
                        memset(password, 0, sizeof(password));
                        printf("Waiting for Password\n");
                        n2=recv(nsd, password, sizeof(password)-1, 0);
                        if(n2==-1)
                        {
                            perror("Receive failed");
                            exit(1);
                        }
                        password[n2]='\0';
                        printf("Received Password\n");
                        int fp=open("user_login.txt",O_RDONLY);
                        if(fp==-1)
                        {
                            perror("File not found");
                            exit(1);
                        }
                        struct flock lock;
                        lock.l_type = F_RDLCK;
                        lock.l_whence = SEEK_SET;
                        lock.l_start = 0;
                        lock.l_len = 0;
                        lock.l_pid = getpid();
                        fcntl(fp, F_SETLKW, &lock);
                        int flag=0;
                        struct User user;
                        while(read(fp,&user,sizeof(struct User))>0)
                        {
                            if(strcmp(user.username,username)==0 && strcmp(user.password,password)==0)
                            {
                                flag=1;
                                break;
                            }
                        }
                        fcntl(fp, F_UNLCK, &lock);
                        close(fp);
                        if(flag==1)
                        {
                            char *msg="Login successful";
                            x=1;
                            send(nsd, msg, strlen(msg), 0);
                        }
                        else
                        {
                            char *msg="Login failed";
                            send(nsd, msg, strlen(msg), 0);
                        }
                    }
                }
                else if(strcmp(buffer,"Register")==0)
                {
                    char username[10],password[10];
                    memset(choice, 0, sizeof(choice));
                    n=recv(nsd, choice, sizeof(choice)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    choice[n]='\0';
                    if(strcmp(choice,"Admin")==0)
                    {
                        memset(username, 0, sizeof(username));
                        printf("Waiting from Username\n");
                        n1=recv(nsd, username, sizeof(username)-1, 0);
                        if(n1==-1)
                        {
                            perror("Receive failed");
                            exit(1);
                        }
                        username[n1]='\0';
                        printf("Received Username\n");
                        memset(password, 0, sizeof(password));
                        printf("Waiting for Password\n");
                        n2=recv(nsd, password, sizeof(password)-1, 0);
                        if(n2==-1)
                        {
                            perror("Receive failed");
                            exit(1);
                        }
                        password[n2]='\0';
                        printf("Received Password\n");
                        int fp=open("admin_login.txt",O_CREAT|O_WRONLY|O_APPEND);
                        if(fp==-1)
                        {
                            perror("File not found");
                            exit(1);
                        }
                        struct flock lock;
                        lock.l_type = F_WRLCK;
                        lock.l_whence = SEEK_SET;
                        lock.l_start = 0;
                        lock.l_len = 0;
                        lock.l_pid = getpid();
                        fcntl(fp, F_SETLKW, &lock);
                        struct Admin admin;
                        strcpy(admin.username,username);
                        strcpy(admin.password,password);
                        write(fp,&admin,sizeof(struct Admin));
                        fcntl(fp, F_UNLCK, &lock);
                        close(fp);
                        char *msg="Registration successful";
                        send(nsd, msg, strlen(msg), 0);
                    }
                    else if(strcmp(choice,"User")==0)
                    {
                        memset(username, 0, sizeof(username));
                        printf("Waiting from Username\n");
                        n1=recv(nsd, username, sizeof(username)-1, 0);
                        if(n1==-1)
                        {
                            perror("Receive failed");
                            exit(1);
                        }
                        username[n1]='\0';
                        printf("Received Username\n");
                        memset(password, 0, sizeof(password));
                        printf("Waiting for Password\n");
                        n2=recv(nsd, password, sizeof(password)-1, 0);
                        if(n2==-1)
                        {
                            perror("Receive failed");
                            exit(1);
                        }
                        password[n2]='\0';
                        printf("Received Password\n");
                        int fp=open("user_login.txt",O_CREAT|O_WRONLY|O_APPEND);
                        if(fp==-1)
                        {
                            perror("File not found");
                            exit(1);
                        }
                        struct flock lock;
                        lock.l_type = F_WRLCK;
                        lock.l_whence = SEEK_SET;
                        lock.l_start = 0;
                        lock.l_len = 0;
                        lock.l_pid = getpid();
                        fcntl(fp, F_SETLKW, &lock);
                        struct User user;
                        strcpy(user.username,username);
                        strcpy(user.password,password);
                        write(fp,&user,sizeof(struct User));
                        fcntl(fp, F_UNLCK, &lock);
                        close(fp);
                        char *msg="Registration successful";
                        send(nsd, msg, strlen(msg), 0);
                    }
                }
                else if(strcmp(buffer,"ForgotPass")==0)
                {
                    char username[10],password[10];
                    memset(choice, 0, sizeof(choice));
                    n=recv(nsd, choice, sizeof(choice)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    choice[n]='\0';
                    if(strcmp(choice,"Admin")==0)
                    {
                        memset(username, 0, sizeof(username));
                        printf("Waiting for Username\n");
                        n1=recv(nsd, username, sizeof(username)-1, 0);
                        if(n1==-1)
                        {
                            perror("Receive failed");
                            exit(1);
                        }
                        username[n1]='\0';
                        printf("Received Username\n");
                        memset(password, 0, sizeof(password));
                        printf("Waiting for new Password\n");
                        n2=recv(nsd, password, sizeof(password)-1, 0);
                        if(n2==-1)
                        {
                            perror("Receive failed");
                            exit(1);
                        }
                        password[n2]='\0';
                        printf("Received new Password\n");
                        int fp=open("admin_login.txt",O_RDWR);
                        if(fp==-1)
                        {
                            perror("File not found");
                            exit(1);
                        }
                        struct flock lock;
                        lock.l_type = F_WRLCK;
                        lock.l_whence = SEEK_SET;
                        lock.l_start = 0;
                        lock.l_len = 0;
                        lock.l_pid = getpid();
                        fcntl(fp, F_SETLKW, &lock);
                        int user_found = 0;
                        struct Admin admin;
                        while(read(fp,&admin,sizeof(struct Admin))>0)
                        {
                            if(strcmp(admin.username,username)==0)
                            {
                                strcpy(admin.password,password);
                                lseek(fp, -sizeof(struct Admin), SEEK_CUR);
                                write(fp,&admin,sizeof(struct Admin));
                                user_found = 1;
                                break;
                            }
                        }
                        fcntl(fp, F_UNLCK, &lock);
                        close(fp);
                        if(user_found)
                        {
                            char *msg = "Password updated successfully!";
                            send(nsd, msg, strlen(msg), 0);
                        }
                        else
                        {
                            char *msg = "User not found!";
                            send(nsd, msg, strlen(msg), 0);
                        }
                    }
                    else if(strcmp(choice,"User")==0)
                    {
                        memset(username, 0, sizeof(username));
                        printf("Waiting for Username\n");
                        n1=recv(nsd, username, sizeof(username)-1, 0);
                        if(n1==-1)
                        {
                            perror("Receive failed");
                            exit(1);
                        }
                        username[n1]='\0';
                        printf("Received Username\n");
                        memset(password, 0, sizeof(password));
                        printf("Waiting for new Password\n");
                        n2=recv(nsd, password, sizeof(password)-1, 0);
                        if(n2==-1)
                        {
                            perror("Receive failed");
                            exit(1);
                        }
                        password[n2]='\0';
                        printf("Received new Password\n");
                        int fp=open("user_login.txt",O_RDWR);
                        if(fp==-1)
                        {
                            perror("File not found");
                            exit(1);
                        }
                        struct flock lock;
                        lock.l_type = F_WRLCK;
                        lock.l_whence = SEEK_SET;
                        lock.l_start = 0;
                        lock.l_len = 0;
                        lock.l_pid = getpid();
                        fcntl(fp, F_SETLKW, &lock);
                        int user_found = 0;
                        struct User user;
                        while(read(fp,&user,sizeof(struct User))>0)
                        {
                            if(strcmp(user.username,username)==0)
                            {
                                strcpy(user.password,password);
                                lseek(fp, -sizeof(struct User), SEEK_CUR);
                                write(fp,&user,sizeof(struct User));
                                user_found = 1;
                                break;
                            }
                        }
                        fcntl(fp, F_UNLCK, &lock);
                        close(fp);
                        if(user_found)
                        {
                            char *msg = "Password updated successfully!";
                            send(nsd, msg, strlen(msg), 0);
                        }
                        else
                        {
                            char *msg = "User not found!";
                            send(nsd, msg, strlen(msg), 0);
                        }
                    }
                }
            }
            while(strcmp(choice,"Admin")==0)
            {
                memset(buffer, 0, sizeof(buffer));
                int n = recv(nsd, buffer, sizeof(buffer)-1, 0);
                if(n == -1)
                {
                    perror("Receive failed");
                    exit(1);
                }
                buffer[n] = '\0';
                printf("Option selected by user: %s\n", buffer);
                if(strcmp(buffer,"1")==0)
                {
                    printf("Waiting for the bookID\n");
                    char bookID[10];
                    n=recv(nsd, bookID, sizeof(bookID)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    bookID[n]='\0';
                    printf("Received bookID\n");
                    printf("Waiting for the bookname\n");
                    char bookname[10];
                    n=recv(nsd, bookname, sizeof(bookname)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    bookname[n]='\0';
                    printf("Received bookname\n");
                    printf("Waiting for the quantity\n");
                    char quantity[10];
                    n=recv(nsd, quantity, sizeof(quantity)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    quantity[n]='\0';
                    printf("Received quantity\n");
                    int fp=open("books.txt",O_CREAT|O_WRONLY|O_APPEND);
                    if(fp==-1)
                    {
                        perror("File not found");
                        exit(1);
                    }
                    struct flock lock;
                    lock.l_type = F_WRLCK;
                    lock.l_whence = SEEK_SET;
                    lock.l_start = 0;
                    lock.l_len = 0;
                    lock.l_pid = getpid();
                    fcntl(fp, F_SETLKW, &lock);
                    struct Book book;
                    strcpy(book.bookID,bookID);
                    strcpy(book.bookname,bookname);
                    strcpy(book.quantity,quantity);
                    sleep(5);
                    write(fp,&book,sizeof(struct Book));
                    fcntl(fp, F_UNLCK, &lock);
                    close(fp);
                    char *msg="Book added successfully";
                    send(nsd, msg, strlen(msg), 0);
                }
                else if(strcmp(buffer,"2")==0)
                {
                    printf("Waiting for the bookID\n");
                    char bookID[10];
                    n=recv(nsd, bookID, sizeof(bookID)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    bookID[n]='\0';
                    printf("Received bookID\n");
                    int fp=open("books.txt",O_RDWR);
                    if(fp==-1)
                    {
                        perror("File not found");
                        exit(1);
                    }
                    struct flock lock;
                    lock.l_type = F_WRLCK;
                    lock.l_whence = SEEK_SET;
                    lock.l_start = 0;
                    lock.l_len = 0;
                    lock.l_pid = getpid();
                    fcntl(fp, F_SETLKW, &lock);
                    int fp1=open("books.txt",O_RDONLY);
                    if(fp1==-1)
                    {
                        perror("File not found");
                        exit(1);
                    }
                    struct flock lock1;
                    lock1.l_type = F_RDLCK;
                    lock1.l_whence = SEEK_SET;
                    lock1.l_start = 0;
                    lock1.l_len = 0;
                    lock1.l_pid = getpid();
                    fcntl(fp1, F_SETLKW, &lock1);
                    int book_found = 0;
                    struct Book book;
                    struct Book book1;
                    struct Book book2;
                    book2.bookID[0]='\0';
                    book2.bookname[0]='\0';
                    book2.quantity[0]='\0';
                    while(read(fp,&book,sizeof(struct Book))>0 && read(fp1,&book1,sizeof(struct Book))>0)
                    {
                        if(strcmp(book.bookID,bookID)==0)
                        {
                            lseek(fp, -sizeof(struct Book), SEEK_CUR);
                            while(read(fp1,&book1,sizeof(struct Book))>0)
                            {
                                write(fp,&book1,sizeof(struct Book));
                            }
                            write(fp,&book2,sizeof(struct Book));
                            book_found = 1;
                            break;
                        }
                    }
                    fcntl(fp, F_UNLCK, &lock);
                    fcntl(fp1, F_UNLCK, &lock1);
                    close(fp1);
                    close(fp);  
                    if(book_found)
                    {
                        char *msg = "Book deleted successfully!";
                        send(nsd, msg, strlen(msg), 0);
                    }
                    else
                    {
                        char *msg = "Book not found!";
                        send(nsd, msg, strlen(msg), 0);
                    }
                }
                else if(strcmp(buffer,"3")==0)
                {
                    printf("Waiting for the username\n");
                    char username[100];
                    n=recv(nsd, username, sizeof(username)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    username[n]='\0';
                    printf("Received username\n");
                    printf("Waiting for the password\n");
                    char password[100];
                    n=recv(nsd, password, sizeof(password)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    password[n]='\0';
                    printf("Received password\n");
                    int fp=open("user_login.txt",O_CREAT|O_WRONLY|O_APPEND);
                    if(fp==-1)
                    {
                        perror("File not found");
                        exit(1);
                    }
                    struct flock lock;
                    lock.l_type = F_WRLCK;
                    lock.l_whence = SEEK_SET;
                    lock.l_start = 0;
                    lock.l_len = 0;
                    lock.l_pid = getpid();
                    fcntl(fp, F_SETLKW, &lock);
                    struct User user;
                    strcpy(user.username,username);
                    strcpy(user.password,password);
                    write(fp,&user,sizeof(struct User));
                    fcntl(fp, F_UNLCK, &lock);
                    close(fp);
                    char *msg="User added successfully";
                    send(nsd, msg, strlen(msg), 0);
                }
                else if(strcmp(buffer,"4")==0)
                {
                    printf("Waiting for the username\n");
                    char username[100];
                    n=recv(nsd, username, sizeof(username)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    username[n]='\0';
                    printf("Received username\n");
                    int fp=open("user_login.txt",O_RDWR);
                    if(fp==-1)
                    {
                        perror("File not found");
                        exit(1);
                    }
                    struct flock lock;
                    lock.l_type = F_WRLCK;
                    lock.l_whence = SEEK_SET;
                    lock.l_start = 0;
                    lock.l_len = 0;
                    lock.l_pid = getpid();
                    fcntl(fp, F_SETLKW, &lock);
                    int fp1=open("user_login.txt",O_RDONLY);
                    if(fp1==-1)
                    {
                        perror("File not found");
                        exit(1);
                    }
                    struct flock lock1;
                    lock1.l_type = F_RDLCK;
                    lock1.l_whence = SEEK_SET;
                    lock1.l_start = 0;
                    lock1.l_len = 0;
                    lock1.l_pid = getpid();
                    fcntl(fp1, F_SETLKW, &lock1);
                    int user_found = 0;
                    struct User user;
                    struct User user1;
                    struct User user2;
                    user2.username[0]='\0';
                    user2.password[0]='\0';
                    while(read(fp,&user,sizeof(struct User))>0 && read(fp1,&user1,sizeof(struct User))>0)
                    {
                        if(strcmp(user.username,username)==0)
                        {
                            lseek(fp, -sizeof(struct User), SEEK_CUR);
                            while(read(fp1,&user1,sizeof(struct User))>0)
                            {
                                write(fp,&user1,sizeof(struct User));
                            }
                            write(fp,&user2,sizeof(struct User));
                            user_found = 1;
                            break;
                        }
                    }
                    fcntl(fp, F_UNLCK, &lock);
                    fcntl(fp1, F_UNLCK, &lock1);
                    close(fp);
                    close(fp1);
                    if(user_found)
                    {
                        char *msg = "User deleted successfully!";
                        send(nsd, msg, strlen(msg), 0);
                    }
                    else
                    {
                        char *msg = "User not found!";
                        send(nsd, msg, strlen(msg), 0);
                    }
                }
                else if(strcmp(buffer,"5")==0)
                {
                    printf("Waiting for the bookname\n");
                    char bookname[100];
                    n=recv(nsd, bookname, sizeof(bookname)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    bookname[n]='\0';
                    printf("Received bookname\n");
                    int fp=open("books.txt",O_RDONLY);
                    if(fp==-1)
                    {
                        perror("File not found");
                        exit(1);
                    }
                    struct flock lock;
                    lock.l_type = F_RDLCK;
                    lock.l_whence = SEEK_SET;
                    lock.l_start = 0;
                    lock.l_len = 0;
                    lock.l_pid = getpid();
                    fcntl(fp, F_SETLKW, &lock);
                    int book_found = 0;
                    struct Book book;
                    while(read(fp,&book,sizeof(struct Book))>0)
                    {
                        if(strcmp(book.bookname,bookname)==0)
                        {
                            char *msg = "Book found!";
                            send(nsd, msg, strlen(msg), 0);
                            book_found = 1;
                            break;
                        }
                    }
                    fcntl(fp, F_UNLCK, &lock);
                    close(fp);
                    if(!book_found)
                    {
                        char *msg = "Book not found!";
                        send(nsd, msg, strlen(msg), 0);
                    }
                }
                else if(strcmp(buffer,"6")==0)
                {
                    printf("Waiting for the username\n");
                    char username[100];
                    n=recv(nsd, username, sizeof(username)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    username[n]='\0';
                    printf("Received username\n");
                    int fp=open("user_login.txt",O_RDONLY);
                    if(fp==-1)
                    {
                        perror("File not found");
                        exit(1);
                    }
                    struct flock lock;
                    lock.l_type = F_RDLCK;
                    lock.l_whence = SEEK_SET;
                    lock.l_start = 0;
                    lock.l_len = 0;
                    lock.l_pid = getpid();
                    fcntl(fp, F_SETLKW, &lock);
                    int user_found = 0;
                    struct User user;
                    while(read(fp,&user,sizeof(struct User))>0)
                    {
                        if(strcmp(user.username,username)==0)
                        {
                            char *msg = "User found!";
                            send(nsd, msg, strlen(msg), 0);
                            user_found = 1;
                            break;
                        }
                    }
                    fcntl(fp, F_UNLCK, &lock);
                    close(fp);
                    if(!user_found)
                    {
                        char *msg = "User not found!";
                        send(nsd, msg, strlen(msg), 0);
                    }
                }
                else if(strcmp(buffer,"7")==0)
                {
                    printf("Waiting for the bookID\n");
                    char bookID[100];
                    n=recv(nsd, bookID, sizeof(bookID)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    bookID[n]='\0';
                    printf("Received bookID\n");
                    printf("Waiting for the quantity\n");
                    char quantity[100];
                    n=recv(nsd, quantity, sizeof(quantity)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    quantity[n]='\0';
                    printf("Received quantity\n");
                    int fp=open("books.txt",O_RDWR);
                    if(fp==-1)
                    {
                        perror("File not found");
                        exit(1);
                    }
                    struct flock lock;
                    lock.l_type = F_WRLCK;
                    lock.l_whence = SEEK_SET;
                    lock.l_start = 0;
                    lock.l_len = 0;
                    lock.l_pid = getpid();
                    fcntl(fp, F_SETLKW, &lock);
                    int book_found = 0;
                    struct Book book;
                    struct Book book1;
                    while(read(fp,&book,sizeof(struct Book))>0)
                    {
                        if(strcmp(book.bookID,bookID)==0)
                        {
                            strcpy(book.quantity,quantity);
                            lseek(fp, -sizeof(struct Book), SEEK_CUR);
                            write(fp,&book,sizeof(struct Book));
                            book_found = 1;
                            break;
                        }
                    }
                    fcntl(fp, F_UNLCK, &lock);
                    close(fp);
                    if(book_found)
                    {
                        char *msg = "Quantity updated successfully!";
                        send(nsd, msg, strlen(msg), 0);
                    }
                    else
                    {
                        char *msg = "Book not found!";
                        send(nsd, msg, strlen(msg), 0);
                    }
                }
                else if(strcmp(buffer,"8")==0)
                {
                    close(nsd);
                    exit(0);
                }
            }
            while(strcmp(choice,"User")==0)
            {
                memset(buffer, 0, sizeof(buffer));
                int n = recv(nsd, buffer, sizeof(buffer)-1, 0);
                if(n == -1)
                {
                    perror("Receive failed");
                    exit(1);
                }
                buffer[n] = '\0';
                printf("Option selected by user: %s\n", buffer);
                if(strcmp(buffer,"1")==0)
                {
                    printf("Waiting for the bookname\n");
                    char bookname[100];
                    n=recv(nsd, bookname, sizeof(bookname)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    bookname[n]='\0';
                    printf("Received bookname\n");
                    printf("Waiting for the quantity\n");
                    char quantity[100];
                    n=recv(nsd, quantity, sizeof(quantity)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    quantity[n]='\0';
                    printf("Received quantity\n");
                    int fp=open("books.txt",O_RDWR);
                    if(fp==-1)
                    {
                        perror("File not found");
                        exit(1);
                    }
                    struct flock lock;
                    lock.l_type = F_WRLCK;
                    lock.l_whence = SEEK_SET;
                    lock.l_start = 0;
                    lock.l_len = 0;
                    lock.l_pid = getpid();
                    fcntl(fp, F_SETLKW, &lock);
                    int book_found = 0;
                    int success=0;
                    struct Book book;
                    while(read(fp,&book,sizeof(struct Book))>0)
                    {
                        if(strcmp(book.bookname,bookname)==0)
                        {
                            int q=atoi(book.quantity)-atoi(quantity);
                            if(q>=0)
                            {
                                sprintf(book.quantity,"%d",q);
                                lseek(fp, -sizeof(struct Book), SEEK_CUR);
                                write(fp,&book,sizeof(struct Book));
                                book_found = 1;
                                success=1;
                                break;
                            }
                            else
                            {
                                book_found = 1;
                                success=0;
                                break;
                            }
                        }
                    }
                    fcntl(fp, F_UNLCK, &lock);
                    close(fp);
                    if(book_found)
                    {
                        if(success==1)
                        {
                            char *msg = "Book issued successfully!";
                            send(nsd, msg, strlen(msg), 0);
                        }
                        else
                        {
                            char *msg = "Book not available!";
                            send(nsd, msg, strlen(msg), 0);
                        }
                    }
                    else
                    {
                        char *msg = "Book not found!";
                        send(nsd, msg, strlen(msg), 0);
                    }
                }
                else if(strcmp(buffer,"2")==0)
                {
                    printf("Waiting for the bookname\n");
                    char bookname[100];
                    n=recv(nsd, bookname, sizeof(bookname)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    bookname[n]='\0';
                    printf("Received bookname\n");
                    printf("Waiting for the quantity\n");
                    char quantity[100];
                    n=recv(nsd, quantity, sizeof(quantity)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    quantity[n]='\0';
                    printf("Received quantity\n");
                    int fp=open("books.txt",O_RDWR);
                    if(fp==-1)
                    {
                        perror("File not found");
                        exit(1);
                    }
                    struct flock lock;
                    lock.l_type = F_WRLCK;
                    lock.l_whence = SEEK_SET;
                    lock.l_start = 0;
                    lock.l_len = 0;
                    lock.l_pid = getpid();
                    fcntl(fp, F_SETLKW, &lock);
                    int book_found = 0;
                    struct Book book;
                    while(read(fp,&book,sizeof(struct Book))>0)
                    {
                        if(strcmp(book.bookname,bookname)==0)
                        {
                            int q=atoi(book.quantity)+atoi(quantity);
                            sprintf(book.quantity,"%d",q);
                            lseek(fp, -sizeof(struct Book), SEEK_CUR);
                            write(fp,&book,sizeof(struct Book));
                            book_found = 1;
                            break;
                        }
                    }
                    fcntl(fp, F_UNLCK, &lock);
                    close(fp);
                    if(book_found)
                    {
                        char *msg = "Book returned successfully!";
                        send(nsd, msg, strlen(msg), 0);
                    }
                    else
                    {
                        char *msg = "Book not found!";
                        send(nsd, msg, strlen(msg), 0);
                    }
                }
                else if(strcmp(buffer,"3")==0)
                {
                    printf("Waiting for the bookname\n");
                    char bookname[100];
                    n=recv(nsd, bookname, sizeof(bookname)-1, 0);
                    if(n==-1)
                    {
                        perror("Receive failed");
                        exit(1);
                    }
                    bookname[n]='\0';
                    printf("Received bookname\n");
                    int fp=open("books.txt",O_RDONLY);
                    if(fp==-1)
                    {
                        perror("File not found");
                        exit(1);
                    }
                    struct flock lock;
                    lock.l_type = F_RDLCK;
                    lock.l_whence = SEEK_SET;
                    lock.l_start = 0;
                    lock.l_len = 0;
                    lock.l_pid = getpid();
                    fcntl(fp, F_SETLKW, &lock);
                    int book_found = 0;
                    struct Book book;
                    while(read(fp,&book,sizeof(struct Book))>0)
                    {
                        if(strcmp(book.bookname,bookname)==0)
                        {
                            char *msg = "Book found!";
                            send(nsd, msg, strlen(msg), 0);
                            book_found = 1;
                            break;
                        }
                    }
                    fcntl(fp, F_UNLCK, &lock);
                    close(fp);
                    if(!book_found)
                    {
                        char *msg = "Book not found!";
                        send(nsd, msg, strlen(msg), 0);
                    }
                }
                else if(strcmp(buffer,"4")==0)
                {
                    int fp=open("books.txt",O_RDONLY);
                    if(fp==-1)
                    {
                        perror("File not found");
                        exit(1);
                    }
                    struct flock lock;
                    lock.l_type = F_RDLCK;
                    lock.l_whence = SEEK_SET;
                    lock.l_start = 0;
                    lock.l_len = 0;
                    lock.l_pid = getpid();
                    fcntl(fp, F_SETLKW, &lock);
                    struct Book book;
                    char msg[MAXLINE];
                    strcpy(msg,"");
                    while(read(fp,&book,sizeof(struct Book))>0)
                    {
                        strcat(msg,book.bookID);
                        strcat(msg," ");
                        strcat(msg,book.bookname);
                        strcat(msg," ");
                        strcat(msg,book.quantity);
                        strcat(msg,"\n");
                    }
                    printf("%s\n",msg);
                    send(nsd, msg, strlen(msg), 0);
                    fcntl(fp, F_UNLCK, &lock);
                    close(fp);
                }
                else if(strcmp(buffer,"5")==0)
                {
                    break;
                }
            }
            pthread_exit(NULL);
}
int main()
{
    // Create a socket
    int sd;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd == -1)
    {
        perror("Socket failed");
        exit(1);
    }
    // Define the server address
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    socklen_t len1 = sizeof(server);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to our specified IP and port
    int b = bind(sd, (struct sockaddr *)&server, len1);
    if(b == -1)
    {
        perror("Bind failed");
        exit(1);
    }
    int l = listen(sd, 5);
    if(l == -1)
    {
        perror("Listen failed");
        exit(1);
    }
    pthread_t client_threads[5];
    int clients=0;
    int nsd;
    while(1)
    {
        // Accept the data packet from client and verification
        nsd = accept(sd, (struct sockaddr *)&client, &len);
        if(nsd == -1)
        {
            perror("Server acccept failed");
            exit(1);
        }
        pthread_create(&client_threads[clients], NULL, client_handler, (void *)&nsd);
        clients++;
        if(clients>=5)
        {
            for(int i=0;i<5;i++)
            {
                pthread_join(client_threads[i],NULL);
            }
            clients=0;
        }
    }
    close(nsd);
    close(sd);
    return 0;
}