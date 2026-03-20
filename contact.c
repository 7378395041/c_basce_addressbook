#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
int unique_phone(char temp[],AddressBook *addressbook) //check whether entered phone is unique or not
{
    int i;
    for(i =0; i<addressbook->contactCount; i++)
    {
        if(strcmp(addressbook->contacts[i].phone,temp)==0)
        {
            printf("Enter a unique phone number , as number already exists\n");
            return 1;
        }
    }
    return 0;
}
int unique_email(char temp[],AddressBook *addressbook) //check whether entered phone is unique or not
{
    int i;
    for(i =0; i<addressbook->contactCount; i++)
    {
        if(strcmp(addressbook->contacts[i].phone,temp)==0)
        {
            printf("Enter a unique email , as email already exists\n");
            return 1;
        }
    }
    return 0;
}
int validate_name(char temp[])  // validate whether user is entering proper name or not
{
    int i = 0;
    while(temp[i] != '\0')
    {
        if(temp[i] >= 'a' && temp[i] <= 'z' || temp[i] >= 'A' && temp[i] <= 'Z'||temp[i] == ' ')
        {
            i++;
        }
        else
        {
            printf("Invalid name entered\n");
            return 1;
        }
    }
    return 0;

}
int validate_phone(char temp[])  // validate whether user is entering proper phone or not
{
    int i = 0;
    while(temp[i] != '\0')
    {
        if(temp[i] >= '0' && temp[i] <= '9')
        {
            i++;
        }
        else
        {
            printf("Invalid phone number entered\n");
            return 1;
        }
    }
    if(10 > i || i > 10)
    {
        printf("\tEnter a valid phone number\n");
        return 1;
    }
    return 0;

}
int validate_email(char temp[])  // validate whether user is entering proper email or not
{
    char com[] = ".com";
    char aderate[] = "@";

    if(strstr(temp, com) == NULL)
    {
        printf("\t Enter email is invalid \"com\" is missing\n");
        return 1;
    }
    if(strstr(temp, aderate) == NULL)
    {
        printf("\t Enter email is invalid \"@\" is missing\n");
        return 1;
    }
    return 0;
}

void listContacts(AddressBook *addressbook, int sortCriteria) 
{
    Contact dummy;
    int i,j;
    switch(sortCriteria)
    {
        case 1 :
            printf("Sorted based on name\n");
            for(i =0; i < addressbook->contactCount-1;i++)
            {
                for(j=0; j<addressbook->contactCount-1; j++)
                {
                    if((strcmp(addressbook->contacts[j].name,addressbook->contacts[j+1].name))>0)
                    {
                        dummy = addressbook->contacts[j];
                        addressbook->contacts[j] = addressbook->contacts[j+1];
                        addressbook->contacts[j+1] = dummy;

                    }
                }
            }

            break;
        case 2 :
            printf("Sorted based on phone\n");
            for(i =0; i < addressbook->contactCount-1;i++)
            {
                for(j=0; j<addressbook->contactCount-1; j++)
                {
                    if((strcmp(addressbook->contacts[j].phone,addressbook->contacts[j+1].phone ))>0)
                    {
                        dummy = addressbook->contacts[j];
                        addressbook->contacts[j] = addressbook->contacts[j+1];
                        addressbook->contacts[j+1] = dummy;

                    }
                }
            }
             break;
        case 3 :
            printf("Sorted based on email\n");
            for(i =0; i < addressbook->contactCount-1;i++)
            {
                for(j=0; j<addressbook->contactCount-1; j++)
                {
                    if((strcmp(addressbook->contacts[j].email,addressbook->contacts[j+1].email))>0)
                    {
                        dummy = addressbook->contacts[j];
                        addressbook->contacts[j] = addressbook->contacts[j+1];
                        addressbook->contacts[j+1] = dummy;

                    }
                }
            }
            break;
            default:
                printf("Selection criteria is invalid\n");
                return;
            
    }
    printf("____________________________________________________________>\n");
    printf("INDEX\tNAME\t\tMOBILE NUMBER\t\tEMAIL\n");
    printf("_____________________________________________________________>\n");

    for(i=0 ; i<addressbook->contactCount; i++)
    {
        printf("%d\t%s\t%s\t%s\n",i+1,addressbook->contacts[i].name,addressbook->contacts[i].phone,addressbook->contacts[i].email);
    }
    // Sort contacts based on the chosen criteria 
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
   // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    char temp[50];
    printf("Menu -->Create Contact\n");
    printf("____________________________________________>\n");
    do
    {
        printf("Enter the name\n");
        scanf(" %[^\n]", temp);
        getchar();
    } while (validate_name(temp));
   
    strcpy(addressBook->contacts[addressBook->contactCount].name, temp);
    
    do
    {
        printf("Enter the phone number\n");
        scanf("%s",temp);
        getchar();
    } while (validate_phone(temp)|unique_phone(temp, addressBook));
    strcpy(addressBook->contacts[addressBook->contactCount].phone, temp);

    do
    {
        printf("Enter the email\n");
        scanf("%s",temp);
        getchar();
    } while (validate_email(temp)|unique_email(temp, addressBook));
    strcpy(addressBook->contacts[addressBook->contactCount].email, temp);
    printf("Contact create successfully\n");
    addressBook->contactCount++;

}

