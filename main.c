#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define buffer_size 100
#define MAX_LINE_LENGTH 100

void account(void);
void clear(void);
void transfer(void);
void balance(void);

int main(void) 
{
while(1){

  int option =0;

  while(1){

  char buffer[100];
  int buffersize = sizeof(buffer)/sizeof(char);
  int digitVerify=0;

  printf("This is Bank Management System with C.\n\n\n");

    printf("\t\t[Main]\n\n");

    printf("1. Making an account.\n");
    printf("2. Checking account balance.\n");
    printf("3. Transfer\n");
    printf("4. Exit\n");
    printf("Please select the option : ");

    fgets(buffer, buffersize, stdin);

  for(int i=0; i < buffersize; i++){
   if (isdigit(buffer[i]) == 0){
     clear();
     printf("Invalid option, try again.\n");
     sleep(3);
     clear();
     break;
   }
     if(strcmp(&buffer[i+1], "\n") == 0) {
       digitVerify = 1;
       break;
     };
  }
    if(digitVerify == 1){
    option = atoi(buffer);
      break;
    }
}


switch(option) {

     case 1:
       clear();
       printf("\t[CREATING ACCOUNT]\n");
      account();
      break;

      case 2:
        clear();
        printf("\t[CHECKING ACCOUNT BALANCE]\n");
       balance();
     break;

      case 3:
        clear();
        printf("\t[TRANSFER MONEY]\n");
        transfer();
     break;

      case 4:
        clear();
          printf("Exiting the program.\n");
        sleep(3);
        clear();
        return(0);

      default:
        clear();
      printf("Invalid option, try again.\n");
        sleep(3);
        clear();
}
}
  return 0;
}

void account(void) 
{
  struct cl{
  char fname[11];
   char lname[11];
   char age[4];
   char phonenum[11];
   char email[51];
   char password[16];
   char confirmpassword[16];
   int a;
};
  char accountname[61] ={0};
  struct cl client;

  while(1){
  printf("Please enter your email : ");
   scanf("%s", client.email);
    sprintf(accountname, "accounts/%s.txt", client.email);
    if(access(accountname, F_OK) == 0){
      printf("This email is already in use.\n");
      sleep(1);
  }
    else{
      printf("This email can be used.\n");
      sleep(1);
      break;

    }
  }
   printf("Please enter your First name : ");
   scanf("%10s", client.fname);

   printf("Please enter your Last name : ");
   scanf("%10s", client.lname);
  getchar();
while(1){

   printf("Please enter your age : ");
  fgets(client.age, 4, stdin);
  int digitVerify = 0;

  // printf("%d\n", isdigit(client.age[0]));
  // printf(" this is length %ld\n", strlen(client.age));

  for(int i=0; i < strlen(client.age)-1; i++){
  if(isdigit(client.age[i]) != 0){
    digitVerify++;
    //https://stackoverflow.com/questions/26583717/how-to-scanf-only-integer
  }
    }
  if(digitVerify == strlen(client.age)-1) break;
  else printf("Please enter a number.\n");
}
  client.age[strcspn(client.age, "\n")] = 0;
   printf("Please enter your phone number : ");
   scanf("%10s", client.phonenum);

  while(1){
   printf("Please enter your password : ");
   scanf("%15s", client.password);

   printf("Please enter your confirm password : ");
   scanf("%15s", client.confirmpassword);
    getchar();

   if(strcmp(client.password, client.confirmpassword) == 0){
     printf("Password match.\n");
     break;
   }
      else{
        printf("Password does not match.\n");
        sleep(3);
      }
   }


  FILE *fp;

  fp = fopen(accountname, "w");

  fprintf(fp, "Email : %s\nFirstName : %s\nLastName : %s\nAge : %s\nPhoneNumber : %s\nPassword : %s\nBalance : $0", client.email, client.fname, client.lname, client.age, client.phonenum, client.password);

  fclose(fp);
  printf("%s","ACCOUNT MAKING SUCCESSFUL!\n");

  sleep(3);
  clear();
}

