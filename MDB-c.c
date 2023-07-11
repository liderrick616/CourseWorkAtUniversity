/*
 *  CSC A48 - Winter 2023 - Assignment 1 starter
 *
 *  (c) 2020-23 Francisco Estrada
 *  - No part of this code may be reproduced without written authorization
 *
 * This is the file where you will be doing most of your work. The
 * functionality you must provide for part 1 of the assignment is described
 * in the handout. Given in detail in the comments at the head of each
 * function below.
 *
 * Plan your work carefully, review the notes for Unit 3, and work carefully
 * to complete the functions in this file. You can bring
 * questions to your TAs or instructors during office hours. Please
 * remember:
 *
 * - You should not share any part of your solution in any form
 * - You should not post any assignment code on Piazza
 * - You should definitely *help* other understand any ideas and
 *   concepts regarding linked lists that you have already mastered,
 *   but being careful not to give away parts of the solution, or
 *   descriptions of how to implement functions below.
 * - If you are not sure whether you can or can not discuss some
 *   particular aspect of the work to be done, remember it's always
 *   safe to talk with your TAs.
 * - Obtaining external 'help' including being given code by an
 *   external party, or being tutored on how to solve
 *   the assignment constitutes an academic offense.
 *
 * All tasks to be completed by you are clearly labeled with a
 * ***** TO DO ****** comment block, which also gives you details
 * about what you have to implement. Look carefully and make sure
 * you don't miss a thing!
 *
 * NOTE: This file contains no main() function! you can not compile
 * it on its own to create an executable. It's meant to be used
 * together with Part1_driver.c - be sure to read that file carefully
 * to understand how to use the tests there - Any additional tests
 * you want to run on the code below should be added to Part1_driver.c
 *
 * Before you even get starter implementing, please complete the
 * student identification section below, and check that you are aware
 * of the policy on academic honesty and plagiarism.
 */

/* Student identification:
 *
 * Student Name (Last name, First name): Derrick Li
 * Student Number: 1009049959
 * UTORid: liderric
 * Your instructor's name is: Paco Estrada
 */

/* Academic Integrity Statement:
 *
 * I hereby certify that the work contained in this file is my own, and
 * that I have not received any parts of my solution from other sources
 * including my fellow students, external tutoring services, the internet,
 * or algorithm implementations found online.
 *
 * Sign here with your name:
 *Derrick Li
 *
 */

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STR_LEN 1024

/* Compound data type declarations */
/***************************************************************************/
/******                         TO DO                               ********/
/****** In the space below, complete the definitions of the compound *******/
/****** data types that will be needed to implement the movie review *******/
/****** linked list. This includes the MovieReview type, and the     *******/
/****** ReviewNode. Details about the contents of these can be       *******/
/****** found in the assignment handout. Read them carefully!        *******/
/******                                                              *******/
/****** AFTER completing the basic linked list, complete the CDT     *******/
/****** required to implement a list for the movie's cast.           *******/
/***************************************************************************/

typedef struct castList_struct
{
    char name[MAX_STR_LEN];
    float salary;
    struct castList_struct *next;
} CastList;

typedef struct movieReview_struct
{
    char movie_title[MAX_STR_LEN];
    char movie_studio[MAX_STR_LEN];
    int year;
    float BO_total;
    int score;

    //struct movieReview_struct *cast;
    CastList *cast;

} MovieReview;

typedef struct reviewNode_struct
{
    MovieReview review;
    struct reviewNode_struct *next;
} ReviewNode;

ReviewNode *newMovieReviewNode()
{
    ReviewNode *newMovieReview = NULL;
    newMovieReview = (ReviewNode *)calloc(1,sizeof(ReviewNode));
    strcpy(newMovieReview->review.movie_title, "");
    strcpy(newMovieReview->review.movie_studio, "");
    newMovieReview->review.year = -1;
    newMovieReview->review.BO_total = -1;
    newMovieReview->review.score = -1;
    newMovieReview-> next = NULL;

    if (newMovieReview == NULL){
        return NULL;
    }


    //return newMovieReview;
    /*
     * This function allocates an empty ReviewNode, and initializes the
     * contents of the MovieReview for this node to reasonable (uninitialized) values.
     * The fields in the MovieReview should be set to:
     *  movie_title=""
     *  movie_studio=""
     *  year = -1
     *  BO_total = -1
     *  score = -1
     *  scoreList = NULL;
     *
     * The *next pointer for the new node MUST be set to NULL
     *
     * The function must return a pointer to the newly allocated and initialized
     * node. If something goes wrong, the function returns NULL
     */



    //ReviewNode *new_node=NULL;


    return(newMovieReview);
}

