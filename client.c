#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/types.h>

#define PORT 8110
#define MAXLINE 1024

int main()
{
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1)
    {
        perror("Socket failed");
        exit(1);
    }
    struct sockaddr_in servaddr;
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(PORT);
    servaddr.sin_addr.s_addr=INADDR_ANY;
    if(connect(sfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
    {
        perror("Connect failed");
        exit(1);
    }
    char buff[MAXLINE];
    int n;
    char ch[10];
    int admin = 0;
    int x=0;
    while(x==0)
    {
        printf("Welcome to the library\n");
        printf("Login or Register or ForgotPass\n");
        scanf("%s",ch);
        send(sfd,ch,strlen(ch),0);
        if(strcmp(ch,"Login")==0)
        {
            char u[10],p[10],choice[10];
            printf("1. Admin\n");
            printf("2. User\n");
            scanf("%s",choice);
            if(strcmp(choice,"1")==0)
            {
                send(sfd,"Admin",5,0);
                printf("Enter your username\n");
                scanf("%s",u);
                send(sfd,u,strlen(u),0);
                printf("Enter your password\n");
                scanf("%s",p);
                send(sfd,p,strlen(p),0);
                n=recv(sfd,buff,MAXLINE,0);
                if(n<0)
                {
                    perror("Receive failed");
                    exit(1);
                }
                if(strcmp(buff,"Login successful")==0)
                {
                    printf("Login successful\n");
                    admin=1;
                    x=1;
                }
                else
                {
                    printf("Login failed\n");
                }
            }
            else if(strcmp(choice,"2")==0)
            {
                send(sfd,"User",4,0);
                printf("Enter your username\n");
                scanf("%s",u);
                send(sfd,u,strlen(u),0);
                printf("Enter your password\n");
                scanf("%s",p);
                send(sfd,p,strlen(p),0);
                n=recv(sfd,buff,MAXLINE,0);
                if(n<0)
                {
                    perror("Receive failed");
                    exit(1);
                }
                if(strcmp(buff,"Login successful")==0)
                {
                    printf("Login successful\n");
                    x=1;
                }
                else
                {
                    printf("Login failed\n");
                }
            }
            else
            {
                printf("Invalid input\n");
                exit(1);
            }
        }
        else if(strcmp(ch,"Register")==0)
        {
            char u[10],p[10],choice[10];
            printf("1. Admin\n");
            printf("2. User\n");
            scanf("%s",choice);
            if(strcmp(choice,"1")==0)
            {
                send(sfd,"Admin",5,0);
                printf("Enter your username\n");
                scanf("%s",u);
                send(sfd,u,strlen(u),0);
                printf("Enter your password\n");
                scanf("%s",p);
                send(sfd,p,strlen(p),0);
                n=recv(sfd,buff,MAXLINE,0);
                if(n<0)
                {
                    perror("Receive failed");
                    exit(1);
                }
                if(strcmp(buff,"Registration successful")==0)
                {
                    printf("Registration successful\n");
                }
                else
                {
                    printf("Registration failed\n");
                }
            }
            else if(strcmp(choice,"2")==0)
            {
                send(sfd,"User",4,0);
                printf("Enter your username\n");
                scanf("%s",u);
                send(sfd,u,strlen(u),0);
                printf("Enter your password\n");
                scanf("%s",p);
                send(sfd,p,strlen(p),0);
                n=recv(sfd,buff,MAXLINE,0);
                if(n<0)
                {
                    perror("Receive failed");
                    exit(1);
                }
                if(strcmp(buff,"Registration successful")==0)
                {
                    printf("Registration successful\n");
                }
                else
                {
                    printf("Registration failed\n");
                }
            }
            else
            {
                printf("Invalid input\n");
                exit(1);
            }
        }
        else if(strcmp(ch,"ForgotPass")==0)
        {
            char u[10],pass[10],choice[10];
            printf("1. Admin\n");
            printf("2. User\n");
            scanf("%s",choice);
            if(strcmp(choice,"1")==0)
            {
                send(sfd,"Admin",5,0);
                printf("Enter your username\n");
                scanf("%s",u);
                send(sfd,u,strlen(u),0);
                printf("Enter your new password\n");
                scanf("%s",pass);
                send(sfd,pass,strlen(pass),0);
                n=recv(sfd,buff,MAXLINE,0);
                if(n<0)
                {
                    perror("Receive failed");
                    exit(1);
                }
                printf("%s\n",buff);
            }
            else if(strcmp(choice,"2")==0)
            {
                send(sfd,"User",4,0);
                printf("Enter your username\n");
                scanf("%s",u);
                send(sfd,u,strlen(u),0);
                printf("Enter your new password\n");
                scanf("%s",pass);
                send(sfd,pass,strlen(pass),0);
                n=recv(sfd,buff,MAXLINE,0);
                if(n<0)
                {
                    perror("Receive failed");
                    exit(1);
                }
                printf("%s\n",buff);
            }
            else
            {
                printf("Invalid input\n");
                exit(1);
            }
        }
        else
        {
            printf("Invalid input\n");
        }
    }
    while(strcmp(ch,"Login") == 0 && admin == 1)
    {
        char op[100],bookID[100],bookname[100],username[100],qty[100],password[100];
        printf("1. Add a book\n");
        printf("2. Remove a book\n");
        printf("3. Add a user\n");
        printf("4. Remove a user\n");
        printf("5. Search for a book\n");
        printf("6. Search for a user\n");
        printf("7. Update the quantity of a book\n");
        printf("8. Exit\n");
        scanf("%s",op);
        send(sfd,op,strlen(op),0);
        if(strcmp(op,"1")==0)
        {
            printf("Enter the bookID of the book you want to add\n");
            scanf("%s",bookID);
            send(sfd,bookID,strlen(bookID),0);
            printf("Enter the name of the book you want to add\n");
            scanf("%s",bookname);
            send(sfd,bookname,strlen(bookname),0);
            printf("Enter the quantity of the book you want to add\n");
            scanf("%s",qty);
            send(sfd,qty,strlen(qty),0);
            memset(buff,0,sizeof(buff));
            n=recv(sfd,buff,MAXLINE,0);
            if(n<0)
            {
                perror("Receive failed");
                exit(1);
            }
            printf("%s\n",buff);
        }
        else if(strcmp(op,"2")==0)
        {
            printf("Enter the bookID of the book you want to remove\n");
            scanf("%s",bookID);
            send(sfd,bookID,strlen(bookID),0);
            memset(buff,0,sizeof(buff));
            n=recv(sfd,buff,MAXLINE,0);
            if(n<0)
            {
                perror("Receive failed");
                exit(1);
            }
            printf("%s\n",buff);
        }
        else if(strcmp(op,"3")==0)
        {
            printf("Enter the username of the user you want to add\n");
            scanf("%s",username);
            send(sfd,username,strlen(username),0);
            printf("Enter the password of the user you want to add\n");
            scanf("%s",password);
            send(sfd,password,strlen(password),0);
            memset(buff,0,sizeof(buff));
            n=recv(sfd,buff,MAXLINE,0);
            if(n<0)
            {
                perror("Receive failed");
                exit(1);
            }
            printf("%s\n",buff);
        }
        else if(strcmp(op,"4")==0)
        {
            printf("Enter the username of the user you want to remove\n");
            scanf("%s",username);
            send(sfd,username,strlen(username),0);
            memset(buff,0,sizeof(buff));
            n=recv(sfd,buff,MAXLINE,0);
            if(n<0)
            {
                perror("Receive failed");
                exit(1);
            }
            printf("%s\n",buff);
        }
        else if(strcmp(op,"5")==0)
        {
            printf("Enter the name of the book you want to search\n");
            scanf("%s",bookname);
            send(sfd,bookname,strlen(bookname),0);
            memset(buff,0,sizeof(buff));
            n=recv(sfd,buff,MAXLINE,0);
            if(n<0)
            {
                perror("Receive failed");
                exit(1);
            }
            printf("%s\n",buff);
        }
        else if(strcmp(op,"6")==0)
        {
            printf("Enter the username of the user you want to search\n");
            scanf("%s",username);
            send(sfd,username,strlen(username),0);
            memset(buff,0,sizeof(buff));
            n=recv(sfd,buff,MAXLINE,0);
            if(n<0)
            {
                perror("Receive failed");
                exit(1);
            }
            printf("%s\n",buff);
        }
        else if(strcmp(op,"7")==0)
        {
            printf("Enter the bookID of the book you want to update the quantity of\n");
            scanf("%s",bookID);
            send(sfd,bookID,strlen(bookID),0);
            printf("Enter the new quantity\n");
            scanf("%s",qty);
            send(sfd,qty,strlen(qty),0);
            memset(buff,0,sizeof(buff));
            n=recv(sfd,buff,MAXLINE,0);
            if(n<0)
            {
                perror("Receive failed");
                exit(1);
            }
            printf("%s\n",buff);
        }
        else if(strcmp(op,"8")==0)
        {
            close(sfd);
            exit(0);
        }
        else
        {
            printf("Invalid input\n");
        }
    }
    while(strcmp(ch,"Login") == 0 && admin == 0)
    {
        char op[100],bookID[100],bookname[100],username[100],qty[100];
        printf("1. Borrow a book\n");
        printf("2. Return a book\n");
        printf("3. Search for a book\n");
        printf("4. View all books\n");
        printf("5. Exit\n");
        scanf("%s",op);
        send(sfd,op,strlen(op),0);
        if(strcmp(op,"1")==0)
        {
            printf("Enter the name of the book you want to borrow\n");
            scanf("%s",bookname);
            send(sfd,bookname,strlen(bookname),0);
            printf("Enter the quantity of the book you want to borrow\n");
            scanf("%s",qty);
            send(sfd,qty,strlen(qty),0);
            memset(buff,0,sizeof(buff));
            n=recv(sfd,buff,MAXLINE,0);
            if(n<0)
            {
                perror("Receive failed");
                exit(1);
            }
            printf("%s\n",buff);
        }
        else if(strcmp(op,"2")==0)
        {
            printf("Enter the name of the book you want to return\n");
            scanf("%s",bookname);
            send(sfd,bookname,strlen(bookname),0);
            printf("Enter the quantity of the book you want to return\n");
            scanf("%s",qty);
            send(sfd,qty,strlen(qty),0);
            memset(buff,0,sizeof(buff));
            n=recv(sfd,buff,MAXLINE,0);
            if(n<0)
            {
                perror("Receive failed");
                exit(1);
            }
            printf("%s\n",buff);
        }
        else if(strcmp(op,"3")==0)
        {
            printf("Enter the name of the book you want to search\n");
            scanf("%s",bookname);
            send(sfd,bookname,strlen(bookname),0);
            memset(buff,0,sizeof(buff));
            n=recv(sfd,buff,MAXLINE,0);
            if(n<0)
            {
                perror("Receive failed");
                exit(1);
            }
            printf("%s\n",buff);
        }
        else if(strcmp(op,"4")==0)
        {
            memset(buff,0,sizeof(buff));
            // while(strcmp(buff,"End")!=0)
            // {
            //     memset(buff,0,sizeof(buff));
            //     n=recv(sfd,buff,MAXLINE,0);
            //     if(n<0)
            //     {
            //         perror("Receive failed");
            //         exit(1);
            //     }
            //     printf("%s\n",buff);
            // }
            n=recv(sfd,buff,MAXLINE,0);
            if(n<0)
            {
                perror("Receive failed");
                exit(1);
            }
            printf("%s\n",buff);
        }
        else if(strcmp(op,"5")==0)
        {
            close(sfd);
            exit(0);
        }
        else
        {
            printf("Invalid input\n");
        }
    }
    close(sfd);
    return 0;
}