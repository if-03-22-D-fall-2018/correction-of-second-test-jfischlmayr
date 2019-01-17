/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: <your class>
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			dictionary.cpp
 * Author:			P. Bauer
 * Due Date:		November 25, 2012
 * ----------------------------------------------------------
 * Description:
 * Implementation of dictionary.h.
 * ----------------------------------------------------------
 */
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

struct NodeImplementation {
  const char* word;
  Node next;
};

struct DictionaryImplementation {
  int size;
  Node current;
  Node head;
  Node tail;
};

Dictionary new_dictionary() {
  Dictionary new_dictionary = (Dictionary)malloc(sizeof(DictionaryImplementation));
  new_dictionary->size = 0;
  new_dictionary->head = 0;
  new_dictionary->tail = 0;
  new_dictionary->current = 0;

  return new_dictionary;
}

void delete_dictionary (Dictionary dictionary) {
  if (dictionary->head == 0) {
    sfree(dictionary);
    return;
  }
  else if (dictionary->size == 1) {
    sfree(dictionary->head);
    sfree(dictionary);
    return;
  }
  Node toRemove = (Node)malloc(sizeof(NodeImplementation));
  while (dictionary->head != dictionary->tail) {
    toRemove = dictionary->head;
    dictionary->head = dictionary->head->next;
    sfree(toRemove);
  }
  sfree(dictionary->head);
  sfree(dictionary);
}

void add (Dictionary dict, const char *word) {
  if (!is_in_dict(dict, word)) {
    Node toAdd = (Node)malloc(sizeof(NodeImplementation));
    toAdd->word = word;
    toAdd->next = 0;
    if (dict->head == 0) {
      dict->head = toAdd;
    }
    else if (dict->tail == 0) {
      dict->tail = toAdd;
      dict->head->next = dict->tail;
    }
    else {
      dict->tail->next = toAdd;
      dict->tail = toAdd;
    }
    dict->size++;
  }
}

int get_size (Dictionary dict) {
  return dict->size;
}

bool is_in_dict (Dictionary dict, const char *word) {
  Node current = dict->head;
  while (current != 0) {
    if (current->word == word || strcasecmp(word, current->word) == 0) {
      return true;
    }
    current = current->next;
  }
  return false;
}

void start_iterating (Dictionary dict) {
  dict->current = dict->head;
}

bool has_next (Dictionary dict) {
  return dict->current != 0;
}

const char* get_next_entry (Dictionary dict) {
  if (has_next(dict)) {
    const char* string = dict->current->word;
    dict->current = dict->current->next;
    return string;
  }
  return 0;
}

void insert_sorted (Dictionary dict, const char *word) {
  if (!is_in_dict(dict, word)) {
    Node toAdd = (Node)malloc(sizeof(NodeImplementation));
    toAdd->word = word;
    toAdd->next = 0;
    if (dict->head != 0) {
      if (dict->tail == 0) {
        if (strcmp(word, dict->head->word) > 0) {
          dict->tail = toAdd;
          dict->head->next = dict->tail;
        }
        else {
          Node temp = dict->head;
          dict->head = toAdd;
          dict->tail = temp;
          dict->head->next = dict->tail;
        }
        dict->size++;
      }
      else if(strcasecmp(word, dict->head->word) < 0){
        toAdd->next = dict->head;
        dict->head = toAdd;
        dict->size++;
      }
      else {
        bool found = false;
        Node current = dict->head;
        while (current->next != 0 && !found) {
          if (strcmp(word, current->next->word) < 0) {
            toAdd->next = current->next;
            current->next = toAdd;
            dict->size++;
            found = true;
          }
          current = current->next;
        }
        if (current->next == 0) {
          dict->tail->next = toAdd;
          dict->tail = toAdd;
          dict->size++;
        }
      }
    }
    else {
      dict->head = toAdd;
      dict->size = 1;
    }
  }
}
