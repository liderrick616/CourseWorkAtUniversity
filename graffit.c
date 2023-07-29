/**
 * CSC A48 - Intro to Computer Science II
 * 
 * Assignment 3 - Graffit 
 * 
 * This is the file where you will implement your solution for
 * Assignment 3. Please make sure you read through this file carefully
 * and that you understand what is provided and what you need to complete.
 * 
 * You will also need to read the handout carefully. 
 * 
 * Parts where you have to implement functionality are clearly labeled TODO.
 * 
 * Be sure to test your work thoroughly, our testing will be extensive
 * and will check that your solution is *correct*, not only that it
 * provides functionality.
 * 
 * (c) William Song, Mustafa Quraish
 * (c) Charles Xu
 **/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_LEN 1024

#ifndef MAT_SIZE
#define MAT_SIZE 3 // A small graph
#endif

typedef struct user_struct
{
  char name[MAX_STR_LEN];
  struct friend_node_struct *friends;
  struct brand_node_struct *brands;
  bool visited;
} User;

typedef struct friend_node_struct
{
  User *user;
  struct friend_node_struct *next;
} FriendNode;

typedef struct brand_node_struct
{
  char brand_name[MAX_STR_LEN];
  struct brand_node_struct *next;
} BrandNode;

FriendNode *allUsers = NULL;

int brand_adjacency_matrix[MAT_SIZE][MAT_SIZE];
char brand_names[MAT_SIZE][MAX_STR_LEN];

/**
 * Given the head to a FriendNode linked list, returns true if a
 * given user's name exists in the list. Returns false otherwise.
 */
bool in_friend_list(FriendNode *head, User *node)
{
  for (FriendNode *cur = head; cur != NULL; cur = cur->next)
  {
    if (strcmp(cur->user->name, node->name) == 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * Given the head to a BrandNode linked list, returns true if a
 * given brand's name exists in the list. Returns false otherwise.
 */
bool in_brand_list(BrandNode *head, char *name)
{
  for (BrandNode *cur = head; cur != NULL; cur = cur->next)
  {
    if (strcmp(cur->brand_name, name) == 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * Given the head to a FriendNode linked list, inserts a given user
 * into the linked list and returns the head of the new linked list.
 * The insertion is done in alphabetical order. If the user already
 * exists, no modifications are made and the list is returned as is.
 */
FriendNode *insert_into_friend_list(FriendNode *head, User *node)
{
  if (node == NULL)
    return head;

  if (in_friend_list(head, node))
  {
    printf("User already in list\n");
    return head;
  }

  FriendNode *fn = calloc(1, sizeof(FriendNode));
  fn->user = node;
  fn->next = NULL;

  if (head == NULL)
    return fn;

  if (strcmp(head->user->name, node->name) > 0)
  {
    fn->next = head;
    return fn;
  }

  FriendNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->user->name, node->name) < 0;
       cur = cur->next)
    ;

  fn->next = cur->next;
  cur->next = fn;

  return head;
}

/**
 * Given the head to a BrandNode linked list, inserts a given brand into
 * the linked list and returns the head of the new linked list. The
 * insertion is done in alphabetical order. If the brand already exists,
 * no modifications are made and the list is returned as is.
 */
BrandNode *insert_into_brand_list(BrandNode *head, char *node)
{
  if (node == NULL)
    return head;

  if (in_brand_list(head, node))
  {
    printf("Brand already in list\n");
    return head;
  }

  BrandNode *fn = calloc(1, sizeof(BrandNode));
  strcpy(fn->brand_name, node);
  fn->next = NULL;

  if (head == NULL)
    return fn;

  if (strcmp(head->brand_name, node) > 0)
  {
    fn->next = head;
    return fn;
  }

  BrandNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->brand_name, node) < 0;
       cur = cur->next)
    ;

  fn->next = cur->next;
  cur->next = fn;

  return head;
}

/**
 * Given the head to a FriendNode linked list, removes a given user from
 * the linked list and returns the head of the new linked list. If the user
 * does not exist, no modifications are made and the list is returned as is.
 */
FriendNode *delete_from_friend_list(FriendNode *head, User *node)
{
  if (node == NULL)
    return head;

  if (!in_friend_list(head, node))
  {
    printf("User not in list\n");
    return head;
  }

  if (strcmp(head->user->name, node->name) == 0)
  {
    FriendNode *temp = head->next;
    free(head);
    return temp;
  }

  FriendNode *cur;
  for (cur = head; cur->next->user != node; cur = cur->next)
    ;

  FriendNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);

  return head;
}

/**
 * Given the head to a BrandNode linked list, removes a given brand from
 * the linked list and returns the head of the new linked list. If the brand
 * does not exist, no modifications are made and the list is returned as is.
 */
BrandNode *delete_from_brand_list(BrandNode *head, char *node)
{
  if (node == NULL)
    return head;

  if (!in_brand_list(head, node))
  {
    printf("Brand not in list\n");
    return head;
  }

  if (strcmp(head->brand_name, node) == 0)
  {
    BrandNode *temp = head->next;
    free(head);
    return temp;
  }

  BrandNode *cur;
  for (cur = head; strcmp(cur->next->brand_name, node) != 0; cur = cur->next)
    ;

  BrandNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);

  return head;
}