ReviewNode *findMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, ReviewNode *head)
{
    /*
     * This function searches through the linked list for a review that matches the input query.
     * The movie review must match the title, studio, and year provided in the
     * parameters for this function.
     *
     * If a review matching the query is found, this function returns the address of the node that
     * contains that review.
     *
     * If no such review is found, this function returns NULL
     */

    ReviewNode   *p=NULL; //Traversal pointer
    p = head;
    while (p!=NULL){
        if(strcmp(p->review.movie_title,title)==0 && strcmp(p->review.movie_studio,studio)==0 && p->review.year == year ){
            return p;
        }
        p=p->next;
    }
    return NULL;



}

ReviewNode *insertMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, float BO_total, int score, ReviewNode *head)
{

    ReviewNode *current_node=NULL;
    current_node=head;
    while (current_node!=NULL){
        //if(findMovieReview(title,studio,year,head)!=NULL){
        if(strcmp(current_node->review.movie_title,title)==0&&strcmp(current_node->review.movie_studio,studio)==0&&current_node->review.year==year ){
            printf("already in the Database\n");
            return head;
        }
        current_node=current_node->next;
    }
    ReviewNode *new_node=newMovieReviewNode();
    if(new_node==NULL){
        return head;
    } strcpy(new_node->review.movie_title,title);
    strcpy(new_node->review.movie_studio,studio);
    new_node->review.year=year;
    new_node->review.BO_total=BO_total;
    new_node->review.score=score;
    if (head==NULL) {
        head=new_node; // List is empty, new node becomes head
    }
    else
    {
        new_node->next=head;
        //head=new_node;
    }
    return new_node;

    //new_node->review.scoreList = scoreList;
    /*
     * This function inserts a new movie review into the linked list.
     *
     * The function takes as input parameters the data neede to fill-in the review,
     * as well as a pointer to the current head of the linked list.
     *
     * If head==NULL, then the list is still empty.
     *
     * The function inserts the new movie review *AT THE HEAD* of the linked list,
     * and returns the pointer to the new head node.
     *
     * The function MUST check that the movie is not already in the list before
     * inserting (there should be no duplicate entries). If a movie with matching
     * title, studio, and year is already in the list, nothing is inserted and the
     * function returns the current list head.
     */




    //return NULL;        // Remove this before you implement your solution!
}

int countReviews(ReviewNode *head)
{
    /*
     * This function returns the number of reviews.
     */

    int num_review =0;
    ReviewNode *num_node =head;
    while(num_node !=NULL){
        num_review++;
        num_node =num_node->next;
    }
    return num_review;



    //return 0;    // Remove this before you implement your solution
}

void updateMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, float BO_total, int score, ReviewNode *head)
{
    /*
     * This function looks for a review matching the input query [title, studio, year].
     * If such a review is found, then the function updates the Box-office total, and the score.
     * If no such review is found, the function prints out
     * "Sorry, no such movie exists in the database"
     */

    ReviewNode *update =NULL;
    update =head;
    if(update != NULL){
        //if(findMovieReview(title,studio,year,head) == NULL){
        if((strcmp(update->review.movie_title, title) !=0 || strcmp(update->review.movie_studio, studio)) !=0 || year){
            printf("Sorry, no such movie exists in the database\n");
        }
    }
    while(update != NULL) {
        //if(findMovieReview(title,studio,year,head) != NULL){
        if (strcmp(update->review.movie_title, title) ==0 && strcmp(update->review.movie_studio, studio) ==0 &&
            update->review.year ==year) {
            update->review.BO_total =BO_total;
            update->review.score =score;
        }
        update = update->next;

    }

}

