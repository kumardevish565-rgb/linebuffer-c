#include "text_buffer.h"

int main() {
    char **buffer=NULL;
    printf("TEXT BUFFER ARCHITECTURE DEMO\n\n");
    int count=LoadFromFile(&buffer,"buffer.txt");

    printf("Step 1: Displaying Initial Text Lines\n");
    DisplayLines(buffer, count);

    printf("\nStep 2: Buffer Statistics\n");
    printf("• Total Lines: %d\n", count);
    printf("• Total Characters (excluding null terminators): %d\n", CountChar(buffer, count));
    printf("• Average Line Length: %d characters\n\n", AvgLength(buffer, count));

    printf("Step 3: Performing Case-Insensitive Search for 'portfolio'\n");
    char query[] = "portfolio";
    Search(buffer,count,query);
    
    printf("\nStep 4: Sorting All Rows Alphabetically\n");
    SortLines(buffer, count);
    DisplayLines(buffer, count);

    printf("\nStep 5: Saving current state to file\n");
    SaveToFile(buffer,count,"buffer.txt");
    
    printf("\nStep 6: Freeing dynamically allocated memory and safely exiting...\n");
    CleanMemory(buffer, count);
    
    printf("DEMO COMPLETED!\n");
    return 0;
}