/**
 * Given a user, prints their name, friends, and liked brands.
 */
void print_user_data(User *user)
{
  printf("User name: %s\n", user->name);

  printf("Friends:\n");
  for (FriendNode *f = user->friends; f != NULL; f = f->next)
  {
    printf("   %s\n", f->user->name);
  }

  printf("Brands:\n");
  for (BrandNode *b = user->brands; b != NULL; b = b->next)
  {
    printf("   %s\n", b->brand_name);
  }
}

/**
 * Given a brand, returns the index of the brand inside the brand_names array.
 * If it doesn't exist in the array, return -1
 */
int get_brand_index(char *name)
{
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (strcmp(brand_names[i], name) == 0)
    {
      return i;
    }
  }

  printf("Brand '%s' not found\n", name);
  return -1; // Not found
}

/**
 * Given a brand, prints their name, index (inside the brand_names
 * array), and the names of other similar brands.
 */
void print_brand_data(char *brand_name)
{
  int idx = get_brand_index(brand_name);
  if (idx < 0)
  {
    printf("Brand '%s' not in the list.\n", brand_name);
    return;
  }

  printf("Brand name: %s\n", brand_name);
  printf("Brand idx: %d\n", idx);

  printf("Similar brands:\n");
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (brand_adjacency_matrix[idx][i] == 1 && strcmp(brand_names[i], "") != 0)
    {
      printf("   %s\n", brand_names[i]);
    }
  }
}

/**
 * Read from a given file and populate a the brand list and brand matrix.
 **/
void populate_brand_matrix(char *file_name)
{
  // Read the file
  char buff[MAX_STR_LEN];
  FILE *f = fopen(file_name, "r");
  fscanf(f, "%s", buff);
  char *line = buff;
  // Load up the brand_names matrix
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (i == MAT_SIZE - 1)
    {
      strcpy(brand_names[i], line);
      break;
    }
    int index = strchr(line, ',') - line;
    strncpy(brand_names[i], line, index);
    line = strchr(line, ',') + sizeof(char);
  }
  // Load up the brand_adjacency_matrix
  for (int x = 0; x < MAT_SIZE; x++)
  {
    fscanf(f, "%s", buff);
    for (int y = 0; y < MAT_SIZE; y++)
    {
      int value = (int)buff[y * 2];
      if (value == 48)
      {
        value = 0;
      }
      else
      {
        value = 1;
      }
      brand_adjacency_matrix[x][y] = value;
    }
  }
}

/**
 * TODO: Complete this function
 * Creates and returns a user.
 */