ReviewNode *deleteMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN],int year, ReviewNode *head)
{

    // Function to remove a review matching the input query
    ReviewNode *current_node =head;
    ReviewNode *prev_node =NULL;

    while (current_node !=NULL) {
        //if(findMovieReview(title,studio,year,head) != NULL){
        if (strcmp(current_node->review.movie_title, title) ==0 && strcmp(current_node->review.movie_studio, studio) ==0 && current_node->review.year ==year) {
            // Found a review matching the query, remove it from the list
            if (prev_node ==NULL) {
                // Removing the head node
                head =current_node->next;
            }
            else
            {
                prev_node->next =current_node->next;
            }
            free(current_node->review.cast); //*****
            free(current_node);
            //return head;
        }
        prev_node =current_node;
        current_node =current_node->next;
    }
    return head;
}

//return head;
// No review matching the query was found, return the original head pointer
/*return head;
The function takes as input parameters a pointer to the linked list using a
while loop, checking each node to see if it matches the query. If a matching review is found,
the function removes it from the list by updating the next pointers of the previous and
current nodes and freeing the memory occupied by the current node. It then returns a pointer
to the new head of the list.
If no review matching the query is found, the function simply returns the original head pointer.
*/



float printMovieReviews(ReviewNode *head)
{
    //:)/////////////////////////////////////////////////////////////////////////////////
    ReviewNode *print =NULL;
    print =head;
    double bo_total =0.0;
    while (print !=NULL)
    {
        printf("%s\n", print->review.movie_title);
        printf("%s\n", print->review.movie_studio);
        printf("%d\n", print->review.year);
        printf("%f\n", print->review.BO_total);
        printf("%d\n", print->review.score);
        bo_total +=print->review.BO_total;
        printf("*******************\n");
        print = print->next;
    }
    return bo_total;

    /*
     * This function prints out all the reviews in the database, one after another.
     * Each field in the review is printed in a separate line, with *no additional text*
     * (that means, the only thing printed is the value of the corresponding field).
     *
     * Reviews are separated from each other by a line of
     * "*******************"

     * The function also computes and returns the Box-office total, for all the
     * movies that match the query.
     *
     * See the A1 handout for a sample of the output that should be produced
     * by this function
     */



    return 0;           // Remove this before you implement your solution
}

float queryReviewsByStudio(char studio[MAX_STR_LEN], ReviewNode *head)
{
    //:)//////////////////////////////////////////////////////////////////////////////
    ReviewNode *query_node =NULL;
    query_node =head;
    double total =0.0;
    while(query_node !=NULL){
        if(strcmp(query_node->review.movie_studio, studio) ==0){
            printf("%s\n", query_node->review.movie_title);
            printf("%s\n", query_node->review.movie_studio);
            printf("%d\n", query_node->review.year);
            printf("%f\n", query_node->review.BO_total);
            printf("%d\n", query_node->review.score);
            total += query_node->review.BO_total;
            printf("*******************\n");
        }
        query_node = query_node->next;
    }
    return total;

    /*
     * This function looks for reviews whose studio matches the input query.
     * It prints out the contents of all reviews matching the query in exactly
     * the same format used by the printMovieReviews() function above.
     *
     * Additionally, it computes and returns the Box-office total, for all the
     * movies that match the query.
     */


    //return 0;       // Remove this before you implement your solution
}

float queryReviewsByScore(int min_score, ReviewNode *head)
{
    ReviewNode *score_node =head;
    double total_b_office =0.0;
    while(score_node !=NULL){
        if(score_node->review.score >=min_score){
            printf("%s\n", score_node->review.movie_title);
            printf("%s\n", score_node->review.movie_studio);
            printf("%d\n", score_node->review.year);
            printf("%f\n", score_node->review.BO_total);
            printf("%d\n", score_node->review.score);
            total_b_office +=score_node->review.BO_total;
            printf("*******************\n");
        }
        score_node =score_node->next;
    }
    return total_b_office;

    /*
     * This function looks for reviews whose score is greater than, or equal to
     * the input 'min_score'.
     * It prints out the contents of all reviews matching the query in exactly
     * the same format used by the printMovieReviews() function above.
     *
     * Additionally, it computes and returns the Box-office total, for all the
     * movies that match the query.
     */



    //return 0;
}

