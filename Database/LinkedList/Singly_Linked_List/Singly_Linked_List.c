#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE
{
	int data;
	struct _NODE *NextNode;
} NODE;

NODE *Head = NULL;

void Add_Node_At_Start(void)
{
	int data=0;
	printf("Enter the node value : ");
	scanf("%d", &data);
	
	NODE *NewHead = calloc(1, sizeof(NODE));
	NewHead->data = data;
	NewHead->NextNode = Head;

	Head = NewHead;
}

void Add_Node_At_End(void)
{
	int data=0;
	printf("Enter the node value : ");
	scanf("%d", &data);
	
	NODE *NewEnd = calloc(1, sizeof(NODE));
	NewEnd->data = data;
	NewEnd->NextNode = NULL;
	
	if(Head == NULL)
	{
		Head = NewEnd;
	}
	else
	{
		// Traverse to the last node
		NODE *CheckNode = Head;
		while(CheckNode->NextNode != NULL)
		{
			CheckNode = CheckNode->NextNode;
		}
		
		CheckNode->NextNode = NewEnd;
	}
}

void Add_Node_At_Position(void)
{
	int data=0, position=0, index=0;
	printf("Enter Position value : ");
	scanf("%d", &position);
	
	printf("Enter the node value : ");
	scanf("%d", &data);
	//getchar();
	
	NODE *NewEnd = calloc(1, sizeof(NODE));
	NewEnd->data = data;
	NewEnd->NextNode = NULL;

	// Traverse to the last node
	NODE *CheckNode = Head;
	NODE *PrevNode = CheckNode;
	
	if(position == 0) // Handle For First Request Separately
	{
		NewEnd->NextNode = Head;
		Head = NewEnd;
	}
	else
	{
		while((CheckNode != NULL) && (index < position-1)) // index starts from 0
		{
			PrevNode = CheckNode;
			CheckNode = CheckNode->NextNode;
			index++;
		}
		NewEnd->NextNode = PrevNode->NextNode;
		PrevNode->NextNode = NewEnd;
	}
}

void Add_Node_At_Sorted_Position(void)
{
	printf("NOT IMPLEMENTED ...\n");
}

void Remove_Node_From_Head(void)
{
	if(Head != NULL)
	{
		NODE *CheckNode = Head;
		Head = Head->NextNode;
		free(CheckNode);
		CheckNode = NULL;
	}
}

void Remove_Node_From_End(void)
{
	NODE *CheckNode = Head;
	NODE *PrevNode = CheckNode;
	
	// Special treatment for head
	if(CheckNode->NextNode == NULL)
	{
		free(CheckNode);
		CheckNode = NULL;
		Head = CheckNode;
	}
	else
	{
		while(CheckNode->NextNode)
		{
			PrevNode = CheckNode;
			CheckNode = CheckNode->NextNode;
		}
		printf("Address [%p]", PrevNode->NextNode);
		free(PrevNode->NextNode);
		PrevNode->NextNode = NULL;
	}
}

void Remove_Node_Of_Given_Data(void)
{
	int data = 0;
	printf("Enter the node value : ");
	scanf("%d", &data);

	NODE *CheckNode = Head;
	NODE *PrevNode = CheckNode;
	
	while(CheckNode)
	{
		if(CheckNode->data == data)
		{
			if(CheckNode == Head)
			{
				Head = Head->NextNode;
				free(CheckNode);
				CheckNode = Head;
				PrevNode = CheckNode;
			}
			else
			{
				PrevNode->NextNode = CheckNode->NextNode;
				free(CheckNode);
				CheckNode = PrevNode->NextNode;
			}
		}
		else
		{
			PrevNode = CheckNode;
			CheckNode = CheckNode->NextNode;
		}
	}	
}

void Remove_Node_Of_Position(void)
{
	int position = 0, index = 0;
	printf("Enter the node position to remove : ");
	scanf("%d", &position);
	
	NODE *CheckNode = Head;
	NODE *PrevNode = CheckNode;
	if(position > 0)
	{
		for(index=0; (index < position-1) && (CheckNode); index++)
		{
			PrevNode = CheckNode;
			CheckNode = CheckNode->NextNode;
		}
		printf("Data : %d at Index : %d\n", CheckNode->data, index);

		if(PrevNode != CheckNode)
		{
			PrevNode->NextNode = CheckNode->NextNode;
			free(CheckNode);
		}
		else
		{
			// Remove if position is 0
			Head = Head->NextNode;
			free(CheckNode);
		}		
	}
	else
	{
		printf("Invalid Position Provided\n");
	}
}

/*
 * We assign the temp node to the next of the current node and 
 * then reverse the link by assign the current->next to the previous node. 
 * And then increment the previous node to the current node and 
 * then the current node to the temp node.
 * And then we finally return the head node.
 
 * Time complexity: 
 * O(N) because we iterate through each element at least once. 

 * Space complexity: 
 * O(1) because no extra space was used here.
 
 */