User *create_user(char *name)
{
    FriendNode *current = allUsers;
    while(current != NULL) {
        if (strcmp(current->user->name, name) == 0) {
            printf("User already exists\n");
            return NULL;
        }
        current = current->next;
    }
    User *new_user = calloc(1, sizeof(User));
    strcpy(new_user->name,name);
    new_user->friends=NULL;
    new_user->brands=NULL;
    new_user->visited=false;

    FriendNode *fn=calloc(1, sizeof(FriendNode));
    fn->user=new_user;
    fn->next=NULL;
    // insert new_user into allUsers linked list
    // check for duplicate
    if (allUsers==NULL||strcmp(allUsers->user->name,name)>0)
    {
        fn->next=allUsers;
        allUsers=fn;
    }
    else
    {
        FriendNode *cur = allUsers;
        while (cur->next != NULL)
        {
            // Compare the names alphabetically. If the name of the next user is alphabetically
            // before the name of the new user, we want to keep moving in the list.
            if (strcmp(cur->next->user->name, name) < 0)
            {
                cur = cur->next;
            }
            else
            {
                // We found the spot where the new user should be inserted.
                break;
            }
        }
        fn->next = cur->next;
        cur->next = fn;
    }

    return new_user;
}

/**
 * TODO: Complete this function
 * Deletes a given user.
 */
int delete_user(User *user)
{
    if (user==NULL)
    {
        return -1;
    }

    // Remove user from allUsers linked list.
    if (in_friend_list(allUsers, user)==1)
    {
        allUsers = delete_from_friend_list(allUsers, user);
    }
    else
    {
        //DNE
        return -1;
    }

    // Loop over all users to remove user from their friend lists.
    FriendNode *current=allUsers;
    while (current!=NULL)
    {
        if (in_friend_list(current->user->friends, user)==1)
        {
            current->user->friends=delete_from_friend_list(current->user->friends, user);
        }
        current=current->next;
    }
    free(user);
    return 0;
}

/**
 * TODO: Complete this function
 * Create a friendship between user and friend.
 */
int add_friend(User *user, User *friend)
{
    if (user==NULL)
    {
        return -1;
    }
    if(friend==NULL)
    {
        return -1;
    }
    if (in_friend_list(user->friends, friend)==1)
    {
        return -1;
    }
    // Add friend to the user's friend list.
    user->friends = insert_into_friend_list(user->friends, friend);
    // add user to friend's friend list
    friend->friends = insert_into_friend_list(friend->friends, user);
    return 0;
}

/**
 * TODO: Complete this function
 * Removes a friendship between user and friend.
 */
int remove_friend(User *user, User *friend)
{
    if (user==NULL)
    {
        return -1;
    }
    if(friend==NULL)
    {
        return -1;
    }
    // Check if the friend is in the user's friend list.
    if (in_friend_list(user->friends, friend)==0)
    {
        return -1;
    }
    // Remove friend from the user's friend list.
    user->friends = delete_from_friend_list(user->friends, friend);
    // Remove user from friend's friend list
    friend->friends = delete_from_friend_list(friend->friends, user);

    return 0;
}

/**
 * TODO: Complete this function
 * Creates a follow relationship, the user follows the brand.
 */
int follow_brand(User *user, char *brand_name)
{
    if (user==NULL)
    {
        return -1;
    }
    if(brand_name==NULL)
    {
        return -1;
    }
    // valid brand name
    int name=get_brand_index(brand_name);
    if (name<0)
    {
        return -1;
    }
    // if user already follow brand
    if (in_brand_list(user->brands, brand_name)==1)
    {
        return -1;
    }
    // Insert the brand into user's brand list
    user->brands=insert_into_brand_list(user->brands, brand_name);
    return 0;
}

/**
 * TODO: Complete this function
 * Removes a follow relationship, the user unfollows the brand.
 */
int unfollow_brand(User *user, char *brand_name)
{
    if (user == NULL)
    {
        return -1;
    }
    if (brand_name == NULL)
    {
        return -1;
    }
    // valid brand name
    int name = get_brand_index(brand_name);
    if (name < 0)
    {
        return -1;
    }
    // if user doesn't follow brand
    if (in_brand_list(user->brands, brand_name) == 0)
    {
        return -1;
    }
    // Remove the brand from user's brand list
    user->brands = delete_from_brand_list(user->brands, brand_name);
    return 0;
}

/**
 * TODO: Complete this function
 * Return the number of mutual friends between two users.
 */
