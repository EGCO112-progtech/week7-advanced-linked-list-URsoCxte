
// self-referential structure
struct Node {
   int data; // each listNode contains a character
   char name[50];
   struct Node *nextPtr; // pointer to next node
   struct Node *pPtr;
}; // end structure listNode

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*

// prototypes
#define MAX_DELETED 100 // Maximum number of deleted values

int deletedValues[MAX_DELETED]; // Array to store deleted values
int deletedCount = 0;


int deletes( LLPtr *sPtr, int value );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int value, char *name);
void printList( LLPtr currentPtr );
void instructions( void );
void printListR(LLPtr currentPtr);


// display program instructions to user
void instructions( void )
{
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert( LLPtr *sPtr, int value, char *name)
{
   LLPtr newPtr; // pointer to new node
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list

   newPtr =(LLPtr) malloc( sizeof( LLnode ) ); // create node

   if ( newPtr != NULL ) { // is space available
      newPtr->data = value; // place value in node
      strcpy(newPtr->name, name);
      newPtr->nextPtr = NULL; // node does not link to another node
      newPtr->pPtr = NULL;
       
      previousPtr = NULL;
      currentPtr = *sPtr;

      // loop to find the correct location in the list
      while ( currentPtr != NULL && value > currentPtr->data ) {
         previousPtr = currentPtr; // walk to ...
         currentPtr = currentPtr->nextPtr; // ... next node
      } // end while

      // insert new node at beginning of list
      if ( previousPtr == NULL ) {
         newPtr->nextPtr = *sPtr;
         
         if(*sPtr != NULL){
         (*sPtr)->pPtr = newPtr;
         }
         *sPtr = newPtr;
         
        
      } // end if
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->pPtr =previousPtr;
         newPtr->nextPtr = currentPtr;
         if(currentPtr) currentPtr->pPtr = newPtr;
 
         
      } // end else
   } // end if
   else {
      printf( "%d %s not inserted. No memory available.\n", value, name );
   } // end else
} // end function insert

// delete a list element
int deletes( LLPtr *sPtr, int value )
{
   LLPtr previousPtr = NULL; // pointer to previous node in list
   LLPtr currentPtr = *sPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer

   // delete first node
   if (*sPtr != NULL && value == ( *sPtr )->data ) {
      tempPtr = *sPtr; // hold onto node being removed
      *sPtr = ( *sPtr )->nextPtr; // de-thread the node
      if (*sPtr != NULL) {
         (*sPtr)->pPtr = NULL; 
     }
     if (deletedCount < MAX_DELETED) {
      deletedValues[deletedCount++] = tempPtr->data; // Add deleted value
  }

      free( tempPtr ); // free the de-threaded node
      return value;
   } // end if
   
      previousPtr = *sPtr;
      currentPtr = ( *sPtr )->nextPtr;

      // loop to find the correct location in the list
      while ( currentPtr != NULL && currentPtr->data != value ) {
         previousPtr = currentPtr; // walk to ...
         currentPtr = currentPtr->nextPtr; // ... next node
      } // end while

      // delete node at currentPtr
      if ( currentPtr != NULL ) {
         tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
         if(currentPtr->nextPtr != NULL){
         currentPtr->nextPtr->pPtr=previousPtr;
         }
         if (deletedCount < MAX_DELETED) {
            deletedValues[deletedCount++] = tempPtr->data; // Add deleted value
        }
         free( tempPtr );
         return value;
      } // end if
   

   return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( LLPtr currentPtr )
{
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else {
      puts( "The list is:" );

      // while not the end of the list
      while ( currentPtr!= NULL ) {
         printf( "%d %s -->", currentPtr->data, currentPtr->name );
         currentPtr = currentPtr->nextPtr;
      } // end while

      printf( "NULL\n");
       

     
       
   } // end else
} // end function printList

void printListR(LLPtr currentPtr)
{
    if (currentPtr == NULL) {
        return;
    }
    

    printListR(currentPtr->nextPtr);
    printf("%d %s", currentPtr->data, currentPtr->name);
    if (currentPtr->pPtr != NULL) { 
      printf(" -->");
  } else {
      printf(" -->NULL\n");
  }

    
}