int searchContact(AddressBook *addressBook) 
{
    int opt, count = 0;
    char temp[20];
    printf("Menu > Search Contact\n");
    printf("______________________________________________________>\n");
    printf("Press 1 for search by name\t\nPress 2 for search by phone number\t\nPress 3 for search by email\n");
    scanf("%d",&opt);
    getchar();
   
    switch (opt)
    {
        case 1:
        do
        {
            printf("Enter the name\n");
            scanf("%[^\n]",temp);
            getchar();
        } while (validate_name(temp));
        for(int i=0; i<addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].name, temp) != NULL)
            {
                count++;
                printf("%d\t%s\t%s\t%s\n",i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            }
        }
        if(count == 0)
        {
            printf("Contact not found\n");
             return 0;
        }
        break;
    
        case 2 :
        do
        {
            printf("Enter the phone number\n");
            scanf("%[^\n]",temp);
            getchar();
        } while (validate_phone(temp));

        for(int i=0; i<addressBook->contactCount; i++)
        {
                if(strcasestr(addressBook->contacts[i].phone, temp) != NULL)
                {
                    count++;
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone, addressBook->contacts[i].email);
                }
        }
        if(count == 0)
        {
            printf("Contact not found\n");
             return 0;
        }
        break;

        case 3 :
        do
        {
            printf("Enter the email\n");
            scanf("%[^\n]",temp);
            getchar();
        } while (validate_email(temp));
        for(int i=0; i<addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].email, temp) != NULL)
            {
                count++;
                printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
        }
        if(count == 0)
        {
            printf("Contact no found");
            return 0;
        }
        break;
          
    }

}
void editContact(AddressBook *addressBook)
{
    char var[50];
    int index , opt, count =0;
    printf("Menu ---> Edit Contact\n");
    printf("________________________________________________________>\n");
    if(!searchContact(addressBook))
    return;
    printf("Enter the Index to edit --->\n");
    scanf("%d",&index);
    getchar();
    if(index < 0 ||index > addressBook->contactCount)
    {
        printf("You have entered invalid index\n");
        return;
    }
    edit :
    printf("Press 1 Edit name\nPress 2 Edit phone number\nPress 3 Edit email\n");
    scanf("%d",&opt);
    getchar();
    switch(opt)
    {
        case 1 :
        do
        {
            printf("Enter the name to edit\n");
            scanf("%[^\n]",var);
            getchar();
        } while (validate_name(var));
        
        strcpy(addressBook->contacts[index-1].name , var);
        printf("Name edited successfully\n");
        break;
    case 2 :
        do
        {
            printf("Enter the phone number to edit\n");
            scanf("%[^\n]",var);
            getchar();
        } while (validate_phone(var)|unique_phone(var , addressBook));
        
        strcpy(addressBook->contacts[index-1].phone , var);
        printf("Phone number edited successfully\n");
        break;
    case 3 :
        do
        {
            printf("Enter the email to edit\n");
            scanf("%[^\n]",var);
            getchar();
        } while (validate_email(var)|unique_email(var, addressBook));
        
        strcpy(addressBook->contacts[index-1].email , var);
        printf("Email edited successfully\n");
        break;
        default:
        printf("Entered option is invalid\n");
        goto edit ;

}

}
void deleteContact(AddressBook *addressBook)
{
    int index,i;
    printf("Menu --> delete contact\n");
    printf("___________________________________________________>\n");
    if(!searchContact(addressBook))
    return;
    printf("Enter the index to delete--->     \n");
    scanf("%d",&index);
    getchar();
    if( index<0 || index>addressBook->contactCount)
    {
        printf("You have entered a invalid index\n");
        return;
    }
    for(i = index-1; i<addressBook->contactCount-1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("Contact delete successfully\n");
	
}

