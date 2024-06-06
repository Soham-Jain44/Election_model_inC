#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>


void clearscreen();
void results();
void admin();
int authenticate_admin();
void admin_panel();
void new_election();
void display_result();
void add_voter();
void update_schedule();
void schedule();
void voter();
void voter_panel();
int authenticate_voter();
void cast_vote();
void mainmenu();
void encrypt();
void sleep();
int total_voter_finder(int year_t);
int total_candidates_finder(int year_t);

int voter_total,total_candidates,year;
int student_votes_status[3000];
int final_exit = 0,result_dec = 0;
char temp_roll[10];
char temp_password[11];
char temp_roll1[9];
char temp_password1[10];
char encrypted[10];
char filename[20];


struct candidate{
    int cid;
    char cname[50];
    int votes;
};

struct voter{
    char v_roll[9];
    char v_name[50];
    char v_password[10];
};

void results(){
    clearscreen();
    printf("\n\n\t----> ENTER YEAR: ");
    scanf("%d",&year);
    FILE * f;
    sprintf(filename,"%dresults.txt",year);
    f = fopen(filename,"r");
    if(f == NULL){
        printf("***  RESULTS NOT DECLARED YET! PLEASE CONTACT ADMIN FOR DETAILS  ***\n");
        return;
    }
    char l[1000];
    printf("\n\n****  RESULTS FOR THE YEAR %d  ****\n",year);
    while(fgets(l,sizeof(l),f)){
        printf("\t%s\n",l);
    }
    fclose(f);
    getchar();
    mainmenu();
}

void admin(){
    clearscreen();
    printf("\033[1m");
    printf("\t\t\t - - - - - -  A D M I N   P A N E L - - - - - - \n\n");
    printf("\033[0m");
    int a = authenticate_admin();
    if(a!=1){
        printf("\t\tAUTHENTICATION FAILED !!!\n");
        mainmenu();
    }
    printf("\t\t\tLOGGED IN SUCCESFULLY!");
    sleep(2);
    printf("\033[1m");
    admin_panel();
    printf("\033[0m");
}

int authenticate_admin(){
     printf("\033[1m");
    printf("\t\t---> Please enter your username: ");
    printf("\033[0m");
    char admin_username[5];
    scanf("%s",admin_username);
    if(strcmp(admin_username,"Admin")!=0){
        return 0;
    }
    else{
        printf("\033[1m"); 
        printf("\t\t->Please enter your password: ");
        printf("\033[0m"); 
        char admin_password[10];
        scanf("%s",admin_password);
        if(strcmp(admin_password,"Admin@iit")!=0){
            return 0;
        }
    }
    return 1;
}

void admin_panel()
{
    clearscreen();
    printf("\t - - - - - - - W E L C O M E   A D M I N  - - - - - - - \n\n");
    printf("\t\t1. New Election\n\n\t\t2. Update schedule\n\n\t\t3. Display result\n\n\t\t4. Add Voter\n\n\t\t5. Log Out\n\n\n");
    printf("\t\tEnter your choice:");
    int a;
    scanf("%d",&a);
    switch(a){
        case 1:
            new_election();
            break;
        case 2:
            update_schedule();
            break;
        case 3:
            display_result();
            break;
        case 4:
            add_voter();
            break;
        case 5:
            clearscreen();
            mainmenu();
            break;
        default:
            printf("\t\tInvalid Input!");
            admin_panel();
            break;
    }
    admin_panel();
}

void new_election()
{
    clearscreen();
    printf("\n\t - - - - - - - - C R E A T I N G    N E W    E L E C T I O N    S P A C E  - - - - - - - - - \n");
    sleep(1);

    while(1){
        printf("\nElections for which Year:"); 
        scanf("%d",&year);
        if (year < 2030 && year > 2022) 
            break;
        printf("Invalid Year (Year should be between 2022 and 2030) !!!");
    }

    printf("Enter total number of voters:");
    scanf("%d",&voter_total);

    while(1){
        printf("Enter the no. of candidates:");
        scanf("%d",&total_candidates);
        if (total_candidates <= voter_total) 
            break;
        printf("NUMBER OF CANDIDATES CANNOT BE LARGER THAN NUMBER OF VOTERS!!!\n");
    }

    FILE* f1;
    char file[20];
    sprintf(file,"Elections_of_%d.txt",year);
    f1 = fopen(file,"w");
    if(f1 == NULL){
        printf("\n\n\tERROR INITIATING!!!\n\n");
        return ;
    }
    fprintf(f1,"%d\n",year);
    fprintf(f1,"%d\n",voter_total);
    fprintf(f1,"%d\n",total_candidates);

    struct candidate candi_array[total_candidates];
    getchar();
    for (int i = 0;i < total_candidates; i++)
    {
        candi_array[i].cid=i+1;
        printf("Enter name of candidate %d: ",i+1);
        gets(candi_array[i].cname);
        candi_array[i].votes=0;
    }
    for (int i =0 ; i<total_candidates ; i++){
        FILE *f;       
        sprintf(filename,"%dcandidate%d.txt",year,i+1);
        f = fopen(filename, "w");
        if(f==NULL){
            printf("\n\nError opening new files for election!!\n\n");
            return ;
        }
        fprintf(f,"%d    \n%s",0,candi_array[i].cname);
        fclose(f);
    }
    
    printf("\n-> CREATED FILES SUCCESSFULLY <-\n\n");
    printf("NEW ELECTIONS IS READY TO BE HOSTED!\n");
    fclose(f1);
    sleep(4);
    admin_panel();
    return ;
}

