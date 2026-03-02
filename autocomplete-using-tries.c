//TRIES using BST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// BST-style Trie Node
typedef struct tst_node {
char character; // The character stored in this node
struct tst_node *left; // Pointer to characters "smaller" than this one
struct tst_node *mid; // Pointer to the "equal" next character in word
struct tst_node *right; // Pointer to characters "larger" than this one
int is_end; // Flag: 1 if a word ends at this node
} tst_node_t;
// Function to create a new node
tst_node_t* create_node(char c) {
tst_node_t* node = (tst_node_t*)malloc(sizeof(tst_node_t));
if (node) {
node->character = c;
node->left = node->mid = node->right = NULL;
node->is_end = 0;
}
return node;
}
// Insert a word into the BST-style Trie
tst_node_t* insert(tst_node_t* root, char* word) {
if (root == NULL) {
root = create_node(*word);
}
if (*word < root->character) {
root->left = insert(root->left, word); // Comparison step
} else if (*word > root->character) {
root->right = insert(root->right, word); // Comparison step
} else {
if (*(word + 1)) {
root->mid = insert(root->mid, word + 1); // Equal character, move to next
} else {
root->is_end = 1; // Mark the end of the string
}
}
return root;
}
// Recursive helper to display all completions
void traverse_completions(tst_node_t* root, char* prefix, int depth) {
if (root == NULL) return;
traverse_completions(root->left, prefix, depth);
prefix[depth] = root->character;
if (root->is_end) {
prefix[depth + 1] = '\0';
printf(" -> %s\n", prefix);
}
traverse_completions(root->mid, prefix, depth + 1);
traverse_completions(root->right, prefix, depth);
}
// Find the prefix and start auto-complete
void autocomplete(tst_node_t* root, char* prefix) {
tst_node_t* curr = root;
int i = 0;
int len = strlen(prefix);
while (curr != NULL && i < len) {
if (prefix[i] < curr->character) {
curr = curr->left;
} else if (prefix[i] > curr->character) {
curr = curr->right;
} else {
if (i == len - 1) {
char buffer[100];
strcpy(buffer, prefix);
if (curr->is_end) printf(" -> %s\n", buffer);
traverse_completions(curr->mid, buffer, i + 1);
return;
}
curr = curr->mid;
i++;
}
}
printf("No suggestions found for '%s'.\n", prefix);
}
int main() {
tst_node_t* root = NULL;
int choice;
char buffer[100];
printf("--- BST-Trie (Ternary) Auto-Complete ---\n");
while (1) {
printf("\n1. Add Word\n2. Auto-complete Prefix\n3. Exit\nChoice: ");
if (scanf("%d", &choice) != 1) break;
if (choice == 1) {
printf("Enter word: ");
scanf("%s", buffer);
root = insert(root, buffer);
} else if (choice == 2) {
printf("Enter prefix: ");
scanf("%s", buffer);
printf("Suggestions:\n");
autocomplete(root, buffer);
} else {
break;
}
}
return 0;
}