int get_mutual_friends(User *a, User *b)
{
    int mutual_count = 0;
    FriendNode *temp = a->friends;

    while (temp != NULL) {
        if (in_friend_list(b->friends, temp->user)) {
            mutual_count++;
        }
        temp = temp->next;
    }
    return mutual_count;
}

/**
 * TODO: Complete this function
 * A degree of connection is the number of steps it takes to get from
 * one user to another. Returns a non-negative integer representing
 * the degrees of connection between two users.
 */
void resetVisited(User *root) {
    // Initialize a queue and add the root user to it
    User** queue = calloc(MAX_STR_LEN, sizeof(User*));
    int queueSize = 1;
    queue[0] = root;

    while (queueSize > 0) {
        User **tempQueue = calloc(MAX_STR_LEN,sizeof(User*));
        int tempQueueSize = 0;

        for (int i = 0; i < queueSize; ++i) {
            User *currentUser = queue[i];

            // If the user has not been visited, skip it
            if (!currentUser->visited) {
                continue;
            }

            // Reset the 'visited' flag for the current user
            currentUser->visited = false;

            // Add all friends of the current user to the new queue
            struct friend_node_struct *friends = currentUser->friends;
            while (friends != NULL) {
                User *friend = friends->user;

                // If the friend has been visited, add them to the queue
                if (friend->visited) {
                    tempQueue[tempQueueSize++] = friend;
                }

                friends = friends->next;
            }
        }

        // Replace the old queue with the new one
        free(queue);
        queue = tempQueue;
        queueSize = tempQueueSize;
    }

    free(queue);
}
int get_degrees_of_connection(User *a, User *b)
{
    // Create queue and initialize it
    // Create queue and insert 'a' into it
    // Create queue and insert 'a' into it
    User** queue = calloc(MAX_STR_LEN, sizeof(User*));
    int queueSize = 1;
    queue[0] = a;
    a->visited = true;

    int degrees = 0;

    while (queueSize > 0) {
        User **tempQueue = calloc(sizeof(User*) ,MAX_STR_LEN);
        int tempQueueSize = 0;

        for (int i = 0; i < queueSize; ++i) {
            User *currentUser = queue[i];

            // If the current user is 'b', then we have found a connection
            if (strcmp(currentUser->name, b->name) == 0) {
                free(queue);
                free(tempQueue);
                resetVisited(a); // reset 'visited' flag for all users, assume such a function exists
                return degrees;
            }

            // Iterate through all friends of the current user
            struct friend_node_struct *friends = currentUser->friends;
            while (friends != NULL) {
                User *friend = friends->user;

                // If the friend has not been visited, add them to the queue
                if (!friend->visited) {
                    tempQueue[tempQueueSize++] = friend;
                    friend->visited = true;
                }

                friends = friends->next;
            }
        }

        // Increase the degrees of connection and replace the old queue with the new one
        degrees++;
        free(queue);
        queue = tempQueue;
        queueSize = tempQueueSize;
    }

    free(queue);
    resetVisited(a); // reset 'visited' flag for all users

    // If we reached here, it means there's no connection between 'a' and 'b'
    return -1;
}

/**
 * TODO: Complete this function
 * Marks two brands as similar.
 */
void connect_similar_brands(char *brandNameA, char *brandNameB)
{
    int indexA = get_brand_index(brandNameA);
    int indexB = get_brand_index(brandNameB);

    if (indexA == -1) {
        return;
    }
    if (indexB == -1) {
        return;
    }
    if (indexA >= MAT_SIZE) {
        return;
    }
    if (indexB >= MAT_SIZE) {
        return;
    }
    // Connect the two brands in the adjacency matrix.
    brand_adjacency_matrix[indexA][indexB] = 1;
    brand_adjacency_matrix[indexB][indexA] = 1;
}

/**
 * TODO: Complete this function
 * Returns a suggested friend for the given user.
 */