void Reverse_The_Linked_List_Iterative(void)
{
	NODE *CurrentNode = Head;
	NODE *TempNode = NULL;
	NODE *PrevNode = NULL;
	
	while(CurrentNode != NULL)
	{
		TempNode = CurrentNode->NextNode;
		CurrentNode->NextNode = PrevNode;
		PrevNode = CurrentNode;
		CurrentNode = TempNode;
	}
	Head = PrevNode;
}

/*
 * The most important thing to remember in this approach is that the recursive approach uses a stack. 
 * The compiler allocates stack memory after each recursive call, and this solution can run out of memory 
 * in case of very huge linked lists (think billions of elements).
 *  
 * We recursively iterate to each node in the list until we reach the last node and return the new head. 
 * We have to note that the last node in this approach will become the new head of the list.
 * On the return path, each node is going to append itself to the end of the partially reversed linked list.
 
 * Time Complexity: 
 * O(N) because we iterate through each element at least once. 

 * Space complexity: 
 * O(N) because we create a recursive stack each time we call the reverse function recursively. 
 */
NODE * Reverse_The_Linked_List_Recursive(NODE * HeadNode)
{
	if((HeadNode == NULL) || (HeadNode->NextNode == NULL))
	{
		return HeadNode;
	}
	
	// Recursively Call
	NODE* Rest = Reverse_The_Linked_List_Recursive(HeadNode->NextNode);
	HeadNode->NextNode->NextNode = HeadNode;
	HeadNode->NextNode = NULL;
	
	return Rest;
}

/* Recursive function to reverse a given linked list. It reverses the
 * given linked list by fixing the head pointer and then `.next`
 * pointers of every node in reverse order
 * 
 * Usege : reverse (head, NULL, head);
 *
 */
void Reverse_The_Linked_List_Recursive_2(NODE* curr, NODE* prev, head* head)
{
    // base case: end of the list reached
    if (curr == NULL)
    {
        // fix head pointer
        head = prev;
        return;
    }
 
    // recur for the next node and pass the current node as a previous node
    reverse(curr->next, curr, head);
 
    // fix current node (nodes following it are already fixed)
    curr->next = prev;
}

void Swap_Two_Nodes(void)
{
	printf("NOT IMPLEMENTED ...\n");
}

void Sort_The_Linked_List(void)
{
	printf("NOT IMPLEMENTED ...\n");
}

void Delete_Linked_List(NODE *CurrentNode)
{
	if(CurrentNode != NULL)
	{
		if(CurrentNode -> NextNode != NULL)
		{
			Delete_Linked_List(CurrentNode->NextNode);  // Traverse Recursively and delete node from tail to head.
		}
		printf("Node Data : %d\n", CurrentNode->data);
		free(CurrentNode);
		CurrentNode = NULL;
	}
}

void Print_Linked_List(void)
{
	int index=1; // Position starts with number 1
	NODE *CurrentNode = Head;
	if(CurrentNode)
	{
		while(CurrentNode)
		{
			//printf("Address [%p]", CurrentNode);
			printf("[%d] Value : %d\n",index++, CurrentNode->data);
			CurrentNode=CurrentNode->NextNode;
		}
	}
	else
	{
		printf("Link List Is Empty...\n");
	}
}

void HandleRequest(void)
{
	int input;
	scanf("%d", &input);
	getchar();  // Consume new line character that can make mad to scanf
	
	switch(input)
	{		
		case 1: Add_Node_At_Start();
		break;

		case 2: Add_Node_At_End();
		break;

		case 3: Add_Node_At_Position();
		break;
		
		case 4: Add_Node_At_Sorted_Position();
		break;

		case 5: Remove_Node_From_Head();
		break;

		case 6: Remove_Node_From_End();
		break;
		
		case 7: Remove_Node_Of_Given_Data();
		break;

		case 8: Remove_Node_Of_Position();
		break;

		case 9: Sort_The_Linked_List();
		break;

		case 10: Head = Reverse_The_Linked_List_Recursive(Head);
		break;

		case 11: Print_Linked_List();
		break;

		case 12: Delete_Linked_List(Head); Head = NULL;
		break;
		
		case 13 : printf("\nBye... Bye... !!!\n"); exit(0);
		break;

		default: printf("INVALID INPUT !!!\n");fflush(stdin);
		break;
	}
}

void PrintMenu(void)
{
	printf("-------- Linked List Menu --------\n");
	printf("|[1] | Add Node At Start\n");
	printf("|[2] | Add Node At End\n");
	printf("|[3] | Add Node At Position\n");
	printf("|[4] | Add Node At Sorted Position\n");
	printf("|[5] | Remove Node From Head\n");
	printf("|[6] | Remove Node From End\n");
	printf("|[7] | Remove Nodes With of the Value\n");	
	printf("|[8] | Remove Node Of Position\n");
	printf("|[9] | Sort The Linked List\n");
	printf("|[10]| Reverse The Linked List\n");
	printf("|[11]| Print Linked List\n");
	printf("|[12]| Delete Linked List\n");
	printf("|[13]| Quit\n");
	printf("----------------------------------\n");
}

void main(void)
{
	while(1)
	{
		PrintMenu();
		HandleRequest();
	}
}