void balance(void)
{
  char Bemail[51];
  char Bpassword[16];
  char Bpasswordconfirm[16];
  char Baccountname[31];

  printf("Please write your email : ");
  scanf("%50s", Bemail);
  sprintf(Baccountname, "accounts/%s.txt", Bemail);
  printf("Please enter your password : ");
  scanf("%s",Bpassword);
  getchar();

    if(access(Baccountname, F_OK) == 0){
      FILE *fp;
      fp = fopen(Baccountname, "r");

      if(fp == NULL){
        printf("There was error while opening file.\n");
        exit(-1);
      }

      char buf[51];
      unsigned int balancebuf;
      for(int i = 0; i < 6; i++) fscanf(fp, "%*s : %s",buf);

      // printf("%s\n",buf);

      if(strcmp(Bpassword, buf)==0){
        printf("Password Match.\n");
        for(int i = 0; i < 7; i++)
        fscanf(fp, "%*s : $%u",&balancebuf);
        fclose(fp); 
        sleep(2);
        if(fp == NULL){
        printf("The file is modified in unusual way.\n");
          fclose(fp); 
      }
        printf("------------------------------------------------\n");
        printf("\n\n\n|\tBalance of your account is $%u\t|\n\n\n", balancebuf);
        printf("------------------------------------------------\n");
        printf("[ENTER ANY KEY TO CONTINUE]\n");
        char Anykey = 0;
        Anykey = getchar();
        getchar();
        clear();
      }
      else{
        printf("Account does not exist or The pssword does not match.\n");
        sleep(3);
        clear();
      }
    }
    else{
      printf("Account does not exist or The pssword does not match.\n");
      sleep(3);
      clear();

    }
}