int are_similar_brands(char *brandA, char *brandB) {
    int indexA = get_brand_index(brandA);
    int indexB = get_brand_index(brandB);

    if(indexA == -1 || indexB == -1) { // Invalid brand name
        return 0;
    }

    return brand_adjacency_matrix[indexA][indexB] == 1;
}
int are_friends(User *a, User *b) {
    FriendNode *currentNode = a->friends;

    while (currentNode != NULL) {
        if (currentNode->user == b) {
            return 1;  // found b in a's friend list, so they are friends
        }
        currentNode = currentNode->next;
    }
    return 0;  // b not found in a's friend list, so they aren't friends
}
User *get_suggested_friend(User *user)
{
    User *suggested_friend = NULL;
    int max_mutual_brands = 0;

    FriendNode *currentNode = allUsers;
    while(currentNode != NULL) {
        User *candidate = currentNode->user;

        // Skip if the candidate is the user itself or already a friend
        if(candidate == user || are_friends(user, candidate)) {
            currentNode = currentNode->next;
            continue;
        }

        int mutual_brands = 0;
        BrandNode *userBrandNode = user->brands;
        while(userBrandNode != NULL) {
            char *userBrand = userBrandNode->brand_name;
            BrandNode *candidateBrandNode = candidate->brands;
            while(candidateBrandNode != NULL) {
                char *candidateBrand = candidateBrandNode->brand_name;
                if(are_similar_brands(userBrand, candidateBrand)) {
                    mutual_brands++;
                }
                candidateBrandNode = candidateBrandNode->next;
            }
            userBrandNode = userBrandNode->next;
        }

        if(mutual_brands > max_mutual_brands) {
            max_mutual_brands = mutual_brands;
            suggested_friend = candidate;
        } else if(mutual_brands == max_mutual_brands) {
            if(suggested_friend == NULL || strcmp(candidate->name, suggested_friend->name) < 0) {
                suggested_friend = candidate;
            }
        }

        currentNode = currentNode->next;
    }

    return suggested_friend;
}

/**
 * TODO: Complete this function
 * Adds n suggested friends for the given user.
 * Returns how many friends were successfully followed.
 */
int add_suggested_friends(User *user, int n)
{
    if (n <= 0) {//invalid
        return 0;
    }
    int addedCount = 0;
    for (int i = 0; i < n; ++i) {
        User* suggestedFriend = get_suggested_friend(user);
        if (suggestedFriend == NULL) {
            // No more suggested friends available
            break;
        }
        // add the friend to user's friend list
        // assuming that add_friend returns 1 on success and 0 otherwise
        if (add_friend(user, suggestedFriend)) {
            addedCount++;
        }
    }
    return addedCount;
}

/**
 * TODO: Complete this function
 * Follows n suggested brands for the given user.
 * Returns how many brands were successfully followed.
 */

int follow_suggested_brands(User *user, int n)
{
    if (n <= 0) {
        // Invalid input
        return 0;
    }

    int followedCount = 0;
    for (int i = 0; i < n; ++i) {
        char *suggestedBrand = NULL;
        int maxSimilarity = -1;

        for (int j = 0; j < MAT_SIZE; ++j) {
            char *candidateBrand = brand_names[j];
            if (in_brand_list(user->brands, candidateBrand)) {
                // Skip brands that the user already follows
                continue;
            }

            int similarity = 0;
            BrandNode *userBrandNode = user->brands;
            while(userBrandNode != NULL) {
                char *userBrand = userBrandNode->brand_name;
                int userBrandIndex = get_brand_index(userBrand);
                if (brand_adjacency_matrix[userBrandIndex][j] == 1) {
                    similarity++;
                }
                userBrandNode = userBrandNode->next;
            }

            if (similarity > maxSimilarity) {
                maxSimilarity = similarity;
                suggestedBrand = candidateBrand;
            } else if (similarity == maxSimilarity) {
                if (suggestedBrand == NULL || strcmp(candidateBrand, suggestedBrand) > 0) {
                    suggestedBrand = candidateBrand;
                }
            }
        }

        if (suggestedBrand == NULL) {
            // No more suggested brands available
            break;
        }

        // Follow the suggested brand
        if (follow_brand(user, suggestedBrand) == 0) {
            followedCount++;
        }
    }

    return followedCount;
}