ReviewNode *deleteReviewList(ReviewNode *head)
{

    /*
     * This function deletes the movie review database, releasing all the
     * memory allocated to the nodes in the linked list.
     *
     * Returns a NULL pointer so that the head of the list can be set to NULL
     * after deletion.
     */

    ReviewNode *delete_node =head;
    while(delete_node !=NULL){
        //ReviewNode *next = delete_node->next; 0=0:)
        free(delete_node->review.movie_title);
        //free(delete_node->review.movie_studio);
        //free(delete_node->review.score);
        //free(delete_node);
        //delete_node = delete_node->next;
        delete_node=delete_node->next; //delete_node = next; either works
    }
    return NULL;




    //return head;        // Remove this before you implement your solution

}

/* CRUNCHY SECTION! Do not work on the functions below until
 * your basic linked list is working properly and is fully tested!
 */

ReviewNode *sortReviewsByTitle(ReviewNode *head)
{
    //:)//////////////////////////////////////////////////////////////////////////////
    if(head==NULL || head->next==NULL){
        return head;
    }
    ReviewNode* newHead =NULL;
    ReviewNode* cur_rent =head;
    while (cur_rent !=NULL) {
        ReviewNode* next =cur_rent->next;
        if (newHead ==NULL || strcmp(cur_rent->review.movie_title, newHead->review.movie_title) < 0){
            cur_rent->next =newHead;
            newHead =cur_rent;
        }
        else
        {
            ReviewNode* temp =newHead;
            while (temp->next !=NULL && strcmp(cur_rent->review.movie_title, temp->next->review.movie_title) >=0){
                temp = temp->next;
            }
            cur_rent->next =temp->next;
            temp->next =cur_rent;
        }
        cur_rent = next;
    }


    return newHead;
    /*
     * This function sorts the list of movie reviews in ascending order of movie
     * title. If duplicate movie titles exist, the order is arbitrary (i.e. you
     * can choose which one goes first).
     *
     * However you implement this function, it must return a pointer to the head
     * node of the sorted list.
     */
    //bubble sort or insertion sort,no change to node



    //return NULL;            // Remove this before you implement your solution
}
void bubbleSort(CastList *start) {
    int swapped;
    CastList *point_1;
    CastList *point_2 =NULL;
    float tempSalary;
    char tempName[MAX_STR_LEN];
    if (start ==NULL)
    {
        return;
    }
    do {
        swapped =0;
        point_1 =start;
        while (point_1->next !=point_2)
        {
            if (point_1->salary < point_1->next->salary)
            {
                tempSalary =point_1->salary;
                point_1->salary =point_1->next->salary;
                point_1->next->salary =tempSalary;
                strncpy(tempName, point_1->name, MAX_STR_LEN - 1);
                strncpy(point_1->name,point_1->next->name, MAX_STR_LEN - 1);
                strncpy(point_1->next->name, tempName, MAX_STR_LEN - 1);
                swapped =1;
            }
            point_1 =point_1->next;
        }
        point_2 =point_1;
    } while (swapped);
}

void insertCastMember(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, ReviewNode *head, char name[MAX_STR_LEN], float salary) {

    ReviewNode *Member = findMovieReview(title, studio, year, head);
    if (Member == NULL)
    {
        return;
    }
    //if(findMovieReview(title,studio,year,head) != NULL){
    if (strcmp(head->review.movie_title,title)==0 && strcmp(head->review.movie_studio,studio)==0 && head->review.year==year) {
        CastList *newCastMember=(CastList *) calloc(1, sizeof(CastList));
        if (newCastMember==NULL)
        {
            printf("No memory, Error\n");
            return;
        }
        strncpy(newCastMember->name, name, MAX_STR_LEN - 1);
        newCastMember->salary =salary;
        newCastMember->next =Member->review.cast;
        Member->review.cast =newCastMember;
        // Sort the cast list using bubble sort
        bubbleSort(Member->review.cast);
        return;
    }
    while (Member != NULL)
    {
        //if(findMovieReview(title,studio,year,head) != NULL){
        if (strcmp(Member->review.movie_title, title)==0 && strcmp(Member->review.movie_studio, studio)==0 &&Member->review.year==year)
        {
            CastList *newCastMember=(CastList *) calloc(1, sizeof(CastList));
            if (newCastMember == NULL) {
                printf("No memory, Error\n");
                return;
            }
            strncpy(newCastMember->name, name, MAX_STR_LEN - 1);
            newCastMember->salary =salary;
            newCastMember->next =Member->review.cast;
            Member->review.cast =newCastMember;
            // Sort the cast list
            bubbleSort(Member->review.cast);
            return;
        }
        Member = Member->next;
    }



    /*
     * This function inserts the name of a cast member for the given movie into the
     * linked list of cast members. The new cast member must go to the end of the list.
     *
     * Duplicate names are allowed - this time!
     *
     * Notice the function receives the title, studio, and year for the movie, as
     * well as a pointer to the movie DB linked list. The function must find the
     * correct movie and if such a movie exists, add the cast member's name to its
     * cast list.
     *
     * If no such movie is found, this function does nothing.
     *
     * You're free to add helper functions to insert the cast member's name
     * into the cast list.
     */
    //access findmoviereview node
    //node->review.cast->salary=salary
    //special case for head, rest use while loop

}