void transfer(void)
{
  char buffer[buffer_size];
  unsigned int TransferAmount;

  char TransferEmail[51];
  char TransferPassword[16];
  char TransferPasswordConfirm[16];
  // char TransferFirstName[11];
  // char TransferLastName[11];
  // char TransferOwnerName[21];
  char TransferAccountName[31];

  char TargetEmail[51];
  char TargetPassword[16];
  char TargetFirstName[11];
  char TargetLastName[11];
  char TargetOwnerName[21];
  char TargetAccountName[31];
  unsigned int TargetBalancebuf;

    printf("Please write your email : ");
    scanf("%50s", TransferEmail);
    sprintf(TransferAccountName, "accounts/%s.txt", TransferEmail);
    printf("Please enter your password : ");
    scanf("%s",TransferPassword);
    getchar();

      if(access(TransferAccountName, F_OK) == 0){
        FILE *fp3;
        fp3 = fopen(TransferAccountName, "r");

        if(fp3 == NULL){
          printf("There was error while opening file.\n");
          exit(-1);
        }

        char buf[51];
        unsigned int balancebuf;
        unsigned int balancebufChecker;
        char TransferFirstName[11];
        char TransferLastName[11];
        for(int i = 0; i < 6; i++) fscanf(fp3, "%*s : %s",buf);

        // printf("%s\n",buf);

        if(strcmp(TransferPassword, buf)==0){
          printf("Password Match.\n");
          // fseek(fp3, 0,SEEK_SET);
          rewind(fp3);
          for(int i = 0; i < 2; i++)
            fscanf(fp3, "%*s : %s",TransferFirstName);
          fscanf(fp3, "%*s : %s",TransferLastName);
          for(int i = 0; i < 4; i++){
           fscanf(fp3, "%*s : $%d",&balancebuf);
            printf("%u\n",balancebuf);
            // for(int i = 0; i < 7; i++)
            //   fscanf(fp, "%*s : $%u",&balancebuf);
          }


          fclose(fp3); 
          sleep(2);
          clear();
          if(fp3 == NULL){
          printf("The file is modified in unusual way.\n");
            fclose(fp3); 
        }
          printf("------------------------------------------------\n");
          printf("\n\n|\t%s %s's Account Selected\t|\n\n", TransferFirstName, TransferLastName);
          printf("Is this your account? : [y/n]\n");
          char YorN = 0;
          YorN = getchar();
          if(YorN == 'y'){
            clear();
            while(1){
              printf("------------------------------------------------\n");
              printf("|\tBalance of Your account : $%u\t|\n",balancebuf);
              printf("Transfer ammount : ");
            scanf("%d", &TransferAmount);
            getchar();
            if(TransferAmount < balancebuf){
              clear();
              break;
            }
            else{
              printf("You don't have enough money.\n");
              sleep(2);
              clear();
            }
            }
            printf("------------------------------------------------\n");
            printf("Please write your target email : ");
            scanf(" %50s", TargetEmail);
            sprintf(TargetAccountName, "accounts/%s.txt", TargetEmail);
            printf("Please enter the name of this account owner(Order - First name Last name) : ");
            scanf("%s %s",TargetFirstName, TargetLastName);
            getchar();
            if(access(TargetAccountName, F_OK) == 0){
            FILE *fp;
            fp = fopen(TargetAccountName, "r");
              for(int i = 0; i < 2; i++)
              fscanf(fp,"%*s : %s", TargetFirstName);
              fscanf(fp,"%*s : %s", TargetLastName);
              for(int i = 0; i < 4; i++)
                fscanf(fp, "%*s : %u",&TargetBalancebuf);
              fclose(fp);
              clear();
            }
             printf("------------------------------------------------\n");
            printf("Are you trying to transfer\n\t$%u\nto %s %s's account?\n", TransferAmount, TargetFirstName, TargetLastName);
            printf("Is this true? : [y/n]\n");
            char YorN = 0;
            YorN = getchar();
            if(YorN == 'y'){
              char updateBalance[100];
              char updateBalance2[100];
              sprintf(updateBalance,"Balance : %u", TargetBalancebuf+TransferAmount);
              sprintf(updateBalance2,"Balance : %u", balancebuf-TransferAmount);
              clear();
              printf("------------------------------------------------\n");

              
              FILE *file = fopen(filename, "r+");  // Open the file for reading and writing

              if (file == NULL) {
                  printf("Error opening file %s\n", filename);
                  exit(-1);
              }

                 for (int i = 0; i < 6; i++) {
                      char line[MAX_LINE_LENGTH];
                      if (fgets(line, MAX_LINE_LENGTH, file) == NULL) {
                          printf("Error reading file\n");
                          fclose(file);
                          exit(-1);
                      }
                  }

                  int balance;
                  fscanf(file, "Balance : %d", );

                  // Update the balance
                  balance += amount;

                  // Move back to the beginning of the line and update the balance in the file
                  fseek(file, -strlen("Balance : ") - 1, SEEK_CUR);
                  fprintf(file, "%d\n", );

                  fclose(file);
              
              // FILE *fp;
              // FILE *fpTEMP;
              // FILE *fp2;
              // FILE *fpTEMP2;
              // char scanner[100];

              // // fp  = fopen(TargetAccountName, "r");
              // // fpTEMP = fopen("accounts/TargetTemp.txt", "w");
              // // fp2  = fopen(TargetAccountName, "r");
              // // fpTEMP2 = fopen("accounts/TargetTemp.txt", "w");
              // // if(fp == NULL || fp2 == NULL || fpTEMP == NULL || fpTEMP2 == NULL){
              // //   printf("There was error while opening file.\n");
              // //   exit(-1);
              // // }

              // // while(fgets(scanner, 100, fp) != NULL){
              // //   fputs(scanner, fpTEMP);
              // // }
              // // }



              // FILE *fp;
              // fp =fopen(TargetAccountName, "wr");
              // if(fp == NULL){
              //   printf("There was error while opening file.\n");
              //   exit(-1);
              // }
              // int count = 0;
              // while(fgets(buffer, buffer_size, fp) != NULL){
              //   count++;
              // if(count == 7){
              // fputs(updateBalance, fp);
              //   break;
              // }
              // }
              // fclose(fp);

              // FILE *fp2;
              // fp2 = fopen(TransferAccountName, "w");
              // if(fp2 == NULL){
              //   printf("There was error while opening file.\n");
              //   exit(-1);
              // }
              // count = 0;
              // while(fgets(buffer, buffer_size, fp2) != NULL){
              //   count++;
              // if(count == 7){
              // fputs(updateBalance2, fp2);
              //   break;
              // }
              // }
              // fclose(fp2);

              printf("\t\t[TRANSFER SUCCESSFUL!]\n");
              printf("|\tBalance of Your account : %u\t|\n",balancebuf-TransferAmount);

              }

          printf("------------------------------------------------\n");
          printf("[ENTER ANY KEY TO GO BACK TO MAIN]\n");
          char Anykey = 0;
          Anykey = getchar();
          getchar();
          clear();
        }
        else{
          printf("Account does not exist or The pssword does not match.\n");
          sleep(3);
          clear();
        }
      }
      else{
        printf("Account does not exist or The pssword does not match.\n");
        sleep(3);
        clear();
      }
  getchar();
}

void clear(void)
{
    #ifdef _WIN32 
       system("cls");

    #elif __APPLE__ 
      system("clear");

    #elif __linux__ 
        system("clear");
  #endif

}
