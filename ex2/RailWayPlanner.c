#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define OK 0


typedef struct Piece
{
    char start[2];
    char end[2];
    long len;
    long price;
} Piece;


char *gConnectionsArray = NULL;
Piece *gPiecesArray = NULL;
int gLen;
int gNumOfConnections;
int gNumOfPieces;



long checkNumber(char number[], char lenOrPrice)
{
    long num;
    char *leftOvers = NULL;
    num = strtol(number, &leftOvers, 10);
    if (strlen(leftOvers) != 0)
    {
        return EXIT_FAILURE;
    }
    if (num < 0)
    {
        return EXIT_FAILURE;
    }
    if ((int)lenOrPrice == 'L'){
        if (num == 0)
        {
            return EXIT_FAILURE;
        }
    }
    return num;
}

int getAllConnections(int k, const char connections[])
{
    if (gConnectionsArray == NULL)
    {
        gConnectionsArray = (char *) malloc(sizeof(char) * k);
    }
    if (gConnectionsArray != NULL)
    {
        for (int i = 0; i < k; i++)
        {
            gConnectionsArray[i] = connections[i];
        }
    }
    return EXIT_FAILURE;
}

int checkConnectionExist(char *connection)
{
    for (int i = 0; i < gNumOfConnections; i++)
    {
        if (strcmp(connection,gConnectionsArray) == OK)
        {
            return OK;
        }
    }
    return EXIT_FAILURE;
}

int creatPiecesArray(int numOfPieces){
    if (gPiecesArray == NULL)
    {
        gPiecesArray = (Piece *) malloc(sizeof(Piece) * numOfPieces);
    }
    if (gPiecesArray != NULL){
        printf("malloc succeed\n");
        return OK;
    }
    return EXIT_FAILURE;
}
int getOnePiece(char givenPiece[1024])
{
    Piece piece;
    char start[2], end[2], len[gLen], price[10];
    sscanf(givenPiece, "%[^,],%[^,],%[^,],%s", start, end, len, price);
    printf("%s\n", len);
    if (checkConnectionExist(start) == OK)
    {
        printf("connection exist\n");
        piece.start[0] = start[0];
    }
    else
    {
        return EXIT_FAILURE;
    }
    if (checkConnectionExist(end) == OK)
    {
        piece.start[0] = start[0];
    }
    else
    {
        return EXIT_FAILURE;
    }
    if (checkNumber(len,'L') != 0)
    {
        piece.len = checkNumber(len,'L');
    }
    else
    {
        return EXIT_FAILURE;
    }
    if (checkNumber(len,'P') != -1)
    {
        piece.price = checkNumber(len,'P');
    }
    else
    {
        return EXIT_FAILURE;
    }

    gPiecesArray[gNumOfPieces] = piece;
    return OK;

}


int main(int argc, char *argv[])
{
    char const *const fileName = argv[1];
    FILE *file = fopen(fileName, "r");
    char line[1024];
    if (file == NULL)
    {
        printf("null");
    }
    else
    {
        printf("The file is now opened.\n");
        while (fgets(line, 1024, file) != NULL)
        {
            // Print the dataToBeRead

            printf("%s", line);
        }
    }
    fclose(file);
    printf("Data successfully read from file GfgTest.c\n");
    printf("The file is now closed.\n");



    /////////////////////////////////////2d array

    int tDArray[6][6];
    int i, j;
    for (i = 0; i < 5; i++)
    {
        tDArray[i][0] = 5 - i - 1;
        for (j = 1; j < 6; j++)
        {
            tDArray[i][j] = 0;
//            printf("Enter value for disp[%d][%d]:", i, j);
//            scanf("%d", &tDArray[i][j]);
        }
    }
    for (int j = 0; j < 6; j++)
    {
        tDArray[5][j] = 8;
    }
    //Displaying array elements
    printf("Two Dimensional array elements:\n");
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            printf("%d ", tDArray[i][j]);
            if (j == 5)
            {
                printf("\n");
            }
        }
    }
    char connection = {'+'};
    getAllConnections(1, (const char *) connection);
    char piece = (char) "+,+,3,20";
    creatPiecesArray(2);
    gNumOfPieces = 0;
    getOnePiece(&piece);
    printf("%s\n%s\n%ld\n%ld\n",gPiecesArray[0].start,gPiecesArray[0].end,gPiecesArray[0].len,
            gPiecesArray[0].price);
    return 0;
}
