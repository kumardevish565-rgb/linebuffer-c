#include "text_buffer.h"


void ClearInputBuffer() {
    int ch=getchar(); 
    while(ch!=EOF && ch!='\n') {
        ch=getchar();
    }
}

void CleanMemory(char **buffer, const int index){
    for(int a=0;a<index;a++){
        free(buffer[a]);
    } 
    free(buffer);
}

int ValidateIndex(const int lines, const int index){
    if(index<0 || index>=lines){
        printf("Invalid index\n");
        return 0;
    }
    else{
        return 1;
    }
}

char **ShrinkToFit(char **buffer, const int size){
    return realloc(buffer,(size-1)*sizeof(char *));    
}

void ShrinkToFitError(char ***buffer, char **temp, int *lines){
    if(temp==NULL){
        perror("Error: Memory re-allocation failed for buffer. Size is still the same\n");
        (*buffer)[*lines-1]=NULL;
    }
    else{
        *buffer=temp;
        (*lines)--;
    }
}

void AddNewLine(char ***buffer, int *lines){
    char **temp=realloc(*buffer,(*lines+1)*sizeof(char *));
    if(temp==NULL){
        perror("Error: Memory re-allocation failed for new line in buffer\n");
        return ;
    }
    *buffer=temp;
    (*lines)++;
    char tempBuffer[MAX];
    printf("Enter the new text line \n");
    fgets(tempBuffer,MAX,stdin);
    tempBuffer[strcspn(tempBuffer,"\n")]='\0';
    (*buffer)[*lines-1]=(char *)malloc((strlen(tempBuffer)+1) * sizeof(char));
    if((*buffer)[*lines-1]==NULL){
        perror("Error: Memory allocation failed for the text\n"); 
        if(*lines==1){
            *lines=0;
            free(*buffer);
            *buffer=NULL;
        }   
        else{
            temp=ShrinkToFit(*buffer,*lines);
            ShrinkToFitError(buffer,temp,lines);
        }
        return ;
    }
    strcpy((*buffer)[*lines-1],tempBuffer);
    printf("New line successfully added\n");
}

void InsertLine(char ***buffer, int *lines, const int index){
    if(ValidateIndex(*lines,index)==0){
        return ;
    }
    char tempBuffer[MAX];
    printf("Enter the text line to be inserted at index %d \n",index);
    fgets(tempBuffer,MAX,stdin);
    tempBuffer[strcspn(tempBuffer,"\n")]='\0';
    char *newline=(char *)malloc((strlen(tempBuffer)+1)*sizeof(char));
    if(newline==NULL){
        perror("Error: Memory allocation failed for the text\n"); 
        return ;  
    }
    strcpy(newline,tempBuffer);
    char **temp=realloc(*buffer,(*lines+1)*sizeof(char *));
    if(temp==NULL){
        perror("Error: Memory re-allocation failed for new line\n");
        free(newline);
        return ;
    }
    *buffer=temp;
    (*lines)++;
    for(int a=*lines-1;a>index;a--){
        (*buffer)[a]=(*buffer)[a-1];
    }
    (*buffer)[index]=newline;
    printf("New Line successfully inserted at index %d\n",index);
}

void DeleteLine(char ***buffer, int *lines, const int index){
    if(ValidateIndex(*lines,index)==0){
        return ;
    }
    free((*buffer)[index]);
    for(int a=index;a<*lines-1;a++){
        (*buffer)[a]=(*buffer)[a+1];
    }
    char **temp=NULL; 
    if(*lines==1){
        *lines=0;
        free(*buffer);
        (*buffer)=NULL;
    }  
    else{
        temp=ShrinkToFit(*buffer,*lines);
        ShrinkToFitError(buffer,temp,lines);
    }
    if(temp!=NULL || *lines==0){
        printf("Line on index %d successfully deleted\n",index);
    }
}

int Compare(const void *str1, const void *str2){
    const char **s1=(const char **)str1;
    const char **s2=(const char **)str2;
    if(*s1==NULL && *s2==NULL) {
        return 0;
    }
    if(*s1==NULL){
        return 1;
    }
    if(*s2==NULL){
        return -1;
    }
    return strcmp(*s1,*s2);
}

void SortLines(char **buffer, const int lines){
    qsort(buffer,lines,sizeof(char *),Compare);
    printf("Lines sorted alphabetically\n");
}