void whosTheStar(ReviewNode *head)
{
    CastList *castEarn =NULL;
    ReviewNode *currReview =head;
    int num_movies =1;
    float tot_earnings;
    if (currReview == NULL)
    {
        return;
    }
    while (currReview !=NULL)
    {
        CastList *currCast =currReview->review.cast;
        while (currCast !=NULL)
        {
            float earnings =currReview->review.BO_total;
            CastList *otherCast=currReview->review.cast;
            while (otherCast != NULL)
            {
                earnings -=otherCast->salary;
                otherCast =otherCast->next;
            }
            earnings += currCast->salary;
            CastList *currCastEarn=castEarn;
            while (currCastEarn != NULL && strcmp(currCastEarn->name, currCast->name) != 0)
            {
                currCastEarn=currCastEarn->next;
            }
            if (currCastEarn==NULL)
            {
                currCastEarn=(CastList *) calloc(1, sizeof(CastList));
                if (currCastEarn==NULL)
                {
                    printf("No memory, Error\n");
                    return;
                }
                strncpy(currCastEarn->name, currCast->name, MAX_STR_LEN - 1);
                tot_earnings=earnings;
                num_movies=1;
                currCastEarn->next=castEarn;
                castEarn=currCastEarn;
            }
            else
            {
                tot_earnings+=earnings;
                num_movies++;
            }
            currCast=currCast->next;
        }
        currReview=currReview->next;
    }
    // Find the cast member with the highest average earnings
    CastList *bestCast = castEarn;
    CastList *currCastEarn = castEarn->next;
    while (currCastEarn != NULL)
    {
        float currAvgEarnings = tot_earnings / num_movies;
        float bestAvgEarnings = tot_earnings / num_movies;
        if (currAvgEarnings > bestAvgEarnings)
        {
            bestCast=currCastEarn;
        }
        currCastEarn=currCastEarn->next;
    }

    // Print out the result
    printf("%s has the greatest average earnings: $%f\n", bestCast->name, tot_earnings / num_movies);

    // Free the memory used by the linked list of cast earnings
    currCastEarn = castEarn;
    while (currCastEarn != NULL)
    {
        CastList *nextCastEarnings = currCastEarn->next;
        free(currCastEarn);
        currCastEarn = nextCastEarnings;
    }
    /*
     *  This function goes through the movie database and determines who is
     * the cast members whose movies have the greatest average earnings.
     *
     * Earnings are defined as the box office total minus the salaries of all
     * cast members involved with the movie.
     *
     *  You're free to implement this function however you like, use any of
     * the code you wrote for other parts of the assignment, and write any
     * helper functions that you need. But:
     *
     *  You can not import extra libraries (no additional #include), and
     * all the implementation here should be your own.
     *
     *  The function simply prints out:
     *
     *  Name of cast member
     *  Average movie earnings (as a floating point number)
     *
     *  For the cast member whose movies make the greatest average earnings
     */


    // create new linked list which inclues name of actor, their salary. (use next)
    //sort this list
    //then find the average( use while loop)
    //put this result in an array, traverse through array to find highest earning. print
}
void printNames(ReviewNode *movie)
{
    //Prints out names of cast members for this movie
    CastList *p;
    if (movie==NULL||movie->review.cast==NULL) return;
    p=movie->review.cast;
    printf("The cast for this movie are:\n");
    while (p!=NULL)
    {
        printf("Cast Member: %s, Salary: %f\n",p->name,p->salary);
        p=p->next;
    }
}

