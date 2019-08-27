/*
    Program : Frame sort
    Author: Gangadhara Shetty P J

    Algorithm:
    ----------
    1. Read a message to be sent
    2. Read the length of the frame
    3. shuffle the frames
    4. sort the frame

    Algorithm for shuffling Fisher yates algorithm)
    -----------------------
    for i from n-1 downto 1 do
        j = rand() % (i+1)
        swap frame[i] and frame[j]

*/


#include<stdio.h>
#include<string.h>
int frameLength, messageLength;
char message[1000];

struct frame
{
    int id;
    char data[100];
};
struct frame f[100];
int num_of_frames;

// Fisher yates algorithm to shuffle the frame
void shuffleFrame()
{
    int i;
    for(i = num_of_frames; i>=0;i--)
    {
        int j = rand()%(i+1);
        // Swapping a number
        struct frame temp = f[j];
        f[j] = f[i];
        f[i] = temp;
    }
}

// Insertion sort algorithm to sort frames based on it's id'
void sortFrames()
{
    int i,j;
    for(i=1; i<=num_of_frames; i++)
    {
        struct frame t = f[i];
        j = i-1;
        while(j>=0 && f[j].id>t.id)
        {
            f[j+1] = f[j];
            j=j-1;
        }
        f[j+1] = t;
    }
}

int main()
{
    int mind=0, i, j;

    srand(time(NULL));

    printf("Enter a message: ");    // STEP 1 in algorithm
    gets(message);
    messageLength = strlen(message);

    printf("Enter a frame length: ");   // STEP 2 in algorithm
    scanf("%d", &frameLength);

    num_of_frames = messageLength / frameLength ;   // find the number of frames

    //Divide the message into  frames
    for(i=0; message[i] != '\0'; i++){
        for(j=0;j<frameLength && mind <= messageLength;j++)
            f[i].data[j] = message[mind++];
        f[i].id = i;    // Giving ID to each frame
    }

    shuffleFrame();     // STEP 3 in algorithm

    printf("\nShuffled frames:\n frame_id\tframe_data\n");
    for(i=0; i<= num_of_frames; i++)
        printf("%d\t\t%s\n", f[i].id, f[i].data);

    sortFrames();   // STEP 4 in algorithm

    printf("\nSorted frame:\n frame_id\tframe_data\n");
    for(i=0; i<= num_of_frames; i++)
        printf("%d\t\t%s\n", f[i].id, f[i].data);

    printf("\nfinal message:\t ");
    for(i=0; i<= num_of_frames; i++)
        printf("%s", f[i].data);
    printf("\n");
}

/*
Sample output:

Enter a message: SIDDAGANGA INSTITUTE OF TECHNOLOGY
Enter a frame length: 5

Shuffled frames:
 frame_id       frame_data
4                OF T
0               SIDDA
2                INST
5               ECHNO
6               LOGY
3               ITUTE
1               GANGA

Sorted frame:
 frame_id       frame_data
0               SIDDA
1               GANGA
2                INST
3               ITUTE
4                OF T
5               ECHNO
6               LOGY

final message:   SIDDAGANGA INSTITUTE OF TECHNOLOGY

*/
