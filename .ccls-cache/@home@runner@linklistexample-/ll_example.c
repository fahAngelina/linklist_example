// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>

// self-referential structure                       
struct Node {                                      
   //int ID; // each listNode contains a character 
   //char name[20];
   int data;
   struct Node *nextPtr; // pointer to next node
   struct Node *pPtr;
}; // end structure listNode                        

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*

// prototypes

int deletes( LLPtr *sPtr, int value );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int value );
void printList( LLPtr currentPtr );
void reverseList( LLPtr currrentPtr );
void instructions( void );

int main( void )
{ 
   LLPtr startPtr = NULL; // initially there are no nodes
   unsigned int choice; // user's choice
   int item; // char entered by user

   instructions(); // display the menu
   printf( "%s", "? " );
   scanf( "%u", &choice );

   // loop while user does not choose 3
   while ( choice != 3 ) { 

      switch ( choice ) { 
         case 1:
            printf( "%s", "Enter a number: " );
            scanf( "%d", &item );
            insert( &startPtr, item ); // insert item in list
            printList( startPtr );
            reverseList( startPtr );
            break;
         case 2: // delete an element
            // if list is not empty
            if ( !isEmpty( startPtr ) ) { 
               printf( "%s", "Enter number to be deleted: " );
               scanf( "%d", &item );

               // if character is found, remove it
               if ( deletes( &startPtr, item ) ) { // remove item
                  printf( "%d deleted.\n", item );
                  printList( startPtr );
                  reverseList( startPtr );
               } // end if
               else {
                  printf( "%d not found.\n\n", item );
               } // end else
            } // end if
            else {
               puts( "List is empty.\n" );
            } // end else

            break;
         default:
            puts( "Invalid choice.\n" );
            instructions();
            break;
      } // end switch

      printf( "%s", "? " );
      scanf( "%u", &choice );
   } // end while
  /* Clear all nodes at the end of nodes*/
   puts( "End of run." );
} // end main

// display program instructions to user
void instructions( void )
{ 
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert( LLPtr *sPtr, int value )//สร้างnodeใหม่ เกบค่า ละเชื่อม
{ 
   LLPtr newPtr; // pointer to new node
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list

   newPtr =(LLPtr) malloc( sizeof( LLnode ) ); // create node

   if ( newPtr != NULL ) { // is space available
      newPtr->data = value; // place value in node
      newPtr->nextPtr = NULL; // node does not link to another node
      newPtr->pPtr =NULL;//ชี้กลับ
       
      previousPtr = NULL;
      currentPtr = *sPtr;

      // loop to find the correct location in the list       
      while ( currentPtr != NULL && value > currentPtr->data ) {//หาตน ที่จะใส่
         previousPtr = currentPtr; // walk to ...               
         currentPtr = currentPtr->nextPtr; // ... next node 
      } // end while                                         

      // insert new node at beginning of list
      if ( previousPtr == NULL ) { 
         newPtr->nextPtr = *sPtr;
         if(currentPtr!=NULL)//ป้องกันแรกแรกสุด 
           currentPtr->pPtr = newPtr; 
         *sPtr = newPtr;
        
      } // end if
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->pPtr=previousPtr;
          
         newPtr->nextPtr = currentPtr;
         if(currentPtr!=NULL)//เอาไว้กันมันไหลไปNULL มีปห เวลาแทรกตัวสุดท้าย
           currentPtr->pPtr=newPtr;
    
      } // end else
   } // end if
   else {
      printf( "%d not inserted. No memory available.\n", value );
   } // end else
} // end function insert

// delete a list element
int deletes( LLPtr *sPtr, int value )
{ 
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer

   // delete first node
   if ( value == ( *sPtr )->data ) { //ชี้ที่ตัวแรกอยู่
      tempPtr = *sPtr; // hold onto node being removed
      *sPtr = ( *sPtr )->nextPtr; // de-thread the node
      if(*sPtr) //ป้องกันตอนลบหมดแล้ว
        (*sPtr)->pPtr=NULL;
      free( tempPtr ); // free the de-threaded node
      return value;
   } // end if
   else { 
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
         if(currentPtr->nextPtr!=NULL)
         {
           currentPtr=currentPtr->nextPtr;
           currentPtr->pPtr=previousPtr;
         }
        //currentPtr->nextPtr->pPtr=previousPtr;
         free( tempPtr );
         return value;
      } // end if
   } // end else

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
      while ( currentPtr->nextPtr!= NULL ) {
         printf( "%d --> ", currentPtr->data );
         currentPtr = currentPtr->nextPtr;   
      } // end while

      printf( "%d --> NULL\n",currentPtr->data );    
   } // end else
} // end function printList

void reverseList( LLPtr currentPtr )
{
  if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else { 
      puts( "The reverse list is:" );
      while ( currentPtr->nextPtr!= NULL )//วนลูปไปตัวสุดท้าย เชคเปนเนา
         currentPtr = currentPtr->nextPtr; 
     
      // while not the end of the list
      while ( currentPtr->pPtr!= NULL ) {
         printf( "%d --> ", currentPtr->data );
         currentPtr = currentPtr->pPtr;   
      } // end while

      printf( "%d --> NULL\n",currentPtr->data );    
   } // end else
}