void update_schedule()
{
    FILE *f;
    f = fopen("schedule.txt","w");
    if(f==NULL){
        printf("\t\tERROR IN OPENING FILE!!!");
        return ;
    }
    char input[20];
    printf("UPDATE THE DATES FOR ELECTIONS:\n");
        
    printf("Enter the date for SOP submission of candidates:");
    scanf("%s",input);
    fprintf(f,"Date for SOP submission of candidates is %s \n\n",input);

    printf("Enter the date for SOP session :");
    scanf("%s",input);
    fprintf(f,"Date for SOP session is %s \n\n",input);

    printf("Enter the date for voting:");
    scanf("%s",input);
    fprintf(f,"Date for Voting is %s \n\n",input);

    printf("Enter the date for result :");
    scanf("%s",input);
    fprintf(f,"Date for result declaration is %s \n\n",input);


    printf("\n\n UPDATED THE SCHEDULE SECCESSFULLY!!!\n\n");
    fclose(f);
    sleep(2);
    return ;
}

int total_candidates_finder(int year_t){
    sprintf(filename,"Elections_of_%d.txt",year_t);
    FILE * file;
    file=fopen(filename,"r");
    if(file==NULL){
        printf("Error opening file!\n");
        sleep(2);
        return 0;
    }
    fscanf(file,"%*s\n%*d\n%d\n",&total_candidates);
    fclose(file);
    return total_candidates;
}

int total_voter_finder(int year_t){
    sprintf(filename,"Elections_of_%d.txt",year_t);
    FILE * file;
    file=fopen(filename,"r");
    if(file==NULL){
        printf("Error opening file!\n");
        sleep(2);
        return 0;
    }
    fscanf(file,"%*s\n%d\n%*d\n",&voter_total);
    fclose(file);
    return voter_total;
}

void display_result(){
    printf("Enter the year:");
    scanf("%d",&year);
    char votes[4],cand_name[50];
    FILE * f;
    total_candidates = total_candidates_finder(year);
    sprintf(filename,"%dresults.txt",year);
    f = fopen(filename,"w");
    if(f == NULL){
        printf("Error! PLease try again.\n");
        return;
    }
    for(int i=0;i<=total_candidates;i++)
    {
        FILE * file;
        sprintf(filename,"%dcandidate%d.txt",year,i);
        file = fopen(filename,"r");
        if(file == NULL && i!=0){
            printf("ERROR!!!\n");
            return ;
        }
        else if(file == NULL || i==0){
            continue ;
        }
        fseek(file, 0, SEEK_SET);
        fscanf(file,"%s\n%s",votes,cand_name);
        fprintf(f,"%d.%s got %s votes.\n",i,cand_name,votes);
        fclose(file);
    }
    printf("RESULTS ARE LIVE NOW !!\n\n");
    sleep(5);
    fclose(f);
    result_dec = 1;
}

void add_voter()
{
    int new_voters;
    printf("Enter the number of new voters you want to add:");
    scanf("%d",&new_voters);
    voter_total += new_voters;
    struct voter v_array[new_voters];
    FILE * f_voter;
    f_voter = fopen("voterdata.txt","a");
    if(f_voter == NULL){
        printf("Error in opening file.\n");
        return ;
    }

    for(int i=0;i<new_voters;i++)
    {
        printf("Enter the roll number:");
        scanf("%s",v_array[i].v_roll);
        fprintf(f_voter,"%s", v_array[i].v_roll);

        getchar();

        printf("Enter the name:");
        gets(v_array[i].v_name);
        fprintf(f_voter," %s ",v_array[i].v_name);

        printf("Enter the password:");
        gets(v_array[i].v_password);
        encrypt(v_array[i].v_password);
        fprintf(f_voter,"%s ",encrypted);
        fprintf(f_voter,"%d\n",0);
        
        printf("\t\tSUCCESS !!!\n");
    }
    fclose(f_voter);
    sleep(2);
}

void encrypt(char password[])
{   // e=5, d=77; x= 17; y=13.
    long int i=0, len=strlen(password);
    int e=5;
    while(i!=len){
        int k=1;
        for(int j=0; j<e; j++){
            k=k*password[i];
            k=k%(17*13);
        }
        encrypted[i]=k;
        i++;
    }
}

void clearscreen()
{
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        // For macOS and Linux
        system("clear"); // Executes the "clear" command to clear the console screen
    #endif
}

void voter()
{
    clearscreen();
    printf("- - - - - - W E L C O M E   T O   V O T I N G   P O R T A L - - - - - - \n\n");
    sleep(1);
    int a = authenticate_voter();
    if(a!=1){
        printf("INVALID ID or PASSWORD\n");
        sleep(2);
        clearscreen();
        mainmenu();
    }
    voter_panel();
}

