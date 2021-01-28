#include "stack.h"
#include <iostream>

using namespace std;

template <class Object>
  Stack<Object>::Stack( )
  {
              topOfStack = NULL;
  }

  template <class Object>bool Stack<Object>::isFull( ) const
        {
               return false;
        }
template <class Object>bool Stack<Object>::isEmpty( ) const//checking if the stack is empty
        {
              if(topOfStack == NULL)
			  {
				  return true;
			  }
			  return false;
        }
template <class Object>void Stack<Object>::pop( )//popping elements from the stack
  {
        if ( isEmpty()){
        cout << "Stack is empty!" << endl;
		}
		else{
			ListNode *oldTop = topOfStack;
			topOfStack = topOfStack->next;
			delete oldTop;
		}
  }
template <class Object>
const Object & Stack<Object>::top() const//getting the top stack element
{
	
	if (topOfStack != nullptr)
		return topOfStack->element;
	cout << "Stack is empty!" << endl;
}
template <class Object>void Stack<Object>::push( const Object & x )//psuhing the elements in the stack
        {
             topOfStack = new ListNode( x, topOfStack );
        }
template <class Object>Object Stack<Object>::topAndPop( )
        {
             Object topItem = top( );
             pop( );
             return topItem;
        }
template <class Object> void Stack<Object>::makeEmpty( )
 {
            while ( ! isEmpty( ) )
                 pop( );
}
template <class Object>const Stack<Object> & Stack<Object>::
        operator=( const Stack<Object> & rhs )
        {
              if ( this != &rhs )
              {
                   makeEmpty( );
                   if ( rhs.isEmpty( ) )
                        return *this;

                   ListNode *rptr = rhs.topOfStack;
                   ListNode *ptr  = new ListNode( rptr->element );
                   topOfStack = ptr;

                   for ( rptr = rptr->next; rptr != NULL; rptr = rptr->next )
                         ptr = ptr->next = new ListNode( rptr->element );
            }
            return *this;
        }
template <class Object>Stack<Object>::Stack( const Stack<Object> & rhs )//deep copy constructor
        {
               topOfStack = NULL;
               *this = rhs; // deep copy 
        }
        template <class Object>//destructor
        Stack<Object>::~Stack( )
        {
              makeEmpty( );
        }