void Search(char **buffer, const int lines, char *searchText){
    int found=-1;
    for(int a=0;searchText[a]!='\0';a++){
        searchText[a]=tolower(searchText[a]);
    }
    char tempBuffer[MAX+1];
    for(int a=0;a<lines;a++){
        if(buffer[a]!=NULL){
            for(int b=0;buffer[a][b]!='\0';b++){
                tempBuffer[b]=tolower(buffer[a][b]);
            }
            tempBuffer[strlen(buffer[a])]='\0';
            char *temp=strstr(tempBuffer,searchText);
            if(temp!=NULL){
                found=a;
                break;
            }
        }
    }
    if(found==-1){
        printf("Substring not found\n");
    }
    else{
        printf("Substring found at index %d\n",found);
        printf("%d: %s\n",found+1,buffer[found]);
    }
}

void EditLine(char **buffer, const int lines, const int index){
    if(ValidateIndex(lines,index)==0){
        return ;
    }
    char tempBuffer[MAX];
    printf("Enter the updated text line \n");
    fgets(tempBuffer,MAX,stdin);
    tempBuffer[strcspn(tempBuffer,"\n")]='\0';
    if(strlen(tempBuffer)!=strlen(buffer[index])){
        char *temp=realloc(buffer[index],(strlen(tempBuffer)+1)*sizeof(char));
        if(temp==NULL){
            perror("Error: Unale to edit text line due to memory re-allocation failure\n");
            return ;
        }
        buffer[index]=temp;
    }
    strcpy(buffer[index],tempBuffer);
    printf("Line edited successfully\n");
}

int CountChar(char **buffer, const int lines){
    int count=0;
    for(int a=0;a<lines;a++){
        if(buffer[a]!=NULL) {
            count+=strlen(buffer[a]);
        }
    }
    return count;
}

int AvgLength(char **buffer, const int lines){
    if(lines==0){
        return 0;
    }
    else{
        return CountChar(buffer,lines)/lines;
    }
}

void DisplayLines(char **buffer, const int lines){
    if(lines==0){
        printf("No lines to display\n");
    }
    else{
        for(int a=0;a<lines;a++){
            if(buffer[a]!=NULL){
                printf("%d: %s\n",a+1,buffer[a]);
            }
            else{
                printf("%d: \n",a);
            }       
        }
    }
}

int LoadFromFile(char ***buffer, const char *fileName){
    FILE *fptr=fopen(fileName,"r");
    if(fptr==NULL){
        perror("Failed to open the file\n");
        return -1;
    }
    int count=0,size=0;
    char temp[MAX];
    char **tempPtr=NULL;
    while(fgets(temp,MAX,fptr)!=NULL){
        temp[strcspn(temp,"\n")]='\0';
        count++;
        if(count>size){
            size=count*2;
            tempPtr=realloc(*buffer,size*sizeof(char *));
            if(tempPtr==NULL){
                perror("Error: Failed to load text lines due to memory allocation failure\n");
                goto CleanUp;
            }
            *buffer=tempPtr;
        }
        (*buffer)[count-1]=(char *)malloc((strlen(temp)+1) * sizeof(char));
        if((*buffer)[count-1]==NULL){
            perror("Error: Failed to load text lines due to memory allocation failure\n");
            goto CleanUp;
        }
        strcpy((*buffer)[count-1],temp);
    }
    if(count!=0){
        tempPtr=realloc(*buffer,count*sizeof(char *));
        if(tempPtr==NULL){
            perror("Error: Failed to shrink the size of buffer to actual number of lines loaded\n");
            goto CleanUp;
        }
        *buffer=tempPtr;
        printf("Text lines successfully loaded into the buffer\n");
    }
    else{
        printf("File is empty\n");
    }
    fclose(fptr);
    return count;

CleanUp:
    CleanMemory(*buffer,count);
    fclose(fptr);
    return -1;
}

void SaveToFile(char **buffer, const int lines, const char *fileName){
    FILE *fptr=fopen(fileName,"w");
    if(fptr==NULL){
        perror("Failed to open the file\n");
        return ;
    }
    for(int a=0;a<lines;a++){
        if(buffer[a]!=NULL){
            fprintf(fptr,"%s\n",buffer[a]); 
        }  
    }
    printf("All text lines succesfully saved\n");
    fclose(fptr);
}