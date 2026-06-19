#include "text_buffer.h"

int main(){
    char **buffer=NULL;
    const char *fileName="buffer.txt";
    int count=LoadFromFile(&buffer,fileName);
    char temp[MAX];
    int value;
    do{
        printf("Enter 1 to add new line, 2 to insert new line at an index, 3 to delete a line at an index, 4 to edit a line, 5 to sort all lines alphabetically , 6 to search for a substring, 7 to display all lines, 8 to view text lines related statistics, 9 to save changes, 10 to exit \n");
        fgets(temp,MAX,stdin);
        temp[strcspn(temp,"\n")]='\0';
        for(int a=0;temp[a]!='\0';a++) {
            if(!isdigit(temp[a])) {
                temp[a]='\0';
                break;
            }
        }
        value=atoi(temp);
        switch (value) {
            case 1:
                AddNewLine(&buffer,&count);
                break;
            case 2: {
                int index;
                printf("Enter index(0 to %d) at which new line is to be inserted \n",count-1);
                scanf("%d",&index);
                ClearInputBuffer();
                InsertLine(&buffer,&count,index);
                break;
            }
            case 3: {
                int index;
                printf("Enter index(0 to %d) at which line is to be deleted \n",count-1);
                scanf("%d",&index);
                ClearInputBuffer();
                DeleteLine(&buffer,&count,index);
                break;
            }
            case 4: {
                int index;
                printf("Enter index(0 to %d) at which line is to be edited \n",count-1);
                scanf("%d",&index);
                ClearInputBuffer();
                EditLine(buffer,count,index);
                break;
            }
            case 5:
                SortLines(buffer,count);
                break;
            case 6: {
                char searchText[MAX];
                printf("Enter the substring to search for \n");
                fgets(searchText,MAX,stdin);
                searchText[strcspn(searchText,"\n")]='\0';
                Search(buffer,count,searchText);
                break;
            }
            case 7:
                DisplayLines(buffer,count);
                break;
            case 8:
                printf("Total characters: %d\tTotal Lines: %d\tAverage length of a line: %d\n",CountChar(buffer,count),count,AvgLength(buffer,count));
                break;
            case 9:
                SaveToFile(buffer,count,fileName);
                break;
            case 10: {
                int x;
                do{
                    printf("Do you want to save your changes(1 for yes and 0 for no) \n");
                    scanf("%d",&x);
                    ClearInputBuffer();
                } while(x<0 || x>1);
                if(x==1){
                    SaveToFile(buffer,count,fileName);
                }
                printf("Exitting...\n");
                CleanMemory(buffer,count);
                break;
            }
            default:
                printf("Invalid choice\n");
        }
    } while(value!=10);
    return 0;
}