void voter_panel()
{
    printf("PLEASE CHOOSE:\n1.Cast Your Vote\n2.Logout\n\nOption:");
    int b;
    scanf("%d",&b);
    switch(b){
        case 1:
            cast_vote();
            break;
        case 2:
            clearscreen();
            mainmenu();
            break;
        default:
            printf("Please enter a valid choice!");
            voter_panel();
            break;
    }
    mainmenu();
}

int authenticate_voter() {
    getchar();

    printf("Please enter your roll number:");
    fgets(temp_roll, sizeof(temp_roll), stdin);
    temp_roll[strcspn(temp_roll, "\n")] = '\0';

    getchar();

    printf("Please enter your password:");
    fgets(temp_password, sizeof(temp_password), stdin);
    temp_password[strcspn(temp_password, "\n")] = '\0';
    encrypt(temp_password);

    FILE *f = fopen("voterdata.txt", "r");
    if (f == NULL) {
        printf("Error loading the details of voters!\n");
        return 0;
    }

    char temp_roll1[10];
    char temp_password1[11];
    int found = 0;

    while (fscanf(f, "%9s %*s %10s %*s", temp_roll1, temp_password1) == 2) {
        if (strcmp(temp_roll, temp_roll1) == 0 && strcmp(encrypted, temp_password1) == 0) {
            found = 1;
            break;
        }
    }

    fclose(f);
    return found;
}

void cast_vote()
{   
    printf("Enter the year of election:");
    int year1;
    scanf("%d",&year1);
    int v_status;

    FILE * f;
    f = fopen("voterdata.txt","r+");

    if(f == NULL)
        printf("Error opening file!\n");

    voter_total = total_voter_finder(year1);
    
    total_candidates = total_candidates_finder(year1);

    for(int i=0;i<voter_total;i++){
        fscanf(f,"%9s %*s %*s %d",temp_roll1,&v_status);
        if(strcmp(temp_roll,temp_roll1)==0 && v_status == 0){

            printf("CANDIDATES CONTESTING IN THE ELECTION:\n");
            for(int i=0;i<total_candidates;i++){
                FILE * file;
                sprintf(filename,"%dcandidate%d.txt",year1,i+1);
                file = fopen(filename,"r");
                if(file == NULL){
                    printf("ERROR!!\n");
                    return;
                }
                char candi_name[50];
                fscanf(file,"%*s\n%s",candi_name);
                printf("%d.%s\n",i+1,candi_name);
                fclose(file);
            }
            printf("Choose the candidate you want to vote for: ");
            int a;
            scanf("%d",&a);
            for(int i=1;i<=total_candidates;i++){
                if(a == i){
                    FILE * file;
                    sprintf(filename,"%dcandidate%d.txt",year1,i);
                    file = fopen(filename,"r+");
                    if(file == NULL){
                        printf("ERROR!!!\n");
                        return;
                    }
                    fseek(file, 0, SEEK_SET);
                    int votes;
                    fscanf(file,"%d",&votes);
                    votes++;
                    fseek(file, 0, SEEK_SET);
                    fprintf(file,"%d",votes);
                    fclose(file);
                    fseek(f,-1,SEEK_CUR);
                    fprintf(f,"%d",1);
                    fclose(f);
                }   
            }
            printf("ADDED YOUR VOTE SUCCESSFULLY !!!\n");
            sleep(4);
            mainmenu();
        }
    }
    printf("You cannot vote!\n(Either you have already voted or please re-enter your roll number and password)\n");
    sleep(5);
    fclose(f);
    voter();
}

void schedule()
{
    FILE * f;
    f = fopen("schedule.txt","r");
    char l[1000];
    if(f==NULL){
        printf("\t\tERROR IN OPENING FILE!\n");
        sleep(2);
        clearscreen();
        return ;
    }
    clearscreen();
    printf("SCHEDULE:\n");
    while(fgets(l,sizeof(l),f)){
        printf("%s",l);
    }
    printf("\n\n");
    fclose(f);
    sleep(3);
    return ;
}

void mainmenu(){
    printf("--> What would you like to do:\n\n");//edd
    printf("\t1. Check Schedule\n\n\t2. Check Results\n\n\t3. Admin\n\n\t4. Voter\n\n\t5. Exit\n\n");
    printf("Enter your choice: ");
    printf("\033[0m");
    char a;
    scanf("%c",&a);

    switch (a){
    case '1':
        schedule();
        break;
    case '2':
        results();
        printf("\n\n\n");
        mainmenu();
        break;
    case '3':
        admin();
        break;
    case '4':
        voter();
        break;
    case '5':
        exit(0);
        break;
    default:
        printf("Enter a valid choice.\n");
        clearscreen();
    }
    mainmenu();
}

int main(){
    clearscreen();
    voter_total=0;
    printf("\033[1m");
    printf("\t\t- - - - - - - - - - - -  W E L C O M E  - - - - - - - - - - - -\n\n\n");
    mainmenu();
}